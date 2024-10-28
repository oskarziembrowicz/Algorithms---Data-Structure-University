#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

int main()
{

    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    unsigned int t, n, *h1, *h2, tmp, cnt1, cnt2;
    string *nam1, *nam2;
    string tmpN;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        cin >> n;
        nam1 = new string[n];
        nam2 = new string[n];
        h1 = new unsigned int[n];
        h2 = new unsigned int[n];
        cnt1 = 0;
        cnt2 = 0;
        for (int j = 0; j < n; j++)
        {
            cin >> tmpN >> tmp;
            if ((tmp & (tmp - 1)) == 0)
            {
                h2[cnt2] = tmp;
                nam2[cnt2] = tmpN;
                cnt2++;
            }
            else
            {
                h1[cnt1] = tmp;
                nam1[cnt1] = tmpN;
                cnt1++;
            }
        }

        int k;
        for (int j = 1; j < cnt2; j++)
        {
            tmp = h2[j];
            tmpN = nam2[j];
            k = j - 1;
            while (k >= 0 && h2[k] > tmp)
            {
                h2[k + 1] = h2[k];
                nam2[k + 1] = nam2[k];
                --k;
            }
            h2[k + 1] = tmp;
            nam2[k + 1] = tmpN;
        }

        int l;
        for (int j = 1; j < cnt1; j++)
        {
            tmp = h1[j];
            tmpN = nam1[j];
            l = j - 1;
            while (l >= 0 && h1[l] > tmp)
            {
                h1[l + 1] = h1[l];
                nam1[l + 1] = nam1[l];
                --l;
            }
            h1[l + 1] = tmp;
            nam1[l + 1] = tmpN;
        }

        for (int j = 0; j < cnt2; j++)
        {
            cout << nam2[j] << "-" << h2[j] << " ";
        }
        for (int j = 0; j < cnt1; j++)
        {
            cout << nam1[j] << "-" << h1[j] << " ";
        }
        cout << "\n";
    }
    return 0;
}