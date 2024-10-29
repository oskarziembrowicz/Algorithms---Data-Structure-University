#include <iostream>

using namespace std;

int main()
{

    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int numberOfHunters;
    const int CRABS = 100;
    const int TRAPS = 10;
    string scoreArray[TRAPS][CRABS];

    cin >> numberOfHunters;

    for (int i = 0; i < numberOfHunters; i++)
    {
        string name;
        int crabs, traps;
        cin >> name >> crabs >> traps;
        scoreArray[traps][crabs].append(name);
        scoreArray[traps][crabs].append(" ");
    }

    for (int i = CRABS - 1; i >= 0; i--)
    {
        for (int j = 0; j < TRAPS; j++)
        {
            cout << scoreArray[j][i];
        }
    }

    return 0;
}