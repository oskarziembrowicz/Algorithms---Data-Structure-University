#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

int main()
{

    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n;
    int m;
    int tab[3];
    string s[2];
    int u[2];
    float w[2];
    int c[2];
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        s[0] = "";
        u[0] = 0;
        w[0] = 0;
        c[0] = 0;
        cin >> m;
        cin >> tab[0] >> tab[1] >> tab[2];
        for (int j = 0; j < m; j++)
        {
            cin >> s[1] >> u[1] >> w[1] >> c[1];

            if (tab[0] == 1)
            {
                if (u[1] > u[0])
                {
                    s[0] = s[1];
                    u[0] = u[1];
                    w[0] = w[1];
                    c[0] = c[1];
                }
                else if (u[1] == u[0])
                {
                    if (tab[1] == 2)
                    {
                        if (w[1] > w[0])
                        {
                            s[0] = s[1];
                            u[0] = u[1];
                            w[0] = w[1];
                            c[0] = c[1];
                        }
                        else if (w[1] == w[0])
                        {
                            if (c[1] > c[0])
                            {
                                s[0] = s[1];
                                u[0] = u[1];
                                w[0] = w[1];
                                c[0] = c[1];
                            }
                        }
                    }
                    else if (tab[1] == 3)
                    {
                        if (c[1] > c[0])
                        {
                            s[0] = s[1];
                            u[0] = u[1];
                            w[0] = w[1];
                            c[0] = c[1];
                        }
                        else if (c[1] == c[0])
                        {
                            if (w[1] > w[0])
                            {
                                s[0] = s[1];
                                u[0] = u[1];
                                w[0] = w[1];
                                c[0] = c[1];
                            }
                        }
                    }
                }
            }
            else if (tab[0] == 2)
            {
                if (w[1] > w[0])
                {
                    s[0] = s[1];
                    u[0] = u[1];
                    w[0] = w[1];
                    c[0] = c[1];
                }
                else if (w[1] == w[0])
                {
                    if (tab[1] == 1)
                    {
                        if (u[1] > u[0])
                        {
                            s[0] = s[1];
                            u[0] = u[1];
                            w[0] = w[1];
                            c[0] = c[1];
                        }
                        else if (u[1] == u[0])
                        {
                            if (c[1] > c[0])
                            {
                                s[0] = s[1];
                                u[0] = u[1];
                                w[0] = w[1];
                                c[0] = c[1];
                            }
                        }
                    }
                    else if (tab[1] == 3)
                    {
                        if (c[1] > c[0])
                        {
                            s[0] = s[1];
                            u[0] = u[1];
                            w[0] = w[1];
                            c[0] = c[1];
                        }
                        else if (c[1] == c[0])
                        {
                            if (u[1] > u[0])
                            {
                                s[0] = s[1];
                                u[0] = u[1];
                                w[0] = w[1];
                                c[0] = c[1];
                            }
                        }
                    }
                }
            }
            else if (tab[0] == 3)
            {
                if (c[1] > c[0])
                {
                    s[0] = s[1];
                    u[0] = u[1];
                    w[0] = w[1];
                    c[0] = c[1];
                }
                else if (c[1] == c[0])
                {
                    if (tab[1] == 1)
                    {
                        if (u[1] > u[0])
                        {
                            s[0] = s[1];
                            u[0] = u[1];
                            w[0] = w[1];
                            c[0] = c[1];
                        }
                        else if (u[1] == u[0])
                        {
                            if (w[1] > w[0])
                            {
                                s[0] = s[1];
                                u[0] = u[1];
                                w[0] = w[1];
                                c[0] = c[1];
                            }
                        }
                    }
                    else if (tab[1] == 2)
                    {
                        if (w[1] > w[0])
                        {
                            s[0] = s[1];
                            u[0] = u[1];
                            w[0] = w[1];
                            c[0] = c[1];
                        }
                        else if (w[1] == w[0])
                        {
                            if (u[1] > u[0])
                            {
                                s[0] = s[1];
                                u[0] = u[1];
                                w[0] = w[1];
                                c[0] = c[1];
                            }
                        }
                    }
                }
            }
        }
        cout << s[0] << "\n";
    }
    return 0;
}