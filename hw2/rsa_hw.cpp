#include <iostream>
#include <algorithm> 
using namespace std;

int solve_for_p(int n);           // finds a divisor of n
int mod_inv(int e, int n);        // calculates modular inverse (e^-1 (mod n)) by listing multiples
int pow_mod(int m, int d, int n); // calculates M^d % n
char int_to_char(int m);          // converts numbers to characters as specified by the homework

int main()
{
    int e = 0;
    int n = 0;
    int char_count = 0;
    cin >> e >> n >> char_count;

    // find p,q
    int p = solve_for_p(n); // 61
    int q = n / p;          // 73
    // find phi
    int phi = (p - 1) * (q - 1); // 4320
    // find d
    int d = mod_inv(e, phi); // 3703

    // test public key validity
    if (__gcd(e, phi) != 1) {
        cout << "Public key is not valid!\n";
        return 1;
    }

    // decrypt message
    string message;
    for (int i = 0; i < char_count; i++)
    {
        int encrypted_data = 0;
        if (!(cin >> encrypted_data))
            return 1;
        // calculate M^d
        int decrypted_data = pow_mod(encrypted_data, d, n);
        message += int_to_char(decrypted_data);
    }
    cout << message << endl;
    
}

int solve_for_p(int n)
{
    for (int p = 2; p < n; p++)
    {
        if (n % p == 0)
        {
            return p;
        }
    }
    return -1;
}

int mod_inv(int e, int n)
{
    // xe === 1 (mod n) -> ex = ny + 1
    int x = 1;
    int y = 1;
    int lhs = e * x;
    int rhs = n * y + 1;
    while (lhs != rhs)
    {
        if (lhs < rhs)
        {
            x++;
        }
        else
        {
            y++;
        }
        lhs = e * x;
        rhs = n * y + 1;
    }
    return x;
}

// doesn't work for big numbers
int pow_mod(int m, int d, int n)
{
    // simplify by squaring:
    m %= n;
    int extra = 1;
    // while there is an exponent (> 1),
    while (d > 1)
    {
        if (d % 2 != 0)
        {
            extra *= m;
            d--;
        }
        m *= m;     // square m
        d /= 2;     // reduce exponent
        m %= n;     // reduce m
        extra %= n; // reduce m
    }
    m *= extra;
    int result = m % n;
    if (result < 0)
    {
        return result + n;
    }
    return result;
}

char int_to_char(int m)
{
    switch (m)
    {
    case 34:
        return ' ';
        break;
    case 35:
        return '\"';
        break;
    case 36:
        return ',';
        break;
    case 37:
        return '.';
        break;
    case 38:
        return '\'';
        break;
    default:
        return static_cast<char>(m + 'A' - 8);
        break;
    }
}