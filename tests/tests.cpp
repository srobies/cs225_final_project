#include <string>
#include <vector>
#include "../cs225/catch/catch.hpp"
#include "../AirportsData.h"
#include "../Graph.h"

TEST_CASE("Check for self-loops") {
  AirportsData test = AirportsData();
  // an entry shouldn't have a connection with itself. Unless you're PKN apparently
  auto matrix = test.getMatrix();
  for(size_t i = 0; i < matrix.size(); i++) {
    if(i != 3090)
      REQUIRE(0 == matrix[i][i]);
  }
}

TEST_CASE("Verify that getAirportName returns airport name given airport code") {
  AirportsData test = AirportsData();
  std::string name = test.getAirportName("GKA");
  REQUIRE("Goroka Airport" == name);

  std::string test2_name = test.getAirportName("MNH");
  REQUIRE("Rustaq Airport" == test2_name); 

  std::string test3_name = test.getAirportName("VHZ");
  REQUIRE("Vahitahi Airport" == test3_name);
}

TEST_CASE("Verify that getAirportIndex returns airport index given airport code") {
  // first airport in airports.csv
  AirportsData test = AirportsData();
  int GKA_index = test.getAirportIndex("GKA");
  REQUIRE(0 == GKA_index);

  // second airport in airports.csv
  int MAG_index = test.getAirportIndex("MAG");
  REQUIRE(1 == MAG_index);

  int YAM_index = test.getAirportIndex("YAM");
  REQUIRE(20 == YAM_index);
}
