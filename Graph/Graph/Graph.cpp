#include "Graph.h"

//Graph::Graph() {};

//Graph::~Graph() {};

void Graph::addVertex(int v) {
    if (v < 0) {
        std::cout << "Invalid vertex index" << std::endl;
        return;
    }
    else if (v < Adjlist.size())
        std::cout << "Vertex " << v << " already exists." << std::endl;
    else
        Adjlist.resize(v + 1);
};

void Graph::addEdge(int source, int dest) {
    if (source < 0 || dest < 0) {
        std::cout << "Invalid vertex index" << std::endl;
        return;
    }
    else if (source >= Adjlist.size() || dest >= Adjlist.size()) {
        std::cout << "Invalid vertex index" << std::endl;
        return;
    }


    if (std::find(Adjlist[source].begin(), Adjlist[source].end(), dest) == Adjlist[source].end()) {
        Adjlist[source].push_back(dest);
    }
    /*if (std::find(Adjlist[dest].begin(), Adjlist[dest].end(), source) == Adjlist[dest].end()) {
        Adjlist[dest].push_back(source);
    }*/
}

void Graph::printGraph() {
    for (int i = 0; i < Adjlist.size(); i++) {
        std::cout << i << " -> ";
        for (int j = 0; j < Adjlist[i].size(); j++)
            std::cout << Adjlist[i][j] << " /";
        std::cout << std::endl;
    }
}

void Graph::bfs(int source) {
    std::vector<char> visited(Adjlist.size(), 0);
    std::queue<int> queue;
    queue.push(source);
    visited[source] = 1;
    while (!queue.empty()) {
        int u = queue.front();
        std::cout << u << " / ";
        queue.pop();
        for (int v : Adjlist[u]) {
            if (visited[v] == 0) {
                queue.push(v);
                visited[v] = 1;
            }
        }
    }
}

void Graph::dfsIterative(int source) {
    std::vector<char> visited(Adjlist.size(), 0);
    std::stack<int> stack;
    stack.push(source);
    visited[source] = 1;
    while (!stack.empty()) {
        int u = stack.top();
        stack.pop();
        std::cout << u << " / ";
        for (int v : Adjlist[u]) {
            if (visited[v] == 0) {
                stack.push(v);
                visited[v] = 1;
            }
        }

    }
}

void Graph::dfsRecursive(int source) {
    std::vector<int> visited(Adjlist.size(), 0);
    int componentcount = 0;
    bool flag = 1;
    while (flag) {
        for (int i = 0; i < visited.size(); i++) {
            if (visited[i] == 0) {
                dfsRecursivehelper(i, visited);
                componentcount++;
            }
            else
                flag = false;
        }
    }
    //std::cout << std::endl << "Count of components is - " << componentcount << std::endl;
}

void Graph::dfsRecursivehelper(int source, std::vector<int>& visited) {
    visited[source] = 1;
    std::cout << source << " / ";
    for (int v : Adjlist[source]) {
        if (visited[v] == 0) {
            dfsRecursivehelper(v, visited);
        }
    }
}

void Graph::transpose() {
    std::vector<std::vector<int>> templist(Adjlist.size());
    for (int i = 0; i < Adjlist.size(); i++) {
        for (int j = 0; j < Adjlist[i].size(); j++) {
            templist[Adjlist[i][j]].push_back(i);
        }
    }

    Adjlist.clear();
    Adjlist = templist;
    templist.clear();
    //printGraph();
}

std::list<int> Graph::shortestPath(int source, int dest) {
    std::vector<char> visited(Adjlist.size(), 0);
    std::queue<int> queue;
    std::vector<short> parents(Adjlist.size(), -1);
    queue.push(source);
    visited[source] = 1;
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();
        for (int v : Adjlist[u]) {
            if (parents[v] == -1)
                parents[v] = u;
            if (v == dest)
                break;
            if (visited[v] == 0) {
                queue.push(v);
                visited[v] = 1;
            }
        }
    }

    std::list<int> shortestpath;
    int olddest = dest;
    while (source != dest) {
        shortestpath.push_front(dest);
        dest = parents[dest];
    }
    shortestpath.push_front(source);

    for (auto v : shortestpath) {
        if (v != olddest)
            std::cout << v << "->";
        else
            std::cout << v;
    }
    return shortestpath;
}

int Graph::nthlevelnodecount(int level) {
    std::vector<char> visited(Adjlist.size(), 0);
    std::queue<int> queue;
    std::vector<short> levels(Adjlist.size(), 0);
    queue.push(0);
    visited[0] = 1;
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();
        for (int v : Adjlist[u]) {
            if (visited[v] == 0) {
                levels[v] = levels[u] + 1;
                queue.push(v);
                visited[v] = 1;
            }
        }
    }

    int count = 0;
    std::cout << "Nodes in " << level << " level are ";
    for (int i = 0; i < levels.size(); i++) {
        if (levels[i] == level) {
            //std::cout << i << " ";
            count++;
        }
    }
    std::cout << " / " << count << " / ";
    return count;
}



