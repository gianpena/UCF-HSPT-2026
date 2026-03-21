#include <bits/stdc++.h>
using namespace std;
int n;
string s;
int simulate(int i, vector<int> *arr1, vector<int> *arr2) {
    auto next_pos = upper_bound(arr2->begin(), arr2->end(), i);
    if(next_pos == arr2->end()) return 1;
    return 1 + simulate(*next_pos, arr2, arr1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>s;

    vector<int> R, S;
    for(int i=0;i<n;++i){
        if(s[i] == 'R')
            R.push_back(i);
        else
            S.push_back(i);
    }

    int ans = 0;
    if(!R.empty())
        ans = simulate(R[0], &R, &S);
    if(!S.empty())
        ans = max(ans, simulate(S[0], &S, &R));
    
    ans -= (ans&1)==0;
    ans = n-ans;
    cout<<ans<<'\n';

    return 0;
}

