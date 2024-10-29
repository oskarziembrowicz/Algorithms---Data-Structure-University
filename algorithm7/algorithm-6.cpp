#include <iostream>
#include <cstring>

using namespace std;

void printArray(int **arr, int cols, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << arr[j][i] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void recountPrefixMaximumArray(int **prefixMaximum, int **sourceArray, int cols, int rows, int adminLocation)
{

    for (int i = rows - 1; i >= 0; i--)
    {
        int maxInRow = 0;
        int startCol = adminLocation - i;
        if (startCol < 0)
            startCol = 0;
        for (int j = startCol; j < cols; j++)
        {
            if (sourceArray[j][i] > maxInRow)
            {
                maxInRow = sourceArray[j][i];
            }
            prefixMaximum[j][i] = maxInRow;
        }
    }
}

void shiftOldAndNewArrays(int ***oldArray, int ***newArray, int cols, int rows)
{
    int **tmp = *oldArray;
    *oldArray = *newArray;
    *newArray = tmp;
}

void emptyAnArray(int **array, int cols, int rows)
{
    for (int i = 0; i < cols; i++)
    {
        fill(array[i], array[i] + rows, 0);
    }
}

void maximalValueFromTheLastRow(int **arr, int cols, int rows)
{
    int max = 0;
    for (int i = 0; i < cols; i++)
    {
        if (arr[i][rows - 1] > max)
        {
            max = arr[i][rows - 1];
        }
    }

    cout << max;
}

void maximalScore(int *teams, int size)
{

    int adminLocation;        // miejsce sołtysa
    int **dataArray;          // aktualnie edytowana tablica
    int **prevDataArray;      // tablica z poprzedniej iteracji
    int **prefixMaximumArray; // tablica maximów prefixowych dla tablicy z poprzedniej iteracji
    int cols = size;
    int rows = size + 1;

    // tworzenie i inicjowanie dwuwymiarowych tablic:
    dataArray = new int *[cols];
    prevDataArray = new int *[cols];
    prefixMaximumArray = new int *[cols];
    for (int i = 0; i < cols; i++)
    {
        dataArray[i] = new int[rows];
        prevDataArray[i] = new int[rows];
        prefixMaximumArray[i] = new int[rows];
        fill(dataArray[i], dataArray[i] + rows, 0);
        fill(prevDataArray[i], prevDataArray[i] + rows, 0);
        fill(prefixMaximumArray[i], prefixMaximumArray[i] + rows, 0);
    }

    // krok pierwszy - sołtys do pierwszej drużyny
    prevDataArray[0][0] = teams[0];
    prevDataArray[0][1] = teams[0];
    prevDataArray[1][1] = teams[1];

    int currCols = cols;
    if (4 < cols)
    {
        currCols = 4;
    }
    recountPrefixMaximumArray(prefixMaximumArray, prevDataArray, currCols, 2, 0);

    // cout << "Start:\n";
    // printArray(prevDataArray, cols, rows);

    // cout << "Prefix Maximums:\n";
    // printArray(prefixMaximumArray, cols, rows);

    // główna pętla-wykonana tyle razy ile jest elementów(pierwszy krok wykonany)
    for (int i = 1; i < size; i++)
    {
        adminLocation = i;                 // w rzeczywistości i+1, ale wygoniej dla indeksowania
        int sizeOfBlockOfInterest = i + 2; // wysokość i szerokość obszaru zainteresowań(schodków)

        // krok 1 - przepisanie wartości z poprzedniej tablicy+wartości aktualnych miejsc
        for (int j = 0; j < adminLocation + sizeOfBlockOfInterest && j < cols; j++)
        {
            for (int k = adminLocation + 1; k > 0; k--)
            {
                if (prevDataArray[j][k - 1] != 0)
                {
                    dataArray[j][k] = prevDataArray[j][k - 1] + teams[j];
                }
            }
        }
        // cout << "Step 1:\n";
        // printArray(dataArray, cols, rows);

        // krok 2 - wypełnianie interesujących nas bloków
        //  na szerokość (cols) zaczynamy od miejsca sołtysa
        //  i idziemy po kilku blokach
        for (int j = adminLocation; j < adminLocation + sizeOfBlockOfInterest && j < cols; j++)
        {
            // na wysokość (rows) zaczynamy od góry i idzemy w dół do interesującej wysokości
            // Idziemy po schodkach, więc w każdej kolejnej kolumnie zaczynamy niżej
            for (int k = j - adminLocation; k < sizeOfBlockOfInterest && k < rows; k++)
            {
                // objaśnienie w notatkach:
                int potentialValue = prefixMaximumArray[j - 1][k - (j - adminLocation)] + teams[j];
                if (potentialValue > dataArray[j][k])
                {
                    // jeśli nowo obliczona wartość jest większa od starej:
                    dataArray[j][k] = potentialValue;
                }
            }
        }

        int currCols = cols;
        if (adminLocation + sizeOfBlockOfInterest + 1 < cols)
        {
            currCols = adminLocation + sizeOfBlockOfInterest + 1;
        }

        // cout << "Step 2:\n";
        // printArray(dataArray, cols, rows);

        // zamiana tablic:
        shiftOldAndNewArrays(&prevDataArray, &dataArray, cols, rows);
        emptyAnArray(dataArray, cols, rows);

        // obliczanie maksimów prefiksowych:
        emptyAnArray(prefixMaximumArray, cols, rows); // MOŻE DO USUNIĘCIA JAK ZA WOLNO
        recountPrefixMaximumArray(prefixMaximumArray, prevDataArray, currCols, sizeOfBlockOfInterest, adminLocation);
        // cout << "Prefix Maximums:\n";
        // printArray(prefixMaximumArray, cols, rows);
    }

    // wynikiem jest maksimum z wiersza:
    maximalValueFromTheLastRow(prevDataArray, cols, rows);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int numberOfTeams;
    int *teamScores;

    // Data entering segment
    // cout << "Enter number of teams:\n";
    cin >> numberOfTeams;

    teamScores = new int[numberOfTeams];

    // cout << "Enter team scores:\n";
    for (int i = 0; i < numberOfTeams; i++)
    {
        cin >> teamScores[i];
    }
    // End of data entering segment

    maximalScore(teamScores, numberOfTeams);

    return 0;
}