#include <cstddef>
#include <string>
#include <vector>
#include "../cs225/catch/catch.hpp"
#include "../AirportsData.h"
#include "../Graph.h"
using namespace std;

TEST_CASE("Check for self-loops") {
  AirportsData test = AirportsData("data/airports.csv", "data/routes.csv");
  // an entry shouldn't have a connection with itself. Unless you're PKN apparently
  auto matrix = test.getMatrix();
  int PKN_index = test.getAirportIndex("PKN");
  for(size_t i = 0; i < matrix.size(); i++) {
    if(i != (size_t)PKN_index)
      REQUIRE(0 == matrix[i][i]);
  }
}

TEST_CASE("Verify that getAirportName returns airport name given airport code") {
  AirportsData test = AirportsData("data/airports.csv", "data/routes.csv");
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
  // Airports are inserted in alphabetical order
  AirportsData test = AirportsData("data/airports.csv", "data/routes.csv");
  int AAE_index = test.getAirportIndex("AAE");
  REQUIRE(0 == AAE_index);

  // second airport in airports.csv
  int MAG_index = test.getAirportIndex("MAG");
  REQUIRE(1663 == MAG_index);

  int YAM_index = test.getAirportIndex("YAM");
  REQUIRE(3005 == YAM_index);

  int INVALID_index = test.getAirportIndex("ZJA");
  REQUIRE(-1 == INVALID_index);
}

TEST_CASE("Verify that hasFlightBetween correctly returns whether there is a flight from the source to the destination.") {
  // first airport in airports.csv
  AirportsData test = AirportsData("data/airports.csv", "data/routes.csv");
  int AER_index = test.getAirportIndex("AER");
  int KZN_index = test.getAirportIndex("KZN");
  bool connected1 = test.hasFlightBetween("AER", "KZN");
  REQUIRE(true == connected1);

  int LAX_index = test.getAirportIndex("LAX");
  int YYZ_index = test.getAirportIndex("YYZ");
  bool connected2 = test.hasFlightBetween("LAX", "YYZ");
  REQUIRE(true == connected2);

  int TSA_index = test.getAirportIndex("TSA");
  int TTT_index = test.getAirportIndex("TTT");
  bool connected3 = test.hasFlightBetween("TSA", "TTT");
  REQUIRE(true == connected3);

  int ORD_index = test.getAirportIndex("ORD");
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

  auto first_node_begin = first_node->dest_nodes.begin();
  auto first_node_end = first_node->dest_nodes.end();
  auto second_node_begin = second_node->dest_nodes.begin();
  auto second_node_end = second_node->dest_nodes.end();
  auto third_node_begin = third_node->dest_nodes.begin();
  auto third_node_end = third_node->dest_nodes.end();
  auto fourth_node_begin = fourth_node->dest_nodes.begin();
  auto fourth_node_end = fourth_node->dest_nodes.end();

  const int numNodes = test_graph.get_num_nodes();
  const int numEdges = test_graph.get_num_edges();

  //Number of nodes and edges
  REQUIRE(numNodes == 4);
  REQUIRE(numEdges == 8);
  // Connections
  // Connections for dst_nodes
  REQUIRE(find(first_node_begin, first_node_end, second_node) != first_node_end);
  // No connections
  REQUIRE(find(first_node_begin, first_node_end, first_node) == first_node_end);
  REQUIRE(find(first_node_begin, first_node_end, third_node) == first_node_end);
  REQUIRE(find(first_node_begin, first_node_end, fourth_node) == first_node_end);

  // Connections for dst_nodes
  REQUIRE(find(second_node_begin, second_node_end, first_node) != second_node_end);
  REQUIRE(find(second_node_begin, second_node_end, third_node) != second_node_end);
  // No connections
  REQUIRE(find(second_node_begin, second_node_end, second_node) == second_node_end);
  REQUIRE(find(second_node_begin, second_node_end, fourth_node) == second_node_end);

  // Connections for dst_nodes
  REQUIRE(find(third_node_begin, third_node_end, second_node) != third_node_end);
  REQUIRE(find(third_node_begin, third_node_end, fourth_node) != third_node_end);
  // No connections
  REQUIRE(find(third_node_begin, third_node_end, first_node) == third_node_end);
  REQUIRE(find(third_node_begin, third_node_end, third_node) == third_node_end);

  // Connections for dst_nodes
  REQUIRE(find(fourth_node_begin, fourth_node_end, first_node) != fourth_node_end);
  REQUIRE(find(fourth_node_begin, fourth_node_end, second_node) != fourth_node_end);
  REQUIRE(find(fourth_node_begin, fourth_node_end, third_node) != fourth_node_end);
  // No connections
  REQUIRE(find(fourth_node_begin, fourth_node_end, fourth_node) == fourth_node_end);

  first_node_begin = first_node->src_nodes.begin();
  first_node_end = first_node->src_nodes.end();
  second_node_begin = second_node->src_nodes.begin();
  second_node_end = second_node->src_nodes.end();
  third_node_begin = third_node->src_nodes.begin();
  third_node_end = third_node->src_nodes.end();
  fourth_node_begin = fourth_node->src_nodes.begin();
  fourth_node_end = fourth_node->src_nodes.end();
  
  // Connections for src_nodes
  REQUIRE(find(first_node_begin, first_node_end, second_node) != first_node_end);
  REQUIRE(find(first_node_begin, first_node_end, fourth_node) != first_node_end);
  // No connections
  REQUIRE(find(first_node_begin, first_node_end, first_node) == first_node_end);
  REQUIRE(find(first_node_begin, first_node_end, third_node) == first_node_end);

  // Connections for src_nodes
  REQUIRE(find(second_node_begin, second_node_end, first_node) != second_node_end);
  REQUIRE(find(second_node_begin, second_node_end, third_node) != second_node_end);
  REQUIRE(find(second_node_begin, second_node_end, fourth_node) != second_node_end);
  // No connections
  REQUIRE(find(second_node_begin, second_node_end, second_node) == second_node_end);

  // Connections for src_nodes
  REQUIRE(find(third_node_begin, third_node_end, second_node) != third_node_end);
  REQUIRE(find(third_node_begin, third_node_end, fourth_node) != third_node_end);
  // No connections
  REQUIRE(find(third_node_begin, third_node_end, first_node) == third_node_end);
  REQUIRE(find(third_node_begin, third_node_end, third_node) == third_node_end);

  // Connections for src_nodes
  REQUIRE(find(fourth_node_begin, fourth_node_end, third_node) != fourth_node_end);
  // No connections
  REQUIRE(find(fourth_node_begin, fourth_node_end, first_node) == fourth_node_end);
  REQUIRE(find(fourth_node_begin, fourth_node_end, second_node) == fourth_node_end);
  REQUIRE(find(fourth_node_begin, fourth_node_end, fourth_node) == fourth_node_end);

}

