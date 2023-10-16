#include <iostream>
#include <vector>
// Prim en O(n^2)

using namespace std;

long long inf = 1e18;
int n, m;
vector<vector<pair<int, long long>>> g;

// (u, v) está en la frontera si u están
void prim(){
    // empezamos de 0
    vector<bool> enArbol(n, false);
    enArbol[0] = true;

    vector<long long> d(n, inf);
    for(pair<int, long long> a : g[0]){
        d[a.first] = a.second;
    }

    long long s = 0;
    for(int it = 0; it < n-1; it++){
        // queremos la arista de menor peso de las que están en la frontera
        int masCercano = -1;
        for(int i = 0; i < n; i++){ // nodos candidatos a agregar
            if(enArbol[i]) continue;
            // queremos que d[i] sea el peso de la arista más chica de i a un nodo del árbol (si no existe, inf)
            if(masCercano == -1 || d[i] < d[masCercano]){
                masCercano = i;
            }
        }
        if(d[masCercano] == inf){
            cout << "IMPOSSIBLE" << endl;
            return;
        }

        enArbol[masCercano] = true;
        s += d[masCercano];

        for(auto [v, w] : g[masCercano]){
            if(enArbol[v]) continue;
            if(w < d[v]){
                d[v] = w;
            }
        }
    }
    cout << s << endl;
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
    }

    prim();

}