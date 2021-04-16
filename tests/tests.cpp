#include <string>
#include <vector>
#include "../cs225/catch/catch.hpp"
#include "../AirportsData.h"

TEST_CASE("Verify contents of adjacency matrix") {
  AirportsData *test = new AirportsData();
  // print contents of adjacency matrix, but only the first entry is a 1 and everything else is 0
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      std::cout << test->getMatrix()[i][j] << endl;
    }
  }
  // an entry should have a connection with itself
  REQUIRE(1 == getMatrix()[1][1]);
}

TEST_CASE("Verify that getAirportName returns airport name given airport code") {
  AirportsData *test = new AirportsData();
  std::string name = test->getAirportName("GKA");
  REQUIRE("Goroka Airport" == name);
}

TEST_CASE("Verify that getAirportIndex returns airport index given airport code") {
  AirportsData *test = new AirportsData();
  // first airport in airports.csv
  int GKA_index = test->getAirportIndex("GKA");
  REQUIRE(0 == GKA_index);

  // second airport in airports.csv
  int MAG_index = test->getAirportIndex("MAG");
  REQUIRE(1 == MAG_index);
}
