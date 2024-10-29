#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

float BIGNUMBER = __FLT_MAX__;

class Warrior
{
public:
    int number;
    int x;
    int y;
    int strength;
};

// funkcja wybierająca parę gdzie jeden z wojowników ma numer najniższy ze wszystkich - mark2
pair<Warrior, Warrior> pairWithSmallestNumber(pair<Warrior, Warrior> pair1, pair<Warrior, Warrior> pair2)
{
    int minP1 = min(pair1.first.number, pair1.second.number);
    int maxP1 = max(pair1.first.number, pair1.second.number);
    int minP2 = min(pair2.first.number, pair2.second.number);
    int maxP2 = max(pair2.first.number, pair2.second.number);
    if (minP1 < minP2)
    {
        return pair1;
    }
    else if (minP1 > minP2)
    {
        return pair2;
    }
    else
    {
        // najmniejsze są równe - wybrać min z pozostałych
        if (maxP1 < maxP2)
        {
            return pair1;
        }
        else
        {
            return pair2;
        }
    }
}

// funkcja zwracająca przegranego z dwóch wojowników:
Warrior lostWarrior(pair<Warrior, Warrior> pair)
{
    if (pair.first.strength > pair.second.strength)
    {
        // wygrał first
        return pair.second;
    }
    else if (pair.first.strength < pair.second.strength)
    {
        // wygrał second
        return pair.first;
    }
    else
    {
        // siła równa -> zwraca tego o mniejszym numerze
        if (pair.first.number < pair.second.number)
        {
            // wygrał first
            return pair.second;
        }
        else
        {
            // wygrał second
            return pair.first;
        }
    }
}

// sort
bool compareByX(Warrior r1, Warrior r2)
{
    return (r1.x < r2.x);
}
// sort
bool compareByY(Warrior r1, Warrior r2)
{
    return (r1.y < r2.y);
}

// qsort
int compareX(const void *a, const void *b)
{
    Warrior *w1 = (Warrior *)a;
    Warrior *w2 = (Warrior *)b;
    // return (*(int*)w1->x - *(int*)w2->x);
    return (w1->x - w2->x);
}

// zwraca dystans między dwoma wojownikami
float distance(Warrior w1, Warrior w2)
{
    // jeśli to te same elementy
    if (w1.number == w2.number)
    {
        // na wszelki wypadek
        return BIGNUMBER;
    }
    return sqrt(pow((w1.x - w2.x), 2) + pow((w1.y - w2.y), 2));
}

// wyszukiwnie siłowe - do zbioru środkowego
pair<Warrior, Warrior> forceMinimalSpace(vector<Warrior> w)
{
    float min = BIGNUMBER;

    pair<Warrior, Warrior> minPair;

    // 'bezużyteczne' wartości w przypadku, gdy pętla się nie wykona
    Warrior tmp, tmp1;
    tmp.x = BIGNUMBER;
    tmp.y = BIGNUMBER;
    tmp.strength = 0;
    tmp.number = __INT16_MAX__ - 1;
    tmp1.x = 0;
    tmp1.y = 0;
    tmp1.strength = 0;
    tmp1.number = __INT16_MAX__;
    minPair.first = tmp;
    minPair.second = tmp1;

    for (int i = 0; i < w.size(); i++)
    {
        for (int j = i + 1; j < w.size(); j++)
        {
            if (distance(w.at(i), w.at(j)) < min)
            {
                min = distance(w.at(i), w.at(j));
                minPair.first = w.at(i);
                minPair.second = w.at(j);
            }
            else if (distance(w.at(i), w.at(j)) == min)
            {
                // wybierz parę o najmniejszym numerze
                pair<Warrior, Warrior> tmpPair;
                tmpPair.first = w.at(i);
                tmpPair.second = w.at(j);

                minPair = pairWithSmallestNumber(minPair, tmpPair);
            }
        }
    }
    return minPair;
}

