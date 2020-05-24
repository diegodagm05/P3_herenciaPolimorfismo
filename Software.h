#include <iostream>
#include "Material.h"

using namespace std;

class Software : public Material
{
    public:
        Software();
        Software(int, string, int, string);
        
        void setVersion(int v) {version = v;};
        void setSO(string s) {SO = s;};
        
        int getVersion() {return version;};
        string getSO() {return SO;};
        
        void muestraDatos();
        int cantidadDiasPrestamo();
        
    private:
        int version;
        string SO;
};

Software::Software() : Material()
{
    version = 0;
    SO = "N/A";
}

Software::Software(int idm, string t, int version, string SO) : Material(idm, t)
{
    this->version = version;
    this->SO = SO;
}

void Software::muestraDatos()
{
    cout<<"Software"<<idMaterial<<titulo<<version<<SO<<endl;
}

int Software::cantidadDiasPrestamo()
{
    return 1;
}
