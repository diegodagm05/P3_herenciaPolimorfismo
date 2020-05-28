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
    
    int listres=0, listmat=0, listlib=0, listdis=0, listsoft=0; //Contadores de arreglos
    
    int idMat, idMatR, idC, dato1, di, me, an, dias, cont, cont1; //Variables de los objetos
    string titulo, dato2;
    bool rsvNuev = false; //variable para crear reservas nuevas
    
    Fecha fIniR, fFinR, faRsv;
    
    char tipo;
    Libro l[30];
    Disco d[30];
    Software s[30];
    
    while(archE>>idMat>>titulo>>tipo>>dato1>>dato2)
    {
        if (tipo == 'L'){
            l[listlib].setIdMaterial(idMat);
            l[listlib].setTitulo(titulo);
            l[listlib].setNumPag(dato1);
            l[listlib].setAutor(dato2);
            materiales[listmat] = &l[listlib];
            listlib++;
        }
        else if(tipo == 'D'){
            d[listdis].setIdMaterial(idMat);
            d[listdis].setTitulo(titulo);
            d[listdis].setDuracion(dato1);
            d[listdis].setGenero(dato2);
            materiales[listmat] = &d[listdis];
            listdis++;
        }
        else if(tipo == 'S'){
            s[listsoft].setIdMaterial(idMat);
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
    while(archE>>di>>me>>an>>idMatR>>idC)
    {
        Fecha fechaR;
        fechaR.setFecha(di, me, an);
        reservaciones[listres].setFechaReservacion(fechaR);
        reservaciones[listres].setIdMaterial(idMatR);
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
        cout<<"                          [RESERVACIONES]"<<endl;
        cout<<"[InicioReserva]\t"<<"[FinReserva]\t"<<"[NombreMaterial]\t"<<"\t[IdCliente]"<<endl;
        for (int i = 0; i<listres; i++) //Ciclo para impimir
        {   
            idMatR = reservaciones[i].getIdMaterial();
            cont=0;
            for(int j = 0; j<listmat; j++) //Ciclo para buscar datos
            {   
                idMat = materiales[j]->getIdMaterial();
                if(idMatR ==  idMat)
                {
                    dias = materiales[j]->cantidadDiasPrestamo();
                    titulo = materiales[j]->getTitulo();
                }
                else if(idMatR != idMat)
                    cont++;
            }
            if(cont==listmat)
                cout<<"El id "<<idMatR<<" no está registrado en Materiales"<<endl;
            idC = reservaciones[i].getIdCliente();
            fIniR = reservaciones[i].getFechaReservacion();
            fFinR = reservaciones[i].calculaFechaFinReserva(dias);
            
            cout<<fIniR<<"\t"<<fFinR<<"\t"<<titulo<<setw(40-titulo.length())<<idC<<endl;
        }
        cout<<endl;
        goto menu;
    }
    
    else if(op=='C'||op=='c'){
        int idDado;
        cout<<"Ingrese el id del Material: "; cin>>idDado;
        cont=0;
        for(int i=0; i<listmat; i++)
        {
            idMat = materiales[i]->getIdMaterial();
            if(idDado==idMat)
            {
                cont1=0;
                for(int j=0; j<listres; j++)
                {
                    idMatR = reservaciones[j].getIdMaterial();
                    if(idDado==idMatR)
                    {
                        fIniR = reservaciones[j].getFechaReservacion();
                        dias = materiales[i]->cantidadDiasPrestamo();
                        fFinR = reservaciones[j].calculaFechaFinReserva(dias);
                        cout<<"Titulo: "<<materiales[i]->getTitulo()<<endl;
                        cout<<"Inicio Rsv: "<<fIniR<<endl;
                        cout<<"Fin Rsv: "<<fFinR<<endl;
                        cout<<endl;
                        //goto menu;
                    }
                    else if(idDado!=idMatR)
                        cont1++;
                    if (cont1==listres)
                    {
                        cout<<"El id "<< idDado<<" NO está reservado"<<endl;
                        goto menu;
                    }
                }
            }
            else if (idDado != idMat)
                cont++;
            if (cont==listmat)
            {
                cout<<"El id "<<idDado<< " NO se encuentra en materiales"<<endl;
                goto menu;
            }
        }
        goto menu;
    }
    
    else if(op=='D'||op=='d')
    {
        fechaN:
        Fecha fDada;
        cont=0;
        cout<<"Ingresa la fecha "<<endl;
        cin>>fDada;
        if(!fDada.validarFecha()){
            goto fechaN;
        }
        for (int i=0; i<listres; i++)
        {   
            idMatR = reservaciones[i].getIdMaterial();
            fIniR = reservaciones[i].getFechaReservacion();
            for(int j=0; j<listmat; j++)
            {
                idMat = materiales[j]->getIdMaterial();
                if(idMatR==idMat)
                {
                    dias = materiales[j]->cantidadDiasPrestamo();
                    titulo = materiales[j]->getTitulo();
                }
            }
            fFinR = reservaciones[i].calculaFechaFinReserva(dias);
            if(fDada>=fIniR && fDada<=fFinR)
            {
                cout<<titulo<<" "<<reservaciones[i].getIdCliente()<<endl;
            }
            else cont++;
            if(cont==listres)
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
        cont=0;
        bool disp = false;
        for(int i=0; i<listmat; i++)
        {
            if(idMatR == materiales[i]->getIdMaterial())
            {
                fecha:
                cout<<"[Ingrese la fecha en que desea reservar]"<<endl;
                cin>>faRsv;
                if(!faRsv.validarFecha()){
                    goto fecha;
                }
                cont1 = 0;
                for(int j=0; j<listres; j++)
                {
                    dias = materiales[i]->cantidadDiasPrestamo();
                    if(idMatR==reservaciones[j].getIdMaterial())
                    {
                        fIniR = reservaciones[j].getFechaReservacion();
                        fFinR = reservaciones[j].calculaFechaFinReserva(dias);
                        Fecha faRsvF = faRsv;
                        faRsvF = faRsvF+dias;
                        if(faRsvF<fIniR || faRsv>fFinR)
                            disp = true;
                        else{
                            cout<<"El Material no esta disponible en la fecha " <<faRsv<<endl;
                            goto menu;
                        }
                    }
                    else cont1++; //Para saber si el material esta previamente reservado
                    if((cont1==listres||disp)&&listres<60)
                    {   idcliente:
                        cout<<"[Material disponible] Ingrese id Cliente: ";cin>>idC;
                        if(idC<0||idC>99999){
                            cout<<"[ERROR] El id del cliente no esta en el rango"<<endl;
                            goto idcliente;
                        }
                        cout<<"[Reservacion Hecha]"<<endl;
                        reservaciones[listres].setIdMaterial(idMatR);
                        reservaciones[listres].setIdCliente(idC);
                        reservaciones[listres].setFechaReservacion(faRsv);
                        listres++;
                        rsvNuev = true; 
                        goto menu;
                    }
                    else if(idC>=60){
                        cout<<"[ERROR] ya hay 60 reservaciones hechas"<<endl;
                        goto menu;
                    }
                }
            }
            else cont++;
            if (cont ==listmat)
            {
                cout<<"No existe material con Id "<<idMatR<<endl;
                goto menu;
            }
        }
        goto menu;
    }
    
    else if(op=='F'||op=='f'){
        if(rsvNuev)//Solo entra cuando se hizo una reserva nueva
        {
            ofstream archS;
            archS.open("Reserva.txt");
            for(int i=0; i<listres;i++)
            {
                di = reservaciones[i].getFechaReservacion().getDd();
                me = reservaciones[i].getFechaReservacion().getMm();
                an = reservaciones[i].getFechaReservacion().getAa();
                idMatR = reservaciones[i].getIdMaterial();
                idC = reservaciones[i].getIdCliente();
                archS<<di<<" "<<me<<" "<<an<<" "<<idMatR<<" "<<idC<<endl;
            }
            archS.close();
            cout<<"[Reservaciones Actualizadas]"<<endl;
        }
        return 0;
    }
    else {cout<<"Opcion Invalida"<<endl; goto menu;}
    
    return 0;
}
