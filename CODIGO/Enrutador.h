#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <string>
#include <map>

class Enrutador {
private:
    std::string nombreDeLaCiudad;
    std::map<std::string, int> vecinosConCosto;
    std::map<std::string, int> tablaDeCostosMinimos;
    std::map<std::string, std::string> tablaDeRutasPrevias;

public:
    Enrutador();
    Enrutador(std::string nombre);

    void agregarVecinoDirecto(std::string nombreDelVecino, int costoDelPeaje);
    void eliminarVecinoDirecto(std::string nombreDelVecino);

    std::map<std::string, int> obtenerVecinosConCosto();

    void actualizarTablaDeRutas(std::map<std::string, int> nuevosCostos, std::map<std::string, std::string> rutasPrevias);

    int consultarCostoHaciaDestino(std::string ciudadDestino);
    void imprimirRutaPasoAPaso(std::string ciudadDestino);
    void imprimirInformacionCompletaDelEnrutador();
};

#endif