#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
vector<vector<int> > grafo;
vector<int> estado;
vector<vector<int> > tree_edges;
vector<int> padres;
vector<int> back_edges_inferior_en;
vector<int> back_edges_superior_en;
vector<int> memo;
vector<pair<int, int> > back_edges;

int NO_LO_VI = 0;
int EMPECE_A_VER = 1;
int TERMINE_VER = 2;

void sort_by_first_int(vector<pair<int, int>>& pairs) {
  // Create a temporary vector to store the sorted pairs.
  vector<pair<int, int>> sorted_pairs;

  // Iterate over the original vector and add the pairs to the sorted vector in ascending order.
  for (const auto& pair : pairs) {
    // Find the index in the sorted vector where the pair should be inserted.
    int index = std::lower_bound(sorted_pairs.begin(), sorted_pairs.end(), pair, [](const pair<int, int>& a, const pair<int, int>& b) {
      return a.first < b.first;
    }) - sorted_pairs.begin();

    // Insert the pair into the sorted vector at the index.
    sorted_pairs.insert(sorted_pairs.begin() + index, pair);
  }

  // Assign the sorted vector back to the original vector.
  pairs = sorted_pairs;
}

void dfs(int v, int p = -1){
    estado[v] = EMPECE_A_VER;
    for(int u : grafo[v]){
        if(estado[u] == NO_LO_VI){
            tree_edges[v].push_back(u);
            padres[u] = v;
            dfs(u, v);
        }else if(u != p){
            if(estado[u] == EMPECE_A_VER){
                back_edges_inferior_en[v]++;
                back_edges.push_back({v, u});
            }
            else
                back_edges_superior_en[v]++;
        }
    }
    estado[v] = TERMINE_VER;
}

int cubren(int v, int p = -1) {
    if (memo[v] != -1) return memo[v];
    int res = 0;
    for (int hijo : tree_edges[v]) {
        if (hijo != p) {
            res += cubren(hijo, v);
        }
    }
    res -= back_edges_superior_en[v];
    res += back_edges_inferior_en[v];
    memo[v] = res;
    return res;
}

bool chequear(int inf, int sup){
    int it = inf;
    while(inf != sup){
        if(cubren(inf) == 1) return true;
        inf = padres[inf];
    }
    return false;
}

int main(int argc, char** argv){
    int cases;
    cin >> cases;

    while(cases--){
        int n, m;
        cin >> n >> m;


        grafo = vector<vector<int> >(n, vector<int>());
        estado = vector<int>(n, NO_LO_VI);
        back_edges_inferior_en = vector<int>(n, 0);
        back_edges_superior_en = vector<int>(n, 0);
        tree_edges = vector<vector<int> >(n, vector<int>());
        back_edges = vector<pair<int, int> >();
        memo = vector<int>(n+1, -1);
        padres = vector<int>(n, -1);

        for(int i = 0; i < m; i++){
            int u, v;
            cin >> u >> v;

            grafo[u].push_back(v);
            grafo[v].push_back(u);
        }

        dfs(0);
        cubren(0);

        vector<pair<int, int> > aristas_importantes = vector<pair<int, int> >();
        
        for(int i = 1; i < n; i++){
            if(cubren(i) == 1 || cubren(i) == 0){
                aristas_importantes.push_back({min(padres[i], i), max(i, padres[i])});
            }
        }

        vector<pair<int,int>> temp;

        for (auto be : back_edges) {
            int u = be.first, v = be.second;
            for (auto imp : aristas_importantes) {
                if (imp.first == u || imp.first == v || imp.second == u || imp.second == v) {
                    int extremoInf = max(u,v);
                    int extremoSup = min(u,v);  
                    if(!chequear(extremoInf, extremoSup)) continue;
                    temp.push_back({extremoSup, extremoInf});
                    break;
                }
            }
        }
        
        aristas_importantes.insert(aristas_importantes.end(), temp.begin(), temp.end());
        sort_by_first_int(aristas_importantes);
        cout << aristas_importantes.size() << endl;
        for(pair<int, int> arista : aristas_importantes){
            cout << arista.first << " " << arista.second << endl;
        }
    }
    return 0;
}


