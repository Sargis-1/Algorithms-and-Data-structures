#pragma once
#include <iostream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>

class Graph
{
public:
    void addVertex(int v);

    void addEdge(int source, int dest);

    void printGraph();

    void bfs(int source);

    void dfsIterative(int source);

    void dfsRecursive(int source);

    void transpose();

    std::list<int> shortestPath(int source, int dest);

    int nthlevelnodecount(int level);

    void allpossiblepathshelper(int source, int dest, std::vector<bool>& visited, std::vector<int>& current,
        std::vector<std::vector<int>>& allpaths);

    void allpossiblepaths(int source, int dest);

    bool isCycledUndirected();

    bool isCycledDirected();

    void topSort();

    void topSortKahn();

    void SccKosaraju();

    void FindArticulationPoints();

    void FindArticulationBridges();

    bool FindEulerianPaths();
private:
    void dfsRecursivehelper(int source, std::vector<int>& visited);

    bool dfsisCycledUndirected(int source, int parent, std::vector<bool>& visited);

    bool dfsisCycledDirected(int source, std::vector<bool>& visited, std::vector<bool>& recstack);

    void dfstopSort(int source, std::vector<bool>& visited, std::list<int>& result);

    void dfsSccKosaraju(int source, std::vector<bool>& visited, std::stack<int>& stack);

    void dfscollectingScc(int source, std::vector<bool>& visited, std::vector<int>& currencscc);

    void dfsartPoints(int u, std::vector<int>& disctime, std::vector<int>& lowlink,
        std::vector<int>& parent, std::vector<int>& artPoints, int& time);

    void dfsartBridges(int u, std::vector<int>& disctime, std::vector<int>& lowlink,
        std::vector<int>& parent, std::vector<std::pair<int, int>>& artBridges, int& time);

    void dfseuler(int source, std::vector<int>& path, std::vector<int>& outdegree);
private:
    std::vector<std::vector<int>> Adjlist;
};

