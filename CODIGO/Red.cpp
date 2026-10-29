#include "Red.h"
#include "BuscadorDeRutas.h"
#include <iostream>

using namespace std;

Red::Red() {
    huboCambiosEnLaRed = false;
}

bool Red::agregarNuevoEnrutador(string nombreDeLaCiudad) {
    if (enrutadoresEnElSistema.find(nombreDeLaCiudad) != enrutadoresEnElSistema.end()) {
        return false;
    }

    enrutadoresEnElSistema[nombreDeLaCiudad] = Enrutador(nombreDeLaCiudad);
    huboCambiosEnLaRed = true;
    return true;
}

bool Red::removerEnrutador(string nombreDeLaCiudad) {
    if (enrutadoresEnElSistema.find(nombreDeLaCiudad) == enrutadoresEnElSistema.end()) {
        return false;
    }

    map<string, int> vecinosAfectados = enrutadoresEnElSistema[nombreDeLaCiudad].obtenerVecinosConCosto();

    for (auto iterador = vecinosAfectados.begin(); iterador != vecinosAfectados.end(); iterador++) {
        string vecino = iterador->first;
        enrutadoresEnElSistema[vecino].eliminarVecinoDirecto(nombreDeLaCiudad);
    }

    enrutadoresEnElSistema.erase(nombreDeLaCiudad);
    huboCambiosEnLaRed = true;
    return true;
}

bool Red::conectarEnrutadores(string ciudadOrigen, string ciudadDestino, int costoDelPeaje) {
    if (enrutadoresEnElSistema.find(ciudadOrigen) == enrutadoresEnElSistema.end() ||
        enrutadoresEnElSistema.find(ciudadDestino) == enrutadoresEnElSistema.end()) {
        return false;
    }

    enrutadoresEnElSistema[ciudadOrigen].agregarVecinoDirecto(ciudadDestino, costoDelPeaje);
    enrutadoresEnElSistema[ciudadDestino].agregarVecinoDirecto(ciudadOrigen, costoDelPeaje);

    huboCambiosEnLaRed = true;
    return true;
}

bool Red::desconectarEnrutadores(string ciudadOrigen, string ciudadDestino) {
    if (enrutadoresEnElSistema.find(ciudadOrigen) == enrutadoresEnElSistema.end() ||
        enrutadoresEnElSistema.find(ciudadDestino) == enrutadoresEnElSistema.end()) {
        return false;
    }

    enrutadoresEnElSistema[ciudadOrigen].eliminarVecinoDirecto(ciudadDestino);
    enrutadoresEnElSistema[ciudadDestino].eliminarVecinoDirecto(ciudadOrigen);

    huboCambiosEnLaRed = true;
    return true;
}

void Red::sincronizarTodasLasTablas() {
    if (huboCambiosEnLaRed) {
        for (auto iterador = enrutadoresEnElSistema.begin(); iterador != enrutadoresEnElSistema.end(); iterador++) {
            BuscadorDeRutas::calcularDijkstra(iterador->first, enrutadoresEnElSistema);
        }
        huboCambiosEnLaRed = false;
    }
}

void Red::consultarRutaYCosto(string ciudadOrigen, string ciudadDestino) {
    if (enrutadoresEnElSistema.find(ciudadOrigen) == enrutadoresEnElSistema.end() ||
        enrutadoresEnElSistema.find(ciudadDestino) == enrutadoresEnElSistema.end()) {
        cout << "Error: Alguna ciudad no existe." << endl;
        return;
    }

    sincronizarTodasLasTablas();

    int costoFinal = enrutadoresEnElSistema[ciudadOrigen].consultarCostoHaciaDestino(ciudadDestino);

    if (costoFinal >= 999999) {
        cout << "No hay camino posible desde " << ciudadOrigen << " hasta " << ciudadDestino << endl;
        return;
    }

    cout << "Costo de viaje de " << ciudadOrigen << " a " << ciudadDestino << ": " << costoFinal << endl;
    enrutadoresEnElSistema[ciudadOrigen].imprimirRutaPasoAPaso(ciudadDestino);
}

void Red::imprimirEstadoDelSistema() {
    sincronizarTodasLasTablas();

    cout << "\n=== ESTADO DE LA RED ===" << endl;
    for (auto iterador = enrutadoresEnElSistema.begin(); iterador != enrutadoresEnElSistema.end(); iterador++) {
        iterador->second.imprimirInformacionCompletaDelEnrutador();
    }
    cout << "========================\n" << endl;
}