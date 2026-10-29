#ifndef LECTOR_ARCHIVOS_H
#define LECTOR_ARCHIVOS_H

#include <string>

class Red;

class LectorDeArchivos {
public:
    static void construirRedDesdeTexto(std::string nombreArchivo, Red& redCentral);
};

#endif