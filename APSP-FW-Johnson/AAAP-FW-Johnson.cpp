#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>
#include <queue>

//Floyd Warshall's and Johnson's algorithms are effectively finding shortest path between graph's any pair of vertexes.
class FloydWarshall{
public:
    FloydWarshall(std::vector<std::vector<std::pair<int, int>>> adjlist) {
        int size = adjlist.size();
        std::vector<std::vector<int>> matrix(size, std::vector<int>(size, INT32_MAX));
        Adjmatrix = matrix;
        for (int u = 0; u < size; ++u) {
            for (const auto& [v, w] : adjlist[u]) {
                Adjmatrix[u][v] = w;
                if (u == v)
                    Adjmatrix[u][v] = 0;
            }
        }

        for (int u = 0; u < size; ++u) 
                Adjmatrix[u][u] = 0;   

        dp = Adjmatrix;
        next.resize(size, std::vector<int>(size, -1));

        for (int u = 0; u < size; ++u) {
            for (int v = 0; v < size; ++v) {
                if (Adjmatrix[u][v] != INT32_MAX)
                    next[u][v] = v;
            }
        }

    }


    void printmatrix(std::vector<std::vector<int>> matrix) {
        int maxElementWidth = 4;

        for (int i = 0; i < matrix.size(); ++i) {
            //std::cout << std::setw(maxElementWidth) << i;
            for (int j = 0; j < matrix[i].size(); ++j) {
                if (matrix[i][j] == INT32_MAX) {
                    std::cout << std::setw(maxElementWidth) << "+I";
                }
                else if (matrix[i][j] == INT32_MIN) {
                    std::cout << std::setw(maxElementWidth) << "-I";
                }
                else {
                    std::cout << std::setw(maxElementWidth) << matrix[i][j];
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void solveFloydWarshall() {
        for (int k = 0; k < Adjmatrix.size(); ++k) {
            for (int i = 0; i < Adjmatrix.size(); ++i) {
                for (int j = 0; j < Adjmatrix.size(); ++j) {
                    if (dp[i][k] != INT32_MAX && dp[k][j] != INT32_MAX && dp[i][j] > dp[i][k] + dp[k][j]) {
                        //std::cout << i << " , " << j << " , " << k << std::endl;
                        dp[i][j] = dp[i][k] + dp[k][j];
                        next[i][j] = next[i][k];
                    }
                }
            }
            //printmatrix(dp);
        }

        detectNegaiveCycles();
        printmatrix(dp);
    }


    bool detectNegaiveCycles() {
        bool flag = false;
        for (int k = 0; k < Adjmatrix.size(); ++k) {
            for (int i = 0; i < Adjmatrix.size(); ++i) {
                for (int j = 0; j < Adjmatrix.size(); ++j) {
                    if (dp[i][k] != INT32_MAX && dp[k][j] != INT32_MAX && dp[i][j] > dp[i][k] + dp[k][j]) {
                        flag = true;
                        dp[i][j] = INT32_MIN;
                        next[i][j] = -1;
                    }
                }
            }
        }

        return flag;
    }


    void reconstructPath(int source, int dest) {
        if (dp[source][dest] == INT32_MAX) {
            std::cout << "No path" << std::endl;
            return;
        }

        int i = source;
        std::vector<int> path;
        for (; i != dest; i = next[i][dest]) {
            if (next[i][dest] == -1) {
                std::cout << "No path orr affeced by negative cycle" << std::endl;
                return;
            }
            path.push_back(i);
        }

        path.push_back(i);
        for (int j = 0; j < path.size(); ++j)
            std::cout << path[j] << " ";

    }

private:
    std::vector<std::vector<int>> Adjmatrix;
    std::vector<std::vector<int>> dp;
    std::vector<std::vector<int>> next;
};


class Johnson {
public:
    Johnson() {}

    Johnson(std::vector<std::vector<std::pair<int, int>>> newadjlist) :Adjlist(newadjlist) {}


    void addVertex(int v) {
        if (v < 0) {
            std::cout << "Invalid vertex index" << std::endl;
            return;
        }
        else if (v < Adjlist.size())
            std::cout << "Vertex " << v << " already exists." << std::endl;
        else
            Adjlist.resize(v + 1);
    }

    void addEdge(int source, int dest, int weight) {
        if (source < 0 || dest < 0) {
            std::cout << "Invalid vertex index" << std::endl;
            return;
        }
        else if (source >= Adjlist.size() || dest >= Adjlist.size()) {
            std::cout << "Invalid vertex index" << std::endl;
            return;
        }


        if (std::find(Adjlist[source].begin(), Adjlist[source].end(), std::make_pair(dest, weight))
            == Adjlist[source].end()) {
            Adjlist[source].push_back({ dest, weight });
        }
        /*if (std::find(Adjlist[dest].begin(), Adjlist[dest].end(), source) == Adjlist[dest].end()) {
            Adjlist[dest].push_back(source);
        }*/
    }

    void printGraph() {
        for (int i = 0; i < Adjlist.size(); i++) {
            std::cout << i << " -> ";
            for (int j = 0; j < Adjlist[i].size(); j++) {
                std::cout << Adjlist[i][j].first << ",";
                if (Adjlist[i][j].second > 0)
                    std::cout << " " << Adjlist[i][j].second << "  /";
                else
                    std::cout << Adjlist[i][j].second << "  /";
            }
            std::cout << std::endl;
        }
    }

    struct comparator {
        bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.second > b.second;
        }
    };


    std::vector<int> Dijkstra(int source) {
        std::vector<bool> visited(Adjlist.size(), 0);
        std::vector<int> distance(Adjlist.size(), INT32_MAX);
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, comparator> pq;
        pq.push({ source, 0 });
        distance[source] = 0;
        while (!pq.empty()) {
            auto [u, w] = pq.top();
            pq.pop();
            //std::cout << u << ", " << w << std::endl;
            if (w > distance[u])
                continue;

            visited[u] = true;
            for (auto& [v, weight] : Adjlist[u]) {
                int newdistance = 0;
                if (!visited[v]) {
                    if (distance[u] == INT32_MAX)
                        newdistance = INT32_MAX;
                    else
                        newdistance = distance[u] + weight;

                    if (distance[v] > newdistance) {
                        distance[v] = newdistance;
                        pq.push({ v, distance[v] });
                    }
                }
            }
        }

        /*for (int i = 0; i < distance.size(); ++i)
            std::cout << i << " " << distance[i] << std::endl;*/

        return distance;
    }


    std::vector<int> BellmanFord(int source) {
        std::vector<int> distance(Adjlist.size(), INT32_MAX);
        distance[source] = 0;
        bool relaxed = true;
        for (int i = 0; i < Adjlist.size() - 1; ++i) {
            if (!relaxed)
                break;

            relaxed = false;
            for (int u = 0; u < Adjlist.size(); ++u) {
                for (const auto& [v, w] : Adjlist[u]) {
                    int newdistance = 0;
                    if (distance[u] == INT32_MAX)
                        continue;
                    else
                        newdistance = distance[u] + w;

                    if (distance[v] > newdistance) {
                        relaxed = true;
                        distance[v] = newdistance;
                    }
                }
            }
        }


        std::vector<int> finaldistance = distance;
        for (int i = 0; i < Adjlist.size() - 1; ++i) {
            for (int u = 0; u < Adjlist.size(); ++u) {
                for (const auto& [v, w] : Adjlist[u]) {
                    int newdistance = 0;
                    if (distance[u] == INT32_MAX)
                        continue;
                    else
                        newdistance = distance[u] + w;

                    if (distance[v] > newdistance) {
                        distance[v] = newdistance;
                        finaldistance[v] = INT32_MIN;
                    }

                }
            }
        }

        /*for (int i = 0; i < finaldistance.size(); ++i)
            std::cout << i << " " << finaldistance[i] << std::endl;*/

        return finaldistance;
    }


    std::vector<std::vector<int>> Johnsonssolver() {
        int source = Adjlist.size();
        addVertex(source);
        for (int v = 0; v < source; ++v)
            addEdge(source, v, 0);
        
        std::vector<int> bellmanmap = BellmanFord(source);

        for (int u = 0; u < source; ++u) {
            for (auto& [v, w] : Adjlist[u]) {
                w = w + bellmanmap[u] - bellmanmap[v];
            }
        }

        /*for (int i = 0; i < bellmanmap.size(); ++i) {
            std::cout << i << " = " << bellmanmap[i] << std::endl;
        }*/

        std::vector<std::vector<int>> matrix(source, std::vector<int>(source, INT32_MAX));
        for (int u = 0; u < source; ++u) {
            std::vector<int> dist = Dijkstra(u);
            for (int v = 0; v < source; ++v) {
                matrix[u][v] = dist[v] - bellmanmap[u] + bellmanmap[v];
            }
        }

        for (int i = 0; i < matrix.size(); ++i) {
            std::cout << i << " -> ";
            for (int j = 0; j < matrix[i].size(); ++j)
                std::cout << matrix[i][j] << " ";
            std::cout << std::endl;
        }

        return matrix;
    }
private:
    std::vector<std::vector<std::pair<int, int>>> Adjlist;
};


int main(){
    std::vector<std::vector<std::pair<int, int>>> adjlist = { {{1, 10}, {2, 5}},
                                                              {{2,  -2}, {4, 1},},
                                                              {{1,  3}, {4, 9}, {3, 2}},
                                                              {{0,  7}, {4, -1}},
                                                              {{3, 4}}
                                                               };

    std::vector<std::vector<std::pair<int, int>>> adjlist2 = {
        {{1, 1}},
        {{2, 2}, {5, 4}},
        {{3, -1}},
        {{4, 3}},
        {{2, 1}},
        {{4, 5}}
    };
    FloydWarshall graph(adjlist);
    graph.solveFloydWarshall();
    //graph.reconstructPath(4, 1);
    std::cout << std::endl;

    
    Johnson g(adjlist);
    g.Johnsonssolver();
    /*int size = 5;
    for (int i = 0; i < size; ++i)
        g.addVertex(i);
    
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 5);
    g.addEdge(1, 2, -2);
    g.addEdge(1, 4, 1);
    g.addEdge(2, 1, 3);
    g.addEdge(2, 4, 9);
    g.addEdge(2, 3, 2);
    g.addEdge(3, 0, 7);
    g.addEdge(3, 4, -1);
    g.addEdge(4, 3, 4);*/
    //g.printGraph();

    
    /*Johnson g;
    int size = 10;
    for (int i = 0; i < size; ++i)
        g.addVertex(i);

    g.addEdge(0, 1, 5);
    g.addEdge(1, 2, 20);
    g.addEdge(1, 5, 30);
    g.addEdge(1, 6, 60);
    g.addEdge(2, 3, 10);
    g.addEdge(2, 4, 75);
    g.addEdge(3, 2, -15);
    g.addEdge(4, 9, 100);
    g.addEdge(5, 4, 25);
    g.addEdge(5, 8, 50);
    g.addEdge(5, 6, 5);
    g.addEdge(6, 7, -50);
    g.addEdge(7, 8, -10);
    g.Johnsonssolver();*/
    //g.printGraph();
}

