#include <bits/stdc++.h>

using namespace std;

class SegTree {
    
    typedef int T;
    
    struct Node {
        
        static const T WORST = 0;
        
        int l, r;
        T mark, max_value;
        
        Node(int l, int r) : l(l), r(r) {
            mark = 0;
            max_value = WORST;
        }
        
        bool cover(int ll, int rr) const {
            return ll <= l && rr >= r;
        }
        
        bool goLeft(int ll, int rr) const {
            int mid = (l + r) >> 1;
            return ll <= mid;
        }
        
        bool goRight(int ll, int rr) const {
            int mid = (l + r) >> 1;
            return rr > mid;
        }
        
        void update(T x) {}
        
        void merge(const Node* l, const Node* r) {}
        
        T query() const {}
        
        static T best(T x, T y) {}
    };
    
    int n;
    vector <Node*> ns;
    
    void pushDown(int d) {
        T &mark = ns[d]->mark;
        if (mark)
            return;
        ns[d << 1]->update(mark);
        ns[d << 1 | 1]->update(mark);
        mark = 0;
    }
    
    void pushUp(int d) {
        const Node *l = ns[d << 1];
        const Node *r = ns[d << 1 | 1];
        Node *me = ns[d];
        me->merge(l, r);
    }
    
    void build(int d, int l, int r) {
        ns[d] = new Node(l, r);
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(d << 1, l, mid);
        build(d << 1 | 1, mid + 1, r);
        pushUp(d);
    }
    
    void update(int d, int l, int r, T v) {
        Node *me = ns[d];
        if (me->cover(l, r)) {
            me->update(v);
            return;
        }
        pushDown(d);
        if (me->goLeft(l, r))
            update(d << 1, l, r, v);
        if (me->goRight(l, r))
            update(d << 1 | 1, l, r, v);
        pushUp(d);
    }
    
    T query(int d, int l, int r) {
        const Node *me = ns[d];
        if (me->cover(l, r))
            return me->query();
        pushDown(d);
        T ret = Node::WORST;
        if (me->goLeft(l, r))
            ret = Node::best(ret, query(d << 1, l, r));
        if (me->goRight(l, r))
            ret = Node::best(ret, query(d << 1 | 1, l, r));
        pushUp(d);
        return ret;
    }
    
public:
    
    SegTree(int n=1) {
        build(n);
    }
    
    void build(int n) {
        ns.resize(n << 2);
        build(1, 1, n);
    }
    
    void update(int l, int r, T v) {
        update(1, l, r, v);
    }
    
    T query(int l, int r) {
        return query(1, l, r);
    }
};

int main()
{
    return 0;
}