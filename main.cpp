#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>
#include <string>

using namespace std;


//Clase Usuario
class Usuario{
private: //Atributos
    string nombre;
    int edad;
    string contrasena;
    string correo;

public://Constructor y metodos
    Usuario(string nombre,int edad,string correo, string contrasena);
    int getEdad();
    string getNombre();
    string getCorreo();
    string getContrasena();

};
//Inicializando un usuario
Usuario::Usuario(string nombre,int edad,string correo, string contrasena){
    this->nombre=nombre;
    this->edad=edad;
    this->correo=correo;
    this->contrasena=contrasena;
}
//Getters
int Usuario::getEdad(){
    return edad; //Devolver edad
}
string Usuario::getNombre(){
    return nombre; //Devolver nombre
}

string Usuario::getCorreo(){
    return correo; //Devolver correo electronico
}

string Usuario::getContrasena(){
    return contrasena; //Devolver contraseña
}

//Clase Tarea
class Tarea {
private://Atributos
    string descripcion;

public: //Constructor - Metodo getDescription
    Tarea(const string& desc) : descripcion(desc) {}

    string getDescripcion() const {
        return descripcion; //Devolver descripcion de la tarea
    }
};

// Nodo que contiene el correo y la lista de tareas
struct HashNode {
    string correo; //Variable correo para verificar la pertenencia de la tarea
    list<Tarea> tareas; //Lista de <Tareas> llamada tareas
};

// Clase HashTable para gestionar la tabla hash
class HashTable {
private:
    vector<list<HashNode>> table; // La tabla hash
    int size;

    // Función de hash simple basada en la suma de los caracteres de la clave
    int hashFunction(const string& correo) const {
        int hashValue = 0;
        for (char c : correo) {
            hashValue += c;
        }
        return hashValue % size; // Calcular el índice en la tabla hash
    }

public:
    // Constructor para inicializar la tabla con un tamaño específico
    HashTable(int tableSize) : size(tableSize) {
        table.resize(tableSize); // Redimensionar la tabla hash
    }

    // Función para agregar una tarea a la tabla hash
    void agregarTarea(const string& correo, const Tarea& tarea) {
        int hashIndex = hashFunction(correo); // Obtener el índice de la tabla hash

        // Buscar si el correo ya existe en la tabla
        for (auto& node : table[hashIndex]) {
            if (node.correo == correo) {
                node.tareas.push_back(tarea); // Agregar tarea si ya existe el correo
                return;
            }
        }

        // Si no existe, agregar un nuevo nodo
        HashNode newNode;
        newNode.correo = correo;
        newNode.tareas.push_back(tarea);
        table[hashIndex].push_back(newNode); // Insertar nuevo nodo en la tabla hash
    }

