#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "simulation.hpp"

#include "doctest.h"

TEST_CASE("Testing Simulation")
{
  SUBCASE("Testing initial state")
  {
    double A = 0.1, B = 0.02, C = 0.01, D = 0.1;
    double x0 = 50, y0 = 20;

    volterra::Simulation sim(A, B, C, D, x0, y0, 0.001);
    auto state0 = sim.get_results()[0];

    CHECK(state0.x == doctest::Approx(x0));
    CHECK(state0.y == doctest::Approx(y0));
  }

  SUBCASE("Testing H computing")
  {
    volterra::Simulation sim(0.1, 0.02, 0.01, 0.1, 50., 20., 0.001);

    double H1 = sim.compute_H(50., 20.);
    double H2 = sim.compute_H(30., 40.);
    double H3 = sim.compute_H(1000., 10.);

    CHECK(H1 == doctest::Approx(0.21).epsilon(0.001));
    CHECK(H2 == doctest::Approx(0.39).epsilon(0.001));
    CHECK(H3 == doctest::Approx(0.99).epsilon(0.001));
  }

  SUBCASE("Simulation with non positive parameters")
  {
    CHECK_THROWS(volterra::Simulation(0.2, 0.05, -0.02, 0.3, 30., 100., 0.001));
    CHECK_THROWS(volterra::Simulation(0.2, 0.01, 0.02, 0.3, 0., 100., 0.001));
  }

  SUBCASE("")
  {}
  SUBCASE("")
  {}
  SUBCASE("")
  {}
  SUBCASE("")
  {}
  SUBCASE("")
  {}
  SUBCASE("")
  {}
}