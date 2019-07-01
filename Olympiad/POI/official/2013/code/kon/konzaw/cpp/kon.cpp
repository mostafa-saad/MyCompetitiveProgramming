int N, K, t[10];

void inicjuj(int n, int k, int *D)
{
    N = n, K = k;
    for (int i = 0; i < n; ++i)
        t[i] = D[i];
}

void podlej(int a, int b)
{
    t[a] += 1;
    t[b] += 1;
}

int dojrzale(int a, int b)
{
    return (t[a] >= K) + (t[b] >= K); /* cos glupiego */
}
