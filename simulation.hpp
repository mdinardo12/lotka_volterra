#ifndef VOLTERRA_SIMULATION_HPP
#define VOLTERRA_SIMULATION_HPP

#include <cmath>
#include <iostream>
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
  // Parametri del modello (tutti > 0)
  double A_;
  double B_;
  double C_;
  double D_;
  double dt_;

  // Stato relativo (x_rel, y_rel)
  double x_rel_;
  double y_rel_;

  // Punti di equilibrio
  double x_eq_;
  double y_eq_;

  // Risultati assoluti: (x, y, H)
  std::vector<State> results_;

 public:
  // Costruttore
  Simulation(double A, double B, double C, double D, double x0, double y0,
             double dt)
      : A_{A}
      , B_{B}
      , C_{C}
      , D_{D}
      , dt_{dt}
      , x_eq_{D / C}
      , y_eq_{A / B}
      , x_rel_{x0 * C / D}
      , y_rel_{y0 * B / A}
      , results_{}
  {
    results_.push_back({x0, y0, compute_H(x0, y0)});
  }

  // Calcola l'integrale primo H(x, y)
  double compute_H(double x, double y) const
  {
    double H = -D_ * std::log(x) + C_ * x + B_ * y - A_ * std::log(y);
    return H;
  };

  // Esegue un passo temporale Δt
  void evolve() {};

  // Esegue più passi
  void run(int steps) {};

  // Restituisce i risultati assoluti (x, y, H)
  const std::vector<State>& get_results() const;
};

} // namespace volterra

#endif // VOLTERRA_SIMULATION_HPP
