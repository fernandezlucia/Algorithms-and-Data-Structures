#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <limits.h>

using namespace std;

#define INF INT_MAX

int n;
vector<vector<int>> aristas;
vector<vector<bool>> aristas_orig;
vector<vector<int>> matriz_orig;

void printSolution(vector<vector<int>> &matriz_dist){
    for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (matriz_dist[i][j] == INF)
				cout << "INF"
					<< " ";
			else
				cout << matriz_dist[i][j] << " ";
		}
		cout << endl;
	}
}

bool floydWarshallCheck(vector<vector<int>> &dist){
	int i, j, k;
    bool res = true;
	for (k = 0; k < n; k++) {
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (dist[i][k] != INF && dist[k][j] != INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
            if(matriz_orig[i][j] != INF && dist[i][j] < matriz_orig[i][j]){
                return false;
            }
		}
	}  

    for (k = 0; k < n; k++) {
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
                //if(aristas_orig[i][j]) continue;
                if(k == i || k == j) continue;
                if(i == j) aristas[i][j] = 0;
				else if(dist[i][j] == dist[i][k] + dist[k][j]){
                    aristas[i][j] = INF;
			    }
		    }
	    }
    }
    return res;
}

void floydWarshall(vector<vector<int>> &d){
    int i, j, k;
	for (k = 0; k < n; k++) {
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (d[i][k] < INF && d[k][j] < INF)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]); 
			}
		}
	}
}

int main(){
    int c;
    cin >> c;

    for(int k = 0; k < c; k++){
        cin >> n;
        vector<vector<int>> matriz_ady(n, vector<int>(n, INF));
        aristas = vector<vector<int>>(n, vector<int>(n, 0));
        aristas_orig = vector<vector<bool>>(n, vector<bool>(n, false));
        for(int i = 1; i < n; i++){
            for(int j = 0; j < i; j++){
                int temp;
                cin >> temp;
                matriz_ady[i][j] = temp;
                matriz_ady[j][i] = temp;
                aristas[i][j] = 1;
                aristas[j][i] = 1;
            }
        }

        matriz_orig = matriz_ady;

        if(!floydWarshallCheck(matriz_ady)){
            cout << "IMPOSIBLE" << endl;
            continue;
        }else{
            floydWarshall(aristas);
            cout << "POSIBLE" << endl;
            printSolution(aristas);
        }
    }
    return 0;
}
