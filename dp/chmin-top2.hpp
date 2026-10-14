#pragma once

// A: 一番目 B: 二番目
template <typename T, typename U>
bool ChminTop2(pair<T, U> &A, pair<T, U> &B, pair<T, U> now) {
    if (now.second == A.second) {
        if (A > now) { A = now; return true; }
        return false;
    }
    if (now.second == B.second) {
        if (B > now) {
            B = now;
            if (A > B) swap(A, B);
            return true;
        }
        return false;
    }
    if (A > now) {
        B = A;
        A = now;
        return true;
    }
    if (B > now) { B = now; return true; }
    return false;
}

template <typename T, typename U>
bool ChmaxTop2(pair<T, U> &A, pair<T, U> &B, pair<T, U> now) {
    if (now.second == A.second) {
        if (A < now) { A = now; return true; }
        return false;
    }
    if (now.second == B.second) {
        if (B < now) {
            B = now;
            if (A < B) swap(A, B);
            return true;
        }
        return false;
    }
    if (A < now) {
        B = A;
        A = now;
        return true;
    }
    if (B < now) { B = now; return true; }
    return false;
}
