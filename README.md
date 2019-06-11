Chinese-Postman Problem - Graph Theory Term-Project

To Execute The Code:

Step1:
		Modify the content in /Graph-Theory-Project-Template/ topo.txt (copy the data which
        
        in test_book.txt, house.txt, cycle.txt into topo.txt)

Step2:
		execute make clean && make all && ./main.out command in linux.
		
		It will print Path: and Cost: .
Solution:

Solution of Logic:

Step1:
		Initialization As a first step, all nodes that don't have any incoming or outgoing nodes are deleted. These isolated nodes have no influence on the further behavior of the algorithm.	


Step2:
		Checking whether the problem can be solved First we check, whether the graph is strongly connected and whether there are any negative cycles.

		A graph is strongly connected if any node can be reached from any other node. Only then does a round tour exist.

		The graph is strongly connected. Then there is a round tour that uses all edges.

		There are no negative cycles. Thus the costs of round trips are bounded from below.

		The problem is solvable on this graph.
		
Step3:
		Finding nodes with different In-Out Degrees
		
		First, we calculate the difference of out- and in-degrees. Nodes that have a differnce of 0 are balanced; the remaining ones are imbalanced.

		The imbalanced nodes have been highlighted. An Euler tour would exist in the graph only if all nodes were balanced. An Euler tour (or Euler cycle) is a path in the graph that contains all edges exactly once and starts and ends in the same node.

		The goal of the next steps will be to find a set of paths between the imbalanced nodes, such that the graph will become completely balanced after inserting these additional paths. The length of these additional paths should be minimal.

		The Euler tour in the graph with the additional paths will then be the shortest round tour that we are ultimately aiming to find.
		
Step4:
		 Finding the Additional Paths
		
		Let's only consider the imbalanced nodes. The edge weights represent the shortest possible graph from the nodes with negative out-in difference to the nodes with positive difference.

		In order to find the shortest paths for each such pair of nodes we will use the Floyd-Warshall algorithm method.

		By adding one additional path from a node with negative difference to one with a positive one, the difference at the start and ending nodes will change by exactly 1. For all other vertices along the path, the difference will remain unchanged.

		We are looking for a set of paths such that all nodes will be balanced and the total lengths of the extra paths will be minimized.
		
		
Step5:
		The optimal set of paths is illustrated by the highlighted edges.

		After inserting the additional paths, the out-in difference for all imbalanced graphs will be reduced to 0. All nodes between the highlighted nodes will remain unchanged.
		
Step6:
		Inserting the Additional Paths
		
		Now we take the graphs we found in the last step and add them to the original graph. The edges we insert represent those edges in the original graph that will have to be traversed multiple times in the optimal solution.

		After the insertion, all nodes will have an out-in difference of exactly 0. Thus, an Euler tour exists in the graph.
		
		Adding an additional shortest path between the highlighted nodes. The difference of out- and in-degrees of the origin and destination nodes is changed by exactly 1.
		
		In- and out-degrees agree for all nodes in the graph. Thus, an Euler tour exists in the graph.

		An Euler tour is a path in the graph that contains all edges exactly once and starts and ends in the same node.
		
		
Step7:
		Determining the Euler Tour
		
		In order to find the Euler tour, we use the Hierholzer algorithm method.

		The costs of the shortest round trip in the graph are exactly those of the Euler tour. 
		
		The cost of an Euler tour, however, is always exactly the sum of all the edges in the graph.