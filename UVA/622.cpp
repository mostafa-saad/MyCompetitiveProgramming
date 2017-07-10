// This is a context free grammar: https://en.wikipedia.org/wiki/Context-free_grammar
// One natural way to handle this style is using recursion

// One can still handle it using stl datastructures
	// E.g. https://en.wikipedia.org/wiki/Context-free_grammar

#include <iostream>
#include <string>
using namespace std;

int p;
char e[10000];	//The input expression

int expression();
int component();
int factor();
bool error_occur;

int expression()
{
	if(error_occur)
		return 0;
	int x;
	x = component();
	
	if(e[p] == '+')
	{
		while(e[p] == '+')
		{
			p++;
			x += expression();
		}
	}
	else if(e[p] !='\0' && e[p] != '*' && e[p] != ')')
		error_occur = true;
	return x;
}

int component()
{
	if(error_occur)
		return 0;

	int x;
	x = factor();
	if(e[p] == '*')
	{
		while(e[p] == '*')
		{
			p++;
			x *= component();
		}
	}
	else if(e[p] !='\0' && e[p] != '+' && e[p] != ')')
		error_occur = true;

	return x;
}

int factor()
{
	if(error_occur)
		return 0;

	int x = 0;
	if( isdigit(e[p]) )
	{
		while( isdigit(e[p]) )
			x = x*10 + (e[p++]-'0');
	}
	else if( e[p] == '(' )
	{
		p++;
		x = expression();
		if(e[p] != ')')
			error_occur = true;
		
		p++;
	}
	else
		error_occur = true;
	return x;
}

int main()
{
	int cases;
	cin>>cases;

	while(cases--)
	{
		cin>>e;
		p = 0;		
		error_occur = false;

		int res = expression();

		if(p != strlen(e))
			error_occur = true;

		if(error_occur)
			cout<<"ERROR\n";
		else
			cout<<res<<"\n";
	}
	return 0;
}
