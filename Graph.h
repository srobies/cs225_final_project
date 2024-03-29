/**
 * @file Graph.h
 * Definition for the Graph class and DFS algorithm
 */
#pragma once

#include "AirportsData.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <stack>
#include <set>

using namespace std;

struct Node {
    //node variables
    int ID; // row index in adjacency matrix. Can be used to identify node
    set<struct Node*> dest_nodes; // marks outgoing flights as neighbors
    set<struct Node*> src_nodes; // mark incoming flights as neighbors
    // incoming flights not marked
    int index; // index in nodes_ private variable

    //node constructor
    Node(int index) : ID(index) {}
};

/**
 * This class contains our graph of routes for routes.dat.txt, where nodes
 * represent the airport and edges represent the routes between them. The
 * code also contains a DFS algorithm
 */

class Graph {
  public:
    Graph();
    Graph(vector<vector<int> > adjacencyMatrix);
    Graph(const Graph& other);
    Graph& operator=(const Graph& other);
    ~Graph();
    Node* get_node_ptr(const int& node_ID);
    vector<struct Node*>& getNodes();
    int get_num_nodes();
    int get_num_edges();
    vector<int> DFS(int start_node_ID);
    bool checkVisited(const int node_ID);
    pair<vector<pair<int,int>>,vector<int>> calculateDijkstras(size_t starting_node, size_t ending_node,
        AirportsData ap, Graph refGraph);
    int getNumberAirports();
    vector<string> GirvanNewman(AirportsData& ap, vector<pair<int, int>>& distances, vector<int>& bcNodes);

    class Iterator : std::iterator<std::forward_iterator_tag, Node> {
      public:
        Iterator();

        Iterator & operator++();
        Node* operator*();
        bool operator!=(const Iterator &other);
        Iterator(Graph* graph, int startID);

      private:
        Graph* graph_;
        int currentNodeID_;
        std::stack<int> stack_;
        int startID_;
        vector<bool> visited_;
        bool finished_;
  };

  private:
    void add_edge_(const int& src_node_ID, const int& dst_node_ID);
    void add_node_(const int& node_ID);
    void del_edge_(const int& src_node_ID, const int& dst_node_ID);
    bool contains_node_(const int& ID);
    bool check_node_exists_(const int& ID);
    int find_node_of_index_(const int& node_index);
    int find_node_of_ID_(const int& ID);

    int num_edges_ = 0;
    int num_nodes_ = 0;
    vector<struct Node*> nodes_;
    vector<bool> visitCheck;
};
