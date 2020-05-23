#include <iostream>
#include "Fecha.h"

using namespace std;

class Reserva
{
    public:
        Reserva();
        Reserva(int, int, Fecha);
        
        void setIdMaterial(int im) {idMaterial = im;};
        void setIdCliente(int ic) {idCliente = ic;};
        void setFechaReservacion (Fecha fr) {fechaReservacion = fr;};
        
        int getIdMaterial() {return idMaterial;};
        int getIdCliente() {return idCliente;};
        Fecha getFechaReservacion() {return fechaReservacion;};
        
        Fecha calculaFechaFinReserva(int);
        
    private:
        int idMaterial;
        int idCliente;
        Fecha fechaReservacion;
};

Reserva::Reserva()
{
    idMaterial = 0;
    idCliente = 0;
    Fecha f(0,0,0);
    fechaReservacion = f;
}

Reserva::Reserva(int idMaterial, int idCliente, Fecha f1)
{
    this->idMaterial = idMaterial;
    this->idCliente = idCliente;
    fechaReservacion = f1;
}

Fecha Reserva::calculaFechaFinReserva(int dM)
{
    int A = fechaReservacion.getAa();
    int M = fechaReservacion.getMm();
    int D = fechaReservacion.getDd();
    a:
    D = D + dM;
    if((M==1||M==3||M==5||M==7||M==8||M==10) && D>31)
    {
        M++;
        dM = D - 31;
        D = 0;
        goto a;
    }
    else if(M==2 && D>28)
    {
        M++;
        dM = D - 28;
        D = 0;
        goto a;
    }
    else if((M==4||M==6||M==9||M==11) && D>30)
    {
        M++;
        dM = D - 30;
        D = 0;
        goto a;
    }
    else if(M==12 && D>31)
    {
        A++;
        M = 1;
        dM = D - 31;
        D = 0;
        goto a;
    }
    Fecha fR(D, M, A);
    return fR;
}
