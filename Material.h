#include <iostream>

using namespace std;

class Material
{
    public:
        Material();
        Material(int, string);
        
        void setIdMaterial(int idm) {idMaterial = idm;};
        void setTitulo(string t) {titulo = t;};
        
        int getIdMaterial() {return idMaterial;};
        string titulo() {return titulo;};
        
        virtual void muestraDatos() = 0;
        virtual int cantidadDiasPrestamo() = 0;
        
    protected:
        int idMaterial;
        string titulo;
};

Material::Material()
{
    idMaterial = 0;
    titulo = "N/A";
}

Material::Material(int idMaterial, string titulo)
{
    this->idMaterial = idMaterial;
    this->titulo = titulo;
}
