#include <iostream>

using namespace std;

// Wariacja 2 wyboru najstarszej pary

/* Dla znalezionej pary wyznaczyć odległosć drugiego
elementu od początku i zapisać jako max
Wybrać parę o największej odległości */

class List
{
public:
    int size;

    class element
    {
    public:
        int value;
        element *next;
        element *prev;
    };
    class iterator
    {
    public:
        element *ptr;
        iterator next()
        {
            ptr = ptr->next;
            return *this;
        }
        iterator prev()
        {
            ptr = ptr->prev;
            return *this;
        }
    };
    iterator start;

    List(int value)
    {
        element *a = new element;
        a->next = a;
        a->prev = a;
        a->value = value;
        start.ptr = a;
        size = 1;
    }

    void insert(iterator iter, int value) // Dodaje za
    {
        element *a = iter.ptr;
        element *b = new element;
        element *c = a->next;
        b->next = c;
        b->prev = a;
        b->value = value;
        c->prev = b;
        a->next = b;
        size++;
    }

    iterator delete_element(iterator iter) // Usuwa za iter
    {
        element *toDelete = iter.ptr;
        element *thePrevious = toDelete->prev;
        element *theNext = toDelete->next;
        thePrevious->next = theNext;
        theNext->prev = thePrevious;
        iter.ptr = thePrevious;
        if (start.ptr == toDelete)
        {
            start.ptr = theNext;
        }
        delete toDelete;
        size--;
        return iter;
    }

    void print()
    {
        iterator iter = start;
        for (int i = 0; i < size; i++)
        {
            cout << iter.ptr->value << " ";
            iter.ptr = iter.ptr->next;
        }
        cout << "\n";
    }

    void print_back()
    {
        iterator iter = start;
        for (int i = 0; i < size; i++)
        {
            cout << iter.ptr->value << " ";
            iter.ptr = iter.ptr->prev;
        }
        cout << "\n";
    }

    void delete_list()
    {
        element *curr = start.ptr;
        element *another;
        for (int i = 0; i < size; i++)
        {
            another = curr->next;
            delete curr;
            curr = another;
        }
    }
};

