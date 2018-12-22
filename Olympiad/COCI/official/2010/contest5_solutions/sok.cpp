#include <cstdio>
#define eps 1e-9

int main(){
	int buy[3];
	int need[3];
	scanf("%d %d %d", &buy[0], &buy[1], &buy[2]);
	scanf("%d %d %d", &need[0], &need[1], &need[2]);

	double best = 0;
	for (int i = 0; i < 3; i++){
		double t = 1.0 * buy[i] / need[i];
		if ( t > best )
			if ( buy[0] - need[0] * t >= -eps )
				if ( buy[1] - need[1] * t >= -eps )
					if ( buy[2] - need[2] * t >= -eps )
						best = t;
	}

	printf("%lf %lf %lf\n", buy[0] - need[0] * best, buy[1] - need[1] * best, buy[2] - need[2] * best);
	return 0;
}