// funkcja rekurencyjna:
pair<Warrior, Warrior> findMinimalSpace(vector<Warrior> w)
{
    vector<Warrior> leftHalf;
    vector<Warrior> rightHalf;
    int divideLine;                  // linia podziału na osi
    int halfSize;                    // punkt podziału wśród elementów
    pair<Warrior, Warrior> minPair;  // para z minimalną odległością
    pair<Warrior, Warrior> minPairL; // minimalna para dla lewej połowy
    pair<Warrior, Warrior> minPairR; // minimalna para dla prawej połowy
    float min = BIGNUMBER;
    float minL; // minimum dla pierwszej połowy
    float minR; // minimum dla drugiej połowy

    // Jeśli jest tylko dwóch wojowników:
    if (w.size() == 2)
    {
        minPair.first = w.front();
        minPair.second = w.back();
        return minPair;
    }
    else if (w.size() < 2) // jest mniej niż dwóch wojowników
    {
        // zwróć parę 'bezużytecznych' wojowników
        Warrior tmp, tmp1;
        tmp.x = BIGNUMBER;
        tmp.y = BIGNUMBER;
        tmp.strength = 0;
        tmp.number = __INT16_MAX__ - 1;
        tmp1.x = 0;
        tmp1.y = 0;
        tmp1.strength = 0;
        tmp1.number = __INT16_MAX__;
        minPair.first = tmp;
        minPair.second = tmp1;
        return minPair;
    }
    else
    {
        // wykonaj rekurencję:

        halfSize = w.size() / 2;       // będziemy dzielić względem 'środkowego' elementu zbioru
        divideLine = w.at(halfSize).x; // długość x do referencji przy punktach wokół środka

        // cout << "DivLine: " << divideLine << "\n";

        // dzielenie na lewą i prawą połowę pola
        for (int i = 0; i < w.size(); i++)
        {
            if (i < halfSize)
            {
                leftHalf.push_back(w.at(i));
            }
            else
            {
                rightHalf.push_back(w.at(i));
            }
        }

        // rekurencja dla obu połówek
        minPairL = findMinimalSpace(leftHalf);
        minPairR = findMinimalSpace(rightHalf);

        minL = distance(minPairL.first, minPairL.second);
        minR = distance(minPairR.first, minPairR.second);

        // wybrać parę z mniejszą odległością
        if (minL < minR)
        {
            min = minL;
            minPair = minPairL;
        }
        else if (minL > minR)
        {
            min = minR;
            minPair = minPairR;
        }
        else
        {
            // równe odległości - wybierz parę o najmniejszym numerze:
            minPair = pairWithSmallestNumber(minPairL, minPairR);
            min = minL; // odległości są takie same dla lewej i prawej połowy
        }

        // tworzenie puli elementów znajdujących się < min od linii środkowej:

        // leftHalf będzie pełnić rolę listy elementów wokół linii środkowej
        leftHalf.clear();
        for (int i = 0; i < w.size(); i++)
        {
            if (abs(divideLine - w.at(i).x) <= min)
            {
                leftHalf.push_back(w.at(i));
            }
        }

        // wybór najmniejszej odległości siłowo
        sort(leftHalf.begin(), leftHalf.end(), compareByY);
        minPairL = forceMinimalSpace(leftHalf);
        minL = distance(minPairL.first, minPairL.second);

        if (minL < min)
        {
            min = minL;
            minPair = minPairL;
        }
        else if (minL == min)
        {
            //  wybór pary z mniejszym numerem

            minPair = pairWithSmallestNumber(minPair, minPairL);
        }

        return minPair;
    }
}

int main()
{

    unsigned int numberOfWarriors, numberOfFights;
    vector<Warrior> warriors;
    pair<Warrior, Warrior> pairOfWarriors;
    Warrior looser;
    Warrior tmp;

    // Data entering segment
    // cout << "Enter contestants, and fights: \n";
    cin >> numberOfWarriors >> numberOfFights;

    for (int i = 0; i < numberOfWarriors; i++)
    {
        // cout << "Enter x, y, and strength for each contestant:\n";
        cin >> tmp.x >> tmp.y >> tmp.strength;
        tmp.number = i;
        warriors.push_back(tmp);
    }
    // End of data entering segment

    // for(int i=0; i<numberOfWarriors; i++){
    //     cout << "Warrior " << i << ": " << warriors.at(i).x << ", " << warriors.at(i).y << ", " << warriors.at(i).strength << "\n";
    // }
    // cout << "\n";

    sort(warriors.begin(), warriors.end(), compareByX); // QSORT???
    for (int i = 0; i < numberOfFights; i++)
    {
        pairOfWarriors = findMinimalSpace(warriors);

        looser = lostWarrior(pairOfWarriors);

        cout << looser.x << " " << looser.y << "\n";

        // usuwanie przegranego zawodnika
        for (int j = 0; j < warriors.size(); j++)
        {
            if (warriors.at(j).number == looser.number)
            {
                warriors.erase(warriors.begin() + j);
                break;
            }
        }
    }

    return 0;
}