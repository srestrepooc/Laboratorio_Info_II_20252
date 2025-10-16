#include <iostream>
#include <fstream>

using namespace std;

void menu_administrador();
void ingreso_usuario();
bool validar_usuario(const string &cedula_ingresada, const string &clave_ingresada);
//Funciones para validar el ingreso del administrador
bool comparar_archivos(const char *archivo1, const char *archivo2);
unsigned char rotar_izquierda(unsigned char byte);
unsigned char binario_a_byte(char bits[8]);
unsigned char guardar_usuarios(unsigned char byte, int n);

//Funciones para encriptar XOR + rotacion
string byte_a_binario(unsigned char byte);
string encriptarDato(string dato, int n);
void registrar_usuario();
unsigned char guardar_usuarios(unsigned char byte, int n);

int main()
{
    int opcion;

    do {
        cout<<"--------Sistema Bancario---------\n";
        cout<<"Elija una opcion:\n";
        cout<<"1. Administrador\n";
        cout<<"2. Usuario\n";
        cout<<"3. Salir\n";
        if (!(cin >> opcion)){
            cout<<"Entrada no valida\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else if (opcion <= 0 || opcion >= 4){
            cout<<"Opcion no valida\n";
        }

    } while (cin.fail() || opcion <= 0 || opcion >= 4);

    switch (opcion) {
    case 1: menu_administrador();
        break;
    case 2: ingreso_usuario();

        break;

    case 3:
        cout << "Saliendo del programa...\n";
        break;
    default:
        break;
    }

    return 0;
}


