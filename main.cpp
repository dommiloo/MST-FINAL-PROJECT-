#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Vertex {
    int id;
    explicit Vertex(int id_) : id(id_) {}
};

struct Edge {
    int src;
    int dest;
    int weight;
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
};


class UnionFind {
    vector<int> parent, rank;
public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (x != parent[x])
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unionSets(int x, int y) {
        int xr = find(x);
        int yr = find(y);
        if (xr == yr) return false;
        if (rank[xr] < rank[yr])
            parent[xr] = yr;
        else if (rank[xr] > rank[yr])
            parent[yr] = xr;
        else {
            parent[yr] = xr;
            rank[xr]++;
        }
        return true;
    }
};


vector<Edge> kruskalMST(int numVertices, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    UnionFind uf(numVertices);
    vector<Edge> mst;

    for (const auto& edge : edges) {
        if (uf.unionSets(edge.src, edge.dest)) {
            mst.push_back(edge);
        }
    }

    return mst;
}

int main() {
    int numVertices = 5;
    vector<Vertex> vertices;
    for (int i = 0; i < numVertices; ++i)
        vertices.emplace_back(i);

    vector<Edge> edges = {
        Edge(0, 1, 10),
        Edge(0, 2, 6),
        Edge(0, 3, 5),
        Edge(1, 3, 15),
        Edge(2, 3, 4)
    };

    vector<Edge> mst = kruskalMST(numVertices, edges);

    int totalWeight = 0;
    cout << "MST Edges:\n";
    for (const auto& edge : mst) {
        cout << edge.src << " -- " << edge.dest << " == " << edge.weight << endl;
        totalWeight += edge.weight;
    }

    cout << "Total weight of MST: " << totalWeight << endl;
    return 0;
}
