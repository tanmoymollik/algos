#define MAX (1 << 20)
const int mod = 1000000007;

template<class T>
T bigmod(T x, T pw) {
    T ret = 1;
    while(pw > 0) {
        if(pw & 1) ret = ret * x % mod;
        pw >>= 1;
        x = x * x % mod;
    }
    return ret;
}

/// xor transform
/// T[2][2] = (1 / sqrt(2)) * { {1, 1}, {1, -1} }
/// H^(-1) = H
/// We compute sqrt(N) * H here.
/// P -> FWHT(P, n, false) = sqrt(N) * H * P
/// Q -> FWHT(Q, n, false) = sqrt(N) * H * Q
/// PQ -> FWHT(P . Q, n, true) = N * H * (P * Q)
/// So to invert divide by N
void FWHT(int A[MAX], int n, bool invert) {
    int u, v;
    for(int len = 1; (len<<1) <= n; len <<= 1)
        for(int st = 0; st < n; st += (len<<1))
            for(int i = 0; i < len; i++) {
                u = A[st+i], v = A[st+i+len];
                A[st+i] = u + v;
                A[st+i+len] = u - v;
                if(A[st+i] >= mod) A[st+i] -= mod;
                if(A[st+i+len] < 0) A[st+i+len] += mod;
            }
    if(invert)
        for(int i = 0; i < n; i++)
            A[i] = A[i] * bigmod<long long>(n, mod-2) % mod;
}

/// and transform
/// T[2][2] = { {0, 1}, {1, 1} } T^(-1)[2][2] = { {-1, 1}, {1, 0} }
void FWHT(int A[MAX], int n, bool invert) {
    int u, v;
    for(int len = 1; (len<<1) <= n; len <<= 1)
        for(int st = 0; st < n; st += (len<<1))
            for(int i = 0; i < len; i++) {
                u = A[st+i], v = A[st+i+len];
                if(invert) {
                    A[st+i] = v - u;
                    A[st+i+len] = u;
                } else {
                    A[st+i] = v;
                    A[st+i+len] = u + v;
                }
                if(A[st+i] < 0) A[st+i] += mod;
                if(A[st+i+len] >= mod) A[st+i+len] -= mod;
            }
}

/// or transform
/// T[2][2] = { {1, 1}, {1, 0} } T^(-1)[2][2] = { {0, 1}, {1, -1} }
void FWHT(int A[MAX], int n, bool invert) {
    int u, v;
    for(int len = 1; (len<<1) <= n; len <<= 1)
        for(int st = 0; st < n; st += (len<<1))
            for(int i = 0; i < len; i++) {
                u = A[st+i], v = A[st+i+len];
                if(invert) {
                    A[st+i] = v;
                    A[st+i+len] = u - v;
                } else {
                    A[st+i] = u + v;
                    A[st+i+len] = u;
                }
                if(A[st+i] >= mod) A[st+i] -= mod;
                if(A[st+i+len] < 0) A[st+i+len] += mod;
            }
}
