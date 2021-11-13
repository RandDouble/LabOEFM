#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>
//librerie stronze ROOT
#include "TGraph.h"
#include "TApplication.h"
#include "TCanvas.h"

using namespace std;

#define DIM 100 //definizione numero di punti usati

vector<double> Read(const char* filename);
void Print(vector<double> Data, const char* nameVett);
int ki(double Data, double q);
vector<double> Sq(vector<double> Data, vector<double> v, int nsteps);
vector<double> arrayq(double qmin, double qmax, int nsteps);

TApplication app("App",NULL,NULL);

int main(int argc, char**argv){
    
    char* filename=argv[1];//nome del file da cui recuperare i dati
    vector<double> Data=Read(filename);//caricamento dei dati nel vettore
    vector<double> vettq=arrayq(1.55, 1.70, DIM);
    vector<double> SQ(Sq(Data, vettq, DIM));
    Print(Data, "Data");
    Print(vettq, "Vettq");
    Print(SQ, "S(q)");
   
    //Iniziamo a ROOTare
//    TCanvas *c1= new TCanvas("mygraph");
    //creazione vettori dinamici per ROOTto
    TGraph* graph= new TGraph();
    for (int i=0; i<DIM; ++i ){
        graph->SetPoint(i, vettq[i], SQ[i]);
    }
    graph->Draw("AL*");
    
    app.Run();


    return 0;
}

vector<double> Read(const char* filename){
//Caricamento dei dati da file in un Vector di Double
    vector<double> Temp;
    ifstream in(filename);
    double appo;
    while(in>>appo) Temp.push_back(appo);
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
            appo+=pow((x/ki(x,q[i]))-q[i],2);
        }
        Sq.push_back(appo);
        appo=0;
    }
   
    return Sq;
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