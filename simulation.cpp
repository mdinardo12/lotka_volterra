#include "simulation.hpp"

namespace lv {

auto start(Simulation)
{
  std::cout << "Inserisci il periodo di evoluzione dell'ecosistema: ";
  std::cin >> dt_;
};

} // namespace lv