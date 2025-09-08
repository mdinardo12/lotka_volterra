#include <exception>
#include <fstream>
#include <string>

#include "input_utils.hpp"
#include "simulation.hpp"

int main()
{
  try {
    using namespace volterra;

    std::cout << "=== Volterra simulation ===\n";

    double A = read_param<double>("Enter A (prey reproduction rate): ");
    double B = read_param<double>("Enter B (prey mortality rate): ");
    double C = read_param<double>("Enter C (predator reproduction rate): ");
    double D = read_param<double>("Enter D (predator mortality rate): ");
    double x0 =
        read_param<double>("Enter x0 (initial prey population density): ");
    double y0 =
        read_param<double>("Enter y0 (initial predator population density): ");
    int steps = read_param<int>("Enter number of steps: ");

    Simulation sim(A, B, C, D, x0, y0);

    sim.run(steps);

    std::ofstream file("results.txt");
    if (!file) {
      std::cerr << "Error opening output file.\n";
      return EXIT_FAILURE;
    }

    file << "x    y    H\n";
    for (auto const& s : sim.get_results()) {
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