void Graph::allpossiblepathshelper(int source, int dest, std::vector<bool>& visited, std::vector<int>& current,
    std::vector<std::vector<int>>& allpaths) {
    current.push_back(source);
    visited[source] = 1;

    if (source == dest) {
        allpaths.push_back(current);
    }

    for (int v : Adjlist[source]) {
        if (visited[v] == 0) {
            allpossiblepathshelper(v, dest, visited, current, allpaths);
        }
    }

    visited[source] = 0;
    current.pop_back();
}

void Graph::allpossiblepaths(int source, int dest) {
    std::vector<bool> visited(Adjlist.size(), 0);
    std::vector<int> current;
    std::vector<std::vector<int>> allpaths;
    allpossiblepathshelper(source, dest, visited, current, allpaths);
    for (int i = 0; i < allpaths.size(); ++i) {
        for (int j = 0; j < allpaths[i].size(); ++j) {
            std::cout << allpaths[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

bool Graph::dfsisCycledUndirected(int source, int parent, std::vector<bool>& visited) {
    visited[source] = 1;
    for (int v : Adjlist[source]) {
        if (visited[v] == 0) {
            if (dfsisCycledUndirected(v, source, visited))
                return true;
        }
        else if (v != parent)
            return true;
    }
    return false;
}


bool Graph::isCycledUndirected() {
    std::vector<bool> visited(Adjlist.size(), 0);
    int parent = -1;
    for (int i = 0; i < Adjlist.size(); ++i) {
        if (visited[i] == 0) {
            if (dfsisCycledUndirected(i, parent, visited))
                return true;
        }
    }
    return false;
}

bool Graph::dfsisCycledDirected(int source, std::vector<bool>& visited, std::vector<bool>& recstack) {
    visited[source] = 1;
    recstack[source] = 1;
    for (int v : Adjlist[source]) {
        if (visited[v] == 0) {
            if (dfsisCycledDirected(v, visited, recstack))
                return true;
        }
        else if (recstack[v])
            return true;
    }
    recstack[source] = 0;
    return false;
}


bool Graph::isCycledDirected() {
    std::vector<bool> visited(Adjlist.size(), 0);
    std::vector<bool> recstack(Adjlist.size(), 0);
    for (int i = 0; i < Adjlist.size(); ++i) {
        if (visited[i] == 0) {
            if (dfsisCycledDirected(i, visited, recstack))
                return true;
        }
    }
    return false;
}


void Graph::dfstopSort(int source, std::vector<bool>& visited, std::list<int>& result) {
    visited[source] = 1;
    for (int v : Adjlist[source]) {
        if (visited[v] == 0)
            dfstopSort(v, visited, result);
    }
    result.push_front(source);
}

void Graph::topSort() {
    std::vector<bool> visited(Adjlist.size(), 0);
    std::list<int> result;
    if (isCycledDirected()) {
        std::cout << "Graph is cyclic, doesn't have topsort" << std::endl;
        return;
    }
    for (int i = 0; i < Adjlist.size(); ++i) {
        if (visited[i] == 0) {
            dfstopSort(i, visited, result);
        }
    }

    for (int v : result)
        std::cout << v << " ";
}

void Graph::topSortKahn() {
    std::vector<int> inorder(Adjlist.size());
    std::vector<int> indegree(Adjlist.size());
    for (int i = 0; i < Adjlist.size(); ++i) {
        for (int v : Adjlist[i]) {
            indegree[v]++;
        }
    }

    std::queue<int> queue;
    int index = 0;
    for (int j = 0; j < indegree.size() && index < Adjlist.size(); ++j) {
        if (!indegree[j]) {
            queue.push(j);
            while (!queue.empty()) {
                int u = queue.front();
                queue.pop();
                inorder[index++] = u;
                for (int vertex : Adjlist[u]) {
                    --indegree[vertex];
                    if (!indegree[vertex]) {
                        queue.push(vertex);
                    }
                }
            }
        }
    }

    if (index < inorder.size())
        std::cout << "Cycle detected" << std::endl;
    else {
        for (int v : inorder)
            std::cout << v << " ";
    }
}

void Graph::dfsSccKosaraju(int source, std::vector<bool>& visited, std::stack<int>& stack) {
    visited[source] = 1;
    for (int v : Adjlist[source]) {
        if (!visited[v])
            dfsSccKosaraju(v, visited, stack);
    }
    stack.push(source);
}

void Graph::dfscollectingScc(int source, std::vector<bool>& visited, std::vector<int>& currencscc) {
    visited[source] = 1;
    for (int v : Adjlist[source]) {
        if (!visited[v])
            dfscollectingScc(v, visited, currencscc);
    }
    currencscc.push_back(source);
}

void Graph::SccKosaraju() {
    std::vector<bool> visited(Adjlist.size());
    std::vector<std::vector<int>> Scc;
    int source = 0;
    std::stack<int> stack;
    dfsSccKosaraju(source, visited, stack);
    transpose();
    visited.assign(Adjlist.size(), false);
    std::vector<int> currentscc;
    while (!stack.empty()) {
        int u = stack.top();
        stack.pop();
        if (!visited[u]) {
            dfscollectingScc(u, visited, currentscc);
            Scc.push_back(currentscc);
            currentscc.clear();
        }
    }

    for (int i = 0; i < Scc.size(); ++i) {
        for (int j = 0; j < Scc[i].size(); ++j) {
            std::cout << Scc[i][j] << "  ";
        }
        std::cout << std::endl;
    }

    transpose();
}


void Graph::dfsartPoints(int u, std::vector<int>& disctime, std::vector<int>& lowlink,
    std::vector<int>& parent, std::vector<int>& artPoints, int& time) {
    disctime[u] = lowlink[u] = time++;
    int childcount = 0;
    for (int v : Adjlist[u]) {
        //std::cout << u << "->" << v << std::endl;
        if (disctime[v] == -1) {
            parent[v] = u;
            ++childcount;
            dfsartPoints(v, disctime, lowlink, parent, artPoints, time);
            lowlink[u] = std::min(lowlink[u], lowlink[v]);

            if (parent[u] == -1 && childcount > 1)
                artPoints.push_back(u);

            if (parent[u] != -1 && lowlink[v] >= disctime[u])
                artPoints.push_back(u);
        }
        else if (v != parent[u])
            lowlink[u] = std::min(lowlink[u], lowlink[v]);
    }
}

void Graph::FindArticulationPoints() {
    std::vector<int> disctime(Adjlist.size(), -1);
    std::vector<int> lowlink(Adjlist.size(), INT32_MAX);
    std::vector<int> parent(Adjlist.size(), -1);
    int time = 0;
    std::vector<int> artPoints;
    dfsartPoints(0, disctime, lowlink, parent, artPoints, time);

    for (int i = 0; i < artPoints.size(); ++i)
        std::cout << artPoints[i] << " ";

    std::cout << std::endl;
}


void Graph::dfsartBridges(int u, std::vector<int>& disctime, std::vector<int>& lowlink,
    std::vector<int>& parent, std::vector<std::pair<int, int>>& artBridges, int& time) {
    disctime[u] = lowlink[u] = time++;
    for (int v : Adjlist[u]) {
        //std::cout << u << "->" << v << std::endl;
        if (disctime[v] == -1) {
            parent[v] = u;
            dfsartBridges(v, disctime, lowlink, parent, artBridges, time);
            lowlink[u] = std::min(lowlink[u], lowlink[v]);

            if (lowlink[v] > disctime[u])
                artBridges.push_back({ u, v });
        }
        else if (v != parent[u])
            lowlink[u] = std::min(lowlink[u], lowlink[v]);
    }
}


void Graph::FindArticulationBridges() {
    std::vector<int> disctime(Adjlist.size(), -1);
    std::vector<int> lowlink(Adjlist.size(), INT32_MAX);
    std::vector<int> parent(Adjlist.size(), -1);
    int time = 0;
    std::vector<std::pair<int, int>> artBridges;
    dfsartBridges(0, disctime, lowlink, parent, artBridges, time);

    for (int i = 0; i < artBridges.size(); ++i)
        std::cout << artBridges[i].first << " ->" << artBridges[i].second << std::endl;;

    std::cout << std::endl;
}


void Graph::dfseuler(int source, std::vector<int>& path, std::vector<int>& outdegree) {
    while (outdegree[source] != 0) {
        int index = outdegree[source] - 1;
        --outdegree[source];
        int v = Adjlist[source][index];
        dfseuler(v, path, outdegree);
    }
    path.push_back(source);
}

bool Graph::FindEulerianPaths() {
    std::vector<int> indegree(Adjlist.size());
    std::vector<int> outdegree(Adjlist.size());
    for (int u = 0; u < Adjlist.size(); ++u) {
        outdegree[u] = Adjlist[u].size();
        for (int v : Adjlist[u])
            ++indegree[v];
    }

    std::vector<int> startpoints;
    std::vector<int> endpoints;
    for (int u = 0; u < Adjlist.size(); ++u) {
        if (std::abs(indegree[u] - outdegree[u]) > 1)
            return false;
        else if (indegree[u] - outdegree[u] == 1)
            endpoints.push_back(u);
        else if (outdegree[u] - indegree[u] == 1)
            startpoints.push_back(u);
    }

    if (startpoints.size() == 0 && endpoints.size() == 0) {
        std::vector<int> euleriancycle;
        dfseuler(0, euleriancycle, outdegree);
        std::cout << "Here is eulerian cycle" << std::endl;
        reverse(euleriancycle.begin(), euleriancycle.end());
        for (int i = 0; i < euleriancycle.size(); ++i)
            std::cout << euleriancycle[i] << " ";
        std::cout << std::endl;
    }
    else if (startpoints.size() == 1 && endpoints.size() == 1) {
        std::vector<int> eulerianpath;
        dfseuler(startpoints[0], eulerianpath, outdegree);
        reverse(eulerianpath.begin(), eulerianpath.end());
        for (int i = 0; i < eulerianpath.size(); ++i)
            std::cout << eulerianpath[i] << " ";
        std::cout << std::endl;
    }
    else
        return false;

    return true;
}




