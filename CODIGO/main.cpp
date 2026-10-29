#include <iostream>
#include <string>
#include "Red.h"
#include "leerArchivos.h"

using namespace std;

int main() {
    Red redCentralDeSimulacion;
    int opcionSeleccionada = 0;

    cout << "Iniciando simulador..." << endl;

    // Crea un archivo llamado topologia.txt en la misma carpeta del ejecutable
    LectorDeArchivos::construirRedDesdeTexto("topologia.txt", redCentralDeSimulacion);

    while (opcionSeleccionada != 6) {
        cout << "\n=== MENU DEL SIMULADOR ===" << endl;
        cout << "1. Mostrar topologia completa" << endl;
        cout << "2. Consultar ruta entre dos ciudades" << endl;
        cout << "3. Agregar ciudad (Enrutador)" << endl;
        cout << "4. Conectar ciudades (Enlace)" << endl;
        cout << "5. Eliminar ciudad (Enrutador)" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opcion: ";

        cin >> opcionSeleccionada;

        string origen, destino;
        int costo;

        switch (opcionSeleccionada) {
        case 1:
            redCentralDeSimulacion.imprimirEstadoDelSistema();
            break;
        case 2:
            cout << "Ciudad origen: ";
            cin >> origen;
            cout << "Ciudad destino: ";
            cin >> destino;
            redCentralDeSimulacion.consultarRutaYCosto(origen, destino);
            break;
        case 3:
            cout << "Nombre de la nueva ciudad: ";
            cin >> origen;
            if (redCentralDeSimulacion.agregarNuevoEnrutador(origen)) {
                cout << "Ciudad agregada con exito." << endl;
            } else {
                cout << "La ciudad ya existe." << endl;
            }
            break;
        case 4:
            cout << "Ciudad origen: ";
            cin >> origen;
            cout << "Ciudad destino: ";
            cin >> destino;
            cout << "Costo del peaje: ";
            cin >> costo;
            if (redCentralDeSimulacion.conectarEnrutadores(origen, destino, costo)) {
                cout << "Ciudades conectadas con exito." << endl;
            } else {
                cout << "Error: Alguna de las ciudades no existe." << endl;
            }
            break;
        case 5:
            cout << "Nombre de la ciudad a destruir: ";
            cin >> origen;
            if (redCentralDeSimulacion.removerEnrutador(origen)) {
                cout << "Ciudad y sus carreteras eliminadas limpiamente." << endl;
            } else {
                cout << "La ciudad no existe." << endl;
            }
            break;
        case 6:
            cout << "Apagando simulador..." << endl;
            break;
        default:
            cout << "Opcion invalida." << endl;
            break;
        }
    }

    return 0;
}