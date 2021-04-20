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
  AirportsData();
  std::vector< std::vector<int> > getMatrix();
  std::map<std::string, std::string> getMap();
  std::string getAirportName(std::string airport_code);
  int getAirportIndex(std::string airport_code);
  bool hasFlightBetween(std::string airport_src, std::string airport_dest);
  int numIncomingFlights(std::string airport_code);
  int numOutgoingFlights(std::string airport_code);

private:
  // adjacency matrix for storing connections between airports
  std::vector<std::vector<int> > adjacency_matrix_;

  // map for finding index in vector each airport corresponds to using airport code
  std::map<std::string, int> airport_index_;

  // map storing airport codes and their names
  // map<airport_code, airport_name>
  std::map<std::string, std::string> airport_names_;
};
