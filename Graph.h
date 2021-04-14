/**
 * @file Graph.h
 * Definition for the Graph class and DFS algorithm
 */
#pragma once

#include <iostream>
#include <vector>
#include <iterator>
#include <string>

using namespace std;

struct Node {
    //node variables
    int ID;
    vector<struct Node*> neighbors;
    int index;

    //node constructor
    Node(int index) : index(index) {}
};

/**
 * This class contains our graph of routes for routes.dat.txt, where nodes
 * represent the airport and edges represent the routes between them. The
 * code also contains a DFS algorithm
 */

class Graph {
  public:
    Graph();
    Graph(vector<vector<int>> adjacencyMatrix);
    Graph(const Graph& other);
    Graph& operator=(const Graph& other);
    ~Graph();
    void DFS();

  private:
    void add_edge_(const int& src_node_ID, const int& dst_node_ID);
    void add_node_(const int& node_ID);
    bool contains_node_(const int& ID);
    bool check_node_exists_(const int& ID);
    int find_node_of_index_(const int& node_index);
    int find_node_of_ID_(const int& ID);

    int num_edges_;
    int num_nodes_;
    vector<struct Node*> nodes_;
};
