#include "bits/stdc++.h"

using namespace std;
const int INF = 1e9;

int minF(vector<pair<int, int>>& span, int k){
    int mn = INF;
    for(int i =0;i < span.size(); i++){
        if(!(i & 1) || span[i+1].first - span[i-1].first <= k)
            mn = min(mn, span[i].second);
    }
    return mn;
}

int maxF(vector<pair<int, int>>& span, int k){
int n = span.size();
    if (!n) return 0;
    vector<pair<int, int>> dp(n + 1);
    dp[n] = {0, -INF};
    for (int i = n - 1; ~i; i--) {
        dp[i] = dp[i + 1];
        int ub = upper_bound(span.begin(), span.end(),
                             make_pair(span[i].first + k, INF)) -
                 span.begin();
        if (i == 0 || i == n - 1 ||
            span[i + 1].first - span[i - 1].first <= k || !(n - i & 1))
            dp[i].first = max(dp[i].first, dp[ub].second + span[i].second);
        if (i == 0 || i == n - 1 ||
            span[i + 1].first - span[i - 1].first <= k || (n - i & 1))
            dp[i].second = max(dp[i].second, dp[ub].first + span[i].second);
    }
    return (n & 1 ? dp[0].second : dp[0].first);
}

int main(){
    cin.tie(0)->sync_with_stdio(0);

    int t, n, k;
    cin >> t >> n >> k;
    int prev_x = 0, ans = 0;
    vector<pair<int, int>> cur;
    while(n--){
        int x, y;
        cin >> x >> y;
        if(x - prev_x > k){
            if(t == 1){
                if (cur.size() & 1)
                    ans += minF(cur, k);
            }
            else
                ans += maxF(cur, k);
            cur.clear();
        }
        cur.push_back({x, y});
        prev_x = x;
    }
    if (t == 1) {
        if (cur.size() & 1) ans += minF(cur, k);
    } else
        ans += maxF(cur, k);
    cout << ans << endl;
}