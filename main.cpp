#include <fstream>
#include <future>
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
      << " to " << inputData.getAirportCode(i) << " is " << dijkstra[i].first 
      << " flights" << endl;
    }
  }
  outputFile << "\n";
  
  size_t increment = outputGraph.get_num_nodes() / 8;

  // async stuff
  auto thread1 = std::async(&Graph::calculateDijkstras, &outputGraph, 0, increment,
      inputData, outputGraph);
  auto thread2 = std::async(&Graph::calculateDijkstras, &outputGraph, increment, 2*increment,
      inputData, outputGraph);
  auto thread3 = std::async(&Graph::calculateDijkstras, &outputGraph, 2*increment, 3*increment,
      inputData, outputGraph);
  auto thread4 = std::async(&Graph::calculateDijkstras, &outputGraph, 3*increment, 4*increment,
      inputData, outputGraph);
  auto thread5 = std::async(&Graph::calculateDijkstras, &outputGraph, 4*increment, 5*increment,
      inputData, outputGraph);
  auto thread6 = std::async(&Graph::calculateDijkstras, &outputGraph, 5*increment, 6*increment,
      inputData, outputGraph);
  auto thread7 = std::async(&Graph::calculateDijkstras, &outputGraph, 6*increment, 7*increment,
      inputData, outputGraph);
  auto thread8 = std::async(&Graph::calculateDijkstras, &outputGraph, 7*increment, outputGraph.get_num_nodes()-1,
      inputData, outputGraph);

  thread1.wait();
  thread2.wait();
  thread3.wait();
  thread4.wait();

  auto result1 = thread1.get();
  auto result2 = thread2.get();
  auto result3 = thread3.get();
  auto result4 = thread4.get();

  vector<pair<int, int>> distances;
  distances.insert(distances.end(), result1.first.begin(), result1.first.end());
  distances.insert(distances.end(), result2.first.begin(), result2.first.end());
  distances.insert(distances.end(), result3.first.begin(), result3.first.end());
  distances.insert(distances.end(), result4.first.begin(), result4.first.end());
  vector<int> bcNodes(outputGraph.get_num_nodes(), 0);
  for (size_t i = 0; i < result1.second.size(); i++) {
    bcNodes[i] += result1.second[i];
    bcNodes[i] += result2.second[i];
    bcNodes[i] += result3.second[i];
    bcNodes[i] += result4.second[i];
  }

  auto centrality = outputGraph.GirvanNewman(inputData, distances, bcNodes);
  for(size_t i = 0; i < centrality.size(); i++) {
    outputFile << "The airport with importance " << i << " has code " << centrality[i] << endl;
  }
  outputFile.close();
  return 0;
}