    // Función para obtener las tareas de un usuario
    list<Tarea> obtenerTareas(const string& correo) const {
        int hashIndex = hashFunction(correo); // Obtener el índice de la tabla hash

        // Buscar el nodo correspondiente al correo
        for (const auto& node : table[hashIndex]) {
            if (node.correo == correo) {
                return node.tareas; // Retornar las tareas si se encuentra el correo
            }
        }

        // Si no se encuentra, retornar una lista vacía
        return list<Tarea>();
    }
};
//Clase Programa
class Programa {
private:
    unordered_map<string, Usuario*> usuarios; // Hashtable de usuarios

public: //Metodos y constructor
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

//Funciones prototipo de verificacion de valores
void restringirEntradaNum(int &n);
void restringirEntradaNumRan(int &n, int ranMax, int ranMin);
//Funciones prototipo de Proceso
void abrirApp(Programa& programa, HashTable &hashTable);
int inicio(Programa& programa, int &salirApp);
Usuario* logging(Programa& programa);
bool menu(HashTable& hashTable, bool &salirApp);
//Funciones del proceso

int main() {
    HashTable hashTable(10); // Crear una tabla hash con tamaño 10
    Programa programa; //Creamos un objeto programa
    abrirApp(programa,hashTable); //Llamada a la funcion abrirApp
    system("pause"); //Impedir que el ejecutable se cierre
    return 0; //Finalizando el programa con 0
}


void restringirEntradaNum(int &n) { //Funcion de verificacion de datos de entrada numericos
    cin >> n; //Lectura de un numero
    while(cin.fail()) { //Mientras falle la lectura de la variable de tipo int, entonces:
        cin.clear(); //Limpiamos el estado de error
        cin.ignore(10000,'\n'); //Limpiamos el buffer de entrada avanzando diez mil caracteres y empezando a leer a partir de la siguiente linea
        cout << "Dato ingresado no valido ..." << endl; //Notificacion al usuario del no ingreso de datos
        cout << "Ingrese un valor numerico: " << endl;
        cin >> n; //Lectura de correccion
    }
}

void restringirEntradaNumRan(int &n, int ranMax, int ranMin) { //Funcion de verificacion de datos de entrada numericos entre un rango de valores
    cin >> n; //Lectura del valor
    while(cin.fail() || n > ranMax || n < ranMin) { //Mientras la lectura falle o el numero sea mayor al rango de opciones o el numero sea menor al numero permitido de opciones, entonces:
        cin.clear(); //Limpiamos el estado de error
        cin.ignore(10000,'\n'); //Limpiamos el buffer de entrada 10000 caracteres hacia adelante y empezamos a leer desde la siguiente linea
        cout << "Dato ingresado no valido ..." << endl; //Notificacion al usuario del dato no procesado
        cout << "Intente otra vez: " << endl;
        cin >> n; //Lectura de correccion
    }
}

// Función para agregar tareas
void agregarTarea(HashTable& hashTable) { //Funcion para agregar una tarea al HashTable
    string correo, descripcion; //Inicializamos las variables correo y descripción, el primero para verificar y encontrar la key en la hashTable y la descripción de la tarea para que nos brinde una descripción de lo que quiera aplicar
    int cantidadTareas; //Cantidad de tareas a ingresar
    int ranMax = 10; //Maximo de tareas para agregar 10
    int ranMin = 1; //Minimo de tareas para agregar 1

    cout << "\nAGREGAR TAREAS:\n";
    cout << "Ingrese el correo del usuario: ";
    cin >> correo; //Lectura de la variable correo
    cin.ignore(); // Limpiar el buffer de entrada

    cout << "Cuantas tareas desea agregar? ";
    restringirEntradaNumRan(cantidadTareas,ranMax, ranMin); //Maximo de 10 minimo 1
    cin.ignore(); // Limpiar el buffer de entrada

    for (int i = 0; i < cantidadTareas; ++i) {
        cout << "Ingrese la descripcion de la tarea " << (i + 1) << ": ";
        getline(cin, descripcion);

        Tarea nuevaTarea(descripcion);
        hashTable.agregarTarea(correo, nuevaTarea); // Inserta la tarea en la tabla hash
    }

    cout << "\n" << cantidadTareas << " tarea(s) agregada(s) con exito.\n"; //Notificacion de nueva tarea agregada
}

// Función para mostrar las tareas de un usuario
void mostrarTareas(HashTable& hashTable) { //Funcion para mostrar las tareas por referencia de nuestro HashTable
    string correo; //Variable correo
    cout << "\nMOSTRAR TAREAS:\n";
    cout << "Ingrese el correo del usuario: ";
    cin >> correo;

    list<Tarea> tareas = hashTable.obtenerTareas(correo); // Obtiene las tareas de la tabla hash
    if (!tareas.empty()) { //Si no esta vacia la lista tareas entonces:
        cout << "\nTareas para " << correo << ":\n";
        for (const Tarea& tarea : tareas) { //Iterando por cada tarea de la lista tareas
            cout << "- " << tarea.getDescripcion() << endl; //utilizando el metodo getDescripcion que retorna la descripcion de una tarea
        }
    } else { //De lo contrario:
        cout << "\nNo hay tareas para este usuario.\n"; //Notificar al usuario de la no existencia de tareas por su clave
    }
}

void crearUsuario(Programa& programa){ //Funcion para proseguir con el login
    string nomUsuario,contrasena,correo; //Inicializacion de variables
    int edad; //inicializacion de la variable edad
    int ranMax = 200; //Maximo de edad
    int ranMin = 5; //Minimo de edad
    cout<<" CREA UNA NUEVA CUENTA: ";
    cout<<"\n Ingrese su nombre de Usuario:  ";
    cin>>nomUsuario;
    cout<<"\n Ingrese su correo:  ";
    cin>>correo;
    Usuario* usuario=programa.recorreListaUsuarios(correo); //Recorriendo lista de usuarios
    if(usuario==nullptr){
        cout<<"\n Elija una contrasena: ";
        cin>>contrasena;
        cout<<"\n Ingrese su edad: ";
        restringirEntradaNumRan(edad, ranMax, ranMin);
        Usuario* nuevo = new Usuario(nomUsuario,edad,correo,contrasena);
        programa.agregarUsuario(nuevo);
        cout<<"\n CREADO"<<endl;
    }else{
        cout<<"\n Ya existe un usuario vinculado con ese correo"<<endl;
    }
}


int inicio(Programa& programa, int& salirApp) {
    int respuesta;
    int ranMax = 3;
    int ranMin = 1;
    cout << "Bienvenido elija una opcion: 1 (CREAR USUARIO) / 2 (ACCEDER A USUARIO) / 3 (FINALIZAR PROGRAMA): " << endl;;
    restringirEntradaNumRan(respuesta, ranMax, ranMin);
    if (respuesta == 1) {
        crearUsuario(programa);
        return 0; // No continuar, volver al inicio
    } else if (respuesta == 2) {
        return 1; // Continuar, proceder al logging
    } else {
        salirApp = 1; // Establecer salida
        return 2; // Indicar finalización
    }
}
Usuario* logging(Programa& programa){
    string correo, contrasena;
    cout<<"\n Ingrese su correo:  ";
    cin>>correo;
    Usuario* usuario=programa.recorreListaUsuarios(correo); //Recorriendo lista de usuarios en busca del correo ingresado
    if(usuario==nullptr){
        cout<<"\n No existe ninguna cuenta ligada al correo proporcionado"<<endl; //Notificacion de no haber encontrado
        return nullptr;
    }else{
        cout<<"\n Ingrese su contrasena: ";
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


bool menu(HashTable& hashTable, int &salirApp) {
    int opcion; //Inicializacion de la variable opcion
    int ranMax = 3; //Opciones maximas
    int ranMin = 1; //Opciones minimas
    do {
        cout << "\nBienvenido al gestor de tareas. Elija una opcion:\n";
        cout << "1. Agregar tareas\n";
        cout << "2. Mostrar tareas\n";
        cout << "3. Salir\n";
        cout << "Opcion: ";
        restringirEntradaNumRan(opcion, ranMax, ranMin); //Llamando a la funcion para evitar mala lectura de opciones

        switch (opcion) {
            case 1:
                agregarTarea(hashTable); // Llama a la función para agregar tarea
            break;
            case 2:
                mostrarTareas(hashTable); // Llama a la función para mostrar tareas
            break;
            case 3:
                return salirApp = true; // Salir del programa
            default:
                cout << "Opción inválida. Intente de nuevo.\n";
        }
    }while(salirApp != true);
}

void abrirApp(Programa& programa, HashTable& hashTable) {
    int salirApp = 0; // 0 - Continuar, 1 - Salir
    int registroInicio;
    Usuario* actual = nullptr;
    do {
        do {
            registroInicio = inicio(programa, salirApp);
        } while (registroInicio == 0); // 0 - No continuar, 1 - Continuar
        if (registroInicio == 1) {
            actual = logging(programa);
            if (actual != nullptr) {
                cout << "\nBienvenido de nuevo " << actual->getNombre() << "!!!" << endl;
                menu(hashTable, salirApp);
            }
        }
    } while (salirApp == 0); // 0 - Continuar, 1 - Salir
}