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
vector<int> cant;
vector<int> arist;

int NO_LO_VI = 0;
int EMPECE_A_VER = 1;
int TERMINE_VER = 2;


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

int main(int argc, char** argv){
    int c;
    cant = {};
    cin >> c;

    for(int y = 0; y < c; y++){
        int n, m;
        cin >> n >> m;

        grafo = vector<vector<int> >(n, vector<int>());
        estado = vector<int>(n, NO_LO_VI);
        back_edges_inferior_en = vector<int>(n, 0);
        back_edges_superior_en = vector<int>(n, 0);
        tree_edges = vector<vector<int> >(n, vector<int>());
        back_edges = vector<pair<int, int> >();
        memo = vector<int>(n, -1);
        padres = vector<int>(n, -1);

        for(int i = 0; i < m; i++){
            int u, v;
            cin >> u >> v;
            grafo[u].push_back(v);
            grafo[v].push_back(u);
        }

        dfs(0);
        cubren(0);
        vector<pair<int,int>> aristas_importantes = vector<pair<int,int>>();
        for(int i = 1; i < n; i++){
            if(cubren(i) == 1){
                aristas_importantes.push_back({min(padres[i],i), max(i, padres[i])});
            }
        }

        vector<pair<int,int>> temp;
        for (auto be : back_edges) {
            int u = be.first, v = be.second;
            // Comprueba si u o v son extremos de alguna arista importante
            for (auto imp : aristas_importantes) {
                if (imp.first == u || imp.first == v || imp.second == u || imp.second == v) {
                    temp.push_back({min(u, v), max(u, v)});
                    break;
                }
            }
        }
        aristas_importantes.insert(aristas_importantes.end(), temp.begin(), temp.end());
        sort(aristas_importantes.begin(), aristas_importantes.end());
        
        cant.push_back(aristas_importantes.size());
        for(pair<int, int> arista : aristas_importantes){
            arist.push_back(arista.first);
            arist.push_back(arista.second);
        }
    }


    for(int j = 0; j < cant.size(); j++){
        int f = cant[j];
        cout << f << endl;
        if(f != 0){
            for(int k=0; k < (f*2); k=k+2){
                cout << arist[k] << " " << arist[k+1] << endl;;
            }
            for(int l=0; l < (f*2); l++){
                arist.erase(arist.begin());
            }
        }
    }

    return 0;
}


