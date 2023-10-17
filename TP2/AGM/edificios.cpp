#include<iostream>
#include<vector>
#include<algorithm>
#include <queue>
#include <tuple>
#include <limits.h>

using namespace std;

const long long inf = 1e18;

struct Arista{
    int dst;
    int d;
    int r;
};

int edificios;
int cant_conexiones;
vector<vector<Arista>> ady;

int totalDG;
int totalDR;
double epsilon = 1e-4;

tuple<bool, int, int> esValido(float C) {
    priority_queue<tuple<float, int, int, int>> pq;
    vector<bool> visitado(edificios, false);
    
    for(Arista e : ady[0]){
        pq.push({(e.d - C * e.r), e.dst,e.d,e.r});
    }
    
    visitado[0] = true;
    int edges = 0;
    int totalD = 0;
    int totalR = 0;
    
    while(!pq.empty()) {
        int value;
        int dst;
        int d,r;
        tie(value, dst, d,r) = pq.top();
        pq.pop();
        
        if(!visitado[dst]){
            visitado[dst] = true;

            totalD += d;
            totalR += r;

            for(Arista e : ady[dst]){
                if(e.d != inf && !visitado[e.dst]){
                    float cost = (e.d - C * e.r);
                    pq.push({cost, e.dst, e.d, e.r});
                }
            }
            edges++;
        }
    }
    
    if(edges != edificios-1) return {0,0,0};
    
    bool res = ((float)totalD / (float)totalR) >= C;
    return {res, totalD, totalR};
}

void solve() {
    double low = 0, high = 10e6, mid;
    int D, R;
    while(high-low > epsilon){
        mid = (low + high) / 2.0;
        bool valido;
        int d, r;
        tie(valido, d, r) = esValido(mid);
        if(valido) {
            low = mid;
            D = d;
            R = r;
        } else {
            high = mid;
        }
    }
    cout << D << " " << R << endl;
}

int main(){
    int casos;
    cin >> casos;

    while(casos--){
        cin >> edificios >> cant_conexiones;

        ady = vector<vector<Arista>>(edificios);

        for(int i = 0; i < cant_conexiones; ++i){
            int e1, e2;
            int d, r;
            cin >> e1 >> e2 >> d >> r;
            e1--; e2--;
            ady[e1].push_back({e2, d, r});
            ady[e2].push_back({e1, d, r});
        }

        solve();
    }

   return 0;
}