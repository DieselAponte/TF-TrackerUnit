#include <iostream>
#include <unordered_map>
#include <string>

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

class Programa {
private:
    unordered_map<string, Usuario*> usuarios; // Hashtable de usuarios

public:
    Programa() {}

    void agregarUsuario(Usuario* usuario) {
        usuarios[usuario->getCorreo()] = usuario;
    }

    Usuario* recorreListaUsuarios(string correo) {
        auto it = usuarios.find(correo);
        if (it!= usuarios.end()) {
            return it->second;
        }
        return nullptr;
    }
};

void crearUsuario(Programa& programa);
bool inicio(Programa& programa);

int main(){
    Programa programa;
    bool registroInicio;
    do{
        registroInicio=inicio(programa);
    }while(registroInicio==false);
    cout<<" hOLA MUNDO";
}

bool inicio(Programa& programa){
    int respuesta;
    cout<<"Bienvenido Elija una opcion: 1 o 2: ";
    cin>>respuesta;
    if(respuesta==1){
        crearUsuario(programa);
        return false;
    }else{
        cout<<"\n Elija usuario ya existente";
        return true;
    }
}

void crearUsuario(Programa& programa){
    string nomUsuario,contrasena,correo;
    int edad;
    cout<<" CREA UNA NUEVA CUENTA: ";
    cout<<"\n Ingrese su nombre de Usuario:  ";
    cin>>nomUsuario;
    cout<<"\n Ingrese su correo:  ";
    cin>>correo;
    Usuario* usuario=programa.recorreListaUsuarios(correo);
    if(usuario==nullptr){
        cout<<"\n Elija una contrasena: "<<endl;
        cin>>contrasena;
        cout<<"\n Ingrese su edad: "<<endl;
        cin>>edad;
        Usuario* nuevo = new Usuario(nomUsuario,edad,correo,contrasena);
        programa.agregarUsuario(nuevo);
        cout<<"\n CREADO"<<endl;
    }else{
        cout<<"\n Ya existe un usuario vinculado con ese correo";
    }
}