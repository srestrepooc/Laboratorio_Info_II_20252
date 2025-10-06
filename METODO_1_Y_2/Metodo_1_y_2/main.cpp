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
void encriptar_binario(int n) {

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

    cout<<endl;


    for (int i = 0; i < tamano; i++) {
        cout << unos_y_ceros[i];
    }
    cout << endl;



    //Se empieza a encriptar el archivo binario----------------------------------------------------------||||||||||
    int total_bits = i;
    int grupos = (total_bits + n - 1) / n;

    //Se reserva memoria para el nuevo arreglo que va a almacenar el resultado de la encriptación
    char* encriptado = new char[total_bits + 1];

    int unos;
    int ceros;


    //Este for me marca el recorrido por cada grupo de n bits hasta llegar al último
    for (int j=0; j < grupos;j++) {
        int inicio = j * n;
        int fin = inicio + n;
        if (fin > total_bits) fin = total_bits;

        //contar los 1s y 0s despues de pasar al segundo grupo
        if (j > 0){
            //Cuento los 1s y 0s del grupo actual
            unos = 0;
            ceros = 0;
            for (int k=inicio; k < fin;k++) {
                if (unos_y_ceros[k] == '1') unos++;
                else ceros++;
            }

        }

        //copia temporal del grupo con respecto a la posición en la que este unos_y_ceros
        char grupo[8] = {0};
        int tam_grupo = fin - inicio;
        for (int l=0; l < tam_grupo;l++){
            grupo[l] = unos_y_ceros[inicio + l];
        }

        // Aplicar reglas de inversión
        if (j == 0) {

            //Primer grupo: invertir todos los bits
            for (int k=0; k < tam_grupo;k++) {                //Esta condición solo se ejecuta una vez con el primer grupo para invertir sus bits
                grupo[k] = (grupo[k] == '1') ? '0' : '1';
            }

            //Cuento los 1s y 0s del grupo actual
            unos = 0;
            ceros = 0;
            for (int k=inicio; k < fin;k++) {
                if (unos_y_ceros[k] == '1') unos++;
                else ceros++;
            }


        } else {
            // Grupos siguientes
            if (unos == ceros) {
                for (int k=0; k < tam_grupo;k++) {
                    grupo[k] = (grupo[k] == '1') ? '0' : '1';    //Si grupo enn la posición k es igual 1, entoces se cambia por 0 y viciversa
                }
            } else if (ceros > unos) {
                // Invertir cada 2 bits
                for (int k=0; k < tam_grupo; k += 2) {         //Invierte cada 2 bits empezando desde la posición 0, mientras k sea menor a tam_grupo
                    grupo[k] = (grupo[k] == '1') ? '0' : '1';

                }
            } else {
                // Invertir cada 3 bits
                for (int k=0; k < tam_grupo; k += 3) {
                    grupo[k] = (grupo[k] == '1') ? '0' : '1';     //Invierte cada 3 bits empezando desde la posición 0, mientras k sea menor a tam_grupo
                }
            }
        }

        // Guardar grupo en el arreglo final
        for (int k=0; k < tam_grupo;k++) {                     //Voy guardando el grupo transformado desde la posición actual y final
            encriptado[inicio + k] = grupo[k];                 //Finaliza el ciclo para el grupo en la posición de inicio
        }
    }

    encriptado[total_bits] = '\0';


    //Escribir en el archivo de salida el resultado de la encriptación
    ofstream salida("Encriptado.txt", ios::binary);
    if (!salida.is_open()) {
        cout << "Error al crear Encriptado.txt\n";
        delete[] unos_y_ceros;
        delete[] encriptado;
        return;
    }

    salida << encriptado;
    salida.close();

    cout << "Archivo Encriptado.txt generado correctamente.\n";

    // Liberar memoria
    delete[] unos_y_ceros;
    delete[] encriptado;



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
        encriptar_binario(n);
    }






}








