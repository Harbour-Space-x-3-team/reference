/**
 * Author: Lucian Bicsi
 * Date: 2015-06-25
 * License: GNU Free Documentation License 1.2
 * Source: csacademy
 * Description: Transform to a basis with fast convolutions of the form
 * $\displaystyle c[z] = \sum\nolimits_{z = x \oplus y} a[x] \cdot b[y]$,
 * where $\oplus$ is one of AND, OR, XOR. The size of $a$ must be a power of two.
 * Time: O(N \log N)
 */
#pragma once

// Notes: if you use mod make sure 0 <= a[i], b[i] < mod when you call convolve
enum bit_op { AND, OR, XOR };

namespace bitwise_transform {
    template<int P, typename T>
    inline void add(T &x, T y) {
        x += y;
        if (P != 0 && x >= P) x -= P;
    }
    template<bit_op B, int P, bool inv = false, typename T>
    void transform(T a[], int n) {
        for (int len = 1; len < n; len <<= 1)
            for (int i = 0; i < n; i += len << 1)
                for (int j = i; j < i + len; ++j) {
                    T u = a[j], v = a[j + len];
                    if (B == AND) add<P>(a[j], inv ? P-v : v);
                    if (B == OR) add<P>(a[j + len], inv ? P-u : u);
                    if (B == XOR)
                        add<P>(a[j], v),
                            add<P>(a[j + len] = u, P-v);
                }
        if (B == XOR && inv) {
            int in = pow_mod(n, P-2, P);


            for (int i = 0; i < n; ++i) {
                if (P == 0) a[i] /= n;
                else a[i] = (ll)a[i] * in % P;
            }
        }
    }
    template<bit_op B, int P = 0, typename T>
    vector<T> convolve(vector<T> a, vector<T> b) {
        int n = max(a.size(), b.size()), sz = 1;
        while (sz < n) sz <<= 1;
        a.resize(sz);
        b.resize(sz);
        transform<B, P>(a.data(), sz);
        transform<B, P>(b.data(), sz);
        for (int i = 0; i < sz; ++i) {
            if (P == 0) a[i] *= b[i];
            else a[i] = (ll)a[i] * b[i] % P;
        }
        transform<B, P, true>(a.data(), sz);
        return a;
    }
}
