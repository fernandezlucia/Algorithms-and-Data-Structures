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
vector<vector<bool>> removerAristas;
int n,m;

int NO_LO_VI = 0;
int EMPECE_A_VER = 1;
int TERMINE_VER = 2;

void dfs(int v, int p, vector<int>& estado, vector<int>& padres, vector<vector<int>>& tree_edges, vector<int>& back_edges_inferior_en, vector<int>& back_edges_superior_en, vector<pair<int,int>>& back_edges){
    estado[v] = EMPECE_A_VER;
    for(int u : grafo[v]){
        if(removerAristas[v][u] || removerAristas[u][v]) {continue; }
        if(estado[u] == NO_LO_VI){
            padres[u] = v;
            tree_edges[v].push_back(u);
            dfs(u, v, estado, padres, tree_edges, back_edges_inferior_en, back_edges_superior_en, back_edges);
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

int cubren(int v, int p, vector<int>& memo, vector<vector<int>>& tree_edges, vector<int>& back_edges_inferior_en, vector<int>& back_edges_superior_en) {
    if (memo[v] != -1) return memo[v];
    int res = 0;
    for (int hijo : tree_edges[v]) {
        if(removerAristas[v][hijo]) continue;
        if (hijo != p) {
            res += cubren(hijo, v, memo, tree_edges, back_edges_inferior_en, back_edges_superior_en);
        }
    }
    res -= back_edges_superior_en[v];
    res += back_edges_inferior_en[v];
    memo[v] = res;
    return res;
}

bool chequear(int inf, int sup, vector<int>& padres, vector<int>& memo, vector<vector<int>>& tree_edges, vector<int>& back_edges_inferior_en, vector<int>& back_edges_superior_en){
    int it = inf;
    while(inf != sup){
        if(cubren(inf, -1, memo, tree_edges, back_edges_inferior_en, back_edges_superior_en) == 1) return true;
        inf = padres[inf];
    }
    return false;
}

int encontrarPuentes(){
    
    int res = 0;

    vector<int> estado = vector<int>(n, NO_LO_VI);
    vector<int> back_edges_inferior_en = vector<int>(n, 0);
    vector<int> back_edges_superior_en = vector<int>(n, 0);
    vector<vector<int> > tree_edges = vector<vector<int> >(n, vector<int>());
    vector<pair<int, int> > back_edges = vector<pair<int, int> >();
    vector<int> memo = vector<int>(n, -1);
    vector<int> padres = vector<int>(n, -1);
    

    dfs(0, -1, estado, padres, tree_edges, back_edges_inferior_en, back_edges_superior_en, back_edges);

    for(int i = 1; i < n; i++){
        if(cubren(i, -1, memo, tree_edges, back_edges_inferior_en, back_edges_superior_en) == 0){
            res++;
        }
    }
    return res;

}

int main(int argc, char** argv){
    int cases;
    cin >> cases;

    while(cases--){
        cin >> n >> m;

        grafo = vector<vector<int> >(n, vector<int>());
        removerAristas = vector<vector<bool>>(n, vector<bool>(n*n, false));
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
        vector<pair<int, int> > aristas_importantes = vector<pair<int, int> >();
        dfs(0, -1, estado, padres, tree_edges, back_edges_inferior_en, back_edges_superior_en, back_edges);

        for (auto be : back_edges) {
            int u = be.first, v = be.second;
            int extremoInf = max(u,v);
            int extremoSup = min(u,v);  
            if(!chequear(extremoInf, extremoSup, padres, memo, tree_edges, back_edges_inferior_en, back_edges_superior_en)) continue;
            aristas_importantes.push_back({extremoSup, extremoInf});        
        }

        for(int i = 0; i < n; i++){
            for(int j : tree_edges[i]){
                
                removerAristas[i][j] = true;
                removerAristas[j][i] = true;

                if(encontrarPuentes() > 0){
                    aristas_importantes.push_back({min(i, j), max(i, j)});
                }
            
                removerAristas[i][j] = false;
                removerAristas[j][i] = false;
            }
        }
        sort(aristas_importantes.begin(), aristas_importantes.end());
        cout << aristas_importantes.size() << endl;
        for(pair<int, int> arista : aristas_importantes){
            cout << arista.first << " " << arista.second << endl;
        }
    }
    return 0;
}


