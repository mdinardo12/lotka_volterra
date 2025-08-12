#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "simulation.hpp"

#include "doctest.h"

TEST_CASE("Testing Simulation")
{
  SUBCASE("Testing initial state")
  {
    double A = 0.1, B = 0.02, C = 0.01, D = 0.1;
    double x0 = 50., y0 = 20.;

    volterra::Simulation sim(A, B, C, D, x0, y0, 0.001);
    auto state0 = sim.get_results()[0];

    CHECK(state0.x == doctest::Approx(x0));
    CHECK(state0.y == doctest::Approx(y0));
  }

  SUBCASE("Testing H computing ")
  {
    volterra::Simulation sim(0.1, 0.02, 0.01, 0.1, 50., 20., 0.001);

    double H1 = sim.compute_H(50., 20.);
    double H2 = sim.compute_H(30., 40.);
    double H3 = sim.compute_H(1000., 10.);

    CHECK(H1 == doctest::Approx(0.21).epsilon(0.001));
    CHECK(H2 == doctest::Approx(0.39).epsilon(0.001));
    CHECK(H3 == doctest::Approx(9.28).epsilon(0.001));
  }

  SUBCASE("Testing H computing high prey mortality ")
  {
    volterra::Simulation sim(0.7, 3.15, 1.1, 0.4, 50., 20., 0.001);

    double H1 = sim.compute_H(1.5, 72.);
    double H2 = sim.compute_H(13.7, 13.7);
    double H3 = sim.compute_H(0.003, 0.0002);

    CHECK(H1 == doctest::Approx(81.93).epsilon(0.001));
    CHECK(H2 == doctest::Approx(55.345).epsilon(0.001));
    CHECK(H3 == doctest::Approx(7.483).epsilon(0.001));
  }

  SUBCASE("Testing H computing high predator mortality ")
  {
    volterra::Simulation sim(2.6, 3.3, 4.2, 7.3, 50., 20., 0.001);

    double H1 = sim.compute_H(0.012, 35.);
    double H2 = sim.compute_H(49., 0.04);
    double H3 = sim.compute_H(100., 100.);

    CHECK(H1 == doctest::Approx(132.585).epsilon(0.001));
    CHECK(H2 == doctest::Approx(175.247).epsilon(0.001));
    CHECK(H3 == doctest::Approx(704.409).epsilon(0.001));
  }

  SUBCASE("Testing H computing high prey reproduction speed")
  {
    volterra::Simulation sim(15.4, 8.2, 7.7, 2.5, 50., 20., 0.001);

    double H1 = sim.compute_H(13.5, 41.1);
    double H2 = sim.compute_H(87.6, 29.);
    double H3 = sim.compute_H(0.1, 0.1);

    CHECK(H1 == doctest::Approx(377.799).epsilon(0.001));
    CHECK(H2 == doctest::Approx(864.321).epsilon(0.001));
    CHECK(H3 == doctest::Approx(42.806).epsilon(0.001));
  }

  SUBCASE("Testing H computing high predator reproduction speed")
  {
    volterra::Simulation sim(5.7, 4.1, 8.9, 7.6, 50., 20., 0.001);

    double H1 = sim.compute_H(24.2, 37.3);
    double H2 = sim.compute_H(30.4, 16.9);
    double H3 = sim.compute_H(34, 34);

    CHECK(H1 == doctest::Approx(385.523).epsilon(0.001));
    CHECK(H2 == doctest::Approx(234.100).epsilon(0.001));
    CHECK(H3 == doctest::Approx(395.099).epsilon(0.001));
  }

  SUBCASE("Simulation with non positive parameters") // non penso abbia senso fare questo test perchè il programma si ferma prima
  {
    CHECK_THROWS(volterra::Simulation(0.2, 0.05, -0.02, 0.3, 30., 100., 0.001));
    CHECK_THROWS(volterra::Simulation(0.2, 0.01, 0.02, 0.3, 0., 100., 0.001));
  }

  SUBCASE("Simulation with dt less than 0.001") // stessa cosa del per il punto prima
  {
    CHECK_THROWS(volterra::Simulation(0.2, 0.05, 0.02, 0.3, 30., 100., 0.0001));
  }

  {
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
}