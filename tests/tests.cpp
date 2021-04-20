#include <string>
#include <vector>
#include "../cs225/catch/catch.hpp"
#include "../AirportsData.h"
#include "../Graph.h"
using namespace std;

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

  // test for non-existant code
  std::string test4_name = test.getAirportName("ABECDEU");
  REQUIRE("Airport Does Not Exist." == test4_name);
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
  
  int INVALID_index = test.getAirportIndex("ZJA");
  REQUIRE(-1 == INVALID_index);
}

TEST_CASE("Verify that hasFlightBetween correctly returns whether there is a flight from the source to the destination.") {
  // first airport in airports.csv
  AirportsData test = AirportsData();
  bool connected1 = test.hasFlightBetween("AER", "KZN");
  REQUIRE(true == connected1);

  bool connected2 = test.hasFlightBetween("LAX", "YYZ");
  REQUIRE(true == connected2);

  bool connected3 = test.hasFlightBetween("TSA", "TTT");
  REQUIRE(true == connected3);

  bool connected4 = test.hasFlightBetween("ORD", "TTT");
  REQUIRE(false == connected4);
}

TEST_CASE("Graph test with a small adjacency matrix") {
  /* 
   * [0, 1, 0, 0]
   * [1, 0, 1, 0]
   * [0, 1, 0, 1]
   * [1, 1, 1, 0]
   */
  vector<vector<int>> test_matrix;
  // first row
  int first_row[] = {0, 1, 0, 0};
  vector<int> current_row;
  for(int i: first_row)
    current_row.push_back(i);
  test_matrix.push_back(current_row);
  // second row
  current_row.clear();
  int second_row[] = {1, 0, 1, 0};
  for(int i: second_row)
    current_row.push_back(i);
  test_matrix.push_back(current_row);
  // third row
  current_row.clear();
  int third_row[] = {0, 1, 0, 1};
  for(int i: third_row)
    current_row.push_back(i);
  test_matrix.push_back(current_row);
  // fourth row
  current_row.clear();
  int fourth_row[] = {1, 1, 1, 0};
  for(int i: fourth_row)
    current_row.push_back(i);
  test_matrix.push_back(current_row);

  Graph test_graph = Graph(test_matrix);
  const Node* first_node = test_graph.get_node_ptr(0);
  const Node* second_node = test_graph.get_node_ptr(1);
  const Node* third_node = test_graph.get_node_ptr(2);
  const Node* fourth_node = test_graph.get_node_ptr(3);
  
  auto first_node_begin = first_node->neighbors.begin();
  auto first_node_end = first_node->neighbors.end();
  auto second_node_begin = second_node->neighbors.begin();
  auto second_node_end = second_node->neighbors.end();
  auto third_node_begin = third_node->neighbors.begin();
  auto third_node_end = third_node->neighbors.end();
  auto fourth_node_begin = fourth_node->neighbors.begin();
  auto fourth_node_end = fourth_node->neighbors.end();

  // Connections
  REQUIRE(find(first_node_begin, first_node_end, second_node) != first_node_end);
  // No connections
  REQUIRE(find(first_node_begin, first_node_end, first_node) == first_node_end);
  REQUIRE(find(first_node_begin, first_node_end, third_node) == first_node_end);
  REQUIRE(find(first_node_begin, first_node_end, fourth_node) == first_node_end);
 
  // Connections
  REQUIRE(find(second_node_begin, second_node_end, first_node) != second_node_end);
  REQUIRE(find(second_node_begin, second_node_end, third_node) != second_node_end);
  // No connections
  REQUIRE(find(second_node_begin, second_node_end, second_node) == second_node_end);
  REQUIRE(find(second_node_begin, second_node_end, fourth_node) == second_node_end);

  // Connections
  REQUIRE(find(third_node_begin, third_node_end, second_node) != third_node_end);
  REQUIRE(find(third_node_begin, third_node_end, fourth_node) != third_node_end);
  // No connections
  REQUIRE(find(third_node_begin, third_node_end, first_node) == third_node_end);
  REQUIRE(find(third_node_begin, third_node_end, third_node) == third_node_end);

  // Connections
  REQUIRE(find(fourth_node_begin, fourth_node_end, first_node) != fourth_node_end);
  REQUIRE(find(fourth_node_begin, fourth_node_end, second_node) != fourth_node_end);
  REQUIRE(find(fourth_node_begin, fourth_node_end, third_node) != fourth_node_end);
  // No connections
  REQUIRE(find(fourth_node_begin, fourth_node_end, fourth_node) == fourth_node_end);
}
