#include <iostream>

using namespace std;

class Disco
{
    public:
        Disco();
        Disco(int, string, int, string);
        
        void setDuracion(int d) {duracion = d;};
        void setGenero(string g) { genero = g;};
        
        int getDuracion() {return duracion;};
        string getGenero() {return genero;};
        
        //Métodos abstractos
        
    private:
        int duracion;
        string genero;
};

Disco::Disco() : Material()
{
    duracion = 0;
    genero = "N/A";
}

Disco::Disco(int idm, string t, int duracion, string genero) : Material(idm, t)
{
    this->duracion = duracion;
    this->genero = genero;
}

void Disco::muestraDatos()
{
    cout<<"Disco"<<idMaterial<<titulo<<duracion<<genero<<endl;
}

int Disco::cantidadDiasPrestamo()
{
    return 2;
}
