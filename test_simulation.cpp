#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "input_utils.hpp"
#include "simulation.hpp"

#include "doctest.h"
#include <sstream>

TEST_CASE("Simulation - constructor and initialization")
{
  SUBCASE("Initial state")
  {
    double A = 0.1, B = 0.02, C = 0.01, D = 0.1;
    double x0 = 50., y0 = 20.;

    volterra::Simulation sim(A, B, C, D, x0, y0, 0.001);
    auto state0 = sim.get_results()[0];

    CHECK(state0.x == doctest::Approx(x0));
    CHECK(state0.y == doctest::Approx(y0));
  }

  SUBCASE("Initial H matches compute_H result")
  {
    volterra::Simulation sim(0.5, 0.1, 0.05, 0.2, 10., 5., .01);
    auto s0    = sim.get_results()[0];
    auto Hcalc = sim.compute_H(10., 5.);

    CHECK(s0.H == doctest::Approx(Hcalc));
  }

  SUBCASE("Parametric tests for Simulation")
  {
    struct Params
    {
      double A, B, C, D, x0, y0, dt;
      bool should_throw;
    };

    std::vector<Params> cases = {

        {0.1, 0.02, 0.01, 0.1, 50.0, 20.0, 0.001, false},
        {2.0, 1.0, 0.5, 0.4, 100.0, 80.0, 0.005, false},
        {1.0, 1.0, 1.0, 1.0, 10.0, 10.0, 0.002, false},

        {0.0, 0.02, 0.01, 0.1, 50.0, 20.0, 0.001, true},  // A non positivo
        {0.1, -0.02, 0.01, 0.1, 50.0, 20.0, 0.001, true}, // B negativo
        {0.1, 0.02, 0.0, 0.1, 50.0, 20.0, 0.001, true},   // C non positivo
        {0.1, 0.02, 0.01, -1.0, 50.0, 20.0, 0.001, true}, // D negativo
        {0.1, 0.02, 0.01, 0.1, -10.0, 20.0, 0.001, true}, // x0 negativo
        {0.1, 0.02, 0.01, 0.1, 50.0, 0.0, 0.001, true},   // y0 zero
        {0.1, 0.02, 0.01, 0.1, 50.0, 20.0, 0.0, true},    // dt zero
        {0.1, 0.02, 0.01, 0.1, 50.0, 20.0, 0.0005, true}  // dt troppo piccolo
    };

    for (auto& p : cases) {
      if (p.should_throw) {
        CHECK_THROWS(
            volterra::Simulation(p.A, p.B, p.C, p.D, p.x0, p.y0, p.dt));
      } else {
        volterra::Simulation sim(p.A, p.B, p.C, p.D, p.x0, p.y0, p.dt);
        auto results = sim.get_results();

        CHECK(results.size() == 1);
        CHECK(results[0].x == doctest::Approx(p.x0));
        CHECK(results[0].y == doctest::Approx(p.y0));
        CHECK(results[0].H == doctest::Approx(sim.compute_H(p.x0, p.y0)));
      }
    }
  }
}

TEST_CASE("Simulation - compute_H function")
{
  SUBCASE("Compute H base case")
  {
    volterra::Simulation sim(0.1, 0.02, 0.01, 0.1);

    double H1 = sim.compute_H(50., 20.);
    double H2 = sim.compute_H(30., 40.);
    double H3 = sim.compute_H(1000., 10.);

    CHECK(H1 == doctest::Approx(0.21).epsilon(0.001));
    CHECK(H2 == doctest::Approx(0.39).epsilon(0.001));
    CHECK(H3 == doctest::Approx(9.28).epsilon(0.001));
  }

  SUBCASE("Compute H high prey mortality")
  {
    volterra::Simulation sim(0.7, 3.15, 1.1, 0.4);

    double H1 = sim.compute_H(1.5, 72.);
    double H2 = sim.compute_H(13.7, 13.7);
    double H3 = sim.compute_H(0.003, 0.0002);

    CHECK(H1 == doctest::Approx(225.29).epsilon(0.001));
    CHECK(H2 == doctest::Approx(55.345).epsilon(0.001));
    CHECK(H3 == doctest::Approx(8.29).epsilon(0.001));
  }

  SUBCASE("Compute H high predator mortality")
  {
    volterra::Simulation sim(2.6, 3.3, 4.2, 7.3);

    double H1 = sim.compute_H(0.012, 35.);
    double H2 = sim.compute_H(49., 0.04);
    double H3 = sim.compute_H(100., 100.);

    CHECK(H1 == doctest::Approx(138.59).epsilon(0.001));
    CHECK(H2 == doctest::Approx(185.89).epsilon(0.001));
    CHECK(H3 == doctest::Approx(704.409).epsilon(0.001));
  }

  SUBCASE("Compute H high prey reproduction speed")
  {
    volterra::Simulation sim(15.4, 8.2, 7.7, 2.5);

    double H1 = sim.compute_H(13.5, 41.1);
    double H2 = sim.compute_H(87.6, 29.);
    double H3 = sim.compute_H(0.1, 0.1);

    CHECK(H1 == doctest::Approx(377.24).epsilon(0.001));
    CHECK(H2 == doctest::Approx(849.28).epsilon(0.001));
    CHECK(H3 == doctest::Approx(42.806).epsilon(0.001));
  }

  SUBCASE("Compute H high predator reproduction speed")
  {
    volterra::Simulation sim(5.7, 4.1, 8.9, 7.6);

    double H1 = sim.compute_H(24.2, 37.3);
    double H2 = sim.compute_H(30.4, 16.9);
    double H3 = sim.compute_H(34, 34);

    CHECK(H1 == doctest::Approx(323.47).epsilon(0.001));
    CHECK(H2 == doctest::Approx(297.78).epsilon(0.001));
    CHECK(H3 == doctest::Approx(395.099).epsilon(0.001));
  }
}

