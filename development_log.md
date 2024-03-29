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

**April 27, 2021:**
For this meeting, Shayna Provine took notes. The leader for this meeting was Matt Weiler. The implementation of DFS is still in progress. Currently, out of 6000 nodes, only 3193 traverses are taking place. We will add tests for add_node_/check_node_exists_ (Matt) as well as tests for the iterator (Spencer) to debug. We have an implementation of Djikstra’s completed, with tests still needing to be written. We plan on having DFS and Djikstra’s debugged and verified with tests by Saturday. We are adding an additional meeting on Reading Day. By next week, Matt and Spencer will work on Graph/DFS tests and Rachel and Shayna will work on Djikstra’s.


**May 4, 2021:**
For this meeting, Matthew took notes. The leader for this meeting was Shayna. DFS is finished, Spencer fixed the node issue and is smoothing out the bugs. Matt started Gervan-Newman on his machine, but still has some work to do before committing anything. Spencer plans on re-implementing Djikstra’s to work off the graph. Our plan is to finish GN asap so we can work on the project this weekend. Our plan is to meet again on May 8th, this coming saturday, at 11am.

**May 8, 2021:**
For this meeting, Rachel Dannhausen-Brun took notes. The leader for this meeting was Spencer Robieson. We first completed any necessary finalizations to the three algorithms. We then all worked together on the presentation as well as the final project report. We decided who would record audio for which slides and how much of the time would be spent on each slide. It was also determined that each member of the group would upload their audio to a shared drive. Rachel would then add both the audio and the presentation slides to an iMovie project in order to create the final presentation.

