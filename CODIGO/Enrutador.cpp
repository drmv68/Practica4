#include "Enrutador.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

Enrutador::Enrutador() {
    nombreDeLaCiudad = "";
}

Enrutador::Enrutador(string nombre) {
    nombreDeLaCiudad = nombre;
}

void Enrutador::agregarVecinoDirecto(string nombreDelVecino, int costoDelPeaje) {
    vecinosConCosto[nombreDelVecino] = costoDelPeaje;
}

void Enrutador::eliminarVecinoDirecto(string nombreDelVecino) {
    vecinosConCosto.erase(nombreDelVecino);
}

map<string, int> Enrutador::obtenerVecinosConCosto() {
    return vecinosConCosto;
}

void Enrutador::actualizarTablaDeRutas(map<string, int> nuevosCostos, map<string, string> rutasPrevias) {
    tablaDeCostosMinimos = nuevosCostos;
    tablaDeRutasPrevias = rutasPrevias;
}

int Enrutador::consultarCostoHaciaDestino(string ciudadDestino) {
    if (tablaDeCostosMinimos.find(ciudadDestino) != tablaDeCostosMinimos.end()) {
        return tablaDeCostosMinimos[ciudadDestino];
    }
    return 999999;
}

void Enrutador::imprimirRutaPasoAPaso(string ciudadDestino) {
    if (tablaDeCostosMinimos.find(ciudadDestino) == tablaDeCostosMinimos.end() || tablaDeCostosMinimos[ciudadDestino] >= 999999) {
        cout << "Ruta inalcanzable." << endl;
        return;
    }

    vector<string> rutaInvertida;
    string ciudadActual = ciudadDestino;

    while (ciudadActual != nombreDeLaCiudad) {
        rutaInvertida.push_back(ciudadActual);
        ciudadActual = tablaDeRutasPrevias[ciudadActual];
    }
    rutaInvertida.push_back(nombreDeLaCiudad);

    reverse(rutaInvertida.begin(), rutaInvertida.end());

    for (size_t iteradorLista = 0; iteradorLista < rutaInvertida.size(); iteradorLista++) {
        cout << rutaInvertida[iteradorLista];
        if (iteradorLista < rutaInvertida.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
}

void Enrutador::imprimirInformacionCompletaDelEnrutador() {
    cout << "Ciudad Origen: " << nombreDeLaCiudad << endl;

    cout << "  [Vecinos Directos]" << endl;
    for (auto iterador = vecinosConCosto.begin(); iterador != vecinosConCosto.end(); iterador++) {
        cout << "    - " << iterador->first << " | Peaje: " << iterador->second << endl;
    }

    cout << "  [Tabla de Rutas Optimizada]" << endl;
    for (auto iterador = tablaDeCostosMinimos.begin(); iterador != tablaDeCostosMinimos.end(); iterador++) {
        if (iterador->second < 999999) {
            cout << "    - Hacia " << iterador->first << " | Costo Total: " << iterador->second << endl;
        }
    }
    cout << endl;
}