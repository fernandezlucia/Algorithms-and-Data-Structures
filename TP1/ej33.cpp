#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;
int tests;
int n;
int obj;

vector<int> nums;
vector<vector<int>> dp;

int sum(){
    int res = 0;
    for(int i = 0; i < nums.size();i++){
        res += nums[i];
    }
    return res;
}

int rec(int i, int target){
    // CASOS BASE
    if(dp[i][target] != -1) return dp[i][target];
    if(i == 0){
        dp[i][target] = abs(target) == nums[i];
        if(abs(target) == nums[i]){
            return 1;
        } else {
            return 0;
        }
    }
    int p = rec(i-1, target - nums[i]);
    int m = rec(i-1, target + nums[i]);
    if(p == 1 || m == 1){
        dp[i][target] = 1;
        return 1;
    } else {
        dp[i][target] = 0;
        return 0;
    }   
}

string solve(){
    string res = "";
    int curObjective = obj;
    if(rec(n-1, obj)){
        for(int i = (n-1); i >= 0; i--){
            bool p = dp[i][curObjective - nums[i]] == 1;
            bool m = dp[i][curObjective + nums[i]] == 1;
            if(p && m){
                res += "?";
                curObjective -= nums[i];
            } else if(p) {
                res += "+";
                curObjective -= nums[i];
            } else if(m){
                res += "-";
                curObjective += nums[i];
            }
        }
    }
    return res;
}

int main(){
    cin >> tests;
    for (int i = 0; i < tests; i++){
        cin >> n;
        cin >> obj;
        for(int j = 0; j < n; j++){
            int k;
            cin >> k;
            nums.push_back(k);
        }
        vector<int> row(sum() + 1, -1);
        dp.assign(n,row);
        cout << solve() << endl;
    }
    return 0;
}