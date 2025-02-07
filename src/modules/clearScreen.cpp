#include "../../include/headers/clearScreen.h"

using namespace std;

void clearScreen() {
    // Clearscreen pake ansi mirip sama project geocalcpp
    cout << "\033[2J\033[1;1H";
}