#include <iostream>

using namespace std;

/*
Given a set of identification numbers, use a hash function to assign 
them to memory locations where there are k memory locations.
*/

int hashFunction(int numbers, int mod)
{
    int result = numbers % mod;

    return result;
}

int main()
{
    int inputNumber, inputKeys, mod, temp;

    cout << "Input keys: ";
    cin >> inputKeys;

    cout << "Input the mod: ";
    cin >> mod;

    int arr[inputKeys];

    // For Input
    for (int i = 0; i < inputKeys; i++)
    {
        cout << "Input numbers: ";
        cin >> inputNumber;
        temp = hashFunction(inputNumber, mod);
        arr[i] = temp;
        // inputKeys++;
    }

    // For Output
    cout << "After hash function: " << endl;
    for (int i = 0; i < inputKeys; i++)
    {
        cout << arr[i] << endl;
    }

    return 0;
}