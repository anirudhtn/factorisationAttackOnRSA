#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;
#define int long long int
#define newl "\n"

//the public keys (n,e)
int n, e;

//template to calculate the factors of a given number
template <typename T>
std::vector<T> divisors(T n)
{
    std::vector<T> divisors;
    for (int i = 1; (T)i * i <= n; i++)
    {
        if (n % i == 0)
        {
            divisors.push_back(i);
            if (i != n / i)
            {
                divisors.push_back(n / i);
            }
        }
    }
    return divisors;
}

void line()
{
    for (int i = 0; i <= 78; ++i)
        cout << '_';
    cout << newl;
}

void adversaryDecrypt(int message, int p, int q)
{
    cout << newl;
    cout << "Encrypted message received is " << message << newl;
    int eulerTotient = (p - 1) * (q - 1);
    // cout << "\ncame hereeee";
    for (int i = 1; i <= 1e5; i++)
    {
        if ((e * i) % eulerTotient == 1)
        {
            cout << "\nMessage decrypted!";
            cout << "\nThe d is calculated as e^-1 mod n = " << i << newl;
            int mod = i % n;
            cout << "Resulting message is  " << message << "^" << mod << newl;
            int res = 1;
            for (int i = 1; i <= mod; i++)
            {
                res *= message;
                res %= n;
            }
            cout << "MESSAGE IS " << res << newl;
            break;
        }
    }
}
bool isPrime(int k) //function to check if number is prime
{
    if (k == 1)
        return false;
    int count = 0;
    for (int i = 2; i * i <= k; ++i)
    {
        if (k % i == 0)
            count += 2;
    }
    return (count == 0);
}

void adversarialAttackOnRSA(int message)
{

    line();
    cout << newl;
    cout << setw(45) << "ADVERSARIAL ATTACK!!\n";
    line();
    //the adversary is going to perform a
    //  FACTORISATION ATTACK BASED ON THE PRIME FACTORS OF N
    // cout << newl;
    vector<int> v = divisors(n); //finding all the factors of the number
    vector<int> prime;
    for (auto i : v)
    {
        // cout << i << ' ';
        if (isPrime(i)) //finding all the prime factors of the number
            prime.push_back(i);
    }
    // for (auto i : prime)
    //   cout << i << ' ';
    //   cout << newl;
    int p, q;
    for (auto i : prime)
    {
        if (find(prime.begin(), prime.end(), n / i) != prime.end()) //finding primes that result in N as product
        {
            // cout << "\ncame herw";
            // cout << i << " " << n / i << newl;
            p = i;
            q = n / i;
            adversaryDecrypt(message, p, q);
            return;
        }
    }
}

void send(int message)
{
    //encryption happens here
    //message m is transmitted as P = m^e
    //ideally, on receiving, receiver will apply a power d
    //it becomes P^d = m^(ed)
    //since ed=1, received message is just m
    message = pow(message, e);
    message %= n;
    cout << "\nEncrypted message that is sent is " << message << newl;
    cout << "\nSending message......\n";
    usleep(3000000);
    //while transmitting the message, an adversary has intercepted the message
    adversarialAttackOnRSA(message);
}
void sender(int n, int e)
{
    cout << "\nEnter message to be sent : ";
    int message;
    //the message being transmitted
    cin >> message;
    line();
    cout << newl;
    cout << setw(45) << "SENDER DETAILS\n";
    line();
    cout << "\nDisplaying details of the messange being sent :";
    cout << "\nValue of N is " << n << newl;
    cout << "Value of e is " << e << newl;
    //message is sent to the receiver
    send(message);
}
signed main()
{
    line();
    cout << newl;
    cout << setw(45) << "PUBLIC KEYS\n";
    line();
    //value of N for encryption
    cout << newl;
    cout << "Enter the value of N : ";
    cin >> n;
    //value of the e parameter used in encoding
    cout << "\nEnter the value of e : ";
    cin >> e;
    //receiver's n and e are public, sender sends message based on (n,e)
    //receiver keeps the value of d to himself
    sender(n, e);
}