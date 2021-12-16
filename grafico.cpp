#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
//Root Libraries
#include "TCanvas.h"
#include "TApplication.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TAxis.h"

using namespace std;

vector<double> Read(const char* filename);


int main(int argc, char** argv){
    TApplication app("app",NULL, NULL);

    char* filename=argv[1];
    double value=atof(argv[2]);
    vector<double> Data=Read(filename);
    cout<<"valore in entrata : "<<std::scientific<<setw(6)<<value<<endl;
    sort(Data.begin(), Data.end());
    for(unsigned int i=0; i<Data.size(); i++){
        Data[i]/=value;
    }

    TGraph* g = new TGraph();

    for(unsigned int i=0; i<Data.size(); i++){
        cout<<"Value of i : "<<i<<"\tValue of Data"<<Data[i]<<endl;
        g->SetPoint(i,i+1,Data[i]);
    }

    TCanvas* c1 = new TCanvas("c1","Grafico",720,480);
    g->Draw("A*");
    
    c1->SaveAs("grafico.png");
    
    app.Run();
    
    delete g;
    delete c1;
    
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