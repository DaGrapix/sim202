#ifndef VECTEUR_HPP
#define VECTEUR_HPP

#include <iostream>
using namespace std;

//utilitaires
void stop(const char * msg);                     //message d'arr�t
void test_dim(int d1, int d2, const char * org); //test dimension

//classe vecteur de r�els double pr�cision
class vecteur
{
private :
  int dim_;          //dimension du vecteur
  double * val_;     //tableaux de valeurs

public:
  vecteur(int d=0, double v0=0); //dim et val constante
  vecteur(const vecteur & v);    //constructeur par copie
  ~vecteur();

  //tools
  void init(int d);        //allocation
  void clear();            //d�sallocation
  int dim() const {return dim_;}                //acc�s dimension

  //op�rateur d'assignation
  vecteur & operator=(const vecteur & v);  //assignation d'un vecteur
  vecteur & operator=(double x);           //assignation d'une valeur

  //op�rateurs d'acc�s (pour les utilisateurs)
  double  operator ()(int i) const {return val_[i-1];} //valeur    1->dim
  double& operator ()(int i) {return val_[i-1];}       //r�f�rence 1->dim

  //op�rateurs alg�briques
  vecteur& operator +=(const vecteur & v);             // u += v
  vecteur& operator -=(const vecteur & v);             // u -= v
  vecteur& operator +=(double x);                      // u += x
  vecteur& operator -=(double x);                      // u -= x
  vecteur& operator *=(double x);                      // u *= x
  vecteur& operator /=(double x);                      // u /= x

}; //fin de d�finition de la classe

//op�rateurs externes
vecteur operator +(const vecteur & u); //+ unaire ne fait rien !
vecteur operator -(const vecteur & u); //- unaire : chgt de signe
vecteur operator +(const vecteur & u,const vecteur & v); // u + v
vecteur operator -(const vecteur & u,const vecteur & v); // u - v
vecteur operator +(const vecteur & u,double x);          // u + x
vecteur operator +(double x, const vecteur & u);         // x + u
vecteur operator -(const vecteur & u,double x);          // u - x
vecteur operator -(double x, const vecteur & u);         // x - u
vecteur operator *(const vecteur & u,double x);          // u * x
vecteur operator /(const vecteur & u,double x);          // u / x
vecteur operator +(double x,const vecteur & u);          // x + u
vecteur operator -(double x,const vecteur & u);          // x - u
vecteur operator *(double x,const vecteur & u);          // x * u
double operator |(const vecteur & u,const vecteur & v);  // u | v
double norme(const vecteur & u);                         // sqrt(u|u)

//op�rateurs de comparaison
bool operator == (const vecteur & u,const vecteur & v);  // u == v
bool operator != (const vecteur & u,const vecteur & v);  // u != v

//op�rateurs de lecture et d'�criture
ostream & operator<<(ostream & os, const vecteur & u);   // os << u

#endif
