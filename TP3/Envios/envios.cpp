#include<vector>
#include<iostream>
#include<queue>
#include<limits.h>
#include<cmath>
using namespace std;

int n, m, personas;
vector<vector<int>> capacity;
vector<vector<int>> capacityOriginal;
vector<vector<int>> adj;
int max_cap;

int INF = INT_MAX;

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] +=  new_flow;
            cur = prev;
        }
    }

    return flow;
}


void solve(){
    int high = personas * (max_cap+1);
    int low = 0; int mid;
    capacityOriginal = capacity;
    int res = 0;
    while(high-low > 1){
        mid = (high+low)/2;

        int bundle_size = mid / personas;

        if(bundle_size == 0){
            low = mid;
            continue;
        }

        for(int i = 0; i < n; i++){
            for(int j : adj[i]){
                capacity[i][j] = capacityOriginal[i][j] / bundle_size;
            }
        }

        int flow = maxflow(0, n-1);

        if(flow >= personas){
            res = bundle_size*personas;
            low = mid;
        }
        else{
            high = mid;
        }

    }
    cout << res << endl;
}


int main(){
    int c;

    cin >> c;
    for (int i = 0; i < c; i++){
        max_cap = 0;
        cin >> n >> m >> personas;



        adj = vector<vector<int>>(n);
        capacity = vector<vector<int>>(n, vector<int>(n, 0));

        for(int k = 0; k < m; k++){
            int inicio; int destino; int capacidad;
            cin >> inicio >> destino >> capacidad;
            inicio--; destino--;
            adj[inicio].push_back(destino);
            adj[destino].push_back(inicio);
            capacity[inicio][destino] = capacidad;

            if(capacidad >= max_cap)
                max_cap = capacidad;
        }
        
        solve();
    }

    return 0;
}