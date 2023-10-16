#include <iostream>
#include <vector>
#include <algorithm>
// Kruskal en O(m log(n))

using namespace std;

long long inf = 1e18;
int n, m;
vector<vector<pair<int, long long>>> g;
vector<pair<long long, pair<int, int>>> aristas;

struct DSU {
    vector<int> p;
    vector<int> rank; // altura del árbol

    DSU(int n){
        p = vector<int>(n, -1);
        rank = vector<int>(n, 1);
    }

    void unite(int u, int v){
        int c1, c2;
        c1 = find(u); c2 = find(v);
        if(c1 == c2) return;
        if(rank[c2] > rank[c1]) swap(c1, c2);
        p[c2] = c1;
        rank[c1] = max(rank[c1], rank[c2]+1);
    }
    
    int find(int u){
        if(p[u] == -1) return u;
        int rep = find(p[u]);
        p[u] = rep;
        return rep;
    }

};

void kruskal(){
    sort(aristas.begin(), aristas.end()); // O(m log(m)) = O(m log (n))

    DSU d(n);

    long long s = 0;
    int agregadas = 0;
    for(auto [w, e] : aristas){ // m alfa^-1(n) en total
        if(d.find(e.first) == d.find(e.second)) continue;

        d.unite(e.first, e.second);
        s += w;
        agregadas ++;
    }
    if(agregadas == n-1){
        cout << s << endl;
    } else {
        cout << "IMPOSSIBLE" << endl;
    }
}


int main(){
    cin >> n >> m;

    g = vector<vector<pair<int, long long>>>(n);

    for(int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        g[v].push_back({u, w});
        g[u].push_back({v, w});
        aristas.push_back({w, {u, v}});
    }

    kruskal();

}