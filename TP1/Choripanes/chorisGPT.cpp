#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

// Función para calcular el costo de colocar una proveeduría en 'pos' para servir los puestos entre 'l' y 'r'
int cost(int l, int r, int pos, vector<int>& positions) {
    int totalCost = 0;
    for(int i = l; i <= r; ++i) {
        totalCost += abs(positions[i] - pos);
    }
    return totalCost;
}

// Función de DP top-down
int dp(int n, int k, vector<int>& positions, vector<vector<int>>& memo, vector<vector<pair<int, int>>>& parent) {
    if(k == 0) {
        return (n == 0) ? 0 : INT_MAX;
    }
    if(n == 0) {
        return INT_MAX;
    }

    if(memo[n][k] != -1) {
        return memo[n][k];
    }

    int minCost = INT_MAX;
    int best_m = -1;
    int best_pos = -1;

    for(int m = 1; m <= n; ++m) {
        int median_pos = positions[m + (n - m) / 2 - 1];
        int current_cost = dp(m - 1, k - 1, positions, memo, parent) + cost(m - 1, n - 1, median_pos, positions);
        if(current_cost < minCost) {
            minCost = current_cost;
            best_m = m;
            best_pos = median_pos;
        }
    }

    memo[n][k] = minCost;
    parent[n][k] = make_pair(best_m, best_pos);
    return minCost;
}

// Función para reconstruir la solución
vector<int> reconstruct(int n, int k, vector<vector<pair<int, int>>>& parent) {
    if(k == 0) {
        return {};
    }
    pair<int, int> p = parent[n][k];
    vector<int> positions = reconstruct(p.first - 1, k - 1, parent);
    positions.push_back(p.second);
    return positions;
}

int main() {
    int c;
    cout << "Número de casos de test: ";
    cin >> c;

    while(c--) {
        int N, K;
        cin >> N >> K;
        vector<int> positions(N);
        for(int i = 0; i < N; ++i) {
            cin >> positions[i];
        }

        vector<vector<int>> memo(N + 1, vector<int>(K + 1, -1));
        vector<vector<pair<int, int>>> parent(N + 1, vector<pair<int, int>>(K + 1, make_pair(-1, -1)));

        // Calcular el costo mínimo
        int minCost = dp(N, K, positions, memo, parent);
        cout << "Costo mínimo: " << minCost << endl;

        // Reconstruir e imprimir la solución
        vector<int> solution = reconstruct(N, K, parent);
        cout << "Posiciones de las proveedurías: ";
        for(int pos : solution) {
            cout << pos << " ";
        }
        cout << endl;
    }

    return 0;
}

    #include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

// Función para calcular el costo de colocar una proveeduría en 'pos' para servir los puestos entre 'l' y 'r'
int cost(int l, int r, int pos, vector<int>& positions) {
    int totalCost = 0;
    for(int i = l; i <= r; ++i) {
        totalCost += abs(positions[i] - pos);
    }
    return totalCost;
}

// Función de DP top-down
int dp(int n, int k, vector<int>& positions, vector<vector<int>>& memo, vector<vector<pair<int, int>>>& parent) {
    if(k == 0) {
        return (n == 0) ? 0 : INT_MAX;
    }
    if(n == 0) {
        return INT_MAX;
    }

    if(memo[n][k] != -1) {
        return memo[n][k];
    }

    int minCost = INT_MAX;
    int best_m = -1;
    int best_pos = -1;

    for(int m = 1; m <= n; ++m) {
        int median_pos = positions[m + (n - m) / 2 - 1];
        int current_cost = dp(m - 1, k - 1, positions, memo, parent) + cost(m - 1, n - 1, median_pos, positions);
        if(current_cost < minCost) {
            minCost = current_cost;
            best_m = m;
            best_pos = median_pos;
        }
    }

    memo[n][k] = minCost;
    parent[n][k] = make_pair(best_m, best_pos);
    return minCost;
}

// Función para reconstruir la solución
vector<int> reconstruct(int n, int k, vector<vector<pair<int, int>>>& parent) {
    if(k == 0) {
        return {};
    }
    pair<int, int> p = parent[n][k];
    vector<int> positions = reconstruct(p.first - 1, k - 1, parent);
    positions.push_back(p.second);
    return positions;
}

int main() {
    int c;
    cout << "Número de casos de test: ";
    cin >> c;

    while(c--) {
        int N, K;
        cin >> N >> K;
        vector<int> positions(N);
        for(int i = 0; i < N; ++i) {
            cin >> positions[i];
        }

        vector<vector<int>> memo(N + 1, vector<int>(K + 1, -1));
        vector<vector<pair<int, int>>> parent(N + 1, vector<pair<int, int>>(K + 1, make_pair(-1, -1)));

        // Calcular el costo mínimo
        int minCost = dp(N, K, positions, memo, parent);
        cout << "Costo mínimo: " << minCost << endl;

        // Reconstruir e imprimir la solución
        vector<int> solution = reconstruct(N, K, parent);
        cout << "Posiciones de las proveedurías: ";
        for(int pos : solution) {
            cout << pos << " ";
        }
        cout << endl;
    }

    return 0;
}
