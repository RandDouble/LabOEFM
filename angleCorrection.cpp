#include <cmath>
#include <iostream>
#include <cstdlib>
#include <string>

/*DESCRIPTION
    author: Stefano Pilosio
    contact: stefano.pilosio@studenti.unimi.it
    Last modified: 3/11/2021
    Use Case:
        This program was written to be used during Laboratorio di ottica elettronica e fisica moderna
        its purpose is to calculate the angle to correct in the diffraction reticule so that it is perpendicular 
        to the laser, in this way we can see a beautiful diffraction pattern.
*/

using namespace std;

constexpr float CONV=M_PI/180.f;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

//CLASS AND STRUCT
class Angle{
    //The purpose of Angle is to store Angles datas in a easy way
    private:
        double m_rad;
    public:
        //CONSTRUCTOR
        Angle(){m_rad=0;}
        Angle(double degree, double prime){
             //in this use case you give the using degree and radians 
            m_rad=sgn(degree)*(abs(degree)+(prime/60.f))*CONV;
//            cout<<"\tvalore in ingresso degree : "<<sgn(degree)*(abs(degree)+prime)<<"\tvalore in rad : "<<m_rad<<endl;
            }
        Angle(double rad){
            m_rad=rad;
//            cout<<"\tvalore in degree : "<<m_rad/CONV<<"\tvalore in rad : "<<m_rad<<endl;
        }
        Angle(Angle& ang){
            m_rad=ang.m_rad;
//            cout<<"\tvalore in degree : "<<m_degree<<"\tvalore in rad : "<<m_rad<<endl;
        }
        Angle(Angle&& ang){
            m_rad=ang.m_rad;
            ang.m_rad=0;
//            cout<<"\tvalore in degree : "<<m_degree<<"\tvalore in rad : "<<m_rad<<endl;
        }
        //METHODS
        double getDeg() const{
//            cout<<"\ngetDegree() is : "<<sgn(m_rad)*floor(abs(m_rad/CONV))<<endl;
            return sgn(m_rad)*floor(abs(m_rad/CONV));}//return the angle degree part (MAX 359)
        double getPrime() const{ //return the angle prime part (MAX 59) 
            double udeg=abs(m_rad/CONV);
            double temp=udeg-floor(udeg);
            return temp*60.f;
        }
        string getAngle() const{ //return the angle in a format useful to be printed
            string angle=to_string(getDeg())+"° "+to_string(getPrime())+'\'';
            return angle;
        }
        double getRad() const {return m_rad;} //return the angle expressed in radians
        Angle operator-(const Angle sub){
            Angle res((*this));
//            cout<<"preSottrazione sub is :"<<sub.getAngle()<<"\t Radians : "<<sub.getRad()<<endl;
//            cout<<"preSottrazione res is :"<<res.getAngle()<<"\t Radians : "<<res.getRad()<<endl;
            res.m_rad=m_rad-sub.getRad();
//            cout<<"Sottrazione risultato : "<<res.getAngle()<<endl;
            return res;
        }
        void operator=(Angle& ang){
            m_rad=ang.m_rad;    
        }
        void operator=(Angle&& ang ){
            m_rad=ang.m_rad;
            ang.m_rad=0;
        }
        Angle operator+(const Angle sub){
            Angle res((*this));
            res.m_rad+=sub.getRad();
//            cout<<"Somma risultato : "<<res.getAngle()<<endl;
            return res;
        }
        Angle operator/(double num){
            Angle res((*this));
            res.m_rad/=num;
//            cout<<"Divisione risultato : "<<res.getAngle()<<endl;
            return res;            
        }
        Angle operator*(double num){
            Angle res((*this));
            res.m_rad*=num;
//            cout<<"Prodotto risultato : "<<res.getAngle()<<endl;
            return res;
        }
};

Angle Correction(Angle first, Angle second);
Angle PrecisionCorrection(Angle first, Angle second);

int main(int argc, char** argv){
    
    if (argc !=5){
        cerr<<"error, wrong number of elements\n"
        <<"Usage : ./angleCorrection <First Angle Degree><First Angle Prime> <Second Angle Degree><Second Angle Prime> \n";
        exit(-1);
    }
    //cout<<"CONV deg to rad Value: "<<CONV<<"\tDivision Value : "<<(M_PI/180.f)<<endl;
    //cout<<"CONV rad to deg Value: "<<(1.f/(CONV))<<"\tDivision Value : "<<(180.f/M_PI)<<endl;
    Angle first(atof(argv[1]),atof(argv[2]));
    Angle second(atof(argv[3]),atof(argv[4]));
    cout<<"acquired first angle : "<<first.getAngle()<<"\n"
        <<"acquired second angle : "<<second.getAngle()<<endl;
    Angle corrected=Correction(first, second);
    cout<<"Corrected Angle : "<<corrected.getAngle()<<endl;
    cout<<"Precision Correction Angle : "<<PrecisionCorrection(first, second).getAngle()<<endl;

    return 0;
}

//FUNCTION DEFINITION
Angle Correction(Angle first, Angle second){
    Angle alpha, theta;
    alpha=(second-first)/2.f;
    theta=(first+second)/2.f;
    Angle correct(alpha*(cos(theta.getRad())/(1-cos(theta.getRad()))));
    return correct;
}

Angle PrecisionCorrection(Angle first, Angle second){
    Angle alpha, theta;
    alpha=(second-first)/2.f;
    theta=(first+second)/2.f;
    double tanb=(sin(alpha.getRad())*cos(theta.getRad()))/(1-cos(theta.getRad()*cos(alpha.getRad())));
    double beta=atan(tanb);
    Angle Beta(beta);
    return Beta;
}