#include <iostream>
using namespace std;

int find_q(int p);

int main() {
    // find p,q
    // find phi
    // d
    
}

int find_q(int p) {
    for (int q = 1; q < p; q++) {
        if (p % q == 0) {
            return q;
        }
    }
    return -1;
}