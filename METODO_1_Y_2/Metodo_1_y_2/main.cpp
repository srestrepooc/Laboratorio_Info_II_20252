#include <iostream>
#include <fstream>
using namespace std;

void byte_a_binario(unsigned char byte, char* letras);
void convertir_a_binario();
void encriptar_binario();


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
void encriptar_binario() {

    // Abrir el archivo de texto que tiene los 1s y 0s
    ifstream archivo_2("Binario.txt", ios::binary);
    if (!archivo_2.is_open()) {
        cout << "Error en la encriptacion.\n";
        return;
    }

    // Obtener su tamaño
    archivo_2.seekg(0, ios::end);
    streamsize tamano = archivo_2.tellg();
    archivo_2.seekg(0, ios::beg);

    // Variables para recorrer cada bit y guardarlos en un arreglo
    char bit;
    char* unos_y_ceros = new char[tamano + 1];
    int i = 0;

    // Bucle para recorrer cada bit e ir agregando al arreglo
    while (archivo_2.get(bit)) {
        unos_y_ceros[i] = bit;
        i++;
    }

    unos_y_ceros[tamano] = '\0';
    archivo_2.close();


    for (int i = 0; i < tamano; i++) {
        cout << unos_y_ceros[i];
    }
    cout << endl;

    delete[] unos_y_ceros;
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

    bool existe_binario = true;

    if (existe_binario){
        encriptar_binario();
    }






}








