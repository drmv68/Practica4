#include "Red.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <limits>
#include <algorithm>

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

    map<string, int> vecinosDelNodoAEliminar = enrutadoresEnElSistema[nombreDeLaCiudad].obtenerVecinosConCosto();

    for (auto iterador = vecinosDelNodoAEliminar.begin(); iterador != vecinosDelNodoAEliminar.end(); iterador++) {
        string nombreDelVecino = iterador->first;
        enrutadoresEnElSistema[nombreDelVecino].eliminarVecinoDirecto(nombreDeLaCiudad);
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

void Red::cargarTopologiaDesdeArchivo(string nombreDelArchivo) {
    ifstream archivoDeTexto(nombreDelArchivo);

    if (!archivoDeTexto.is_open()) {
        cout << "No se pudo abrir el archivo: " << nombreDelArchivo << endl;
        return;
    }

    string origen, destino;
    int costo;

    while (archivoDeTexto >> origen >> destino >> costo) {
        agregarNuevoEnrutador(origen);
        agregarNuevoEnrutador(destino);
        conectarEnrutadores(origen, destino, costo);
    }

    archivoDeTexto.close();
    huboCambiosEnLaRed = true;
}

void Red::ejecutarAlgoritmoDijkstra(string ciudadOrigen) {
    map<string, int> costosMinimos;
    map<string, string> nodoAnteriorParaRuta;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> colaDePrioridad;

    int infinito = numeric_limits<int>::max();

    for (auto iterador = enrutadoresEnElSistema.begin(); iterador != enrutadoresEnElSistema.end(); iterador++) {
        costosMinimos[iterador->first] = infinito;
    }

    costosMinimos[ciudadOrigen] = 0;
    colaDePrioridad.push({0, ciudadOrigen});

    while (!colaDePrioridad.empty()) {
        int costoAcumuladoActual = colaDePrioridad.top().first;
        string ciudadActual = colaDePrioridad.top().second;
        colaDePrioridad.pop();

        if (costoAcumuladoActual > costosMinimos[ciudadActual]) {
            continue;
        }

        map<string, int> vecinosDeCiudadActual = enrutadoresEnElSistema[ciudadActual].obtenerVecinosConCosto();

        for (auto iterador = vecinosDeCiudadActual.begin(); iterador != vecinosDeCiudadActual.end(); iterador++) {
            string ciudadVecina = iterador->first;
            int costoDelPeajeHaciaVecino = iterador->second;

            int nuevoCostoCalculado = costoAcumuladoActual + costoDelPeajeHaciaVecino;

            if (nuevoCostoCalculado < costosMinimos[ciudadVecina]) {
                costosMinimos[ciudadVecina] = nuevoCostoCalculado;
                nodoAnteriorParaRuta[ciudadVecina] = ciudadActual;
                colaDePrioridad.push({nuevoCostoCalculado, ciudadVecina});
            }
        }
    }

    enrutadoresEnElSistema[ciudadOrigen].actualizarTablaDeRutas(costosMinimos, nodoAnteriorParaRuta);
}

void Red::actualizarTablasSiEsNecesario() {
    if (huboCambiosEnLaRed) {
        for (auto iterador = enrutadoresEnElSistema.begin(); iterador != enrutadoresEnElSistema.end(); iterador++) {
            ejecutarAlgoritmoDijkstra(iterador->first);
        }
        huboCambiosEnLaRed = false;
    }
}

void Red::consultarRutaYCosto(string ciudadOrigen, string ciudadDestino) {
    if (enrutadoresEnElSistema.find(ciudadOrigen) == enrutadoresEnElSistema.end() ||
        enrutadoresEnElSistema.find(ciudadDestino) == enrutadoresEnElSistema.end()) {
        cout << "Error: Alguna de las ciudades no existe en la red." << endl;
        return;
    }

    actualizarTablasSiEsNecesario();

    int costoFinal = enrutadoresEnElSistema[ciudadOrigen].consultarCostoHaciaDestino(ciudadDestino);

    if (costoFinal == numeric_limits<int>::max()) {
        cout << "No existe un camino posible desde " << ciudadOrigen << " hasta " << ciudadDestino << endl;
        return;
    }

    cout << "El costo minimo desde " << ciudadOrigen << " hasta " << ciudadDestino << " es: " << costoFinal << endl;
    cout << "Ruta optima: ";
    enrutadoresEnElSistema[ciudadOrigen].imprimirRutaPasoAPaso(ciudadDestino);
}

void Red::imprimirEstadoDeLaRed() {
    actualizarTablasSiEsNecesario();

    cout << "\n=== ESTADO COMPLETO DE LA RED ===" << endl;
    for (auto iterador = enrutadoresEnElSistema.begin(); iterador != enrutadoresEnElSistema.end(); iterador++) {
        iterador->second.imprimirInformacionCompletaDelEnrutador();
    }
    cout << "=================================\n" << endl;
}