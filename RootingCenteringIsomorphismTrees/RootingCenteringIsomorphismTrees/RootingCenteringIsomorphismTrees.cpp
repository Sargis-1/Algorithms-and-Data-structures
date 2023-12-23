#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


//This algorithms checks if given trees are isomorphic(same by structure) or not.
struct TreeNode {
    int _id;
    TreeNode* _parent;
    std::vector<TreeNode*> _children;

    TreeNode(int id, TreeNode* parent, std::vector<TreeNode*> children):_id(id), _parent(parent),
        _children(children){}


};

class Graph {
public:
    Graph() {}

    ~Graph() {}

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

    void addEdge(int source, int dest) {
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
        if (std::find(Adjlist[dest].begin(), Adjlist[dest].end(), source) == Adjlist[dest].end()) {
            Adjlist[dest].push_back(source);
        }
    }

    void printGraph() {
        for (int i = 0; i < Adjlist.size(); i++) {
            std::cout << i << " -> ";
            for (int j = 0; j < Adjlist[i].size(); j++)
                std::cout << Adjlist[i][j] << " /";
            std::cout << std::endl;
        }
    }

    std::vector<int> collectindegrees() {
        std::vector<int> inDegree(Adjlist.size());
        for (int i = 0; i < Adjlist.size(); ++i) {
            for (int j = 0; j < Adjlist[i].size(); ++j) {
                ++inDegree[i];
            }
        }

        return inDegree;
    }

public:
    std::vector<std::vector<int>> Adjlist;
};


void buildTree(Graph& g, TreeNode* node, TreeNode* parent = nullptr){
    for (int v : g.Adjlist[node->_id]) {
        if (parent && v == parent->_id)
            continue;
        TreeNode* child = new TreeNode(v, node, {});
        node->_children.push_back(child);
        buildTree(g, child, node);
    }
}


TreeNode* rootTree(Graph& g, int root_id) {
    TreeNode* root = new TreeNode(root_id, nullptr, {});
    buildTree(g, root);
    return root;
}


void dfs(TreeNode* node) {
    if (!node)
        return;

    std::cout << node->_id << " " << std::endl;
    for (TreeNode* child : node->_children) 
        dfs(child);
    
}


std::vector<int> treeCentering(Graph& g) {
    std::vector<int> indegree = g.collectindegrees();
    std::vector<int> leaves; 
    int leafcount = 0;
    
    while (leafcount < g.Adjlist.size()) {
        std::vector<int> newleaves;
    
        for (int i = 0; i < indegree.size(); ++i) {
            if (indegree[i] == 1) {
                leaves.push_back(i);
            }
        }

        leafcount += leaves.size();
        
        for (int j = 0; j < leaves.size(); ++j) {
            for (int v : g.Adjlist[leaves[j]]) {
                --indegree[v];
                if (indegree[v] == 1)
                    newleaves.push_back(v);
            }
        }

        leaves = newleaves;
    }

    /*for (int elem : leaves) {
        std::cout << elem << " ";
    }*/

    return leaves;
}


std::string encode(TreeNode* node) {
    if (!node)
        return "";

    std::vector<std::string> labels;
    for (TreeNode* child : node->_children) {
        labels.push_back(encode(child));
    }

    std::sort(labels.begin(), labels.end());
    std::string res;

    for (std::string str : labels)
        res += str;

    return "(" + res + ")";
}


bool TreesareIsom(Graph g1, Graph g2) {
    int treecenter1 = treeCentering(g1)[0];
    std::vector<int> treecenter2 = treeCentering(g2);
    TreeNode* root1 = rootTree(g1, treecenter1);
    std::string s1 = encode(root1);

    for (int elem : treecenter2) {
        TreeNode* root2 = rootTree(g2, elem);
        std::string s2 = encode(root2);
        if (s1 == s2)
            return true;
    }

    return false;
}


int main()
{
    /*Graph g;
    g.addVertex(0);
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
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(3, 0);
    g.addEdge(0, 9);
    g.addEdge(9, 10);
    g.addEdge(10, 4);
    g.addEdge(10, 5);
    g.addEdge(9, 8);
    g.addEdge(8, 7);
    g.addEdge(8, 6);*/


    /*Graph g1;
    g1.addVertex(0);
    g1.addVertex(1);
    g1.addVertex(2);
    g1.addVertex(3);
    g1.addVertex(4);
    g1.addVertex(5);
    g1.addEdge(4, 1);
    g1.addEdge(4, 3);
    g1.addEdge(1, 0);
    g1.addEdge(1, 2);
    g1.addEdge(3, 5);*/
    //g1.printGraph();

    /*Graph g2;
    g2.addVertex(0);
    g2.addVertex(1);
    g2.addVertex(2);
    g2.addVertex(3);
    g2.addVertex(4);
    g2.addVertex(5);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 4);
    g2.addEdge(4, 3);
    g2.addEdge(4, 5);*/
    //g2.printGraph();

    Graph g3;
    g3.addVertex(0);
    g3.addVertex(1);
    g3.addVertex(2);
    g3.addVertex(3);
    g3.addVertex(4);
    g3.addEdge(0, 2);
    g3.addEdge(0, 3);
    g3.addEdge(1, 4);
    g3.addEdge(2, 4);
    //g3.printGraph();

    Graph g4;
    g4.addVertex(0);
    g4.addVertex(1);
    g4.addVertex(2);
    g4.addVertex(3);
    g4.addVertex(4);
    g4.addEdge(0, 1);
    g4.addEdge(0, 4);
    g4.addEdge(1, 2);
    g4.addEdge(2, 3);
    //g4.printGraph();

    //TreeNode* myroot = rootTree(g, 5);
    //dfs(myroot);
    
    bool a = TreesareIsom(g3, g4);
    if (a)
        std::cout << "Trees are Isomorphic";
    else
        std::cout << "Trees are NOT Isomorphic";
}

