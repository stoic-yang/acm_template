template <const int M = 1e9 + 7> struct MInt {
    using LL = long long;
    int x;
    MInt(int x = 0) : x(norm(x)) {}
    MInt(LL x) : x(norm(x % M)) {}
    inline int norm(LL x) const {
        if (x < 0)
            x += M;
        if (x >= M)
            x -= M;
        return x;
    }
    inline MInt ksm(MInt x, LL y) const { return x ^= y; }
    inline int val() const { return x; }
    inline MInt operator-() const { return MInt(norm(M - x)); }
    inline MInt inv() const {
        assert(x != 0);
        return *this ^ (M - 2);
    }
    inline MInt &operator*=(const MInt &rhs) {
        x = LL(x) * rhs.x % M;
        return *this;
    }
    inline MInt &operator+=(const MInt &rhs) {
        x = norm(x + rhs.x);
        return *this;
    }
    inline MInt &operator-=(const MInt &rhs) {
        x = norm(x - rhs.x);
        return *this;
    }
    inline MInt &operator/=(const MInt &rhs) { return *this *= rhs.inv(); }
    inline MInt &operator^=(LL y) {
        LL ans = 1;
        while (y) {
            if (y & 1)
                ans = ans * x % M;
            x = LL(x) * x % M;
            y >>= 1;
        }
        x = ans;
        return *this;
    }
    inline friend MInt operator*(const MInt &lhs, const MInt &rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    inline friend MInt operator+(const MInt &lhs, const MInt &rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    inline friend MInt operator-(const MInt &lhs, const MInt &rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    inline friend MInt operator/(const MInt &lhs, const MInt &rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    inline friend MInt operator^(const MInt &lhs, LL y) {
        MInt res = lhs;
        res ^= y;
        return res;
    }
    inline friend istream &operator>>(istream &is, MInt &a) {
        LL v;
        is >> v;
        a = MInt(v);
        return is;
    }
    inline friend ostream &operator<<(ostream &os, const MInt &a) { return os << a.val(); }
};
using Z = MInt<998244353>;
