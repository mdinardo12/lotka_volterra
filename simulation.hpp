#ifndef VOLTERRA_SIMULATION_HPP
#define VOLTERRA_SIMULATION_HPP

#include <vector>

namespace volterra {

struct State
{
  double x;
  double y;
  double H;
};

class Simulation
{
  double A_;
  double B_;
  double C_;
  double D_;
  double dt_;

  double x_eq_;
  double y_eq_;

  double x_rel_;
  double y_rel_;

  std::vector<State> results_;

 public:
  Simulation(double A, double B, double C, double D, double x0, double y0);
  Simulation(double A, double B, double C, double D);

  double compute_H(double x, double y) const;

  void evolve();

  void run(int steps);

  const std::vector<State>& get_results() const;
};

} // namespace volterra

#endif // VOLTERRA_SIMULATION_HPP