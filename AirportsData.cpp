#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>
#include <set>

#include "AirportsData.h"

using namespace std;

/**
 * Constructs a new adjacency matrix and map to hold airport data.
 */
AirportsData::AirportsData() {
  // maps each airport code to an index & map each airport code to airport name
  ifstream file_airports;
  file_airports.open("data/airports.csv");
  string line_airports;
  set<string> airport_codes; // Set of all airport codes from airports.csv
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
    if(code.find("\\N") == string::npos && name.find("\\N") == string::npos && code.size() == 5) {
    // Need to handle quotes from data file
      code = code.substr(1, code.size()-2);
      name = name.substr(1, name.size()-2);
      airport_names_.insert(pair<string, string>(code,name));
      airport_codes.insert(code);
    }
  }
  file_airports.close();

  ifstream file_routes;
  file_routes.open("data/routes.csv");
  string line_routes;

  map<string, set<string>> routes;
  set<string> sources_and_destinations;
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
    sources_and_destinations.insert(start);
    sources_and_destinations.insert(end);
    routes[start].insert(end);
  }
  file_routes.close();


  set<string> route_intersection; // Find the intersection of airports between routes.csv and airports.csv
  set_intersection(sources_and_destinations.begin(), sources_and_destinations.end(),
    airport_codes.begin(), airport_codes.end(), inserter(route_intersection, route_intersection.begin()));
  // Only use codes that are both in routes.csv and airports.csv for adjacency matrix

  int index = 0;
  for(auto it = route_intersection.begin(); it != route_intersection.end(); ++it) {
    airport_index_.insert(pair<string, int>(*it,index));
    index++;
  }
  // construct adjacency matrix but do not fill yet
  vector<vector<int> > vec(route_intersection.size(), vector<int>(route_intersection.size(), 0));

  // store matrix of 0s in adjacency_matrix_
  adjacency_matrix_ = vec;
  for(auto startAirport = route_intersection.begin(); startAirport != route_intersection.end(); ++startAirport) { // each airport in intersection dataset
    int index_start = getAirportIndex(*startAirport);
    if(routes.find(*startAirport) != routes.end()) {
      for(auto endAirport = routes.find(*startAirport)->second.begin(); endAirport != routes.find(*startAirport)->second.end(); ++endAirport) { // each airport route
        int index_end = getAirportIndex(*endAirport);
        if(index_start != -1 && index_end != -1)
          adjacency_matrix_[index_start][index_end] = 1;
      }
    }
  }
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
 * Gets the 3 letter code of the airport in adjacency matrix using index
 *
 * @param airport_idx The number representing the airport index.
 */
string AirportsData::getAirportCode(int airport_idx) {
  // iterate through the map
  for (auto& entry : airport_index_) {
    if (entry.second == airport_idx) {
      return entry.first;
    }
  }
  return "Not a Valid Airport Index.";
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

/**
 * Count the number of incoming flights at an airport.
 *
 * @param airport_code The code of the airport to count incoming flights for.
 * @return The number of incoming flights at that airport.
 */
int AirportsData::numIncomingFlights(std::string airport_code) {
  int num_flights = 0;
  int size_airports = adjacency_matrix_[0].size();
  int idx = getAirportIndex(airport_code);

  for (int i = 0; i < size_airports; i++) {
    if (adjacency_matrix_[i][idx]) {
      num_flights++;
    }
  }

  return num_flights;
}

/**
 * Count the number of outgoing flights at an airport.
 *
 * @param airport_code The code of the airport to count outgoing flights for.
 * @return The number of outgoing flights at that airport.
 */
int AirportsData::numOutgoingFlights(std::string airport_code) {
  int num_flights = 0;
  int size_airports = adjacency_matrix_[0].size();
  int idx = getAirportIndex(airport_code);

  for (int i = 0; i < size_airports; i++) {
    if (adjacency_matrix_[idx][i]) {
      num_flights++;
    }
  }

  return num_flights;
}

/**
 * Dijkstra's Algorithm
 * @param source_idx the index of the node that is the source
 */
vector<pair<int,int>> AirportsData::dijkstras(int source_idx) {
  // the number of airports in the graph
  int size_airports = adjacency_matrix_[0].size();

  // create vector to store distance to each node.
  // First index is distance. Second index is parent. If no parent, then at source node
  vector<pair<int,int>> dist_to_source(size_airports, pair<int,int>(INT_MAX, -1));

  // create predecessor vector. Set all predecessors to NULL
  vector<bool> predecessor(size_airports, false);

  // distance from source node to source node is 0
  dist_to_source[source_idx].first = 0;

  // find shortest path for all vertices
  for (int count = 0; count < size_airports; count++) {
    // pick minimum from airports not included
    int min = minFlightDistance(dist_to_source, predecessor);

    // Mark this airport as having shortest distance updated
    predecessor[min] = true;

    // Update distance value of the adjacent airports to chosen airport
    for (int i = 0; i < size_airports; i++) {
      // if airport not in predecessor set, and there is a connection,
      // total distance is distance to previous airport plus distance to new one
      if (!predecessor[i]) {
        // check if there is flight from previous to next in adjacency matrix
        if (adjacency_matrix_[min][i] == 1) {
          // make sure distance isnt maximum distance
          if (dist_to_source[min].first != INT_MAX) {
            // check adding new distance is less than distance to this one
            if ((dist_to_source[min].first + adjacency_matrix_[min][i]) < dist_to_source[i].first) {
              // add 1 flight to the distance
              dist_to_source[i].first = dist_to_source[min].first + 1;
              // add the parent node
              dist_to_source[i].second = min;
            }
          }
        }
      }
    }
  }
  return dist_to_source;
}

int AirportsData::minFlightDistance(const vector<pair<int,int>>& dts, const vector<bool>& pred) {
  // initialize a minimum
  int min = INT_MAX;
  int min_index = -50;

  int size_airports = adjacency_matrix_[0].size();

  for (int i = 0; i < size_airports; i++) {
    // if the airport is not already connected
    if (pred[i] == false) {
      // if the distance is less than or equal to the min
      if (dts[i].first <= min) {
        min = dts[i].first;
        min_index = i;
      }
    }
  }
  return min_index;
}
