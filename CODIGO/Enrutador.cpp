#include "Enrutador.h"


Enrutador::Enrutador() {
    nombreDelEnrutador = "";
}


Enrutador::Enrutador(string nombre) {
    nombreDelEnrutador = nombre;
}


void Enrutador::agregarVecino(string nombreDelVecino, int costoDelEnlace) {
    mapaDeVecinosConCosto[nombreDelVecino] = costoDelEnlace;
}


void Enrutador::eliminarVecino(string nombreDelVecino) {
    mapaDeVecinosConCosto.erase(nombreDelVecino);
}


void Enrutador::actualizarTablaDeCostos(map<string, int> nuevaTabla) {
    tablaDeCostosAotrosNodos = nuevaTabla;
}


void Enrutador::mostrarVecinos() {
    cout << "Vecinos de " << nombreDelEnrutador << ":" << endl;

    for (auto iterador = mapaDeVecinosConCosto.begin(); iterador != mapaDeVecinosConCosto.end(); iterador++) {
        string nombreVecino = iterador->first;
        int costoEnlace = iterador->second;
        cout << "  -> " << nombreVecino << " con costo " << costoEnlace << endl;
    }

    cout << endl;
}


void Enrutador::mostrarTablaDeCostos() {
    cout << "Tabla de costos de " << nombreDelEnrutador << ":" << endl;

    for (auto iterador = tablaDeCostosAotrosNodos.begin(); iterador != tablaDeCostosAotrosNodos.end(); iterador++) {
        string nombreDestino = iterador->first;
        int costoMinimo = iterador->second;
        cout << "  -> " << nombreDestino << " costo minimo: " << costoMinimo << endl;
    }

    cout << endl;
}


string Enrutador::obtenerNombre() {
    return nombreDelEnrutador;
}
