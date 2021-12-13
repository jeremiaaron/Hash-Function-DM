#include <bits/stdc++.h>

using namespace std;

/*
PROBLEM:
    Given a set of identification numbers, use a hash function to assign 
    them to memory locations where there are k memory locations.

Double hashing is used to resolve hash collisions.

*k is the identification number input, m is the number of memory locations*

first hash function -> h1(k) = k % m | NOTE: number of memory location (m) must be prime
second hash function -> h2(k, q) = q - (k % q) | NOTE: q must be less than 'm'
double hashing -> (h1(k) + i * h2(k)) % m | NOTE: i is incremented until a free spot is found or when it reaches m

if no collision occurs, then first hash function is used
*/

class HashFunction
{
public:
    long long k;
    long long memoryLength;
    long long qValue;
    long long arrSize;
    long long *arr;
    
    HashFunction(long long k, long long q)
    {
        this->arr = new long long[k];
        this->arrSize = 0;
        this->memoryLength = k;
        this->qValue = q;
        for (long long i = 0; i < memoryLength; i++)
            arr[i] = -1;
    }

    bool memoryIsFull();
    long long firstHash(long long k);
    long long secondHash(long long k);
    void insert(long long k);
    void locate(long long id);
    void printArray();
    void atIndex();
};

// find the
bool checkPrime(long long m)
{   
    bool isPrime = true;
    if(m <= 1)
        return false;
    
    if(m == 2)
        return true;

    if(m % 2 == 0) {
        return false;
    }

    for(long long i = 3; i <= sqrt(m); i+=2) {
        if(m % i == 0) {
            return false;
        }
    }

    return true;
}

//function to check if memory is full
bool HashFunction::memoryIsFull()
{
    return (arrSize == memoryLength);
}

//first hash function -> h1(k) = k % k
long long HashFunction::firstHash(long long k)
{
    return (k % memoryLength);
}

//second hash function -> h2(k, q) = q - (k % q)
long long HashFunction::secondHash(long long k)
{
    return (qValue - (k % qValue));
}

//insert function utilizing hash functions and double hashing if collision occurs
void HashFunction::insert(long long k)
{
    if (memoryIsFull())
        return;

    long long tempLoc1 = firstHash(k);

    //if there is collision, use double hashing
    if (arr[tempLoc1] != -1)
    {
        long long tempLoc2 = secondHash(k);

        long long i = 1;
        while (true)
        {
            //double hashing -> (h1(k) + i * h2(k)) % k

            long long newMemoryLoc = (tempLoc1 + i * tempLoc2) % memoryLength;

            if (arr[newMemoryLoc] == -1)
            {
                arr[newMemoryLoc] = k;
                break;
            }

            i++;
        }
    }

    //if there is no collision
    else if (arr[tempLoc1] == -1)
        arr[tempLoc1] = k;

    arrSize++;
}

//function to print memory location contents
void HashFunction::printArray()
{
    for (long long i = 0; i < memoryLength; i++)
    {
        if (arr[i] != -1)
        {
            cout << "Memory Location (" << i << "): " << arr[i] << endl;
        }
        else
            cout << "Memory Location (" << i << "): " << endl;
    }
}

//function to locate an id number
void HashFunction::locate(long long id)
{
    long long tempLoc1 = firstHash(id);
    long long tempLoc2 = secondHash(id);

    long long i = 0;
    long long count = 0;
    while (arr[(tempLoc1 + i * tempLoc2) % memoryLength] != id)
    {

        if (count > arrSize || arr[(tempLoc1 + i * tempLoc2) % memoryLength] == -1)
        {
            cout << "ID number does not exist in any memory location." << endl;
            return;
        }

        count++;
        i++;
    }

    cout << "ID Number " << id << " found in memory location " << (tempLoc1 + i * tempLoc2) % memoryLength << endl;
}

void HashFunction::atIndex()
{
    long long x;
    cout << "Find data in index number (starting with 0): ";
    cin >> x;
    cout << "In index " << x << ", the data found is: " << arr[x];
    return;
}

//driver function
int main()
{
    long long m;
    long long k;

    //input k (memory length) and q number for double hashing
        cout << "Input number of memory locations (must be a prime number greater than 2): ";
        cin >> m;
        
        while(!checkPrime(m) || m <= 2) {
            cout << endl;

            if(!checkPrime(m))
                cout << "Not a prime number!!" << endl;
            if(m <= 2)
                cout << "Must be greater than 2!!" << endl;
            cout << "Input number of memory locations (must be a prime number greater than 2): ";
            cin >> m;
        }

    // cout << "Input q number for double hashing: ";
    // cin >> q;

    long long q = m - 1;
    HashFunction func = HashFunction(m, q);

    cout << endl;

    //input the set of identification numbers
    long long max;
    cout << "How many ID numbers do you want to input? ";
    cin >> max;

    long long n = 0;
    if(max > m)
        n = m;
    else n = max;

    for(long long i = 0; i < n; i++)
    {
        cout << "Input an ID number: ";
        cin >> k;
        func.insert(k);
    }

    //memory location output
    cout << endl
         << "Output:" << endl;
    func.printArray();
    cout << endl;

    //if user wants to locate an ID number
    char option;
    cout << "Do you want to find an ID number? (Y/N): ";
    cin >> option;

    long long id;
    while (option == 'Y' || option == 'y')
    {
        cout << "Find an ID number: ";
        cin >> id;

        func.locate(id);

        cout << endl
             << "Do you want to find another ID number? (Y/N): ";
        cin >> option;
    }

    cout << endl << "Do you want to find the data in index? (Y/N): ";
    cin >> option;
    while (option == 'Y' || option == 'y')
    {
        func.atIndex();
        cout << endl << endl
             << "Do you want to find another data in index? (Y/N): ";
        cin >> option;
    }

    cout << endl << "=======END=======";

    return 0;
}
