#include <iostream>

using namespace std;

int bestScore = __INT16_MAX__; //najlepszy wyni jako zmienna globalna - wygodniej

void printArray(int** arr, int cols, int rows){
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
}

void printCamps(int* camps, int n){
    for(int i=0; i<n; i++){
        cout << camps[i] << " ";
    }
    cout << "\n";
}

void setBestArray(int* best, int* curr, int n){
    for(int i=0; i<n; i++){
        best[i] = curr[i];
    }
}

int** markTrails(int** map, int size, int y, int x){
    //zaznaczaj tylko w dół, góra nie ma znaczenia

    //zaznaczyć cały wiersz:
    for(int i=0; i<size; i++){
        map[y][i] += 1;
        // w tym zaznaczony będzie punkt na którym jest obóz
        // nie powielać tego punktu!!
    }
    //zaznaczyć kolumnę w dół
    for(int i=y+1; i<size; i++){
        map[i][x] += 1;
    }
    //prawo-dół
    for(int i=y+1, j=x+1; i<size && j<size; i++, j++){
        map[i][j] += 1;
    }
    //lewo-dół
    for(int i=y+1, j=x-1; i<size && j<size && j>=0; i++, j--){
        map[i][j] += 1;
    }

    // cout << "\nAdded trails:\n";
    // printArray(map, size, size);
    // cout << "\n";

    return map;
}

int** deleteTrails(int** map, int size, int y, int x){
    //zaznaczaj tylko w dół, góra nie ma znaczenia

    //zaznaczyć cały wiersz:
    for(int i=0; i<size; i++){
        map[y][i] -= 1;
    }
    //zaznaczyć kolumnę w dół
    for(int i=y+1; i<size; i++){
        map[i][x] -= 1;
    }
    //prawo-dół
    for(int i=y+1, j=x+1; i<size && j<size; i++, j++){
        map[i][j] -= 1;
    }
    //lewo-dół
    for(int i=y+1, j=x-1; i<size && j<size && j>=0; i++, j--){
        map[i][j] -= 1;
    }

    // cout << "\nDeleted trails:\n";
    // printArray(map, size, size);
    // cout << "\n";

    return map;
}

bool setUpCamps(int** field, int** lockedTrails, int* camps, int* bestCamps, int size, int level, int score){
    // przeszukaj wiersz:
    for(int i=0; i<size; i++){
        if(lockedTrails[level][i] == 0){
            //jeśli pole nie jest na trasie
            // postaw na nim obóz:
            camps[level] = i;
            //dodaj wartość pola do wyniku:
            score += field[level][i];
            // zaznacz trasy z obozu:
            lockedTrails = markTrails(lockedTrails, size, level, i);

            // jeśli wynik już przekroczył najlepszy, to nie ma sensu liczyć dalej:
            if(score > bestScore){
                goto discardTheLine;
            }

            // printCamps(camps, size);

            if(level == size-1){
                //sprawdzono ostatni wiersz - zapamiętaj odpowiedź i sprawdzaj dalej
                // cout << "Score: " << score << "\n";
                // cout << "Best score: " << bestScore << "\n";
                if(score < bestScore){
                    //BEST SCORE SIĘ NIE ZAPISUJE
                    bestScore = score;
                    setBestArray(bestCamps, camps, size);
                }

                //cout << "Best score: " << bestScore << "\n";

                //po tym zabiegu idziemy szukać dalej

                // usuń obóz z pola:
                camps[level] = -1;
                // // odejmij wartość pola od wyniku:
                score -= field[level][i];
                // // wymaż trasy z obozu:
                lockedTrails = deleteTrails(lockedTrails, size, level, i);
            }
            else if(level == 0 && i==size-1){
                //dla ostatniego elementu w pierwszym wierszu wykonujemy rekurencję
                //i kończymy proces liczenia
                setUpCamps(field, lockedTrails, camps, bestCamps, size, level+1, score);
                return true;
            }
            //rekurencja dla pozostałych poziomów
            else if(setUpCamps(field, lockedTrails, camps, bestCamps, size, level+1, score)){
                //znaleziono wynik
                // zapamiętaj i przejdź dalej
                if(level == 0 && i==size-1){
                    //sprawdzono wszystkie przypadki
                    return true;
                }
            }
            else{
            discardTheLine:
                // dla tego pola nie ma rozwiązań
                // usuń obóz z pola:
                camps[level] = -1;
                // odejmij wartość pola od wyniku:
                score -= field[level][i];
                // wymaż trasy z obozu:
                lockedTrails = deleteTrails(lockedTrails, size, level, i);

                // printCamps(camps, size);
            }
        }
    }
    //jeżeli wszystkie pola z wiersza są na trasie:
    return false;
}

void showCamps(int** field, int size){
    int** trails = new int*[size];  //tu oznaczone trasy 
    int* camps = new int[size];     //aktualnie rozpatrywane rozłożenie obozów
    int* bestCamps = new int[size]; //tu finalne rozłożenie obozów

    //wypełnienie tablic
    for(int i=0; i<size; i++){
        camps[i] = -1;
        bestCamps[i] = -1;
        trails[i] = new int[size];
        for(int j=0; j<size; j++){
            trails[i][j] = 0;
        }
    }

    setUpCamps(field, trails, camps, bestCamps, size, 0, 0);

    // cout << "\nResult:\n";
    for(int i=0; i<size; i++){
        cout << bestCamps[i] << " ";
    }
    // cout << "\n";
}

int main(){

    int** fieldCost;
    int numberOfCamps;

    //Data entering segment:
    // cout << "Enter the number of camps\n";
    cin >> numberOfCamps;

    fieldCost = new int*[numberOfCamps];

    // cout << "Enter field costs:\n";
    for(int i=0; i<numberOfCamps; i++){
        fieldCost[i] = new int[numberOfCamps];
        for(int j=0; j<numberOfCamps; j++){
            cin >> fieldCost[i][j];
        }
    }
    //End of data entering segment

    showCamps(fieldCost, numberOfCamps);
 
    return 0;
}