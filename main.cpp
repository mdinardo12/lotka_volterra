#include <cstdlib>
#include <exception>
#include <iostream>

#include "simulation.hpp"

int main()
{
  try {
    double A;
    double B;
    double C;
    double D;
    double dt;
    double steps; // considera che deve essere per forza intero qiundi potremmo
                  // cambiarlo in int

    std::cout 
        << "Inserisci rispettivamente la velocità di riproduzione delle prede "
           "e dei predatori, e la mortalità delle prede e dei predatori: \n";
    std::cin >> A, C, B, D;
    std::cout << "Inserisci rispettivamente il tempo di un evento evoluzione e "
                 "il numero di eventi che si vuole avere: \n";
    std::cin >> dt, steps; //da tradurre in inglese

  } catch (std::exception const& e) {
    std::cerr << "Caught exception: '" << e.what() << "'\n";
    return EXIT_FAILURE;
  } catch (...) {
    std::cerr << "Caught unknown exception\n";
    return EXIT_FAILURE;
  }
}
