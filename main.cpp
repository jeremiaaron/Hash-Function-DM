#include <bits/stdc++.h>

using namespace std;

/*
PROBLEM:
    Given a set of identification numbers, use a hash function to assign 
    them to memory locations where there are k memory locations.

Double hashing is used to resolve hash collisions.

*numbers is the identification number input, m is the number of memory locations*

first hash function -> h1(numbers) = numbers % m | NOTE: number of memory location (m) must be prime
second hash function -> h2(numbers, q) = q - (numbers % q) | NOTE: 'q' can be prime or not, but must be less than 'm'
double hashing -> (h1(numbers) + i * h2(numbers)) % m | NOTE: i is incremented until a free spot is found

if no collision occurs, then first hash function is used
*/

class HashFunction
{
public:
    long long numbers;
    int memoryLength;
    int primeNum;
    int arrSize;
    long long *arr;

    HashFunction(int k, int prime)
    {
        this->arr = new long long[k];
        this->arrSize = 0;
        this->memoryLength = k;
        this->primeNum = prime;
        for (int i = 0; i < memoryLength; i++)
            arr[i] = -1;
    }

    bool memoryIsFull();
    int firstHash(long long numbers);
    int secondHash(long long numbers);
    void insert(long long numbers);
    void locate(long long id);
    void printArray();
    int findPrime(int memoryLength);
    void atIndex();
};

// find the
int HashFunction::findPrime(int memoryLength)
{
    if (memoryLength & 1)
        memoryLength -= 2;
    else
        memoryLength--;

    int i, j;
    for (i = memoryLength; i >= 2; i -= 2)
    {
        if (i % 2 == 0)
            continue;
        for (j = 3; j <= sqrt(i); j += 2)
        {
            if (i % j == 0)
                break;
        }
        if (j > sqrt(i))
            return i;
    }

    return 2;
}

//function to check if memory is full
bool HashFunction::memoryIsFull()
{
    return (arrSize == memoryLength);
}

//first hash function -> h1(numbers) = numbers % k
int HashFunction::firstHash(long long numbers)
{
    return (numbers % memoryLength);
}

//second hash function -> h2(numbers, prime) = prime - (numbers % prime)
int HashFunction::secondHash(long long numbers)
{
    return (primeNum - (numbers % primeNum));
}

//insert function utilizing hash functions and double hashing if collision occurs
void HashFunction::insert(long long numbers)
{
    if (memoryIsFull())
        return;

    int tempLoc1 = firstHash(numbers);

    //if there is collision, use double hashing
    if (arr[tempLoc1] != -1)
    {
        int tempLoc2 = secondHash(numbers);

        int i = 1;
        while (true)
        {
            //double hashing -> (h1(numbers) + i * h2(numbers)) % k

            int newMemoryLoc = (tempLoc1 + i * tempLoc2) % memoryLength;

            if (arr[newMemoryLoc] == -1)
            {
                arr[newMemoryLoc] = numbers;
                break;
            }

            i++;
        }
    }

    //if there is no collision
    else if (arr[tempLoc1] == -1)
        arr[tempLoc1] = numbers;

    arrSize++;
}

//function to print memory location contents
void HashFunction::printArray()
{
    for (int i = 0; i < memoryLength; i++)
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
    int tempLoc1 = firstHash(id);
    int tempLoc2 = secondHash(id);

    int i = 0;
    int count = 0;
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
    int x;
    cout << "Find data in index number (start with 0): ";
    cin >> x;
    cout << "In index " << x << ", the data found is: " << arr[x];
    return;
}

//driver function
int main()
{
    int k, prime;
    long long numbers;

    //input k (memory length) and prime number for double hashing
    cout << "Input memory length: ";
    cin >> k;
    // cout << "Input prime number for double hashing: ";
    // cin >> prime;

    HashFunction func = HashFunction(k, prime);

    //input the set of identification numbers
    cout << endl
         << "Input identification numbers (input -1 if you want to end): " << endl;
    do
    {
        cin >> numbers;
        func.insert(numbers);
    } while (numbers != -1);

    //memory location output
    cout << endl
         << "Output:" << endl;
    func.printArray();
    cout << endl;

    //if user wants to locate an ID number
    char option;
    cout << "Do you want to find an ID number? (Y/N) ";
    cin >> option;

    long long id;
    while (option == 'Y' || option == 'y')
    {
        cout << "Find an ID number: ";
        cin >> id;

        func.locate(id);

        cout << endl
             << "Do you want to find another ID number? (Y/N) ";
        cin >> option;
    }

    cout << "Do you want to find the data in index? (Y/N) ";
    cin >> option;
    while (option == 'Y' || option == 'y')
    {
        func.atIndex();
        cout << endl
             << "Do you want to find another data in index? (Y/N) ";
        cin >> option;
    }

    cout << "=======END=======";

    return 0;
}
