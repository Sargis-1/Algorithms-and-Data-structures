#include "Graph.h"


int main()
{
    Graph g;
    /*g.addVertex(0);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    g.addVertex(5);
    g.addVertex(6);
    g.addVertex(7);
    g.addVertex(8);
    g.addVertex(9);
    g.addVertex(10);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(1, 4);
    g.addEdge(1, 7);
    g.addEdge(2, 4);
    g.addEdge(4, 7);
    g.addEdge(5, 8);
    g.addEdge(2, 5);
    g.addEdge(3, 6);
    g.addEdge(7, 8);
    g.addEdge(6, 9);
    g.addEdge(8, 10);
    g.addEdge(9, 10);*/
    // new one 
    /*g.addVertex(0);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);*/

    //DAG example- Directed Acyclic graph
    g.addVertex(0);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    g.addVertex(5);
    g.addVertex(6);
    g.addVertex(7);

    g.addEdge(0, 1);
    g.addEdge(2, 0);
    g.addEdge(3, 1);
    g.addEdge(3, 7);
    g.addEdge(4, 1);
    g.addEdge(3, 4);
    g.addEdge(4, 0);
    g.addEdge(5, 2);
    g.addEdge(6, 3);
    g.addEdge(6, 5);
    g.addEdge(6, 7);
    g.addEdge(7, 4);
    g.addEdge(6, 2);

    /* g.addVertex(1);
     g.addVertex(2);
     g.addVertex(3);
     g.addVertex(4);
     g.addVertex(5);
     g.addVertex(6);
     g.addVertex(7);

     g.addEdge(1, 2);
     g.addEdge(1, 3);
     g.addEdge(2, 4);
     g.addEdge(2, 5);
     g.addEdge(3, 6);
     g.addEdge(6, 5);
     g.addEdge(4, 7);
     g.addEdge(5, 7);
     g.addEdge(6, 7);*/

     //graph with 6 SCC's
     /*g.addVertex(0);
     g.addVertex(1);
     g.addVertex(2);
     g.addVertex(3);
     g.addVertex(4);
     g.addVertex(5);
     g.addVertex(6);
     g.addVertex(7);
     g.addVertex(8);
     g.addVertex(9);
     g.addVertex(10);
     g.addVertex(11);
     g.addVertex(12);
     g.addVertex(13);
     g.addVertex(14);
     g.addVertex(15);

     g.addEdge(0, 2);
     g.addEdge(1, 0);
     g.addEdge(2, 1);
     g.addEdge(2, 4);
     g.addEdge(4, 3);
     g.addEdge(3, 2);
     g.addEdge(3, 12);
     g.addEdge(4, 13);
     g.addEdge(12, 13);
     g.addEdge(13, 15);
     g.addEdge(15, 14);
     g.addEdge(14, 12);
     g.addEdge(13, 14);
     g.addEdge(1, 5);
     g.addEdge(4, 5);
     g.addEdge(5, 6);
     g.addEdge(5, 8);
     g.addEdge(6, 7);
     g.addEdge(7, 8);
     g.addEdge(8, 6);
     g.addEdge(8, 9);
     g.addEdge(5, 10);
     g.addEdge(10, 11);
     g.addEdge(11, 10);
     g.addEdge(10, 9);
     g.addEdge(15, 10);*/

    /*g.addVertex(0);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    g.addEdge(0, 3);
    g.addEdge(0, 2);
    g.addEdge(1, 0);
    g.addEdge(2, 1);
    g.addEdge(3, 4);
    g.addEdge(4, 0);*/

    //g.printGraph();
    //g.bfs(0);
    //g.dfsIterative(10);
    //g.dfsRecursive(0);
    //g.tranpose();
    //g.shortestPath(0, 4);
    //g.nthlevelnodecount(2);
    //g.allpossiblepaths(2, 2);
    //std::cout << g.isCycledUndirected();
    //std::cout << g.isCycledDirected();
    //g.topSort();
    g.topSortKahn();
    //g.SccKosaraju();
    //g.FindArticulationPoints();
    //g.FindArticulationBridges();
    //g.FindEulerianPaths();
    return 0;
}