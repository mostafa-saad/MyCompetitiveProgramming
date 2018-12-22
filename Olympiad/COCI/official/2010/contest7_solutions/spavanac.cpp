#include <cstdio>
#include <cstdlib>

int main(int argc, char **argv, char **env) {
	int s, m;
	scanf("%d %d", &s, &m);
	if ( m < 45 ){
		if ( s > 0 )
			s--;
		else
			s = 23;
		m = 60 - (45 - m);
	}
	else
		m -= 45;
	printf("%d %d\n", s, m);
	return EXIT_SUCCESS;
}
