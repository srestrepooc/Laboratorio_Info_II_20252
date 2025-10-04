#include <iostream>
#include <fstream>
using namespace std;

void byte_a_binario(unsigned char byte, char* letras);
void convertir_a_binario();



int main() {
    int opcion;

    do {
        cout<<"--------Manipulacion de archivos txt---------\n";
        cout<<"Elija una opcion:\n";
        cout<<"1. Encriptar archivo\n";
        cout<<"2. Desencriptar archivo\n";
        cout<<"3. Salir\n";
        cin>>opcion;

        if (opcion <= 0 || opcion >= 4){
            cout<<"Opcion incorrecta, intente de nuevo\n";
        }
    } while (opcion <= 0 || opcion >= 4);

    switch (opcion) {
    case 1: convertir_a_binario();
        break;

    case 3:
        cout << "Saliendo del programa...\n";
        break;
    }

    return 0;
}

void byte_a_binario(unsigned char byte, char* letras){
    for(int i=7;i >= 0;i--){
        letras[7-i] = (byte & (1 << i)) ? '1' : '0';
    }

        letras[8] = '\0';
    }

void convertir_a_binario() {
    int n;
    do {
        cout<<"Ingrese una semilla mayor a 1 y menor a 8: ";
        cin>>n;
        if (n <= 1 || n >= 8) {
            cout<<"Ingrese una semilla correcta.\n";
        }
    } while (n <= 1 || n >= 8);

    string nombre;
    ifstream archivo;

    do {
        cout << "Ingrese el nombre del archivo (Ejemplo: Metodo_1.txt): ";
        cin >> nombre;
        archivo.open(nombre, ios::binary);
        if (!archivo.is_open()) {
            cout << "Error: el nombre del archivo es incorrecto. Intente de nuevo.\n";
        }
    } while (!archivo.is_open());

    archivo.seekg(0, ios::end);
    streamsize tamano = archivo.tellg();
    archivo.seekg(0, ios::beg);


    ofstream binario("Binario.txt", ios::binary);
    if (!binario.is_open()) {
        cout << "Error en la encriptacion.\n";
        archivo.close();
        return;
    }

    char byte;
    char letras[tamano];
    while (archivo.get(byte)){
        byte_a_binario((unsigned char)byte,letras);
        binario << letras;
    }

    archivo.close();
    binario.close();

    cout << "El archivo ha sido convertido correctamente a Binario.txt.\n";
}






