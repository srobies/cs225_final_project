**April 8, 2021:**
The entire team met on Zoom to finalize the team contract and team project proposal. All team members were in attendance. We also delegated tasks to be completed by the first team meeting. We planned to meet on Saturday, April 10th at 11am to upload the data and figure out how to set up the data for our code.

**April 13, 2021:**
For this meeting, Rachel Dannhausen-Brun took notes. The leader for this meeting was Spencer Robieson. Initial setup of make files were pushed to our git repository prior to this meeting. At the beginning of this meeting, initial versions of files which read the airport data and store it in data structures were pushed to our git repository as well. As a team, we determined which tasks need to be completed for the following week. We determined that the make files and initial tests should be the priority to be completed for next week. We also determined that the next most important task is to set up the adjacency matrix, which is partially already completed. We also intend to complete the DFS iterator code and the tests for the adjacency matrix before our meeting on April 20th. For next week, we have assigned the following tasks.
- Spencer: finishing setting up the make file, construct graph from the adjacency matrix 
        (with Rachel)
- Rachel: finalize code for setting up the adjacency matrix, construct graph from the 
adjacency matrix (with Spencer)
- Shayna: write code for DFS iterator and tests (with Matt)
- Matt: write code for DFS iterator and tests (with Shayna)
During this meeting, we determined some details about the graph structure for the project. The nodes would need to contain the codes which correspond to the airports, and information about both ingoing and outgoing flights. The edges of the graph would correspond to the routes between airports. Each route will be weighted as 1. Dijkstra's algorithm will then be used to find the shortest routes in the graph.

**April 20, 2021:**
For this meeting, Spencer Robieson took notes. The leader for this meeting was Rachel Dannhausen-Brun. Shayna Provine and Matt Weiler did not attend this meeting. The make file and graph construction using the adjacency matrix from the data are completed. The DFS iterator and tests are not complete and must be finished ASAP before the mid-project check-in. For next week, we intend to implement Dijkstra’s algorithm on our graph and write tests to verify it by April 27. We should also start looking into betweenness centrality and Girvan-Newman and think of implementations for the algorithm to meet the May 4 due date. We are planning on doing the mid-project check-in at 2:45pm on April 21.
- Spencer: write code and tests for Dijkstra’s algorithm (with Rachel). General code review
- Rachel: write code and tests for Dijkstra’s algorithm (with Spencer). General code review
- Shayna: finish DFS and tests ASAP. Start looking into Girvan-Newman (with Matt). General code review
- Matt: finish DFS and tests ASAP. Start looking into Girvan-Newman (with Shayna) General code review
For the node implementation, it is not necessary to store ingoing flights or the airport code. The node will only store the outgoing flights in its vector. The code for the airport can be accessed using the index for the node.
