#include <iostream>
#include <unordered_map>
#include <string>
//FALTA AGREGAR LOS RESTRINGIR DATOS 
//FALTA AGREGAR LA CLASE TAREAS
//FALTA OPERACIONES DE CONFIGURACION DE USUARIO
// HABRÁ VERIFICACION DE CORREO (es decir que tenga si o si @)? 

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

void abrirApp(Programa& programa);
void menu(Programa& programa, bool& salirApp,Usuario*& actual);
void crearUsuario(Programa& programa);
bool inicio(Programa& programa);
Usuario* logging(Programa& programa);

int main(){
    Programa programa;
    abrirApp(programa);
}   

void abrirApp(Programa& programa){
    bool salircuenta=false,salirApp=false;
    bool registroInicio;
    int respuestaSalida;
    Usuario* actual=nullptr;
    do{
        do{
        registroInicio=inicio(programa);
        }while(registroInicio==false);
        actual=logging(programa);
        if(actual!=nullptr){
            cout<<"\n Bienvenido de nuevo "<<actual->getNombre()<<"!!!"<<endl;
            do{
                menu(programa,salircuenta,actual);
            }while(salircuenta==false);
            cout<<"\n DESEA SALIR DE LA APP??"<<endl;
            cout<<" 1. SI"<<endl;
            cout<<" 2. NO"  <<endl;
            cin>>respuestaSalida;
        }
        
        if(respuestaSalida==1){
            salirApp=true;
        }
    }while(salirApp==false);
}
    
void menu(Programa& programa, bool& salircuenta, Usuario*& actual ){
    int opcion;
    string menu= "\n///////Menú://////\n"
                 "1. Ver tareas pendientes\n"
                 "2. Ver usuario\n"
                 "3. Salir\n"
                 "Seleccione una opcion: ";
    cout<<menu;
    cin>>opcion;
    switch (opcion){
        case 1: 
            // Implementar ver tareas pendientes
            cout<<"h ola";
            break;
        case 2: 
            cout<<"\n Nombre de usuario: "<<actual->getNombre()<<endl;
            cout<<"\n Correo: "<<actual->getCorreo()<<endl;
            cout<<"\n edad: "<<actual->getEdad()<<endl;
            break;
        case 3: 
            salircuenta=true;
            break;
        default:
            cout << "Opcion inválida. Inténtelo de nuevo.\n";
            break;
    }
    if (salircuenta) {
    return;
    }
}



bool inicio(Programa& programa){
    int respuesta;
    cout<<"Bienvenido elija una opcion: 1 (CREAR USUARIO) o 2 (ACCEDER A USUARIO): ";
    cin>>respuesta;
    if(respuesta==1){
        crearUsuario(programa);
        return false;
    }else{
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
        cout<<"\n Ya existe un usuario vinculado con ese correo"<<endl;
    }
}

Usuario* logging(Programa& programa){
    string correo, contrasena;
    cout<<"\n Ingrese su correo:  ";
    cin>>correo;
    Usuario* usuario=programa.recorreListaUsuarios(correo);
    if(usuario==nullptr){
        cout<<"\n No existe ninguna cuenta ligada al correo proporcionado"<<endl;
        return nullptr;
    }else{
        cout<<"\n Ingrese su contrasena: "<<endl;
        cin>>contrasena;
        if(usuario->getContrasena()==contrasena){
            cout<<"\n Sesion iniciada \n";
            return usuario;
        }else{
            cout<<"\n Contraseña incorrecta \n"<<endl;
            return nullptr;
        }
    }
}