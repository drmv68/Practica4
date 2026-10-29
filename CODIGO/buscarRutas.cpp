#include "buscarRutas.h"
#include <queue>
#include <vector>

using namespace std;

void BuscadorDeRutas::calcularDijkstra(string ciudadOrigen, map<string, Enrutador>& universoDeEnrutadores) {
    map<string, int> tablaDeCostos;
    map<string, string> rutasPasoAPaso;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> nodosPendientes;

    const int COSTO_INFINITO = 999999;

    for (auto iterador = universoDeEnrutadores.begin(); iterador != universoDeEnrutadores.end(); iterador++) {
        tablaDeCostos[iterador->first] = COSTO_INFINITO;
    }

    tablaDeCostos[ciudadOrigen] = 0;
    nodosPendientes.push({0, ciudadOrigen});

    while (!nodosPendientes.empty()) {
        int costoAcumulado = nodosPendientes.top().first;
        string ciudadActual = nodosPendientes.top().second;
        nodosPendientes.pop();

        if (costoAcumulado > tablaDeCostos[ciudadActual]) {
            continue;
        }

        map<string, int> vecinosDirectos = universoDeEnrutadores[ciudadActual].obtenerVecinosConCosto();

        for (auto iterador = vecinosDirectos.begin(); iterador != vecinosDirectos.end(); iterador++) {
            string ciudadVecina = iterador->first;
            int costoDelPeaje = iterador->second;

            int nuevoCosto = costoAcumulado + costoDelPeaje;

            if (nuevoCosto < tablaDeCostos[ciudadVecina]) {
                tablaDeCostos[ciudadVecina] = nuevoCosto;
                rutasPasoAPaso[ciudadVecina] = ciudadActual;
                nodosPendientes.push({nuevoCosto, ciudadVecina});
            }
        }
    }

    universoDeEnrutadores[ciudadOrigen].actualizarTablaDeRutas(tablaDeCostos, rutasPasoAPaso);
}