#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

#include "AirportsData.h"

using namespace std;

/**
 * Constructs a new adjacency matrix and map to hold airport data.
 * 
 */
AirportsData::AirportsData() {
  // maps each airport code to an index & map each airport code to airport name
  ifstream file_airports;
  file_airports.open("data/airports.csv");
  string line_airports;
  // stores number of lines
  int line_num = 0;
  while (getline(file_airports,line_airports)) {
    vector<string> result;
    stringstream stream(line_airports);
    while (stream.good()) {
      string substring;
      getline(stream,substring,',');
      result.push_back(substring);
    }
    string code = result[4]; // using 3 letter IATA codes
    string name = result[1];
    // throw entries out if code or name are null
    if(code.find("\\N") == string::npos && name.find("\\N") == string::npos) {
    // Need to handle quotes from data file
      code = code.substr(1, code.size()-2);
      name = name.substr(1, name.size()-2);
      airport_index_.insert(pair<string, int>(code,line_num));
      airport_names_.insert(pair<string, string>(code,name));
      line_num++;
    }
  }
  file_airports.close();

  // at this point, line_num is one bigger than what it should be
  // line_num -= 1;

  // construct adjacency matrix but do not fill yet
  vector<vector<int> > vec(line_num, vector<int>(line_num, 0));

  // store matrix of 0s in adjacency_matrix_
  adjacency_matrix_ = vec;

  ifstream file_routes;
  file_routes.open("data/routes.csv");
  string line_routes;
  while (getline(file_routes,line_routes)) {
    vector<string> result;
    stringstream stream(line_routes);
    while (stream.good()) {
      string substring;
      getline(stream,substring,',');
      result.push_back(substring);
    }
    string start = result[2]; // using 3 letter IATA codes
    string end = result[4];
    int index_start = getAirportIndex(start);
    int index_end = getAirportIndex(end);
    if(index_start == -1 || index_end == -1) { continue; }
    adjacency_matrix_[index_start][index_end] = 1;
  }
  file_routes.close();
}

std::vector< std::vector<int> > AirportsData::getMatrix() {
  return adjacency_matrix_;
}
std::map<std::string, std::string> AirportsData::getMap() {
  return airport_names_;
}

/**
 * Gets the name of an airport using the airport code
 * 
 * @param airport_code The string representing the airport code.
 */
std::string AirportsData::getAirportName(std::string airport_code) {
  // iterate through the map
  // if key not in map, return "Airport Does Not Exist."
  if (airport_names_.find(airport_code) == airport_names_.end()) {
    return "Airport Does Not Exist.";
  } else {
    // if key is in the map, return the name of the aiport
    return airport_names_.at(airport_code);
  }
}

/**
 * Gets the index of the airport in adjacency matrix using the airport code
 * 
 * @param airport_code The string representing the airport code.
 */
int AirportsData::getAirportIndex(std::string airport_code) {
  // iterate through the map
  // if key not in map, return -1
  if (airport_index_.find(airport_code) == airport_index_.end()) {
    return -1;
  } else {
    // if key is in the map, return the index of the aiport
    return airport_index_.at(airport_code);
  }
}

/**
 * Check if an airport has a connection to another airport.
 * 
 * @param airport_src The string representing the source airport code.
 * @param airport_dest The string representing the destination airport code.
 * @return Whether or not there is a flight from the source airport to the destination airport.
 */
bool AirportsData::hasFlightBetween(std::string airport_src, std::string airport_dest) {
  int source = getAirportIndex(airport_src);
  int dest = getAirportIndex(airport_dest);
  if(adjacency_matrix_[source][dest] == 1) {
    return true;
  } else {
    return false;
  }
}
