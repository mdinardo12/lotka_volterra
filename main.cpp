#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>

#include "simulation.cpp"

int main()
{
  try {
    using namespace volterra;

    double A, B, C, D, x0, y0, dt;
    int steps;

    std::cout << "=== Volterra simulation ===\n";

    std::cout << "Enter A (prey reproduction rate):\n";
    // std::cin >> A;

    if (!(std::cin >> A)) {
      std::cerr << "Error: parameter must be a rational number" << std::endl;
      exit(EXIT_FAILURE);
    }

    std::cout << "Enter B (prey mortality rate):\n";
    // std::cin >> B;

    if (!(std::cin >> B)) {
      std::cerr << "Error: parameter must be a rational number" << std::endl;
      exit(EXIT_FAILURE);
    }

    std::cout << "Enter C (predator reproduction rate):\n";
    // std::cin >> C;

    if (!(std::cin >> C)) {
      std::cerr << "Error: parameter must be a rational number" << std::endl;
      exit(EXIT_FAILURE);
    }

    std::cout << "Enter D (predator mortality rate):\n";
    // std::cin >> D;

    if (!(std::cin >> D)) {
      std::cerr << "Error: parameter must be a rational number" << std::endl;
      exit(EXIT_FAILURE);
    }

    std::cout << "Enter x0 (initial prey population density):\n";
    // std::cin >> x0;

    if (!(std::cin >> x0)) {
      std::cerr << "Error: parameter must be a rational number" << std::endl;
      exit(EXIT_FAILURE);
    }

    std::cout << "Enter y0 (initial predator population density):\n";
    // std::cin >> y0;

    if (!(std::cin >> y0)) {
      std::cerr << "Error: parameter must be a rational number" << std::endl;
      exit(EXIT_FAILURE);
    }

    std::cout << "Enter time step dt:\n";
    // std::cin >> dt;

    if (!(std::cin >> dt)) {
      std::cerr << "Error: parameter must be a rational number" << std::endl;
      exit(EXIT_FAILURE);
    }

    std::cout << "Enter number of steps:\n";
    // std::cin >> steps;

    if (!(std::cin >> steps)) {
      std::cerr << "Error: must enter a integer number of steps" << std::endl;
      exit(EXIT_FAILURE);
    } // ! nega il valore booleano, il blocco if viene letto solo se la
      // lettura fallisce

    Simulation sim(A, B, C, D, x0, y0, dt);

    sim.run(steps);

    std::ofstream file("results.txt");
    if (!file) {
      std::cout << "Error opening output file.\n";
      return 1;
    }

    file << "x    y    H\n";
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