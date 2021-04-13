#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

#include "AirportsData.h"

using namespace std;

/**
 * Constructs a new adjacency matrix and map to hold airport data.
 * 
 */
AirportsData::AirportsData() {
  // maps each airport code to an index & map each airport code to airport name
  ifstream file_airports;
  file_airports.open("airports.dat.txt");
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
    string code_ = result[4];
    string name_ = result[1];
    airport_index.insert(pair<string, int>(code_,line_num));
    airport_names.insert(pair<string, string>(code_,name_));
    line_num++;
  }
  file_airports.close();

  // at this point, line_num is one bigger than what it should be
  int line_num1 = line_num - 1;

  // construct adjacency matrix but do not fill yet
  vector<vector<int> > vec(line_num1, vector<int>(line_num1, 0));

  // store matrix of 0s in adjacency_matrix
  adjacency_matrix = vec;

  ifstream file_routes;
  file_routes.open("routes.dat.txt");
  string line_routes;
  while (getline(file_routes,line_routes)) {
    vector<string> result;
    stringstream stream(line_routes);
    while (stream.good()) {
      string substring;
      getline(stream,substring,',');
      result.push_back(substring);
    }
    string start_ = result[2];
    string end_ = result[4];
    int index_start = airport_index[start_];
    int index_end = airport_index[end_];

    adjacency_matrix[index_start][index_end] = 1;
  }
  file_routes.close();
}

std::vector< std::vector<int> > AirportsData::getMatrix() {
  return adjacency_matrix;
}
std::map<std::string, std::string> AirportsData::getMap() {
  return airport_names;
}

/**
 * Gets the name of an airport using the airport code
 * 
 * @param airport_code The string representing the airport code.
 */
std::string AirportsData::getAirportName(std::string airport_code) {
  // iterate through the map
  // if key not in map, return "Airport Does Not Exist."
  if (airport_names.find(airport_code) == airport_names.end()) {
    return "Airport Does Not Exist.";
  } else {
    // if key is in the map, return the name of the aiport
    return airport_names.at(airport_code);
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
  if (airport_index.find(airport_code) == airport_index.end()) {
    return -1;
  } else {
    // if key is in the map, return the index of the aiport
    return airport_index.at(airport_code);
  }
}