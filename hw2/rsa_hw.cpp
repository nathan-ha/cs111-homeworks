#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/*

7 4453
158
1400 2218 99 2088 4191 84 843 99 4191 3780 764 4191 2979 2269 99 764 2218
2269 2088 843 3015 99 2970 1443 1655 99 3237 2979 99 447 1443 3237 1032
2382 871 843 1655 99 871 1443 99 4242 843 99 4191 2269 99 843 4191 2269
2979 99 871 1443 99 2382 2269 843 99 4191 2269 99 3237 2979 99 871 843
3780 843 1032 2088 1443 2962 843 2916 99 3237 2979 99 764 2218 2269 2088
99 2088 4191 2269 99 447 1443 3237 843 99 871 1655 2382 843 99 4242 843
447 4191 2382 2269 843 99 2218 99 447 4191 2962 99 2962 1443 99 3780 1443
2962 1294 843 1655 99 2970 2218 1294 2382 1655 843 99 1443 2382 871 99
2088 1443 764 99 871 1443 99 2382 2269 843 99 3237 2979 99 871 843 3780
843 1032 2088 1443 2962 843 2916 1400

note for gradescope tests: lhs is your output
*/

int solve_for_p(int n);           // finds a divisor of n
int mod_inv(int e, int n);        // calculates modular inverse (e^-1 (mod n)) by listing multiples
int pow_mod(int m, int d, int n); // calculates M^d % n
char int_to_char(int m);          // converts numbers to characters as specified by the homework
bool is_prime(int p);             // checks if number is prime, works for small numbers

int main()
{
    int e = 7;
    int n = 4453;
    int char_count = 158;
    cin >> e >> n >> char_count;
    vector<int> data;
    // get message
    for (int i = 0; i < char_count; i++)
    {
        int temp_msg = 0;
        cin >> temp_msg;
        data.push_back(temp_msg);
    }

    // find p,q
    int p = solve_for_p(n); // 61
    int q = n / p;          // 73
    // find phi
    int phi = (p - 1) * (q - 1); // 4320
    // test public key validity:
    // e and phi(n) are coprime, n has two prime divisors
    if (__gcd(e, phi) != 1 or !is_prime(p) or !is_prime(q) or p == q)
    {
        cout << "Public key is not valid!";
        return 1;
    }
    // find d
    int d = mod_inv(e, phi); // 3703

    // decrypt message
    for (auto &current_letter : data)
    {
        int decrypted_data = pow_mod(current_letter, d, n);
        current_letter = decrypted_data;
    }

    // Output p and q, ϕ(n) and d
    cout //<< endl
        << p << ' '
        << q << ' '
        << phi << ' '
        << d << endl;
    // print decrypted message in integers
    for (auto &current_letter : data)
    {
        cout << current_letter << ' ';
    }
    cout << endl;
    // printed decryped message in English
    for (auto &current_letter : data)
    {
        cout << int_to_char(current_letter);
    }
    // cout << endl;

    // string message;
    // string message_ints;
    // for (int i = 0; i < char_count; i++)
    // {
    //     int encrypted_data = 0;
    //     cin >> encrypted_data;
    //     // calculate M^d
    //     int decrypted_data = pow_mod(encrypted_data, d, n);
    //     message_ints += to_string(decrypted_data) + ' ';
    //     message += int_to_char(decrypted_data);
    // }

    // cout << message_ints << endl;
    // cout << message << endl;
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
    case 33:
        return ' ';
        break;
    case 34:
        return '\"';
        break;
    case 35:
        return ',';
        break;
    case 36:
        return '.';
        break;
    case 37:
        return '\'';
        break;
    default:
        char letter = static_cast<char>(m + 'A' - 7);
        return letter;
        break;
    }
}

bool is_prime(int p)
{
    for (int i = 2; i < p; i++)
    {
        if (p % i == 0)
        {
            return false;
        }
        return true;
    }
}