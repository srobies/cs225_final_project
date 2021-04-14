/**
 * @file Graph.h
 * Definition for the Graph class and DFS algorithm
 */
#pragma once

#include<iostream>
#include <vector>
#include <iterator>
#include <string>

struct Node {
    //node variables
    int ID;
    vector<struct Node*> neighbors;

    //node constructor
    Node(int index) : idx(index) {}
}

using namespace std;
/**
 * This class contains our graph of routes for routes.dat.txt, where nodes
 * represent the airport and edges represent the routes between them. The
 * code also contains a DFS algorithm
 */

 Graph {
 public:
    Graph(vector<vector<int>> adjacencyMatrix);
    void DFS();

   

 private:
    void add_edge_(const int& src_node_ID, const int& dst_node_ID);
    void add_node_(const int& node_ID);
    bool contains_node_(const int& ID);
    bool check_node_exists_(const int& ID);
    int find_node_of_index_(const int& ID);

    int num_edges_;
    int num_nodes_;
    vector<struct Node*> nodes_;
}