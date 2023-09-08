#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int offset;
vector<int> valores = vector<int>(101, 0);
vector<vector<int> > memo = vector<vector<int> >(101, vector<int>((2*100*100) + 1, -1));
vector<pair<bool, bool> > signos = vector<pair<bool, bool> >(101, make_pair(false,false));

bool saldos(int i, int acumulado, int w, vector<int>& v, vector<vector<int> >& memo, vector<pair<bool, bool> >& signos){
    if(i == 0)
        return acumulado == 0;
    if(memo[i][acumulado+offset] == -1){
        bool sumar = saldos(i-1, acumulado+v[i-1], w, v, memo, signos);
        bool restar = saldos(i-1, acumulado-v[i-1], w, v, memo, signos);

        if(sumar)
            signos[i-1].first = true;
        
        if(restar)
            signos[i-1].second = true;
        
        memo[i][acumulado+offset] = sumar || restar;
    }
    return memo[i][acumulado+offset];
}


int main() {

    int casos = 0;
    cin >> casos;
    
    for(int caso = 0; caso < casos; caso++){
        int n, w;
        cin >> n;
        cin >> w;
        for(int x = 0; x < n; x++){
            int val;
            cin >> val;
            valores[x] = val/100;
        }

        offset = 100*n;
        w /= 100;

        if(!saldos(n, w, w, valores, memo, signos)){
            cout << "imposible" << endl;
            continue;
        }

        for(int i = 0; i < n; i++){
            if(signos[i].first and !signos[i].second)
                cout << "-";
            else if(!signos[i].first and signos[i].second)
                cout << "+";
            else
                cout << '?';
        }
        cout << endl;

        
        for(int i = 0; i < n; i++){
            for(int j = 0; j < (2*offset)+1; j++){
                memo[i][j] = -1;
            }
        }
        for(int i = 0; i < n; i++){
            signos[i] = make_pair(false, false);
        }
        for(int i = 0; i < n; i++){
            valores[i] = 0;
        }
    }

    return 0;
}