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
    
    int idMatR, idCli; //Variables usadas para hacer una reservacion
    Fecha faRsv;       //Es necesario que sea scope global para usar en 2 ifs
    bool rsvNuev = false;
    
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
        for(int i=0; i<listmat; i++)
        {
            iM2 = materiales[i]->getIdMaterial();
            if(iDado==iM2)
            {
                noen3=0;
                for(int j=0; j<listres; j++)
                {
                    iR2 = reservaciones[j].getIdMaterial();
                    if(iDado==iR2)
                    {
                        finicio = reservaciones[j].getFechaReservacion();
                        dias2 = materiales[i]->cantidadDiasPrestamo();
                        ffin = reservaciones[j].calculaFechaFinReserva(dias2);
                        cout<<"Titulo: "<<materiales[i]->getTitulo()<<endl;
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
        int noen4, iR3, iM3, dias3, noen5=0;
        string nombMat1;
        Fecha fDada, finicio1, ffin1;
        cout<<"Ingresa la fecha "<<endl;
        cin>>fDada;
        for (int i=0; i<listres; i++)
        {   
            iR3 = reservaciones[i].getIdMaterial();
            finicio1 = reservaciones[i].getFechaReservacion();
            for(int j=0; j<listmat; j++)
            {
                iM3 = materiales[j]->getIdMaterial();
                if(iR3==iM3)
                {
                    dias3 = materiales[j]->cantidadDiasPrestamo();
                    nombMat1 = materiales[j]->getTitulo();
                }
            }
            ffin1 = reservaciones[i].calculaFechaFinReserva(dias3);
            if(fDada>=finicio1 && fDada<=ffin1)
            {
                cout<<nombMat1<<" "<<reservaciones[i].getIdCliente()<<endl;
            }
            else noen5++;
            if(noen5==listres)
            {
                cout<<"NO hay reservaciones en la fecha " << fDada<<endl;
                goto menu;
            }
            
        }
        goto menu;
    }
    
    else if(op=='E'||op=='e')
    {
        cout<<"Ingrese el Id del material a reservar: "; cin>> idMatR;
        int noen6=0, noen7;
        bool disp = false;
        for(int i=0; i<listmat; i++)
        {
            if(idMatR == materiales[i]->getIdMaterial())
            {
                cout<<"[Ingrese la fecha en que desea reservar]"<<endl;
                cin>>faRsv;
                noen7 = 0;
                for(int j=0; j<listres; j++)
                {
                    int dias4 = materiales[i]->cantidadDiasPrestamo();
                    Fecha fResI, fResF;
                    if(idMatR==reservaciones[j].getIdMaterial())
                    {
                        fResI = reservaciones[j].getFechaReservacion();
                        fResF = reservaciones[j].calculaFechaFinReserva(dias4);
                        if(faRsv<fResI || faRsv>fResF)
                            disp = true;
                        else{
                            cout<<"El Material no esta disponible en la fecha " <<faRsv<<endl;
                            goto menu;
                        }
                    }
                    else noen7++;
                    if(noen7==listres||disp)
                    {
                        cout<<"[Material disponible] Ingrese id Cliente: ";cin>>idCli;
                        cout<<"[Reservacion Hecha]"<<endl;
                        reservaciones[listres].setIdMaterial(idMatR);
                        reservaciones[listres].setIdCliente(idCli);
                        reservaciones[listres].setFechaReservacion(faRsv);
                        listres++;
                        rsvNuev = true; 
                        goto menu;
                    }
                }
            }
            else noen6++;
            if (noen6 ==listmat)
            {
                cout<<"No existe material con Id "<<idMat;
                goto menu;
            }
        }
        goto menu;
    }
    
    else if(op=='F'||op=='f'){
        if(rsvNuev)
        {
            int d, m, a, id1, id2;
            ofstream archS;
            archS.open("Reserva2.txt");
            for(int i=0; i<listres;i++)
            {
                d = reservaciones[i].getFechaReservacion().getDd();
                m = reservaciones[i].getFechaReservacion().getMm();
                a = reservaciones[i].getFechaReservacion().getAa();
                id1 = reservaciones[i].getIdMaterial();
                id2 = reservaciones[i].getIdCliente();
                archS<<d<<" "<<m<<" "<<a<<" "<<id1<<" "<<id2<<endl;
            }
            archS.close();
            cout<<"[Reservaciones Actualizadas]"<<endl;
        }
        return 0;
    }
    else {cout<<"Opcion Invalida"<<endl; goto menu;}


    return 0;
}
