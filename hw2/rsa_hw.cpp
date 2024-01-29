#include <iostream>
using namespace std;

int solve_for_p(int n);
int mod_inv(int e, int n);

int main() {
    const int n = 4453;
    const int e = 7;

    // find p,q
    int p = solve_for_p(n); // 61
    int q = n / p; // 73
    // find phi
    int phi = (p - 1)*(q - 1); // 4320
    // find d
    int d = mod_inv(e, n); // 3817

}

// calculates a divisor of n
int solve_for_p(int n) {
    for (int p = 2; p < n; p++) {
        if (n % p == 0) {
            return p;
        }
    }
    return -1;
}

// calculates modular inverse (e^-1 (mod n)) by listing multiples
int mod_inv(int e, int n) {
    // xe === 1 (mod n) -> ex = ny + 1
    int x = 1;
    int y = 1;
    int lhs = e*x;
    int rhs = n*y + 1;
    while (lhs != rhs) {
        if (lhs < rhs) {
            x++;
        }
        else {
            y++;
        }
        lhs = e*x;
        rhs = n*y + 1;
    }
    return x;
}