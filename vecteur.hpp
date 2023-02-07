#ifndef VECTEUR_HPP
#define VECTEUR_HPP

#include <iostream>
#include <vector>

using namespace std;

inline void stop(const string& mes)
{
    cout<<mes<<endl;
    exit(-1);
}

// ==========================================================
// class Vecteur<T> heritant de la classe vector<T> de la STL
// ==========================================================
template <typename T>
class Vecteur:public vector<T>
{
  public:
    Vecteur(int d=0, const T& x=T())
     {if(d>0) this->assign(d,x);}
    void print(ostream& out) const
    {
        int d=this->size();
        out<<"(";
        for(int i=0;i<d-1;i++) out<<this->at(i)<<",";
        out<<this->at(d-1)<<")";
    }
    const T& operator()(int i) const {return vector<T>::at(i-1);}
    T& operator()(int i) {return vector<T>::at(i-1);}

    Vecteur<T>& operator+=(const Vecteur<T>& v)
    {
        if(v.size()!=this->size()) stop("dimensions incompatible dans u+=v");
        auto itv=v.begin();
        for(auto it=this->begin();it!=this->end();++it, ++itv) *it+=*itv;
        return *this;
    }
    Vecteur<T>& operator-=(const Vecteur<T>& v)
    {
        if(v.size()!=this->size()) stop("dimensions incompatible dans u-=v");
        auto itv=v.begin();
        for(auto it=this->begin();it!=this->end();++it, ++itv) *it-=*itv;
        return *this;
    }
    Vecteur<T>& operator*=(const T& a)
    {
        for(auto it=this->begin();it!=this->end();++it) *it*=a;
        return *this;
    }
    Vecteur<T>& operator/=(const T& a)
    {
         if(a==0) stop("division par zero dans u/=a");
         for(auto it=this->begin();it!=this->end();++it) *it/=a;
         return *this;
    }
};

template <typename T>
ostream& operator<<(ostream& out, const Vecteur<T>& u)
{
    u.print(out);
    return out;
}
// operations algebriques
template <typename T>
Vecteur<T> operator-(const Vecteur<T>& u)
{
    Vecteur<T> w=u;
    return w*=-1;
}
template <typename T>
Vecteur<T> operator+(const Vecteur<T>& u, const Vecteur<T>& v)
{
    Vecteur<T> w=u;
    return w+=v;
}
template <typename T>
Vecteur<T> operator-(const Vecteur<T>& u, const Vecteur<T>& v)
{
    Vecteur<T> w=u;
    return w-=v;
}
template <typename T>
Vecteur<T> operator*(const Vecteur<T>& u, const T& a)
{
    Vecteur<T> w=u;
    return w*=a;
}
template <typename T>
Vecteur<T> operator*(const T& a,const Vecteur<T>& u)
{
    Vecteur<T> w=u;
    return w*=a;
}
template <typename T>
Vecteur<T> operator/(const Vecteur<T>& u, const T& a)
{
    Vecteur<T> w=u;
    return w/=a;
}
// produit scalaire
template <typename T>
T operator|(const Vecteur<T>& u, const Vecteur<T>& v)
{
    if(u.size()!=v.size()) stop("dimensions incompatible dans u|v");
    T ps=T();
    auto itv=v.begin();
    for(auto it=u.begin();it!=u.end();++it,++itv) ps+=(*it)*(*itv);
    return ps;
}
#endif