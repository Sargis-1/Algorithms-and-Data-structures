#include <iostream>
#include <vector>
#include <queue>


class graph {
public:
    graph() {}

    graph(std::vector<std::vector<std::pair<int, int>>> newadjlist) :Adjlist(newadjlist) {}


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

        for (int i = 0; i < distance.size(); ++i)
            std::cout << i << " " << distance[i] << std::endl;

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

        for (int i = 0; i < finaldistance.size(); ++i)
            std::cout << i << " " << finaldistance[i] << std::endl;

        return finaldistance;
    }

private:
    std::vector<std::vector<std::pair<int, int>>> Adjlist;
};



int main() {
    graph g;
    int size = 10;
    for (int i = 0; i < size; ++i)
        g.addVertex(i);

    /*g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 5);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 4, 1);
    g.addEdge(2, 1, 3);
    g.addEdge(2, 3, 2);
    g.addEdge(2, 4, 9);
    g.addEdge(2, 4, 9);
    g.addEdge(3, 0, 7);
    g.addEdge(3, 4, 6);
    g.addEdge(4, 3, 4);*/

    /* g.addEdge(0, 1, 5);
     g.addEdge(0, 3, 7);
     g.addEdge(1, 0, 8);
     g.addEdge(1, 2, 6);
     g.addEdge(2, 0, 4);
     g.addEdge(2, 3, 3);
     g.addEdge(3, 0, 2);*/
     //g.printGraph();

     /*std::vector<std::vector<std::pair<int, int>>> Adjlist = {
     {{1, 2}, {2, 4}},
     {{3, 7}},
     {{1, 1}, {3, 3}},
     {{5, 2}},
     {{5, 5}},
     {{}}
     };
     graph g1(Adjlist);*/

     //graph with negative cycle
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

    //g.Dijkstra(0);

    g.BellmanFord(0);
}

