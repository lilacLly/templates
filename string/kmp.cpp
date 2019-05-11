#include <bits/stdc++.h>

using namespace std;

template <class T>
vector <int> buildNxt(T it, int len) {
    vector <int> nxt(len, -1);
    for (int i = 1; i < len; ++i) {
        int tmp = nxt[i - 1];
        while (tmp != -1 && *(it + tmp + 1) != *(it + i))
            tmp = nxt[tmp];
        if (*(it + tmp + 1) == *(it + i))
            tmp += 1;
        nxt[i] = tmp;
    }
    return nxt;
}

template <class T>
int search(T s, int len_s, const T& t, int len_t, const vector <int>& nxt) {
    int i = 0, j = 0, ret = 0;
    while (i < len_s) {
        while (i < len_s && j < len_t && *(s + i) == *(t + j))
            i += 1, j += 1;
        if (j == len_t)
            ret += 1;
        if (j == 0)
            i += 1;
        else
            j = nxt[j - 1] + 1;
    }
    return ret;
}

template <class T>
int solve(const T& s, const T& t) {
    auto nxt = buildNxt(t.begin(), t.size());
    return search(s.begin(), s.size(), t.begin(), t.size(), nxt);
}

int main()
{
    return 0;
}