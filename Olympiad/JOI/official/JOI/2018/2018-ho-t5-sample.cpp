#include<stdio.h>
#include<vector>
#include<algorithm>
#include<string>
#include<iostream>
using namespace std;
int d0[2][1 << 20], d1[2][1 << 20];
int cnt[1 << 20];
int main()
{
	int len, query;
	scanf("%d%d", &len, &query);
	string str;
	cin >> str;
	for (int i = 0; i < str.size(); i++)d0[0][i] = d1[0][i] = str[i] - '0';
	int cur = 0;
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < (1 << len); j++)d0[1 - cur][j] = d1[1 - cur][j] = 0;
		for (int j = 0; j < (1 << len); j++)
		{
			d0[1 - cur][j] += d0[cur][j];
			if (0 == (j&(1 << i)))d0[1 - cur][j | (1 << i)] += d0[cur][j];
			d1[1 - cur][j] += d1[cur][j];
			if (j&(1 << i))d1[1 - cur][j - (j&(1 << i))] += d1[cur][j];
		}
		cur = 1 - cur;
	}
	for (int p = 0; p < (1 << len); p++)
	{
		int c = 0;
		for (int i = 0; i < len; i++)if (p&(1 << i))c++;
		cnt[p] = c & 1;
	}
	for (int p = 0; p < query; p++)
	{
		char s[21];
		scanf("%s", &s);
		reverse(s, s + len);
		int c0 = 0, c1 = 0;
		int a = 0, b = 0, q = 0;
		for (int i = 0; i < len; i++)
		{
			if (s[i] == '0')c0++, a += 1 << i;
			else if (s[i] == '1')c1++, b += 1 << i;
			else q += 1 << i;
		}
		int r = 0;
		if (c0 <= len / 3)
		{
			for (int i = a; i >= 0; i--)
			{
				i &= a;
				if (cnt[i])r -= d1[cur][i | b];
				else r += d1[cur][i | b];
			}
		}
		else if (c1 <= len / 3)
		{
			for (int i = b; i >= 0; i--)
			{
				i &= b;
				if (cnt[i])r -= d0[cur][q + b - i];
				else r += d0[cur][q + b - i];
			}
		}
		else
		{
			for (int i = q; i >= 0; i--)
			{
				i &= q;
				r += str[i + b] - '0';
			}
		}
		printf("%d\n", r);
	}
}