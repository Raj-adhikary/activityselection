#include <iostream>
#include <vector>
#include <algorithm>

struct Edge {
    int src;
    int dest;
    int weight;
};

bool compareEdge(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

class UnionFind {
public:
    UnionFind(int size) : parent(size), rank(size, 0) {
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    bool unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU == rootV) {
            return false;
        }

        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }

        return true;
    }

private:
    std::vector<int> parent;
    std::vector<int> rank;
};

std::vector<Edge> kruskal(int numVertices, const std::vector<Edge>& edges) {
    std::vector<Edge> sortedEdges = edges;
    std::sort(sortedEdges.begin(), sortedEdges.end(), compareEdge);

    UnionFind uf(numVertices);

    std::vector<Edge> mst;
    for (const auto& edge : sortedEdges) {
        if (uf.unionSets(edge.src, edge.dest)) {
            mst.push_back(edge);
        }
    }

    return mst;
}

int main() {
    int numVertices = 5;
    int numEdges = 7;

    std::vector<Edge> edges = {
        {0, 1, 2},
        {0, 3, 6},
        {1, 2, 3},
        {1, 3, 8},
        {1, 4, 5},
        {2, 4, 7},
        {3, 4, 9}
    };

    std::vector<Edge> mst = kruskal(numVertices, edges);

    std::cout << "Edges in the Minimum Spanning Tree:\n";
    for (const auto& edge : mst) {
        std::cout << "Edge (" << edge.src << " -> " << edge.dest << "), Weight: " << edge.weight << "\n";
    }

    return 0;
}