//Funciones para encriptar XOR + rotacion
unsigned char guardar_usuarios(unsigned char byte, int n){
    byte ^= n;
    byte = (byte >> 5) | (byte << 3);
    return byte;
}
string byte_a_binario(unsigned char byte){
    string binario = "";
    for (int i = 7; i >= 0; i--) {
        binario += ((byte >> i) & 1) ? '1' : '0';
    }
    return binario;
}
string encriptarDato(string dato, int n){
    string resultado = "";
    for (int i = 0; i < dato.size(); i++) {
        unsigned char byte = dato[i];
        byte = guardar_usuarios(byte, n);
        resultado += byte_a_binario(byte);
    }
    return resultado;
}
void registrar_usuario(){
    int cedula;
    unsigned long saldo;
    int clave;

    // Validación para la cédula
    do {
        cout<<"--------Registro de usuarios/Administrador---------\n";
        cout<<"Ingrese la cedula del usuario:\n";
        if (!(cin >> cedula)) {
            cout<<"Entrada no valida. Ingrese solo numeros.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        } else if (cedula < 1000000 || cedula > 1999999999) {
            cout<<"Cedula invalida. Debe tener entre 7 y 10 digitos.\n";
        }
    } while (cin.fail() || cedula < 1000000 || cedula > 1999999999);

    // Validación para el saldo
    do {
        cout<<"Ingrese el saldo del usuario:\n";
        if (!(cin >> saldo)) {
            cout<<"Entrada no valida. Ingrese solo numeros.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    } while (cin.fail());

    // Validación para la clave
    do {
        cout<<"Ingrese la clave del usuario (max 4 digitos):\n";
        if (!(cin >> clave)) {
            cout<<"Entrada no valida. Ingrese solo numeros.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        } else if (clave < 1000 || clave > 9999) {
            cout<<"Clave invalida.\n";
        }
    } while (cin.fail() || clave < 1000 || clave > 9999);

    ofstream archivo("usuarios.txt", ios::app);
    if (!archivo.is_open()) {
        cout<<"Error al abrir usuarios.txt\n";
        return;
    }

    archivo << encriptarDato(to_string(cedula), 4) << endl;
    archivo << encriptarDato(to_string(saldo), 4) << endl;
    archivo << encriptarDato(to_string(clave), 4) << endl;

    archivo.close();
    cout<<"\nUsuario registrado correctamente\n";
}


//Funciones para validar el ingreso del administrador
unsigned char rotar_izquierda(unsigned char byte) {
    return (byte << 5) | (byte >> 3);
}
unsigned char binario_a_byte(char bits[8]) {
    unsigned char valor = 0;
    for (int i = 0; i < 8; i++) {
        valor = (valor << 1) | (bits[i] - '0');
    }
    return valor;
}
bool comparar_archivos(const char *archivo1, const char *archivo2) {
    ifstream file1(archivo1, ios::binary);
    ifstream file2(archivo2, ios::binary);

    if (!file1.is_open() || !file2.is_open()) {
        cout << "Error abriendo los archivos para comparar." << endl;
        return false;
    }

    char c1, c2;
    while (true) {
        file1.get(c1);
        file2.get(c2);

        if (file1.eof() && file2.eof()) {
            file1.close();
            file2.close();
            return true;
        }

        if (file1.eof() != file2.eof() || c1 != c2) {
            file1.close();
            file2.close();
            return false;
        }
    }
}
void menu_administrador(){

    //Creacion del archivo sudo.txt con los datos del administrador
    int cedula = 1037370134;
    int clave = 1234;

    ofstream archivo("sudo.txt");
    if (!archivo.is_open()) {
        cout<<"Error al abrir usuarios.txt\n";
        return;
    }

    archivo << encriptarDato(to_string(cedula), 4) << endl;
    archivo << encriptarDato(to_string(clave), 4) << endl;

    archivo.close();
    cout<<"\nAdministrador registrado correctamente\n";

    //Validar ingreso del administrador

    int identificacion;
    int password;

    // Validación para la cédula
    do {
        cout<<"--------Administrador---------\n";
        cout<<"Ingrese su cedula:\n";
        if (!(cin >> identificacion)) {
            cout<<"Entrada no valida. Ingrese solo numeros.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        } else if (identificacion < 1000000 || identificacion > 1999999999) {
            cout<<"Cedula invalida. Debe tener entre 7 y 10 digitos.\n";
        }
    } while (cin.fail() || identificacion < 1000000 || identificacion > 1999999999);

    // Validación para la clave
    do {
        cout<<"Ingrese su clave(max 4 digitos):\n";
        if (!(cin >> password)) {
            cout<<"Entrada no valida. Ingrese solo numeros.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        } else if (password < 1000 || password > 9999) {
            cout<<"Clave invalida.\n";
        }
    } while (cin.fail() || password < 1000 || password > 9999);

    ofstream validar("validar_administrador.txt", ios::app);
    if (!validar.is_open()) {
        cout<<"Error al crear archivo de comparacion.\n";
        return;
    }

    validar << encriptarDato(to_string(identificacion), 4) << endl;
    validar << encriptarDato(to_string(password), 4) << endl;

    validar.close();
    cout<<"\nSe creo el archivo para validar el administrador\n";


    //Comparar los archivos con la funcion

    if (comparar_archivos("sudo.txt", "validar_administrador.txt")){
        if (remove("validar_administrador.txt") == 0) {
            cout << "Archivo de validacion eliminado correctamente.\n";
        } else {
            cout << "No se pudo eliminar el archivo de validacion.\n";
        }
        registrar_usuario();

    }else {
        cout<<"cedula o clave incorrecta.\n";
        if (remove("validar_administrador.txt") == 0) {
            cout << "Archivo de validacion eliminado correctamente.\n";
        } else {
            cout << "No se pudo eliminar el archivo de validacion.\n";
        }
    }


}

bool validar_usuario(const string &cedula_ingresada, const string &clave_ingresada) {
    ifstream archivo("usuarios.txt", ios::binary);
    if (!archivo.is_open()) {
        cout << "Error al abrir usuarios.txt" << endl;
        return false;
    }

    string linea;
    int linea_actual = 0;

    while (getline(archivo, linea)) {
        if (linea_actual % 3 == 0) {
            if (linea == cedula_ingresada) {
                string saldo;
                string clave_archivo;

                getline(archivo, saldo);           //linea 2 para poder tomar la 3
                getline(archivo, clave_archivo);    // linea 3 para comparar

                archivo.close();

                if (clave_archivo == clave_ingresada) {
                    return true; //Usuario autenticado
                }
                else {
                    return false; //cedula correcta, pero la clave no
                }
            }
        }
        linea_actual++;
    }

    archivo.close();
    return false; //No se encontro la cedula
}

void ingreso_usuario(){
    //Validar ingreso del usuario

    int identificacion;
    int password;

    // Validación para la cédula
    do {
        cout<<"--------Usuario---------\n";
        cout<<"Ingrese su cedula:\n";
        if (!(cin >> identificacion)) {
            cout<<"Entrada no valida. Ingrese solo numeros.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        } else if (identificacion < 1000000 || identificacion > 1999999999) {
            cout<<"Cedula invalida. Debe tener entre 7 y 10 digitos.\n";
        }
    } while (cin.fail() || identificacion < 1000000 || identificacion > 1999999999);

    // Validación para la clave
    do {
        cout<<"--------Usuario---------\n";
        cout<<"Ingrese su clave(max 4 digitos):\n";
        if (!(cin >> password)) {
            cout<<"Entrada no valida. Ingrese solo numeros.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        } else if (password < 1000 || password > 9999) {
            cout<<"Clave invalida.\n";
        }
    } while (cin.fail() || password < 1000 || password > 9999);

    ofstream validar("validar_usuario.txt", ios::app);
    if (!validar.is_open()) {
        cout<<"Error al crear archivo de comparacion.\n";
        return;
    }

    validar << encriptarDato(to_string(identificacion), 4) << endl;
    validar << encriptarDato(to_string(password), 4) << endl;

    validar.close();
    cout<<"\nSe creo el archivo para validar el usuario\n";

    string id, contrasena;

    // Leer datos del archivo temporal
    ifstream comparar("validar_usuario.txt", ios::binary);
    if (!comparar.is_open()) {
        cout<<"Error al crear archivo de comparacion.\n";
        return;
    }
    getline(comparar, id);
    getline(comparar, contrasena);
    comparar.close();

    // Validar
    if (validar_usuario(id, contrasena)){
        cout<<"Acceso permitido, datos correctos\n";
        if (remove("validar_usuario.txt") == 0) {
            cout << "Archivo de validacion eliminado correctamente.\n";
        } else {
            cout << "No se pudo eliminar el archivo de validacion.\n";
        }
        //menu_usuario();
    }

    else{
        cout << "Cedula o clave incorrecta\n";
        if (remove("validar_usuario.txt") == 0) {
            cout << "Archivo de validacion eliminado correctamente.\n";
        } else {
            cout << "No se pudo eliminar el archivo de validacion.\n";
        }
    }


}
