#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <stack>

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
      copiedNode->dest_nodes = i->dest_nodes;
      copiedNode->src_nodes = i->src_nodes;
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
      newNode->dest_nodes = i->dest_nodes;
      newNode->src_nodes = i->dest_nodes;
      nodes_.push_back(newNode);
    }
  }
  return *this;
}

/**
 * Constructor that takes in an Adjacency matrix and produces the node graph
 * @param adjMat the adjacency matrix to be processed
 */
Graph::Graph(vector<vector<int> > adjMat) {
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

    visitCheck.resize(num_nodes_);
    fill(visitCheck.begin(), visitCheck.end(), false);
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
 * Check if the node has been created
 * @param node_ID the index of the airport in the adjacency matrix
 */
Node* Graph::get_node_ptr(const int &node_ID) {
  size_t ID = node_ID;
  if(ID < nodes_.size()) {
    return nodes_[node_ID]; // node_ID and index in nodes_ matchup
  }
  return nullptr; // can't find node with that index
}

/**
 * Return the number of airports("nodes") in the graph
 */
int Graph::getNumberAirports() {
  return num_nodes_;
}
/**
 * Check if a node has been visited
 * @param node_ID which node to check if visited
 */
bool Graph::checkVisited(const int node_ID) {
  if(node_ID > -1 && (size_t)node_ID < visitCheck.size())
    return visitCheck[node_ID];
  else 
    return false;
}

/**
 * Performs an iterative Depth First Search
 * @param start_node_ID initial starting node ID
 */
 void Graph::DFS(int start_node_ID) {
  for (auto it = Graph::Iterator(this, start_node_ID); it != Graph::Iterator(); ++it) {
    visitCheck[(*it)->ID] = true;
  }
}

/**
 * Default iterator constructor.
 */
Graph::Iterator::Iterator() {
  finished_ = true;
 }

/**
* Iterator constructor that takes in a graph and starting node ID.
* @param start starting node
*/
Graph::Iterator::Iterator(Graph* graph, int startID) {
  graph_ = graph;
  // Add neighbors of start node to stack
  // NOTE: This is a mildly hacky way of doing it but the easiest off the top
  // of my head
  auto currentNode = graph_->get_node_ptr(startID);
  auto destinations = currentNode->dest_nodes;
  auto sources = currentNode->src_nodes;

  for(auto it = destinations.begin(); it != destinations.end(); ++it) {
    stack_.push((*it)->ID);
  }
  for(auto it = sources.begin(); it != sources.end(); ++it) {
    stack_.push((*it)->ID);
  }

  startID_ = startID;
  currentNodeID_ = startID;
  visited_ = vector<bool>(graph->num_nodes_, false);
  finished_ = false;
  visited_[startID] = true;
}

Graph::Iterator & Graph::Iterator::operator++() {
  int s = stack_.top();
  currentNodeID_ = s;
  stack_.pop();

  while (visited_[s] && !stack_.empty()) {
    s = stack_.top();
    currentNodeID_ = s;
    stack_.pop();
  }

  visited_[s] = true;

  Node* cur_node = graph_->get_node_ptr(s);
  std::set<Node*> destinations = cur_node->dest_nodes;
  std::set<Node*> sources = cur_node->src_nodes;

  // Push adjacent nodes
  for (Node* n: destinations) {
    if (!visited_[n->ID]) {
      stack_.push(n->ID);
    }
  }
  for (Node* n: sources) {
    if (!visited_[n->ID]) {
      stack_.push(n->ID);
    }
  }

  if(stack_.empty()) {
    if(find(visited_.begin(), visited_.end(), false) != visited_.end()) { // visited unconnected nodes
      for(size_t i = 0; i < visited_.size(); i++) {
        if(visited_[i] == false)
          stack_.push(i);
      }
    }
    else { // if all nodes visited, finished
      finished_ = true;
    }
  }

  return *this;
}

Node* Graph::Iterator::operator*() {
  return graph_->get_node_ptr(currentNodeID_);
}

bool Graph::Iterator::operator!=(const Iterator &other) {
  // if(currentNodeID_ != other.currentNodeID_ || finished_ != other.finished_)
  // not sure about this comparison
  if(finished_ != other.finished_)
    return true;
  return false;
}

/**
 * Check if the node has been created
 * @param node_idx the index of the node you want to check for
 */
bool Graph::check_node_exists_(const int& node_ID) {
    for (Node* v: nodes_) {
        if (v->ID == node_ID) return true;
    }
    return false;
}

/**
 * Adds a node to the graph
 * @param node_idx the index of the node you want to add
 */
void Graph::add_node_(const int& node_ID) {
    if (check_node_exists_(node_ID)) return;
    num_nodes_ += 1;
    Node *v;
    v = new Node(node_ID);
    nodes_.push_back(v);
}

/**
 * Returns the index in the list of nodes of the node with the node ID
 * you want
 * @param node_ID the ID of the node you are looking for
 */
int Graph::find_node_of_ID_(const int& node_ID) {
    int i = 0;
    for (Node* v: nodes_) {
        if(v->ID == node_ID) return i;
        i += 1;
    }
    throw runtime_error {"Could not find node"};
}

/**
 * Returns the index in the list of nodes of the node with the node ID
 * you want
 * @param node_ID the ID of the node you are looking for
 */
int Graph::find_node_of_index_(const int& node_idx) {
    int i = 0;
    for (Node* v: nodes_) {
        if(v->index == node_idx) return i;
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
    if (!check_node_exists_(src_node_ID)) throw runtime_error {"Source node does not exist"};
    if (!check_node_exists_(dst_node_ID)) throw runtime_error {"Destination node does not exist"};

    //Checks if the destination node is already included in the neighbors list, if
    //it isn't it adds it and increases the number of edges by 1.
    Node* dst_node = nodes_[find_node_of_ID_(dst_node_ID)];
    Node* src_node = nodes_[find_node_of_ID_(src_node_ID)];
    size_t src_size = src_node->dest_nodes.size();
    size_t dst_size = dst_node->src_nodes.size();
    src_node->dest_nodes.insert(dst_node);
    dst_node->src_nodes.insert(src_node);
    if(src_size != src_node->dest_nodes.size() || dst_size != dst_node->src_nodes.size())
      num_edges_ += 1;
}

/**
 * Dijkstra's Algorithm
 * @param node_ID the ID of the node that is the source
vector<int> Graph::dijkstras(const int& source_node_ID) {
  // the number of nodes in the graph
  int num_nodes = (int) nodes_.size();

  // index of source
  int source_idx = source_node_ID;

  // create vector to store distance to each node
  vector<int> dist_to_source(num_nodes);

  // distance from source node to source node is 0
  dist_to_source[source_idx] = 0;

  // set all other distances to "infinity"
  for (int i = 0; i < (int) dist_to_source.size(); i++) {
    if (i != source_idx) {
      dist_to_source[i] = 100000000;
    }
  }

  return dist_to_source;
}
*/
