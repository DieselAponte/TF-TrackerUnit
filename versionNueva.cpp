#include <iostream>
using namespace std;

class Usuario{
    private:
    string nombre;
    int edad;
    string contrasena;
    string correo;

    public:
    Usuario(string nombre,int edad,string correo, string contrasena);
    int getEdad();
    string getNombre();
    string getCorreo();
    string getContrasena();
};

Usuario::Usuario(string nombre,int edad,string correo, string contrasena){
    this->nombre=nombre;
    this->edad=edad;
    this->correo=correo;
    this->contrasena=contrasena;
}

int Usuario::getEdad(){
    return edad;
}
string Usuario::getNombre(){
    return nombre;
}

string Usuario::getCorreo(){
    return correo;
}
string Usuario::getContrasena(){
    return contrasena;
}

void crearUsuario();
Usuario* recorreListaUsuarios(string correo);
bool inicio();
int main(){
    bool registroInicio;
    //do{
        //registroInicio=inicio();
    //}while(registroInicio==false);
    cout<<" hOLA MUNDO";
}

bool inicio(){
    int respuesta;
    cout<<"Bienvenido Elija una opcion: 1 o 2";
    cin>>respuesta;
    if(respuesta==1){
        crearUsuario();
        return false;
    }else{
        cout<<"\n Elija usuario ya existente";
        return true;
    }
}

void crearUsuario(){
    string nomUsuario,contrasena,correo;
    int edad;
    cout<<" CREA UNA NUEVA CUENTA: ";
    cout<<"\n Ingrese su nombre de Usuario:  ";
    cin>>nomUsuario;
    cout<<"\n Ingrese su correo:  ";
    cin>>correo;
    Usuario* usuario=recorreListaUsuarios(correo);
    if(usuario==nullptr){
        cout<<"\n Elija una contrasena: "<<endl;
        cin>>contrasena;
        cout<<"\n Ingrese su edad: "<<endl;
        cin>>edad;
        Usuario nuevo(nomUsuario,edad,correo,contrasena);
        //agregar a hashtable o lista
        cout<<"\n CREADO";
    }else{
        cout<<"\n Ya existe un usuario vinculado con ese correo";
    }
}