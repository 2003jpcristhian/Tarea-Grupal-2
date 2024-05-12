#include <iostream>
#include <string>
#include <map>
#include <sstream>

using namespace std;

// Define un mapa para almacenar las traducciones
map<string, string> traducciones = {
    {"int", "entero"},
    {"main", "principal"},
    {"cout", "imprimir"},
    {"cin", "leer"},
    {"if", "si"},
    {"else", "entonces"},
    {"return", "retorno"},
    {"exit", "salir"}
};

// Función para traducir el código
string traducirCodigo(const string& codigo) {
    stringstream codigoTraducido;
    stringstream flujoCodigo(codigo);
    string token;
    bool dentroDeComentario = false;

    while (getline(flujoCodigo, token, '\n')) {
        stringstream lineaTraducida;
        stringstream flujoLinea(token);
        string palabra;

        while (flujoLinea >> palabra) {
            if (dentroDeComentario) {
                lineaTraducida << palabra << " ";
                if (palabra.find("*/") != string::npos) {
                    dentroDeComentario = false;
                }
            } else if (palabra == "//") {
                dentroDeComentario = true;
                lineaTraducida << palabra << " ";
            } else if (palabra == "/*") {
                dentroDeComentario = true;
                lineaTraducida << palabra << " ";
                string siguientePalabra;
                while (flujoLinea >> siguientePalabra) {
                    lineaTraducida << siguientePalabra << " ";
                    if (siguientePalabra.find("*/") != string::npos) {
                        dentroDeComentario = false;
                        break;
                    }
                }
            } else if (traducciones.find(palabra) != traducciones.end()) {
                lineaTraducida << traducciones[palabra] << " ";
            } else if (palabra == "{") {
                lineaTraducida << "inicio ";
            } else if (palabra == "}") {
                lineaTraducida << "fin ";
            } else {
                lineaTraducida << palabra << " ";
            }
        }

        codigoTraducido << lineaTraducida.str() << endl;
    }

    return codigoTraducido.str();
}

int main() {
    string codigo;
    cout << "Ingrese el código C++ a traducir (finalice con una línea vacía):" << endl;

    string linea;
    while (getline(cin, linea) && !linea.empty()) {
        codigo += linea + '\n';
    }

    string codigoTraducido = traducirCodigo(codigo);
    cout << "Código traducido: " << endl << codigoTraducido << endl;

    return 0;
}

void cargarTraducciones(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo de traducciones." << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string palabra, traduccion;
        if (getline(ss, palabra, ',') && getline(ss, traduccion)) {
            traducciones[palabra] = traduccion;
        }
    }

    archivo.close();
}
