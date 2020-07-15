#include <iostream>
#include "Queueclass.h"
#include "StackH.h"
#include "LinkedListHeader.h"
#define I 32167
using namespace std;

const int n = 8; // n = size + 1

template <typename T>
class Graph
{
public:
    T node[n];
    // int A[n][n]; // used as cost matrix also, in place of 1, put cost and in place of 0 pur max_int16
    //   int cost[n];
    //   cost[0] = 0;
    // also cost matrix is symmetric matrix
    int A[8][8] =
        {{I, I, I, I, I, I, I, I},
         {I, I, 25, I, I, I, 5, I},
         {I, 25, I, 12, I, I, I, 10},
         {I, I, 12, I, 8, I, I, I},
         {I, I, I, 8, I, 16, I, 14},
         {I, I, I, I, 16, I, 20, 18},
         {I, 5, I, I, I, 20, I, I},
         {I, I, 10, I, 14, 18, I, I}};

public:
    Graph<T>()
    {
        node[0] = 0;
        int i, j;
        for (i = 1; i < n; i++)
            node[i] = i;
        //     for (i = 0; i < n; i++)
        //         A[0][i] = I;
        //     for (i = 0; i < n; i++)
        //         A[i][0] = I;
        //     for (i = 1; i < n; i++)
        //         for (j = 1; j < n; j++)
        //             cin >> A[i][j];
    }

    void BFS(int n1);
    void DFS(int n1);
    void Prims();
    void Krus();
};

template <typename T>
void Graph<T>::BFS(int n1)
{
    int check[n];
    int i, j;
    for (i = 0; i < n; i++)
        check[i] = 0;
    Queue<int> q1(n);
    cout << node[n1];
    q1.enqueue(n1);
    check[n1] = 1;
    while (!q1.isEmpty())
    {
        j = q1.dequeue();
        for (i = 1; i < n; i++)
        {
            if (A[j][i] == 1 && check[i] == 0)
            {
                q1.enqueue(i);
                cout << node[i];
                check[i] = 1;
            }
        }
    }
}

//template <typename T>
//void Graph<T>::DFS(int n1)
//{
//    int i, j;
//    int check[n];
//    check[0] = 0;
//    check[n1] = 1;
//    Stack<int> s1;
//    cout << node[n1];
//    s1.push(n1);
//    while (!s1.isEmpty())
//    {
//        j = s1.pop();
//        for (i = 1; i < n; i++)
//        {
//           if(A[j][i] == 1 && check[j] != 1){
//                cout<<node[i]
//            }
//        }
//    }
//}

template <typename T>
void Graph<T>::DFS(int n1)
{
    static int check[n];
    check[0] = 0;
    if (check[n1] != 1)
    {
        cout << node[n1];
        check[n1] = 1;
        for (int i = 1; i < n; i++)
        {
            if (check[i] != 1)
            {
                DFS(i);
            }
        }
    }
}

template <typename T>
T find_min(T A1[])
{
    T min = A1[0];
    int i;
    for (i = 0; i < n; i++)
    {
        if (min > A1[i])
            min = A1[i];
    }
    return min;
}

template <typename T>
void Graph<T>::Prims()
{
    int final[2][n - 1];
    int near[n];
    int i, j, k, l, min;
    min = I;
    for (i = 0; i < n; i++) // Initialisation
        near[i] = I;

    for (i = 1; i < n; i++)
        for (j = i; j < n; j++)
            if (A[i][j] < min)
            {
                min = A[i][j];
                k = i;
                l = j;
            }
    final[0][1] = k;
    final[1][1] = l;
    near[k] = 0;
    near[l] = 0;
    for (i = 1; i < n; i++)
        for (j = i; j < n; j++)
        {
            if (A[l][j] < A[k][j] && near[j] != 0)
                near[j] = l;
            if (A[l][j] >= A[k][j] && near[j] != 0)
                near[j] = k;
        }
    int m;
    for (m = 2; m < n - 1; m++)
    {
        min = I;
        for (i = 1; i < n; i++)
        {
            if (A[i][near[i]] < min && near[i] != 0)
            {
                min = A[i][near[i]];
                k = i;
                l = near[i];
            }
        }
        final[0][m] = k;
        final[1][m] = l;
        near[k] = 0;
        near[l] = 0;
        for (i = 1; i < n; i++)
            for (j = i; j < n; j++)
            {
                if (A[l][j] < A[k][j] && near[j] != 0)
                    near[j] = l;
                if (A[l][j] >= A[k][j] && near[j] != 0)
                    near[j] = k;
            }
    }
    for (i = 1; i < n - 1; i++)
        cout << final[0][i] << " " << final[1][i] << endl;
}

int find(int s[], int u)
{
    int x = u;
    while (s[x] > 0)
        x = s[x];
    return x;
}

void Union(int s[], int x, int y)
{
    int u = find(s, x);
    int v = find(s, y);
    if (s[u] < s[v])
    {
        s[u] = s[u] + s[v];
        s[v] = u;
    }
    else
    {
        s[v] = s[v] + s[u];
        s[u] = v;
    }
}

template <typename T>
void Graph<T>::Krus()
{
    int i, j;
    int k, l;
    int o = 1;
    int final[2][n - 1];
    int included[n];
    int circuit[n]; // to check for loop in tree

    for (i = 0; i < n; i++)
        circuit[i] = -1;
    for (i = 0; i < n; i++)
        included[i] = 0;

    while (o < n - 1)
    {
        int min = I;
        for (i = 1; i < n; i++) // upper half matrix
            for (j = i; j < n; j++)
                if (A[i][j] < min)
                {
                    k = i;
                    l = j;
                    min = A[i][j];
                }
        if (find(circuit, k) != find(circuit, l))
        {
            final[0][o] = k;
            final[1][o] = l;
            Union(circuit, k, l);
            o++;
        }
        A[k][l] = I;
    }
    for (i = 1; i < n - 1; i++)
        cout << final[0][i] << " " << final[1][i] << endl;
}

int main()
{
    Graph<int> g1;
    //g1.Prims();
    g1.Krus();
    //g1.DFS(4);
    //cout << *g1.A[0];
    return 0;
}