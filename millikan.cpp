#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <cfloat>
//librerie stronze ROOT
#include "TGraph.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TF1.h"
#include "TLegend.h"

using namespace std;

#define DIM 750 //definizione numero di punti usati

vector<double> Read(const char* filename);
void Print(vector<double> Data, const char* nameVett);
int ki(double Data, double q);
vector<double> Sq(vector<double> Data, vector<double> v, int nsteps);
vector<double> arrayq(double qmin, double qmax, int nsteps);
double searchMin(vector<double> Sq, vector<double> vettq);
double minimum(vector<double> Data, double search);
double singleSq(vector<double> Data, double q);
double error(double Sq, int n);

TApplication app("App",NULL,NULL);

int main(int argc, char**argv){
    
    char* filename=argv[1];//nome del file da cui recuperare i dati
    vector<double> Data=Read(filename);//caricamento dei dati nel vettore
    vector<double> vettq=arrayq(1.40e-19, 1.70e-19, DIM);
    vector<double> SQ(Sq(Data, vettq, DIM));
    Print(Data, "Data");
//    Print(vettq, "Vettq");
//    Print(SQ, "S(q)");
    double searchMini=searchMin(SQ, vettq);
    double min=minimum(Data, searchMini);
    double sqMinimum= singleSq(Data, min);
    double err=error(singleSq(Data, min), Data.size());
    cout<<"Valore di minimo della Funzione : "<<std::scientific<<min
        <<endl<<"Errore nel minimo : "<<err<<endl;

    //Iniziamo a ROOTare
    TCanvas c1("mygraph", "parabola", 1000, 500);
    c1.cd();
    //creazione vettori dinamici per ROOTto
    TGraph* graph= new TGraph();
    TF1* f1= new TF1("f1","[1]*(x-[0])^2+[2]", 1.55e-19, 1.65e-19);
    f1->SetParameter(2, sqMinimum);
    f1->SetParameter(0, min);
    for (int i=0; i<DIM; ++i ){
        graph->SetPoint(i, vettq[i], SQ[i]);
    }
    graph->Fit(f1);
    cout<<"Valore del Chi Quadro del Fit : "<<f1->GetChisquare()<<endl;
    cout<<"Valore di minimo della funzione Fittata : "<<f1->GetMinimumX(1.4e-19, 1.7e-19)<<endl;
    f1->Draw("ALP");
    graph->Draw();
    graph->SetTitle("Grafico S(q) con fit della parabola");
    graph->GetXaxis()->SetTitle("Q [C]");
    graph->GetYaxis()->SetTitle("S(Q) [C^2]");
    c1.SaveAs("parabola.png");
    app.Run();
    delete [] graph;
    delete [] f1;

    return 0;
}

vector<double> Read(const char* filename){
//Caricamento dei dati da file in un Vector di Double
    vector<double> Temp;
    ifstream in(filename);
    double appo;
    while(in>>appo) Temp.push_back(abs(appo));
    in.close();
    return Temp;
}

void Print(vector<double> Data, const char* nameVett){
    //stampa degli elementi del vettore
    cout<<"Dati Vettore : "<<nameVett<<endl;
    for(auto x : Data){
        cout<<setw(10)<<x<<endl;
    }
    cout<<"nr dei dati : "<<Data.size()<<endl;
}

int ki(double Data, double q){
    //cout<<"ki pre-floor, Qi : "<<Data<<"\tq : "<<q<<"\tValue ki : "<<((Data/q)+0.5)<<std::endl;
    //per debugging kix
    int kix=round((Data/q));
    return (kix<1)? 1 : kix;
}

vector<double> Sq(vector<double> Data, vector<double> q, int nsteps){
    
    vector<double> Sq;//vettore temporaneo per il calcolo di S(q)    
    double appo=0; //variabile di appoggio
    for(int i=0; i<nsteps; i++){
        //ciclo di caricamento iniziale dei S(q) 
        for(double x : Data){
            //cout<<"Valore ki : "<<ki(x,v[i])<<endl;
            appo+=pow((x/static_cast<double>(ki(x,q[i])))-q[i],2);
        }
        Sq.push_back(appo);
        appo=0;
    }
   
    return Sq;
}

double singleSq(vector<double> Data, double q){
    double appo=0; //variabile di appoggio
    //ciclo di caricamento iniziale dei S(q) 
    for(double x : Data){
        //cout<<"Valore ki : "<<ki(x,v[i])<<endl;
        appo+=pow((x/static_cast<double>(ki(x,q)))-q,2);
    }
    return appo;
}

vector<double> arrayq(double qmin, double qmax, int nsteps){
    vector<double> v(nsteps);
    double passo = (qmax-qmin)/nsteps;
    v[0]=qmin;
    for(int i=1; i<nsteps; i++){
        v[i]=v[i-1]+passo;
    }
    return v;
}

double searchMin(vector<double> Sq, vector<double> vettq){
    cout<<"starting preliminary search of a Minimum\n";
    int size=0;
    if (vettq.size()!=Sq.size()) exit(-5);
    else{ 
//        cout<<"changing size for for-loop\n";
        size=vettq.size();
        cout<<"new size is : "<<size<<endl;
    }
    double min=0, sqmin=DBL_MAX;
/*    cout<<"starting for-loop\n"
        <<"value min : "<<min
        <<"\nvalue sqmin : "<<sqmin<<endl;
*/    for (int i=0; i<size; i++){
//        cout<<"iteration : "<<i<<endl;
        if(sqmin>Sq[i]){
            sqmin=Sq[i];
            min=vettq[i];    
/*            cout<<"new value sqmin : "<<sqmin<<endl
                <<"new position minimum : "<<vettq[i]<<endl;
*/        }
    }
    cout<<"found possible minimum : "<<min<<endl;
    return min;
}

double minimum(vector<double> data, double search){
    double min=0;
    for (auto x : data){
        min += x/static_cast<double>(ki(x, search));
    }
    return min/data.size();
}

double error(double Sq, int n){
    double sigma=sqrt(Sq/static_cast<double>((n*(n-1))));
    return sigma;
}