TEST_CASE("DFS test on graph") {
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

  // make graph from adjacency matrix
  Graph test_graph = Graph(test_matrix);

  // run DFS on test_graph starting with the node with ID 1
  // currently prints out 1 1 2 3 0, need to find bug that's printing the starting node twice
  test_graph.DFS(1);
  int airport_count = test_graph.getNumberAirports();
  for(int i = 0; i < airport_count; i++) {
    REQUIRE(test_graph.checkVisited(i) == true);
  }
}

TEST_CASE("DFS test with full dataset") {
  AirportsData test = AirportsData("data/airports.csv", "data/routes.csv");
  auto matrix = test.getMatrix();
  Graph test_graph = Graph(matrix);
  test_graph.DFS(0);

  int nodes_visited = 0;
  int airport_count = test_graph.getNumberAirports();
  for(int i = 0; i < airport_count; i++) {
    if(test_graph.checkVisited(i) == true)
      nodes_visited++;
  }
  REQUIRE(nodes_visited == test_graph.getNumberAirports());
}

TEST_CASE("Dijkstra's Algorithm Test 1") {
  AirportsData test = AirportsData("data/airports.csv", "data/routes.csv");
  int GKA_index = test.getAirportIndex("GKA");
  vector<pair<int,int>> dijkstras_goroka = test.dijkstras(GKA_index);

  // the shortest path between the source and itself is 0
  REQUIRE(dijkstras_goroka[GKA_index].first == 0);

  // shortest path between GKA and LAE is 1 flight
  int test_lae = test.getAirportIndex("LAE");
  REQUIRE(dijkstras_goroka[test_lae].first == 1);

  // shortest path between GKA and POM is 1 flight
  int test_pom = test.getAirportIndex("POM");
  REQUIRE(dijkstras_goroka[test_pom].first == 1);
}

TEST_CASE("Dijkstra's Algorithm Test 2") {
  AirportsData test = AirportsData("data/airports.csv", "data/routes.csv");
  int ohare_idx = test.getAirportIndex("ORD");
  vector<pair<int,int>> dijkstras_ohare = test.dijkstras(ohare_idx);

  // the shortest path between the source and itself is 0
  REQUIRE(dijkstras_ohare[ohare_idx].first == 0);

  // shortest path between ORD and ATL is 1 flight
  int test_atl = test.getAirportIndex("ATL");
  REQUIRE(dijkstras_ohare[test_atl].first == 1);

  // shortest path between ORD and JFK is 1 flight
  int test_jfk = test.getAirportIndex("JFK");
  REQUIRE(dijkstras_ohare[test_jfk].first == 1);
}

TEST_CASE("Dijkstra's Algorithm Test 3") {
  AirportsData test = AirportsData("data/airports.csv", "data/routes.csv");
  int champaign_idx = test.getAirportIndex("CMI");
  vector<pair<int,int>> dijkstras_champaign = test.dijkstras(champaign_idx);

  // the shortest path between the source and itself is 0
  REQUIRE(dijkstras_champaign[champaign_idx].first == 0);

  // shortest path between CMI and ORD is 1 flight
  int test_ord = test.getAirportIndex("ORD");
  REQUIRE(dijkstras_champaign[test_ord].first == 1);

  // shortest path between CMI and AZO is 2 flights
  int test_azo = test.getAirportIndex("AZO");
  REQUIRE(dijkstras_champaign[test_azo].first == 2);

  // shortest path between CMI and YYZ is 2 flights
  int test_yyz = test.getAirportIndex("YYZ");
  REQUIRE(dijkstras_champaign[test_yyz].first == 2);
}

TEST_CASE("Betweenness centrality test") {
  AirportsData test = AirportsData("data/testairports.csv", "data/testroutes.csv");
  auto matrix = test.getMatrix();
  Graph testGraph = Graph(matrix);

  auto testBetweenness = testGraph.GirvanNewman(test);
  cout << testBetweenness.size() << endl;
  REQUIRE(testBetweenness[0] == "DDD");
  REQUIRE(testBetweenness[1] == "BBB");
  REQUIRE(testBetweenness[2] == "CCC");
  REQUIRE(testBetweenness[3] == "AAA");
}
