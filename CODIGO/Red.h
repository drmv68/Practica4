#ifndef RED_H
#define RED_H

#include <string>
#include <map>
#include "Enrutador.h"

class Red {
private:
    std::map<std::string, Enrutador> enrutadoresEnElSistema;
    bool huboCambiosEnLaRed;

    void sincronizarTodasLasTablas();

public:
    Red();

    bool agregarNuevoEnrutador(std::string nombreDeLaCiudad);
    bool removerEnrutador(std::string nombreDeLaCiudad);
    bool conectarEnrutadores(std::string ciudadOrigen, std::string ciudadDestino, int costoDelPeaje);
    bool desconectarEnrutadores(std::string ciudadOrigen, std::string ciudadDestino);

    void consultarRutaYCosto(std::string ciudadOrigen, std::string ciudadDestino);
    void imprimirEstadoDelSistema();
};

#endif