#include "LectorDeArchivos.h"
#include "Red.h"
#include <fstream>
#include <iostream>

using namespace std;

void LectorDeArchivos::construirRedDesdeTexto(string nombreArchivo, Red& redCentral) {
    ifstream archivoLector(nombreArchivo);

    if (!archivoLector.is_open()) {
        cout << "Error: No se encontro el archivo " << nombreArchivo << endl;
        return;
    }

    string ciudadOrigen, ciudadDestino;
    int costoPeaje;

    while (archivoLector >> ciudadOrigen >> ciudadDestino >> costoPeaje) {
        redCentral.agregarNuevoEnrutador(ciudadOrigen);
        redCentral.agregarNuevoEnrutador(ciudadDestino);
        redCentral.conectarEnrutadores(ciudadOrigen, ciudadDestino, costoPeaje);
    }

    archivoLector.close();
}