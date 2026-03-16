template <typename T, typename F> class SegTree {
    struct Node {
        T val;
        F todo;
    };

    int n;
    vector<Node> tr;
    const F ID = 0;

    T merge(const T &a, const T &b) { return a + b; }

    void apply(int o, int l, int r, F f) {
        tr[o].val += f * (r - l + 1);
        tr[o].todo += f;
    }

    void up(int o) { tr[o].val = merge(tr[o << 1].val, tr[o << 1 | 1].val); }

    void down(int o, int l, int r) {
        if (tr[o].todo != ID) {
            int mid = l + (r - l) / 2;
            apply(o << 1, l, mid, tr[o].todo);
            apply(o << 1 | 1, mid + 1, r, tr[o].todo);
            tr[o].todo = ID;
        }
    }

    void build(vector<T> &a, int o, int l, int r) {
        tr[o].todo = ID;
        if (l == r) {
            tr[o].val = a[l];
            return;
        }
        int mid = l + (r - l) / 2;
        build(a, o << 1, l, mid);
        build(a, o << 1 | 1, mid + 1, r);
        up(o);
    }

    void update(int o, int l, int r, int ql, int qr, F f) {
        if (ql <= l && r <= qr) {
            apply(o, l, r, f);
            return;
        }
        down(o, l, r);
        int mid = l + (r - l) / 2;
        if (ql <= mid)
            update(o << 1, l, mid, ql, qr, f);
        if (qr > mid)
            update(o << 1 | 1, mid + 1, r, ql, qr, f);
        up(o);
    }

    T query(int o, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return tr[o].val;
        down(o, l, r);
        int mid = l + (r - l) / 2;
        T res = 0;
        if (ql <= mid)
            res = merge(res, query(o << 1, l, mid, ql, qr));
        if (qr > mid)
            res = merge(res, query(o << 1 | 1, mid + 1, r, ql, qr));
        return res;
    }

  public:
    SegTree(vector<T> &a) : n(a.size()), tr(n << 2) { build(a, 1, 0, n - 1); }

    void update(int ql, int qr, F f) { update(1, 0, n - 1, ql, qr, f); }

    T query(int ql, int qr) { return query(1, 0, n - 1, ql, qr); }
};
