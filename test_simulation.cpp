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

  SUBCASE("Simulation with non positive parameters")
  {
    CHECK_THROWS(volterra::Simulation(0.2, 0.05, -0.02, 0.3, 30., 100., 0.001));
    CHECK_THROWS(volterra::Simulation(0.2, 0.01, 0.02, 0.3, 0., 100., 0.001));
  }

  SUBCASE("Simulation with dt less than 0.001")
  {
    CHECK_THROWS(volterra::Simulation(0.2, 0.05, 0.02, 0.3, 30., 100., 0.0001));
  }

  SUBCASE("Testing evolve")
  {
    volterra::Simulation sim(1.0, 0.5, 0.75, 0.25, 100.0, 80.0, 0.001);

    CHECK(sim.get_results().size() == 1);

    sim.evolve();
    auto next = sim.get_results()[1];

    CHECK(next.x > 0);
    CHECK(next.y > 0);

    CHECK(next.x == doctest::Approx(103.9).epsilon(0.1));
    CHECK(next.y == doctest::Approx(86.0).epsilon(0.1));
  }

  SUBCASE("Testing run - multiple evolution")
  {
    volterra::Simulation sim(0.8, 0.3, 0.5, 0.2, 50.0, 60.0, 0.001);
    int steps = 100;

    size_t before = sim.get_results().size();
    sim.run(steps);
    size_t after = sim.get_results().size();

    CHECK(after == before + static_cast<size_t>(steps));
  }

  SUBCASE("run(0) does not change the result")
  {
    volterra::Simulation sim(0.6, 0.1, 0.2, 0.05, 80.0, 120.0, 0.002);

    auto before = sim.get_results().size();
    sim.run(0);
    auto after = sim.get_results().size();

    CHECK(before == after);
  }

  SUBCASE("get_results returns consistent absolute states")
  {
    volterra::Simulation sim(1.0, 0.2, 0.3, 0.1, 200.0, 150.0, 0.001);
    sim.run(2);

    const auto& results = sim.get_results();
    CHECK(results.size() == 3);

    auto s0 = results[0];
    auto s1 = results[1];
    auto s2 = results[2];

    // Tutti i valori devono essere positivi
    CHECK(s0.x > 0);
    CHECK(s0.y > 0);
    CHECK(s1.x > 0);
    CHECK(s1.y > 0);
    CHECK(s2.x > 0);
    CHECK(s2.y > 0);
  }

  SUBCASE("Testing H being costant")
  {
    volterra::Simulation sim(1.0, 0.2, 0.3, 0.1, 200.0, 150.0, 0.001);
    sim.run(2);

    const auto& results = sim.get_results();
    CHECK(results.size() == 3);

    auto s0 = results[0];
    auto s1 = results[1];
    auto s2 = results[2];

    CHECK(s0.H == doctest::Approx(s1.H).epsilon(0.01));
    CHECK(s1.H == doctest::Approx(s2.H).epsilon(0.01));
    CHECK(s2.H == doctest::Approx(s0.H).epsilon(0.01));
  }
}