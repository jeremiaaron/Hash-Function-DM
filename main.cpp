#include <bits/stdc++.h>

using namespace std;

/*
Given a set of identification numbers, use a hash function to assign 
them to memory locations where there are k memory locations.
*/

// h(k) = k mod m
// k is the input, m is the memory length

class HashFunction
{
public:
    int hash(long long int numbers, int memoryLength);
    void input();
    void output();

private:
    long long int numbers;
    int memoryLength;
    int memoryLoc;
    int arr[];
};

int HashFunction::hash(long long int numbers, int memoryLength)
{
    memoryLoc = numbers % memoryLength;

    return memoryLoc; // is the location in the memory stored in array
}

void HashFunction::input()
{
    cout << "Input the memory length: ";
    cin >> memoryLength;

    arr[memoryLength + 1];

    cout << endl
         << "Input -1 to terminate the loop." << endl
         << endl;

    for (size_t i = 0; i < memoryLength; i++)
    {
        cout << "Input the identification numbers: ";
        cin >> numbers;

        if (numbers != -1)
        {
            // storing input numbers to the given memory
            arr[hash(numbers, memoryLength)] = numbers;
        }
        else
        {
            break;
        }
    }
}

void HashFunction::output()
{
    cout << endl
         << "Output:" << endl;
    for (size_t i = 0; i < memoryLength; i++)
    {
        // Printing the output
        cout << "Memory Location (" << i << "): " << arr[i] << endl;
    }
}

int main()
{
    HashFunction func;

    func.input();
    func.output();

    return 0;
}
