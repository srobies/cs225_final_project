CS 225 Data Structures
----------------------

Final Project Proposal (racheld3-slr6-mweiler3-provine2)

1.  **Leading Question**\
    For our project, we will be determining the betweenness centrality
    of airports around the world. We will rank all airports by their
    betweenness centrality to determine which airports are most
    important. When successful, the project will use the data from
    OpenFlights.org to produce a list of all airports ranked by the
    betweenness centrality of each airport. The end goal is to find the
    most important airport. In this case, highest importance corresponds
    to greatest betweenness centrality.
2.  **Dataset Acquisition and Processing**\
    The final project will make use of an open source data set of flight
    routes and airports provided on OpenFlights.org. We will be using
    the data set that includes the flight routes (routes.dat) and the
    dataset that includes the airports (airports.dat), which can both be
    found at the following link:
    [https://openflights.org/data.html](https://www.google.com/url?q=https://openflights.org/data.html&sa=D&source=editors&ust=1617933394373000&usg=AOvVaw2g7syrOIp-xx6qU7blFRfI).
    The files routes.dat and airports.dat will be downloaded from the
    website found at the link previously provided. The files will be
    converted to CSVs. The airports.dat file will primarily be used when
    the names of the airports are needed. We plan to store the
    routes.dat data in a 2D vector set up as an adjacency matrix. This
    2D vector constructed as an adjacency matrix is what will be used to
    find the betweenness centrality using an algorithm which will be
    described in the following section of the proposal. We will also
    create a graph data structure using the data in the routes.dat file.
    In our graph data structure, the nodes will be the airports and the
    edges will be the routes between the airports. The edges will be
    weighted, with weights based on the number of flights between the
    two airports. We will not include any lines of the data that have
    null fields or do not provide the needed information to be included.
    
3.  **Graph Algorithms**

Graph Traversal: Depth First Search

-   Goal: Create an iterator that allows traversal of the graph
-   Input: The starting airport node
-   Output: The next airport node
-   Call operator++ on a node to traverse to the next airport node until
    no nodes left

Airport Importance: Girvan-Newman Algorithm

-   Goal: Find betweenness centrality of all airports
-   Input: 2D vector which stores adjacency matrix
-   Output: Map that maps the name of the airport to the betweenness
    centrality
-   Betweenness of vertex v is number of times v appears in the shortest
    path between s,t, for all s,t, in V(G)
-   Time Efficiency: O(E<sup>2</sup> \*N)

Shortest Path: Dijkstra’s Algorithm

-   Goal: Find the shortest path between two airports
-   Find in graph structure, with airports as nodes and routes as edges
-   Input : source airport ID and destination airport ID
-   Output: Vector storing route or collection of routes that make up
    shortest path from source to destination
-   Time Efficiency: O(V + E\*log(V)) (w/ min-priority queue)

4. **Timeline**

- April 8, 2021: Complete, submit and sign the Team Contract
- April 8, 2021: Complete and submit the Final Project Proposal
- April 12, 2021: \
      By this day: complete initial set-up, have files
downloaded and stored, create Makefile and outline of code structure
- April 13, 2021: Team Meeting over Zoom
- April 14, 2021:\
      By this day: adjacency table setup and simple tests written for verification\
- April 20, 2021: Team Meeting over Zoom & Meet with project
mentor for the Mid-Project Checkin\
By this day: adjacency matrix to graph completed and DFS
iterator completed and verified with tests
- April 27, 2021: Team Meeting over Zoom \
By this day: complete Dijkstra’s algorithm and verify with tests
- May 4, 2021: Team Meeting over Zoom\
By this day: complete Girvan-Newman algorithm and verify with tests
- May 9, 2021:\
By this day: complete report and presentation video/slides
- May 11, 2021: Team Meeting over Zoom
By this day: complete any last minute edits on
report/presentation
- May 12, 2021: Make sure entire project and all deliverables are
submitted
