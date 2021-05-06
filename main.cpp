#include <iostream>
#include "AirportsData.h"
#include "Graph.h"

int main() {
  AirportsData test;
  auto matrix = test.getMatrix();
  Graph testGraph(matrix);
  testGraph.DFS(0);
  // cout << 
  int not_visited = 0;
  for(size_t i = 0; i < matrix.size(); i++) {
    if(testGraph.visited_[i] == false) {
      // std::cout << i <<": " << test.getAirportCode(i) << std::endl;
      not_visited++;
      cout << i << " " << test.getAirportCode(i) << endl;
    }
  }
  cout << testGraph.visited_.size() << endl;
  cout << not_visited << endl;
  return 0;
}