int main()
{

    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int numberOfPairs, startingPair, direction;
    int numberOfOperations;
    int operationDescriptor, moves, flag;
    int *playersLeft, *playersIndex;
    int tmp;

    cin >> numberOfPairs >> startingPair >> direction;

    List players(0);
    List::iterator iter = players.start;
    playersLeft = new int[numberOfPairs];
    playersIndex = new int[numberOfPairs];
    players.insert(iter, 0);
    iter.next();
    playersLeft[0] = 2;
    playersIndex[0] = 0;

    for (int i = 1; i < numberOfPairs; i++) // wypełnienie listy
    {
        players.insert(iter, i);
        iter.next();
        players.insert(iter, i);
        iter.next();
        playersLeft[i] = 2;
        playersIndex[i] = i;
    }

    iter = players.start;
    for (int i = 0; i < startingPair; i++) // ustawiamy na początkową parę
    {
        iter.next();
        iter.next();
    }
    players.start = iter;

    iter.next();                            // stoimy na pierwszej lewej
    tmp = iter.ptr->value;                  // zapamiętujemy wartość
    for (int i = 0; i < numberOfPairs; i++) // zamiana lewych osób
    {
        iter.next();
        iter.next();
        swap(tmp, iter.ptr->value);
    }
    iter = players.start; // stoimy na pierwszej prawej

    cin >> numberOfOperations;
    for (int i = 0; i < numberOfOperations; i++)
    {
        cin >> operationDescriptor >> moves;
        if (operationDescriptor == 1)
        {
            cin >> flag;
        }

        if (operationDescriptor == 0) // Działa!
        {
            if (direction == 0)
            {
                for (int j = 0; j < moves - 1; j++)
                {
                    iter.next();
                }
                players.start = iter; // Ustawienie nowego początku
                players.print();      // Wyświetlamy stan gry
            }
            else if (direction == 1)
            {
                for (int j = 0; j < moves - 1; j++)
                {
                    iter.prev();
                }
                players.start = iter;
                players.print_back();
            }
        }
        else if (operationDescriptor == 1)
        {
            if (direction == 0)
            {
                for (int j = 0; j < moves - 1; j++)
                {
                    iter.next();
                }
                // Stoimy na odpadającej osobie
                // playersLeft[iter.ptr->value] -= 1; // Zmniejszamy ilość graczy z pary

                for (int j = 0; j < numberOfPairs; j++)
                {
                    if (playersIndex[j] == iter.ptr->value)
                    {
                        playersLeft[j] -= 1;
                        if (playersLeft[j] == 0)
                        {
                            // Jeśli para odpadła idzie na koniec
                            for (int k = j + 1; k < numberOfPairs; k++)
                            {
                                swap(playersLeft[k], playersLeft[k - 1]);
                                swap(playersIndex[k], playersIndex[k - 1]);
                            }
                        }
                        break;
                    }
                }

                iter = players.delete_element(iter); // Stoimy na iret.prev
                direction = 1;                       // Zmiana kierunku
                players.start = iter;                // Ustawienie początku

                if (flag == 1 || players.size <= 3)
                {
                    tmp = -1;
                    for (int j = 0; j < numberOfPairs; j++)
                    {
                        if (playersLeft[j] == 0)
                        { // Jeśli jakaś para całkiem odpadła
                            tmp = playersIndex[j];
                            playersLeft[j] = 2; // Para wraca do gry
                            break;
                        }
                    }

                    if (tmp != -1) // Jeśli jest jakaś para
                    {
                        iter.prev(); // Stoimy przed miejscem na nowy
                        players.insert(iter, tmp);
                        iter = players.start;
                        iter.next(); // Stoimy przed miejscem na nowy
                        players.insert(iter, tmp);
                        iter = players.start;
                    }
                }
            }
            else if (direction == 1)
            {
                for (int j = 0; j < moves - 1; j++)
                {
                    iter.prev();
                }

                for (int j = 0; j < numberOfPairs; j++)
                {
                    if (playersIndex[j] == iter.ptr->value)
                    {
                        playersLeft[j] -= 1;
                        if (playersLeft[j] == 0)
                        {
                            // Jeśli para odpadła idzie na koniec
                            for (int k = j + 1; k < numberOfPairs; k++)
                            {
                                swap(playersLeft[k], playersLeft[k - 1]);
                                swap(playersIndex[k], playersIndex[k - 1]);
                            }
                        }
                        break;
                    }
                }

                iter = players.delete_element(iter); // Stoimy na iret.prev
                iter.next();                         // Skaczemy bo inny kierunek
                direction = 0;                       // Zmienić kierunek
                players.start = iter;                // Ustawić początek
                if (flag == 1 || players.size <= 3)
                {
                    tmp = -1;
                    for (int j = 0; j < numberOfPairs; j++)
                    {
                        if (playersLeft[j] == 0)
                        { // Jeśli jakaś para całkiem odpadła
                            tmp = playersIndex[j];
                            playersLeft[j] = 2; // Para wraca do gry
                            break;
                        }
                    }

                    if (tmp != -1) // Jeśli jest jakaś para
                    {
                        players.insert(iter, tmp);
                        iter.prev();
                        iter.prev();
                        players.insert(iter, tmp);
                        iter = players.start;
                    }
                }
            }
        }
        else // Operacja - 2 -- Działa!
        {
            if (direction == 0)
            {
                for (int j = 0; j < moves - 1; j++)
                {
                    iter.next();
                }
                direction = 1;
                players.start = iter;
            }
            else if (direction == 1)
            {
                for (int j = 0; j < moves - 1; j++)
                {
                    iter.prev();
                }
                direction = 0;
                players.start = iter;
            }
        }
    }

    // players.delete_list();

    // usuwanie wskaźników

    return 0;
}