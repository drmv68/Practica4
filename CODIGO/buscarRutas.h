#ifndef BUSCADOR_RUTAS_H
#define BUSCADOR_RUTAS_H

#include <string>
#include <map>
#include "Enrutador.h"

class BuscadorDeRutas {
public:
    static void calcularDijkstra(std::string ciudadOrigen, std::map<std::string, Enrutador>& universoDeEnrutadores);
};

#endif