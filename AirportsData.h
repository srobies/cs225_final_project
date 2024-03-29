/**
 * @file AirportsData.h
 * Definition for a class to organize airport data.
 */
#pragma once

#include <list>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;
/**
 * This class is used to store airport data in a matrix and a map.
 * A few operations for retrieving data from the matrix and map
 * will be implemented.
 */
class AirportsData {
public:
  AirportsData(string airportData, string routeData);
  std::vector< std::vector<int> > getMatrix();
  std::map<std::string, std::string> getMap();
  std::string getAirportName(std::string airport_code);
  int getAirportIndex(std::string airport_code);
  string getAirportCode(int airport_idx);
  bool hasFlightBetween(string airport_src, string airport_dest);
  int numIncomingFlights(std::string airport_code);
  int numOutgoingFlights(std::string airport_code);
  int minFlightDistance(const vector<pair<int,int>>& dts, const vector<bool>& pred);
  vector<pair<int,int>> dijkstras(int source_idx);
  friend class Graph; // allow Graph class to access data of AirportsData

private:
  // adjacency matrix for storing connections between airports
  std::vector<std::vector<int> > adjacency_matrix_;

  // map for finding index in vector each airport corresponds to using airport code
  std::map<std::string, int> airport_index_;

  // map storing airport codes and their names
  std::map<std::string, std::string> airport_names_;
};
