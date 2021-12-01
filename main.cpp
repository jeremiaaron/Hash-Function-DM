#include <iostream>

using namespace std;

/*
Given a set of identification numbers, use a hash function to assign 
them to memory locations where there are k memory locations.
*/

// sekarang cuma bisa sampe 352316021

// Function to count the mod
int hashFunction(long long int numbers, int mod)
{
    int result = numbers % mod;

    return result;
}

// Function to ask input and give output
void func(int keys, int mod)
{
    int array[keys]; // Allocate the array
    long long int number;

    // Loop to input and transfer the input to array
    for (int i = 0; i < keys; i++)
    {
        cout << "Input identification numbers: ";
        cin >> number;
        int temp = hashFunction(number, mod); // Searching the mod and store in temp var
        array[i] = temp;
    }

    // Printing out the array after being processed in hash function
    cout << endl
         << "After hash function is implemented: " << endl;
    for (int i = 0; i < keys; i++)
    {
        cout << "Memory location number (" << i << "): " << array[i] << endl;
    }
    return;
}

int main()
{
    int inputKeys, inputMod;

    // Input how many keys
    cout << "Input keys (memory locations length): ";
    cin >> inputKeys;

    // Input mod
    cout << "Input the mod: ";
    cin >> inputMod;
    cout << endl;

    // Use the function
    func(inputKeys, inputMod);

    return 0;
}
