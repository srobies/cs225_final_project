#include <list>
#include <iostream>
#include <map>
#include <vector>

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
    num_nodes_ 0;
}

/**
 * Constructor that takes in an Adjacency matrix and produces the node graph
 * @param adjMat the adjacency matrix to be processed
 */
Graph::Graph(vector<vector<int>> adjMat) {
    //creates nodes
    for (i = 0; i < adjMat.size(); i++) {
        add_node_(i);
    }

    //adds edges
    for (m = 0; m < adjMat.size(); m++) {
        for (n = 0; n < adjMat[m].size(); n++) {
            add_edge_(m,n);
        }
    }
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
bool check_node_exist_(const int& node_ID) {
    for (Node v: nodes) {
        if (v->node_ID == node_ID) return true;
    }
    return false;
}

/**
 * Adds a node to the graph
 * @param node_ID the ID of the node you want to add
 */
void Graph::add_node_(const int& node_ID) {
    if (check_node_exist(node_ID)) return;
    num_nodes_ += 1;
    Node *v;
    v = new Node(node_ID);
    nodes.push_back(v);
}

/**
 * Returns the index in the list of nodes of the node with the node ID 
 * you want
 * @param node_ID the ID of the node you are looking for
 */
int Graph::find_node_of_ID_(const int& node_ID) {
    int i = 0;
    for (Node v: nodes) {
        if(v->ID == node_ID) return i;
        i += 1;
    }
    throw runtime_error {"Could not find node"};
}

/**
 * Adds an edge to the graph
 * @param src_node_ID the ID of the tail end node of the edge
 * @param dst_node_ID the ID of the tip end node of the edge
 */
void Graph::add_edge_(const int& src_node_ID, const int& dst_node_ID) {
    //Check if nodes exist
    if (!check_node_exists(src_node_ID)) throw runtime_error {"Source node does not exist"}
    if (!check_node_exists(dst_node)) throw runtime_error {"Destination node does not exist"}

    //Checks if the destination node is already included in the neighbors list, if 
    //it isn't it adds it and increases the number of edges by 1.
    Node *v = nodes[find_node_of_index(dst_node_ID)];
    Node z = nodes[find_node_of_index(src_node_ID)];
    if (std::none_of(z->neighbors.begin(), z->neighbors.end(), compare(v))) {
        num_edges_ += 1;
        z->neighbors.push_back(v);
    }
}

