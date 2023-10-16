#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const ll inf = 1e18;

int n, m;
vector<vector<pair<ll, int>>> g;

void prim(){
    priority_queue<pair<ll, pair<int, int>>> q;
    vector<bool> visited(n, false);

    //pusheo a la queue los adyacentes a la raiz
    for(auto [w, v] : g[0]){
        q.push(make_pair(-w, make_pair(0, v)));
    }

    //marco la raiz como visitada
    visited[0] = true;
    int edges = 0;
    ll s = 0;
    //voy vaciando la queue
    while(!q.empty()){
        ll w;
        pair<int, int> e; //arista
        //separo el peso y la tupla que saco de la cola
        tie(w, e) = q.top();
        q.pop(); //desencolo

        if(!visited[e.second]){
            visited[e.second] = true;
            //si no visite el nodo de fuera de la frontera lo marco como visitado
            //recorro los adyacentes del de afuera de la frontwea y los encolo
            for(auto [w2, v] : g[e.second]){
                q.push(make_pair(-w2, make_pair(e.second, v)));
            }
            //sumo el costo que viene teniendo este AGM
            s += -w;
            //aumenro la cantidad de aristas que viene teniebdo este AGM
            edges ++;
        }
    }
    if(edges == n-1){
        cout << s << endl;
    } else {
        cout << "IMPOSSIBLE" << endl;
    }
}

int main() {
    cin>>n>>m;
    
    g = vector<vector<pair<ll,int>>>(n);

    for(int i = 0; i < m; i++){
        int u,v; ll c;
        cin>>u>>v>>c;
        u--, v--;
        g[v].push_back({c,u});
        g[u].push_back({c,v});
    }
    prim_m_lg_n();
    return 0;
}