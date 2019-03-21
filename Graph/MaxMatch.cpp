#include <bits/stdc++.h>

using namespace std;

const int N = 5005;

class Hungarian {

  int max_node_cnt;
  vector <vector <int> > edges;
  vector <int> matches;
  vector <bool> used;

public:

  Hungarian(int _max_node_cnt) : max_node_cnt(_max_node_cnt) {
    edges.assign(max_node_cnt, vector <int>());
    matches.assign(max_node_cnt, -1);
    used.assign(max_node_cnt, false);
  }

  void addEdge(int u, int v) {
    edges[u].push_back(v);
  }

  bool dfs(int u) {
    for (int v : edges[u]) {
      if (used[v])
        continue;
      used[v] = true;
      if (matches[v] == -1 || dfs(matches[v])) {
        matches[v] = u;
        return true;
      }
    }
    return false;
  }

  bool extendPath(int u) {
    used.assign(max_node_cnt, false);
    return dfs(u);
  }

  int maxMatch() {
    int ret = 0;
    for (int i = 0; i < max_node_cnt; ++i)
      if (matches[i] == -1)
        ret += extendPath(i);
    return ret;
  }

};

int main()
{
  return 0;
}
