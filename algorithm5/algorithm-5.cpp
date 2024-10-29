#include <iostream>
#include <list>
#include <queue>
#include <map>

using namespace std;

int *countingRoad(map<string, int> villages, int villageListSize, list<int> *neighbours, int start, int *destination, int destinationSize)
{
    bool *visitedArray = new bool[villageListSize]; // tablica prawdziwościowa odwiedzień wiosek
    int *distances = new int[villageListSize];      // tablica odległości

    int *results = new int[destinationSize]; // tablica wyników

    queue<int> villagesQueue; // kolejka oczekujących wiosek

    int index; // indeks pomocniczy

    villagesQueue.push(start); // umieszczanie pierwszej wioski w kolejce

    for (int i = 0; i < villageListSize; i++)
    {
        visitedArray[i] = false; // domyślnie wszystkie wioski są nieodwiedzone
        distances[i] = -1;       // domyślnie dystans wynosi 0
    }

    distances[start] = 0;

    while (!villagesQueue.empty())
    {
        index = villagesQueue.front(); // bierzemy element z kolejki

        if (!visitedArray[index]) // jeśli aktualna wioska nie została odwiedzona
        {
            // dodawanie wioski do odwiedzonych
            visitedArray[index] = true;

            // dodanie jej sąsiadów do kolejki
            for (int x : neighbours[index])
            {
                if (distances[x] == -1) // dodaj jeśli nie ustalano mu już odległości - nie był dodawany
                {
                    villagesQueue.push(x);
                    distances[x] = distances[index] + 1; // odległość sąsiada jest o 1 większa od poprzednika
                }
            }
        }
        // usunięcie wioski z kolejki
        villagesQueue.pop();
    }

    // skompletowanie wyników
    for (int i = 0; i < destinationSize; i++)
    {
        results[i] = distances[destination[i]];
    }
    return results;
}

// maksymalna wartość z tablicy
int maximum(int *arr, int size)
{
    int max = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

int main()
{

    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    map<string, int> villages;
    list<int> *neighbours; // tablica list sąsiadów
    int startVillage;
    int *endVillages;

    int numberOfVillages;
    int numberToVisit; // liczba wiosek do odwiedzenia

    int *roads; // drogi do wiosek
    string tmp;

    // Data Entering Segment
    cin >> numberOfVillages;
    neighbours = new list<int>[numberOfVillages];

    cin >> numberToVisit;
    endVillages = new int[numberToVisit];
    roads = new int[numberToVisit];

    for (int i = 0; i < numberOfVillages; i++)
    {
        cin >> tmp;
        villages.insert(pair<string, int>(tmp, i));
    }

    for (int i = 0; i < numberOfVillages; i++)
    {
        cin >> tmp;
        while (tmp != "X")
        {
            neighbours[i].push_back(villages[tmp]);
            cin >> tmp;
        }
    }

    cin >> tmp;
    startVillage = villages[tmp];

    for (int i = 0; i < numberToVisit; i++)
    {
        cin >> tmp;
        endVillages[i] = villages[tmp];
    }
    // End of Data Entering Segment

    // obliczanie drogi dla każdej wioski końcowej
    roads = countingRoad(villages, numberOfVillages, neighbours, startVillage, endVillages, numberToVisit);

    // wyświetlanie najdłuższej drogi
    cout << maximum(roads, numberToVisit);

    return 0;
}