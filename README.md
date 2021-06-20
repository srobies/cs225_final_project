# UIUC CS225 Final Project

The files containing the two main classes, AirportData.cpp and Graph.cpp, can be found in the main directory of the project. The headers for these two classes and the main.cpp to run the code can also be found in the main project. Our dataset can be found in the folder "data/" under the file names airports.csv and routes.csv. A file containing results can be found in the main folder under the name "results.txt". This run of the code used the Rabah Bitat airport with code AAE for the example Dijkstra's.

To build the main executable, type "make" in the main project folder. To build the test executable, type "make test" in the main project folder. 

The syntax for the main executable is *./main airport_data_name route_data_name dijkstra_source output_file_name*. Airport_data_name is the path to the airport data, route_data_name is the path to the route data, dijkstra_source is the source node for the example Dijkstra's run, and output_file_name is the name of the file you want to output the run results to. For the run found in results.txt, we used *./main data/airports.csv data/routes.csv 0 results.txt*. 

To run the test suite, simply type *./test*. We wrote tests to ensure the data structure construction was correct. We also wrote tests to ensure that our member functions to check connections between airports could be correctly accessed. Additional tests were written to make sure that the graph and airportData classes interacted correctly. There are also small scale tests for DFS, Dijkstra's and Betweenness centrality. 