TEST_CASE("Simulation - evolution")
{
  SUBCASE("Single evolve step")
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

  SUBCASE("Run multiple steps")
  {
    volterra::Simulation sim(3.8, 2.3, 2.5, 1.2, 50.0, 60.0, 0.001);
    int steps = 100;

    size_t before = sim.get_results().size();
    sim.run(steps);
    size_t after = sim.get_results().size();

    CHECK(after == before + static_cast<size_t>(steps));
  }

  SUBCASE("Run zero steps")
  {
    volterra::Simulation sim(5.6, 0.1, 3.2, 0.05, 80.0, 120.0, 0.002);

    auto before = sim.get_results().size();
    sim.run(0);
    auto after = sim.get_results().size();

    CHECK(before == after);
  }

  SUBCASE("Run(1) equals evolve()")
  {
    volterra::Simulation sim1(2.0, 0.5, 1.75, 0.25, 100.0, 80.0, 0.001);
    volterra::Simulation sim2 = sim1; // copia iniziale

    sim1.run(1);
    sim2.evolve();

    auto r1 = sim1.get_results();
    auto r2 = sim2.get_results();

    CHECK(r1.size() == r2.size());
    CHECK(r1[1].x == doctest::Approx(r2[1].x));
    CHECK(r1[1].y == doctest::Approx(r2[1].y));
  }
}

TEST_CASE("Simulation - results consistency")
{
  SUBCASE("Results are positive")
  {
    volterra::Simulation sim(1.0, 0.2, 0.3, 0.1, 200.0, 150.0, 0.001);
    sim.run(2);

    const auto& results = sim.get_results();
    CHECK(results.size() == 3);

    auto s0 = results[0];
    auto s1 = results[1];
    auto s2 = results[2];

    CHECK(s0.x > 0);
    CHECK(s0.y > 0);
    CHECK(s1.x > 0);
    CHECK(s1.y > 0);
    CHECK(s2.x > 0);
    CHECK(s2.y > 0);
  }

  SUBCASE("H remains constant")
  {
    volterra::Simulation sim(1.0, 0.2, 0.3, 0.1, 200.0, 150.0, 0.001);
    sim.run(2);

    const auto& results = sim.get_results();
    CHECK(results.size() == 3);

    auto s0 = results[0];
    auto s1 = results[1];
    auto s2 = results[2];

    CHECK(s0.H == doctest::Approx(s1.H).epsilon(0.1));
    CHECK(s1.H == doctest::Approx(s2.H).epsilon(0.1));
    CHECK(s2.H == doctest::Approx(s0.H).epsilon(0.1));
  }

  SUBCASE("H remains constant within tight tolerance")
  {
    volterra::Simulation sim(1.0, 0.2, 0.3, 0.1, 200.0, 150.0, 0.001);
    sim.run(500);

    const auto& results = sim.get_results();
    double H0           = results[0].H;

    for (auto& state : results) {
      CHECK(state.H == doctest::Approx(H0).epsilon(0.1));
    }
  }
}

TEST_CASE("Testing read_param")
{
  SUBCASE("Valid integer input")
  {
    std::istringstream input("42\n");
    std::cin.rdbuf(input.rdbuf());
    int x = read_param<int>("Enter integer: ");
    CHECK(x == 42);
  }

  SUBCASE("Valid double input")
  {
    std::istringstream input("3.14\n");
    std::cin.rdbuf(input.rdbuf());
    double d = read_param<double>("Enter double: ");
    CHECK(d == doctest::Approx(3.14));
  }

  SUBCASE("Invalid input")
  {
    std::istringstream input("abc\n");
    std::cin.rdbuf(input.rdbuf());
    CHECK_THROWS(read_param<int>("Enter integer: "));
  }

  SUBCASE("Negative number")
  {
    std::istringstream input("-5\n");
    std::cin.rdbuf(input.rdbuf());
    int x = read_param<int>("Enter integer: ");
    CHECK(x == -5);
  }

  SUBCASE("Zero input")
  {
    std::istringstream input("0\n");
    std::cin.rdbuf(input.rdbuf());
    int x = read_param<int>("Enter integer: ");
    CHECK(x == 0);
  }
}