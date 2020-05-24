#include <iostream>

using namespace std;

class Fecha
{
    public:
        Fecha();
        Fecha(int, int, int);
        
        int getDd(){return dd;};
        int getMm(){return mm;};
        int getAa(){return aa;};
        
        int setFecha(int d, int m, int a) {dd=d; mm=m; aa=a;};
        
        bool operator>(Fecha);
        bool operator>=(Fecha);
        bool operator<(Fecha);
        bool operator<=(Fecha);
        bool operator==(Fecha);
        Fecha operator+(int);
        friend ostream &operator <<(ostream &o, Fecha f);
        friend istream &operator >>(istream &i, Fecha &f);
        
        
    private:
       int dd;
       int mm;
       int aa;
};

Fecha::Fecha()
{
    dd = 0;
    mm = 0;
    aa = 0;
}

Fecha::Fecha(int dd, int mm, int aa)
{
    this->dd = dd;
    this->mm = mm;
    this->aa = aa;
}

bool Fecha::operator>(Fecha f1)
{
    if(aa>f1.getAa())
        return true;
    else if(aa==f1.getAa())
    {
        if(mm>f1.getMm())
            return true;
        else if (mm==f1.getMm())
        {
            if(dd>f1.getDd())
                return true;
            else return false;
        }
        else return false;
    }
    else return false;
}

bool Fecha::operator>=(Fecha f1)
{
    if(aa>f1.getAa())
        return true;
    else if(aa==f1.getAa())
    {
        if(mm>f1.getMm())
            return true;
        else if (mm==f1.getMm())
        {
            if(dd>=f1.getDd())
                return true;
            else return false;
        }
        else return false;
    }
    else return false;
}

bool Fecha::operator<(Fecha f1)
{
    if(aa<f1.getAa())
        return true;
    else if(aa==f1.getAa())
    {
        if(mm<f1.getMm())
            return true;
        else if (mm==f1.getMm())
        {
            if(dd<f1.getDd())
                return true;
            else return false;
        }
        else return false;
    }
    else return false;
}    

bool Fecha::operator<=(Fecha f1) 
{
    if(aa<f1.getAa())
        return true;
    else if(aa==f1.getAa())
    {
        if(mm<f1.getMm())
            return true;
        else if (mm==f1.getMm())
        {
            if(dd<=f1.getDd())
                return true;
            else return false;
        }
        else return false;
    }
    else return false;    
}

bool Fecha::operator==(Fecha f1)
{
    if(aa==f1.getAa() && mm==f1.getMm() && dd==f1.getDd())
        return true;
    else return false;
}

Fecha Fecha::operator+(int dias)
{   a:
    dd = dd + dias;
    if((mm==1||mm==3||mm==5||mm==7||mm==8||mm==10)&&dd>31)
    {
        mm++;
        dias = dd - 31;
        dd = 0;
        goto a;
    }
    else if(mm==2 && dd>28)
    {
        mm++;
        dias = dd - 28;
        dd = 0;
        goto a;
    }
    else if((mm==4||mm==6||mm==9||mm==11)&&dd>30)
    {
        mm++;
        dias = dd - 30;
        dd = 0;
        goto a;
    }
    else if(mm==12&&dd>31)
    {
        aa++;
        mm = 1;
        dias = dd - 31;
        dd = 0;
        goto a;
    }
    Fecha fn(dd, mm, aa);
    return fn;
}

ostream &operator <<(ostream &o, Fecha f)
{
    string mes;
    if (f.mm==1)
        mes = "ENE";
    else if (f.mm==2)
        mes = "FEB";
    else if (f.mm==3)
        mes = "MAR";
    else if (f.mm==4)
        mes = "ABR";  
    else if (f.mm==5)
        mes = "MAY";
    else if (f.mm==6)
        mes = "JUN";
    else if (f.mm==7)
        mes = "JUL";
    else if (f.mm==8)
        mes = "AGO";
    else if (f.mm==9)
        mes = "SEP";
    else if (f.mm==10)
        mes = "OCT";
    else if (f.mm==11)
        mes = "NOV";
    else if (f.mm==12)
        mes = "DIC";
        
    o<<f.dd<<"/"<<mes<<"/"<<f.aa;
    return o;
}

istream &operator >>(istream &i, Fecha &f)
{
    cout<<"Dia: ";
    i >> f.dd;
    cout<<"Mes: ";
    i >> f.mm;
    cout<<"Anio: ";
    i >> f.aa;
    return i;
}


