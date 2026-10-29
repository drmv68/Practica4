#include <iostream>
#include "Red.h"

using namespace std;

int main() {

    Red miRed;

    miRed.agregarEnrutador("A");
    miRed.agregarEnrutador("B");
    miRed.agregarEnrutador("C");
    miRed.agregarEnrutador("D");

    miRed.crearEnlaceEntreEnrutadores("A", "B", 4);
    miRed.crearEnlaceEntreEnrutadores("A", "C", 10);
    miRed.crearEnlaceEntreEnrutadores("A", "D", 5);
    miRed.crearEnlaceEntreEnrutadores("B", "C", 3);
    miRed.crearEnlaceEntreEnrutadores("B", "D", 1);
    miRed.crearEnlaceEntreEnrutadores("C", "D", 2);

    miRed.mostrarTodaLaRed();

    return 0;
}
