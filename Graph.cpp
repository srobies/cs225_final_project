#include <list>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

#include "Graph.h"
#include "AirportsData.h"


using namespace std;


/**
 * Class implementation of a graph. Creates a Graph class object
 * with a map of connect airports and routes. 
 */

//Defaults Constructor
Graph::Graph() {
    num_edges_ = 0;
    num_nodes_ = 0;
}


/**
 * Copy constructor
 * @param other graph to be copied
 */
Graph::Graph(const Graph& other) : num_edges_(other.num_edges_), 
  num_nodes_(other.num_nodes_) {
    for(Node* i: other.nodes_) {
      Node* copiedNode = new Node(i->index);
      copiedNode->index = i->index;
      copiedNode->neighbors = i->neighbors;
      nodes_.push_back(copiedNode);
    }
}

/**
 * Copy constructor
 * @param other graph to be copied
 */
Graph& Graph::operator=(const Graph& other) {
  // TODO: check this. no self assignment
  if(this != &other) {
    // clear out lhs
    for(Node* i: nodes_) {
      delete i;
    }
    nodes_.shrink_to_fit();

    // set equal to rhs
    num_nodes_ = other.num_nodes_;
    num_edges_ = other.num_edges_;
    for(Node* i: other.nodes_) {
      Node* newNode = new Node(i->index);
      newNode->index = i->index;
      newNode->neighbors = i->neighbors;
      nodes_.push_back(newNode);
    }
  }
  return *this;
}

/**
 * Constructor that takes in an Adjacency matrix and produces the node graph
 * @param adjMat the adjacency matrix to be processed
 */
Graph::Graph(vector<vector<int>> adjMat) {
    //creates nodes
    for (size_t i = 0; i < adjMat.size(); i++) {
        add_node_(i);
    }

    //adds edges
    for (size_t m = 0; m < adjMat.size(); m++) {
        for (size_t n = 0; n < adjMat[m].size(); n++) {
          if(adjMat[m][n] == 1) // only add edge if there is a route
            add_edge_(m,n);
        }
    }
}

/**
 * Destructor for class
 */
Graph::~Graph() {
  for(Node* i: nodes_) {
    delete i;
  }
  nodes_.shrink_to_fit();
}

/**
 * Performs a recursive Depth First Traversal
 * @param v initial starting node index
 */
void DFS(const int& v) {
    
}

/**
 * Check if the node has been created
 * @param node_ID the ID of the node you want to check for
 */
bool Graph::check_node_exists_(const int& node_idx) {
    for (Node* v: nodes_) {
        if (v->index == node_idx) return true;
    }
    return false;
}

/**
 * Adds a node to the graph
 * @param node_idx the index of the node you want to add
 */
void Graph::add_node_(const int& node_idx) {
    if (check_node_exists_(node_idx)) return;
    num_nodes_ += 1;
    Node *v;
    v = new Node(node_idx);
    nodes_.push_back(v);
}

/**
 * Returns the index in the list of nodes of the node with the node ID 
 * you want
 * @param node_ID the ID of the node you are looking for
 */
// int Graph::find_node_of_ID_(const int& node_ID) {
//     int i = 0;
//     for (Node* v: nodes_) {
//         if(v->ID == node_ID) return i;
//         i += 1;
//     }
//     throw runtime_error {"Could not find node"};
// }

/**
 * Returns the index in the list of nodes of the node with the node ID 
 * you want
 * @param node_ID the ID of the node you are looking for
 */
int Graph::find_node_of_index_(const int& node_index) {
    int i = 0;
    for (Node* v: nodes_) {
        if(v->index == node_index) return i;
        i += 1;
    }
    throw runtime_error {"Could not find node"};
}

/**
 * Adds an edge to the graph
 * @param src_node_ID the ID of the tail end node of the edge
 * @param dst_node_ID the ID of the tip end node of the edge
 */
void Graph::add_edge_(const int& src_node_idx, const int& dst_node_idx) {
    //Check if nodes exist
    if (!check_node_exists_(src_node_idx)) throw runtime_error {"Source node does not exist"};
    if (!check_node_exists_(dst_node_idx)) throw runtime_error {"Destination node does not exist"};

    //Checks if the destination node is already included in the neighbors list, if 
    //it isn't it adds it and increases the number of edges by 1.
    Node* dst_node = nodes_[find_node_of_index_(dst_node_idx)];
    Node* src_node = nodes_[find_node_of_index_(src_node_idx)];
    // TODO: double check this comparison
    // if (std::none_of(z->neighbors.begin(), z->neighbors.end(), [](Node* v){ return i == v; })) {
    //     num_edges_ += 1;
    //     z->neighbors.push_back(v);
    // }
    if(std::find(src_node->neighbors.begin(), src_node->neighbors.end(), dst_node) == src_node->neighbors.end()) {
      num_edges_ += 1;
      src_node->neighbors.push_back(dst_node);
    }
}
