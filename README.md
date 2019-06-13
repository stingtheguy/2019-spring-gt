# Graph-Theory-Project-Template
Project template of course - Graph Theory (EE6622E) in National Cheng Kung University.

## How to run

### Linux

```
# clone first (with submodule)
$ git clone --recursive https://github.com/<your-name>/Graph-Theory-Project-Template.git
# (Option) build libfakemn.a
$ cd fake-mininet && make lib && cd .. && cp fake-mininet/libfakemn.a .
# build
$ make 
# run 
$ ./main.out
```

### Windows

If your PC is `window 10`, then you need to install the related dependencies. For example, if you are using `VSCode` as your IDE, then you can install the plugin of `C/C++` in your vscode. And then install the following programs/packages:
* mingw
* git

Step by step to create `c_cpp_properties.json` and `tasks.json`:
* `Ctrl+Shift+P` -> `C/C++: Edit Configuration` -> then you have the first JSON file.
* `Ctrl+Shift+P` -> `Tasks: Configure Task` -> then you have the second JSON file.

Here is the setting of `c_cpp_properties.json` and `tasks.json`:
```json
# c_cpp_properties.json (If your mingw installed in another folder, then you have to change the value in `compilterPath`)
{
    "configurations": [
        {
            "name": "MinGW",
            "intelliSenseMode": "gcc-x64",
            "includePath": [
                "$(workspaceFolder)"
            ],
            "compilerPath": "C:/mingw/bin/gcc.exe",
            "cStandard": "c11",
            "cppStandard": "c++11"
        }
    ],
    "version": 4
}

# tasks.json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build",
            "type": "shell",
            "command": "g++",
            "args": [
                "-g",
                "main.cc",
                "-o",
                "main.exe",
                "-Ifake-mininet/lib",
                "-g3",
                "-L.",
                "-lfakemn_win",
                "-std=c++11"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
```

After all the settings have been done, we can press `Ctrl+Shift+B` to run the task, if your settings is correct, then there will have an executable file which named `main.exe`.

Or you can just [DOWNLOAD a pre-built VM images](http://gofile.me/39GpL/XU5tznyO6) provided by TA.

> [Guide of environment setting](https://hackmd.io/-5WZQC-1QqOeV3KUX65tEw?view) on Windows.

## TODO - Your descriptions about solutions/algorithms/results

Chinese-Postman Problem - Graph Theory Term-Project

* Execute The Code

    Step 1:
            Change the file name in line 353 (e.g. test_book.txt, house.txt, cycle.txt, topo.txt) to run different case

    Step 2: 
            
            $make clean && make all && ./main.out

* Solution of Logic (Detailed description show in Program implementation)

    Step 1: Check for Solvability

    Step 2: Find imbalanced nodes

    Step 3: Find additional paths

    Step 4: Insert additional paths

    Step 5: Specifying the Euler Tour
    
* The Main Idea of the Algorithm

    First of all, since any nodes without incoming or outgoing edges do not influence the problem, we can assume that no such edges exist. 

    The number of incoming edges at a vertex is called the In-Degree of that vertex, the number of outgoing ones its Out-Degree. A theorem in graph theory states that a graph has an Euler Tour if and only if the In- and Out-degrees are the same for all vertices of the graph. Therefore, it is sufficient to add additional paths to the graph, such that In- and Out-Degrees match for all nodes after inserting the new paths. The sum of the edge weights of these paths should be minimal. We will specify which paths to add in the Matching-Phase of the algorithm.

    After making sure that the graph contains an Euler Tour, we still have to find it. To do so, we may use any appropriate algorithm, such as the Hierholzer method. The cost of the optimal round trip then is exactly the sum of all edge weights in the Euler Tour.

    
* Euler Tour
    
    After adding these additional paths, the in- and out-degrees of all vertices in the graph will be balanced. Then a Euler Tour must exist in the graph and it can be found using the Hierholzer method. The cost of the optimal round trip is given by the sum of all edge weights of this Euler Tour.
    
* Hierholzer Algorithm

    Choose any starting vertex v, and follow a trail of edges from that vertex until returning to v. It is not possible to get stuck at any vertex other than v, because In-Degree and Out-Degree of every vertex must be same, when the trail enters another vertex w there must be an unused edge leaving w.
    
    The tour formed in this way is a closed tour, but may not cover all the vertices and edges of the initial graph.
    As long as there exists a vertex u that belongs to the current tour but that has adjacent edges not part of the tour, start another trail from u, following unused edges until returning to u, and join the tour formed in this way to the previous tour.
    
    Thus the idea is to keep following unused edges and removing them until we get stuck. Once we get stuck, we back-track to the nearest vertex in our current path that has unused edges, and we repeat the process until all the edges have been used. We can use another container to maintain the final path.
        
* Program implementation

    Step 1: Checking whether the problem can be solved
            
            First we check, whether the graph is strongly connected and whether there are any negative cycles.

            The graph is strongly connected. Then there is a round tour that uses all edges.

            There are no negative cycles. Thus the costs of round trips are bounded from below.

            
    Step 2: Finding nodes with different In- and Out- Degrees
            
            An Euler tour is a path in the graph that contains all edges exactly once and starts and ends in the same node which would exist in the graph only if all nodes were balanced. 

            The goal of the next steps will be to find a set of paths between the imbalanced nodes, such that the graph will become completely balanced after inserting these additional paths. The length of these additional paths should be minimal.

            The Euler tour in the graph with the additional paths will then be the shortest round tour that we are ultimately aiming to find.
    
    
    Step 3: Finding the Additional Paths
            
            By adding one additional path from a node with negative difference to one with a positive one, the difference at the start and ending nodes will change by exactly 1. For all other vertices along the path, the difference will remain unchanged.
            
            I store the all possible matching nodes in a 2-dimension vector.

            Looking for a set of paths such that all nodes will be balanced and the total lengths of the extra paths will be minimized.         

            After inserting the additional paths, the out-in difference for all imbalanced graphs will be reduced to 0.
                        
    
    Step 4: Inserting the Additional Paths
            
            After the insertion, all nodes will have an out-in difference of exactly 0. Thus, an Euler tour exists in the graph.
                      
            Use nm-> connect(path->paths.at(i).at(x)->head-> name, path->paths.at(i).at(x)->tail-> name) to connect the new path.
                        
            
    Step 5: Determining the Euler Cycle
    
            In order to find the Euler tour, we use the Hierholzer algorithm method.

            The cost of an Euler tour, however, is always exactly the sum of all the edges in the graph that after insert the additional paths.
                       
               