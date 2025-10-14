#include <iostream>
#include <fstream>

using namespace std;

void menu_administrador(int n);
void administrador();
unsigned char byte_a_binario(unsigned char byte);
unsigned char binario_a_byte(char bits[8]);
unsigned char rotar_izquierda(unsigned char byte);
void registrar_usuario();

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
    case 1: administrador();
        break;
    case 2:

        break;

    case 3:
        cout << "Saliendo del programa...\n";
        break;
    default:
        break;
    }

    return 0;
}

unsigned char byte_a_binario(unsigned char byte){
    byte ^= 4;
    byte = (byte >> 5) | (byte << (8 - 5));
    return byte;
}
unsigned char rotar_izquierda(unsigned char byte) {
    return (byte << 5) | (byte >> 3);
}
void registrar_usuario(){
    int cedula;

    //Validación para la cédula
    do {
        cout<<"--------Registro de usuarios/Administrador---------\n";
        cout<<"Ingrese la cedula del usuario:\n";

        // Intentar leer la cédula
        if (!(cin >> cedula)) {
            cout << "Entrada no valida. Ingrese solo numeros.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else if (cedula < 1000000 || cedula > 1999999999) {
            cout << "Cedula invalida. Debe tener entre 7 y 10 digitos.\n";
        }

    } while (cin.fail() || cedula < 1000000 || cedula > 1999999999);

    //Validación para el saldo
    unsigned long saldo;

    do{
        cout<<"Ingrese el saldo del usuario:\n";

        if (!(cin >> saldo)) {
            cout << "Entrada no valida. Ingrese solo numeros.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else if (saldo < 0 || saldo > 4294967295) {
            cout << "Ingreso invalido.\n";
        }
    }while (cin.fail() || saldo < 0 || saldo > 4294967295 );

    //Validación para la clave

    char clave[5];
    int n;

    do {
        cout << "Ingrese una clave de 4 digitos numericos: ";
        cin >> clave;

        // Validar longitud y que todos sean dígitos
        bool valido = true;
        for (int i = 0; i < 4; i++) {
            if (clave[i] < '0' || clave[i] > '9' || clave[i] == '\0') {
                valido = false;
                break;
            }
        }
        if (clave[4] != '\0') // Si tiene más de 4 caracteres
            valido = false;

        if (!valido) {
            cout << "Entrada invalida. Intente nuevamente.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        } else {
            break;
        }
    }while (cin.fail() || !valido);

    // Calcular semilla n
    n = (clave[0]-'0') + (clave[1]-'0') + (clave[2]-'0') + (clave[3]-'0');
    cout << "Semilla n generada\n";







}
unsigned char binario_a_byte(char bits[8]) {
    unsigned char valor = 0;
    for (int i = 0; i < 8; i++) {
        valor = (valor << 1) | (bits[i] - '0');
    }
    return valor;
}
void menu_administrador(int n){
    int semilla = n;

    ifstream archivo("administrador.txt", ios::binary);
    ifstream adm_binario("sudo.txt", ios::binary);
    if (!archivo.is_open() || !adm_binario.is_open()){
        cout<<"Error al abrir los archivos de administrador\n";
        archivo.close();
        adm_binario.close();
        return;
    }

    char linea_atual[100];
    char bit;
    char bits[8];
    unsigned char byte_desencriptado;

    bool coincide = true;

    int indice_bit = 0;
    int caracter = 0;

    archivo.getline(linea_atual, 100);

    while (adm_binario.get(bit)) {

        bits[indice_bit] = bit;
        indice_bit++;

        if (indice_bit == 8) {
            indice_bit = 0;

            byte_desencriptado = binario_a_byte(bits);

            byte_desencriptado = rotar_izquierda(byte_desencriptado);

            byte_desencriptado = byte_desencriptado ^ semilla;

            if (byte_desencriptado == '\n') {
                if (!archivo.getline(linea_atual, 100)) break;
                caracter = 0;
            } else {
                if (byte_desencriptado != linea_atual[caracter]) {
                    coincide = false;
                    break;
                }
                caracter++;
            }
        }
    }

    if (coincide) {
        registrar_usuario();
    } else {
        cout << "La clave es incorrecta.\n";
    }

    archivo.close();
    adm_binario.close();











}
void administrador(){

    unsigned long cedula;

    do {
        cout << "--------Administrador---------\n";
        cout << "Ingrese la cedula (solo numeros, sin espacios): ";

        // Intentar leer la cédula
        if (!(cin >> cedula)) {
            cout << "Entrada no valida. Ingrese solo numeros.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else if (cedula < 1000000 || cedula > 1999999999) {
            cout << "Cedula invalida. Debe tener entre 7 y 10 digitos.\n";
        }

    } while (cin.fail() || cedula < 1000000 || cedula > 1999999999); //-------------------------------------PENDIENTE POR VALIDAR

    cout<<endl;

    int clave;

    do {
        cout<<"--------Administrador---------\n";
        cout<<"Ingrese la clave:\n";
        if (!(cin >> clave)){
            cout<<"clave invalida\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else if (clave != 4){
            cout<<"Clave invalida\n";
        }

    } while (cin.fail() || clave != 4);

    menu_administrador(clave);
}
