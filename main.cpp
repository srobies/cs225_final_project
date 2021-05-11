#include <fstream>
#include <iostream>
#include <string>
#include <climits>
#include "AirportsData.h"
#include "Graph.h"

int main(int argc, char* argv[]) {
  // Format for cmdline to run
  if(argc != 5) {
    cout << "Please input the correct number of arguments" << endl;
    return 0;
  }
  // ./main airports_csv routes_csv dijkstra_startpoint output_file
  AirportsData inputData(argv[1], argv[2]);
  auto matrix = inputData.getMatrix();
  Graph outputGraph(matrix);
  auto visitOrder = outputGraph.DFS(0);

  // Write to an output file
  ofstream outputFile;
  outputFile.open(argv[4]);
  // Print the dfs output
  for(size_t i = 0; i < visitOrder.size(); i++) {
    outputFile << "Airport with ID: " << visitOrder[i] << " and code: "
      << inputData.getAirportCode(visitOrder[i]) << " visited\n";
  }
  outputFile << "\n";

  // Print an example Dijkstra's
  int index = stoi(argv[3]);
  auto dijkstra = inputData.dijkstras(index);
  for(size_t i = 0; i < dijkstra.size(); i++) {
    if(dijkstra[i].first == INT_MAX) {
    outputFile << "There is no path from " << inputData.getAirportCode(index)
      << " to " << inputData.getAirportCode(i) << endl;
    }
    else {
    outputFile << "The shortest path from " << inputData.getAirportCode(index)
      << " to " << inputData.getAirportCode(i) << " is " << dijkstra[i].first << endl;
    }
  }
  outputFile << "\n";

  auto centrality = outputGraph.GirvanNewman(inputData);
  for(size_t i = 0; i < centrality.size(); i++) {
    outputFile << "The airport with importance " << i << " has code " << centrality[i] << endl;
  }
  outputFile.close();
  return 0;
}
