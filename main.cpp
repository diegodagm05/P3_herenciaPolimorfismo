#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Reserva.h"
#include "Libro.h"
#include "Disco.h"
#include "Software.h"

using namespace std;

int main()
{   
    Material *materiales[30];
    Reserva reservaciones[60];
    
    ifstream archE;
    archE.open("Material.txt");
    
    int idM, dato1, listmat=0, listlib=0, listdis=0, listsoft=0; 
    string titulo, dato2;
    char tipo;
    Libro l[30];
    Disco d[30];
    Software s[30];
    
    while(archE>>idM>>titulo>>tipo>>dato1>>dato2)
    {
        if (tipo == 'L'){
            l[listlib].setIdMaterial(idM);
            l[listlib].setTitulo(titulo);
            l[listlib].setNumPag(dato1);
            l[listlib].setAutor(dato2);
            materiales[listmat] = &l[listlib];
            listlib++;
        }
        else if(tipo == 'D'){
            d[listdis].setIdMaterial(idM);
            d[listdis].setTitulo(titulo);
            d[listdis].setDuracion(dato1);
            d[listdis].setGenero(dato2);
            materiales[listmat] = &d[listdis];
            listdis++;
        }
        else if(tipo == 'S'){
            s[listsoft].setIdMaterial(idM);
            s[listsoft].setTitulo(titulo);
            s[listsoft].setVersion(dato1);
            s[listsoft].setSO(dato2);
            materiales[listmat] = &s[listsoft];
            listsoft++;
        }
        else cout << "Hay una clave de Material no reconocida en el archivo"<<endl;
        listmat++;
    }
    archE.close();
    
    
    archE.open("Reserva.txt");
    int di, me, an, idMat, idC, listres=0;
    while(archE>>di>>me>>an>>idMat>>idC)
    {
        Fecha fechaR;
        fechaR.setFecha(di, me, an);
        reservaciones[listres].setFechaReservacion(fechaR);
        reservaciones[listres].setIdMaterial(idMat);
        reservaciones[listres].setIdCliente(idC);
        listres++;
    }
    archE.close();
    menu:
    char op;
    cout<<" - - - - - - - - -[MENU]- - - - - - - - - "<<endl;
    cout<<"| a) Consultar lista de Materiales       |"<<endl;
    cout<<"| b) Consultar lista de reservaciones    |"<<endl;
    cout<<"| c) Consultar reservaciones de material |"<<endl;
    cout<<"| d) Consultar reservaciones de fecha    |"<<endl;
    cout<<"| e) Hacer una reservacion               |"<<endl;
    cout<<"| f) Terminar                            |"<<endl;
    cout<<" - - - - - - - - - - - - - - - - - - - -  "<<endl;
    cin>>op;
    
    if(op=='A'||op=='a'){
        cout<<endl<<"                [MATERIALES]"<<endl;
        for(int i=0; i<listmat; i++){
            materiales[i]->muestraDatos();
        }
        cout<<endl<<endl;
        goto menu;
    }
    
    else if(op=='B'||op=='b'){
        int iR, iM, dias, iC, noen1;
        string nombMat;
        Fecha inicioR, finR;
        
        cout<<"                          [RESERVACIONES]"<<endl;
        cout<<"[InicioReserva]\t"<<"[FinReserva]\t"<<"[NombreMaterial]\t"<<"\t[IdCliente]"<<endl;
        for (int i = 0; i<listres; i++) //Ciclo para impimir
        {   
            iR = reservaciones[i].getIdMaterial();
            noen1=0;
            for(int j = 0; j<listmat; j++) //Ciclo para buscar datos
            {   
                iM = materiales[j]->getIdMaterial();
                if(iR ==  iM)
                {
                    dias = materiales[j]->cantidadDiasPrestamo();
                    nombMat = materiales[j]->getTitulo();
                }
                else if(iR != iM)
                    noen1++;
            }
            if(noen1==listmat)
                cout<<"El id "<<iR<<" no está registrado en Materiales"<<endl;
            iC = reservaciones[i].getIdCliente();
            inicioR = reservaciones[i].getFechaReservacion();
            finR = reservaciones[i].calculaFechaFinReserva(dias);
            
            cout<<inicioR<<"\t"<<finR<<"\t"<<nombMat<<setw(40-nombMat.length())<<iC<<endl;
        }
        cout<<endl;
        goto menu;
    }
    
    else if(op=='C'||op=='c'){
        int iDado,iR2, iM2, dias2, noen2, noen3;
        Fecha finicio, ffin;
        
        cout<<"Ingrese el id del Material: "; cin>>iDado;
        noen2=0;
        for(int k=0; k<listmat; k++)
        {
            iM2 = materiales[k]->getIdMaterial();
            if(iDado==iM2)
            {
                noen3=0;
                for(int l=0; l<listres; l++)
                {
                    iR2 = reservaciones[l].getIdMaterial();
                    if(iDado==iR2)
                    {
                        finicio = reservaciones[l].getFechaReservacion();
                        dias2 = materiales[k]->cantidadDiasPrestamo();
                        ffin = reservaciones[l].calculaFechaFinReserva(dias2);
                        cout<<"Titulo: "<<materiales[k]->getTitulo()<<endl;
                        cout<<"Inicio Rsv: "<<finicio<<endl;
                        cout<<"Fin Rsv: "<<ffin<<endl;
                        goto menu;
                    }
                    else if(iDado!=iR2)
                        noen3++;
                    if (noen3==listres)
                    {
                        cout<<"El id "<< iDado<<" NO está reservado"<<endl;
                        goto menu;
                    }
                }
            }
            else if (iDado != iM2)
                noen2++;
            if (noen2==listmat)
            {
                cout<<"El id "<<iDado<< " NO se encuentra en materiales"<<endl;
                goto menu;
            }
        }
        goto menu;
    }
    
    else if(op=='D'||op=='d')
    {
        
        goto menu;
    }
    
    else if(op=='E'||op=='e'){
        
        goto menu;
    }
    
    else if(op=='F'||op=='f')
        return 0;
    else {cout<<"Opcion Invalida"<<endl; goto menu;}


    return 0;
}
