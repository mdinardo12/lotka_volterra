// #include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>

#include "simulation.hpp"

int main()
{
  try {
    using namespace volterra;

    double A, B, C, D, x0, y0, dt;
    int steps;

    std::cout << "=== Volterra simulation ===\n";

    std::cout << "Enter A (prey reproduction rate): ";
    std::cin >> A;
    std::cout << "Enter B (prey mortality rate): ";
    std::cin >> B;
    std::cout << "Enter C (predator reproduction rate): ";
    std::cin >> C;
    std::cout << "Enter D (predator mortality rate): ";
    std::cin >> D;

    std::cout << "Enter x0 (initial prey population density): ";
    std::cin >> x0;
    std::cout << "Enter y0 (initial predator population density): ";
    std::cin >> y0;

    std::cout << "Enter time step dt: ";
    std::cin >> dt;

    std::cout << "Enter number of steps: ";
    std::cin >> steps;

    Simulation sim(A, B, C, D, x0, y0, dt);

    sim.run(steps);

    std::ofstream file("results.txt");
    if (!file) {
      std::cout << "Error opening output file.\n";
      return 1;
    }

    file << "x    y    H\n"; // intestazione
    for (const auto& s : sim.get_results()) {
      file << s.x << " " << s.y << " " << s.H << "\n";
    }

    std::cout << "Results saved in 'results.txt'\n";

  } catch (std::exception const& e) {
    std::cerr << "Caught exception: '" << e.what() << "'\n";
    return EXIT_FAILURE;
  } catch (...) {
    std::cerr << "Caught unknown exception\n";
    return EXIT_FAILURE;
  }
}