#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Palabra {
    string palabra;
    string traduccion;
    string funcionalidad;
};

void agregarPalabra(ofstream& archivo, Palabra nuevaPalabra) {
    archivo << nuevaPalabra.palabra << ',' << nuevaPalabra.traduccion << ',' << nuevaPalabra.funcionalidad << '\n';
}

int main() {
    ofstream archivo("diccionario.dat", ios::app);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    int opcion;
    do {
        cout << "1. Agregar palabra" << endl;
        cout << "2. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            Palabra nuevaPalabra;
            cout << "Ingrese Palabra: ";
            cin >> nuevaPalabra.palabra;
            cout << "Ingrese Traduccion: ";
            cin >> nuevaPalabra.traduccion;
            cout << "Ingrese Funcionalidad: ";
            cin.ignore(); 
            getline(cin, nuevaPalabra.funcionalidad);

            agregarPalabra(archivo, nuevaPalabra);
            cout << "Palabra agregada correctamente." << endl;
        }
    } while (opcion != 2);

    archivo.close();
    return 0;
}

