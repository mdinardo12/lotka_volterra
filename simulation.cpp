#include "simulation.hpp"

#include <cassert>
#include <cmath>
#include <stdexcept>

namespace volterra {

Simulation::Simulation(double A, double B, double C, double D, double x0,
                       double y0)
    : A_{A}
    , B_{B}
    , C_{C}
    , D_{D}
    , dt_{.001}
    , x_eq_{D / C}
    , y_eq_{A / B}
    , x_rel_{x0 / x_eq_}
    , y_rel_{y0 / y_eq_}
    , results_{}

{
  if (A <= 0 || B <= 0 || C <= 0 || D <= 0 || x0 <= 0 || y0 <= 0) {
    throw std::runtime_error("Input parameters must be positive");
  };

  results_.push_back({x0, y0, compute_H(x0, y0)});
}

Simulation::Simulation(double A, double B, double C, double D)
    : Simulation(A, B, C, D, 1., 1.)
{}

double Simulation::compute_H(double x, double y) const
{
  return -D_ * std::log(x) + C_ * x + B_ * y - A_ * std::log(y);
}

void Simulation::evolve()
{
  double x_rel_next = x_rel_ + A_ * (1.0 - y_rel_) * x_rel_ * dt_;
  double y_rel_next = y_rel_ + D_ * (x_rel_ - 1.0) * y_rel_ * dt_;

  x_rel_ = x_rel_next;
  y_rel_ = y_rel_next;

  assert(x_rel_ > 0 && y_rel_ > 0);

  double x_abs = x_rel_ * x_eq_;
  double y_abs = y_rel_ * y_eq_;

  results_.push_back({x_abs, y_abs, compute_H(x_abs, y_abs)});
}

void Simulation::run(int steps)
{
  if (steps < 0) {
    throw std::runtime_error("steps must be >= 0");
  }
  for (int i = 0; i < steps; ++i) {
    evolve();
  }
}

const std::vector<State>& Simulation::get_results() const
{
  return results_;
}

} // namespace volterra