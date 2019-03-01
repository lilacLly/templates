#include <bits/stdc++.h>

using namespace std;

template <class T>
class Fenwick {

  int n;
  vector <T> arrays;

  public:

    Fenwick(int _n) : n(_n) {
      arrays.assign(n, 0);
    }

    inline int lowbit(int x) {
      return x & (-x);
    }

    void update(int x, T v) {
      for (int i = x; i < n; i += lowbit(i))
        arrays[i] += v;
    }

    T query(int x) {
      T ret = 0;
      for (int i = x; i > 0; i -= lowbit(i))
        ret += arrays[i];
      return ret;
    }

};

int main()
{
  Fenwick <long long> fw(100);
  fw.update(3, 1);
  fw.update(5, 1);
  cout << fw.query(2) << endl;
  cout << fw.query(3) << endl;
  cout << fw.query(5) << endl;
  return 0;
}
