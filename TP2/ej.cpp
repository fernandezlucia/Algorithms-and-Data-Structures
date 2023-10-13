#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>

using namespace std;

struct Node {
  int id;
  int depth;
  int backedges_down;
  int backedges_up;
};

void dfs(vector<vector<int>> &adj, vector<Node> &nodes, int u, int parent) {
  nodes[u].depth = nodes[parent].depth + 1;

  for (int v : adj[u]) {
    if (v == parent) {
      continue;
    }

    if (nodes[v].depth < nodes[u].depth) {
      dfs(adj, nodes, v, u);
    } else {
      nodes[u].backedges_down++;
    }
  }

  for (int v : adj[u]) {
    if (nodes[v].depth <= nodes[u].depth) {
      nodes[u].backedges_up++;
    }
  }
}

vector<Node> dfs_tree(vector<vector<int>> &adj) {
  int n = adj.size();
  vector<Node> nodes(n);

  for (int i = 0; i < n; i++) {
    nodes[i].id = i;
    nodes[i].backedges_down = 0;
    nodes[i].backedges_up = 0;
  }

  dfs(adj, nodes, 0, -1);

  return nodes;
}


int main() {
  vector<vector<int>> adj = {{1, 2}, {0, 2}, {1, 3}, {2, 3}};

  vector<Node> nodes = dfs_tree(adj);

  for (Node node : nodes) {
    cout << "Nodo " << node.id << ": depth = " << node.depth << ", backedges down = " << node.backedges_down << ", backedges up = " << node.backedges_up << endl;
  }

  return 0;
}

/*

Nodo 0: depth = 0, backedges down = 0, backedges up = 0
Nodo 1: depth = 1, backedges down = 1, backedges up = 1
Nodo 2: depth = 1, backedges down = 0, backedges up = 2
Nodo 3: depth = 2, backedges down = 0, backedges up = 0


*/