#include<vector>
#include<iostream>
#include<limits.h>
#include<queue>

using namespace std;
int n;
vector<vector<int>> tablero;
vector<vector<int>> adj;
vector<vector<int>> capacity;
int INF = INT_MAX;
int grafoSize;

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
    vector<int> parent(grafoSize);
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

void printMatrix(vector<vector<int>> &matriz){
    for (int i = 0; i < matriz.size(); i++) {
		for (int j = 0; j < matriz[i].size() ; j++) {
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}
}

void printSeg(vector<vector<pair<int,int>>> &matriz){
    for (int i = 0; i < matriz.size(); i++) {
		for (int j = 0; j < matriz[i].size(); j++) {
			cout << matriz[i][j].first << "," << matriz[i][j].second << " ";
		}
		cout << endl;
	}
}

vector<vector<pair<int, int>>> getRowSegments(vector<vector<int>>& tablero){
    vector<vector<pair<int,int>>> rowSegments;
    for(vector<int> row : tablero){
        vector<pair<int, int>> segments;
        int start = -1;
        for(int i = 0; i < n; i++){
            if(row[i] == 0 && start == -1){
                start = i;
            }
            if(row[i] == 1 && start != -1){
                segments.emplace_back(start, i-1);
                start = -1;
            }
        }
        if(start != -1)
            segments.emplace_back(start, row.size()-1);

        rowSegments.push_back(segments);
        
    }
    return rowSegments;
}

vector<vector<pair<int, int>>> getColumnSegments(vector<vector<int>>& tablero){
    vector<vector<pair<int,int>>> colSegments(n);
    for(int j = 0; j < n; j++){
        int start = -1;
        for(int i = 0; i < n; i++){
            if(tablero[i][j] == 0 && start == -1){
                start = i;
            }
            if(tablero[i][j] == 1 && start != -1){
                colSegments[j].emplace_back(start, i-1);
                start = -1;
            }
        }
        if(start != -1){
            colSegments[j].emplace_back(start, n-1);
        }
    }
    return colSegments;
}

void buildGraph(vector<vector<int>>& tablero){
    vector<vector<pair<int, int>>> rowSegments = getRowSegments(tablero);
    vector<vector<pair<int, int>>> columnSegments = getColumnSegments(tablero);

    vector<vector<int>> mSegR = vector<vector<int>>(n, vector<int>(n, -1));
    vector<vector<int>> mSegC = vector<vector<int>>(n, vector<int>(n, -1));

    int rowV = 0;
    int colV = 0;

    int segmento = 1;
    for(int i = 0; i < rowSegments.size(); i++){
        int segmentos = rowSegments[i].size();
        rowV += segmentos;
        for(int j = 0; j < segmentos; j++){
            for(int k = rowSegments[i][j].first; k <= rowSegments[i][j].second; k++){
                mSegR[i][k] = segmento;
            }
            segmento++;
        }
    }
    
    for(int i = 0; i < columnSegments.size(); i++){
        int segmentos = columnSegments[i].size();
        colV += segmentos;
        for(int j = 0; j < segmentos; j++){
            for(int k = columnSegments[i][j].first; k <= columnSegments[i][j].second; k++){
                mSegC[k][i] = segmento;
            }
            segmento++;
        }
    }

    adj = vector<vector<int>>(rowV + colV + 2);
    capacity = vector<vector<int>>(rowV+colV+2, vector<int>(rowV+colV+2, 0));

    for(int i = 0; i < mSegR.size(); i++){
        for(int j = 0; j < mSegR[i].size(); j++){
            if(mSegR[i][j] != -1 && mSegC[i][j] != -1){
                adj[mSegR[i][j]].push_back(mSegC[i][j]);
                adj[mSegC[i][j]].push_back(mSegR[i][j]);
                capacity[mSegR[i][j]][mSegC[i][j]] = 1;
            }
        }
    }

    for(int i = 1; i <= rowV; i++){
        adj[0].push_back(i);
        adj[i].push_back(0);
        capacity[0][i] = 1;
    }
    for(int i = rowV + 1; i <= rowV+colV; i++){
        adj[i].push_back(rowV+colV+1);
        adj[rowV+colV+1].push_back(i);
        capacity[i][rowV+colV+1] = 1;
    }
    grafoSize = rowV+colV+2;
    cout << maxflow(0, rowV+colV+1) << endl;
}

int main(){
    int casos;
    cin >> casos;
    while(casos--){
        cin >> n;
        tablero = vector<vector<int>>(n, vector<int>(n, 0));

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                cin >> tablero[i][j];
            }
        }
        buildGraph(tablero);
    }
}

