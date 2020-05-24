#include <iostream>
#include "Material.h"

using namespace std;

class Libro : public Material
{
    public:
        Libro();
        Libro(int, string, int, string);
        
        void setNumPag(int np) {numPag = np;};
        void setAutor(string a) { autor = a;};
        
        int getNumPag() {return numPag;};
        string getAutor() {return autor;};
        
        void muestraDatos();
        int cantidadDiasPrestamo();
        
    private:
        int numPag;
        string autor;
};

Libro::Libro() : Material()
{
    numPag = 0;
    autor = "N/A";
}

Libro::Libro(int idm, string t, int numPag, string autor) : Material(idm, t)
{
    this->numPag = numPag;
    this->autor = autor;
}
void Libro::muestraDatos()
{
    cout<<"Libro"<<idMaterial<<titulo<<numPag<<autor<<endl;
}

int Libro::cantidadDiasPrestamo()
{
    return 7;
}



