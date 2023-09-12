#include <iostream>
#include <vector>

using namespace std;

int main() {
    int casos;
    cin >> casos;

    while (casos--) {
        int N, W;
        cin >> N >> W;

        vector<int> valores(N);
        for (int i = 0; i < N; i++) {
            cin >> valores[i];
        }

        vector<vector<char>> dp(N + 1, vector<char>(2 * W + 1, '?'));

        dp[0][W] = '0';

        for (int i = 1; i <= N; i++) {
            for (int j = 0; j <= 2 * W; j++) {
                if (dp[i - 1][j] != '?') {
                    // Si podemos obtener el saldo j sumando el valor actual, marcamos como venta
                    dp[i][j + valores[i - 1]] = '+';
                    // Si podemos obtener el saldo j restando el valor actual, marcamos como gasto
                    dp[i][j - valores[i - 1]] = '-';
                }
            }
        }

        int saldo_final = W;
        for (int i = N; i > 0; i--) {
            char marcador = dp[i][saldo_final + W];
            if (marcador == '+') {
                cout << '+';
                saldo_final -= valores[i - 1];
            } else if (marcador == '-') {
                cout << '-';
                saldo_final += valores[i - 1];
            } else {
                // Si no está claro, marcamos como ?
                cout << '?';
            }
        }

        cout << endl;
    }

    return 0;
}
