/*
int flujoMaximo(vector<vector<int>>& red_residual, vector<vector<int>> flujo){
    vector<pair<int, int>> camino;
    int flujo_max = 0;
    while(caminoAumento(red_residual, camino).size() > 0){
        printVectorpair(camino);
        cout << "---------" << endl;
        for(int i = 0; i < camino.size(); i++){
            pair<int, int> calle = camino[i];
            int min = minAristaenCamino(camino, red_residual);
            flujo_max += min;
            if(mapa[calle.first][calle.second] != UNDEFINED){
                flujo[calle.first][calle.second] += min;

                if(flujo[calle.first][calle.second] < mapa[calle.first][calle.second]){
                    red_residual[calle.first][calle.second] = red_residual[calle.first][calle.second] - flujo[calle.first][calle.second];
                    red_residual[calle.second][calle.first] =  flujo[calle.first][calle.second];
                } else {
                    red_residual[calle.first][calle.second] = UNDEFINED;
                    red_residual[calle.second][calle.first] = flujo[calle.first][calle.second];
                }

            } else {
                flujo[calle.second][calle.first] -= min;
                red_residual[calle.first][calle.second] = UNDEFINED;
                red_residual[calle.second][calle.first] = flujo[calle.first][calle.second];
            }    
        }
        camino.clear();
        break;
    }
    return flujo_max;
}
*/