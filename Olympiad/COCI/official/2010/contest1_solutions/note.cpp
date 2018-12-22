#include <cstdio>

int skladba[8];

int main(){
	for (int i = 0; i < 8; i++)
		scanf("%d", &skladba[i]);
	
	if ( 
	     skladba[0] == 1 && skladba[1] == 2 && skladba[2] == 3 && skladba[3] == 4 &&
	     skladba[4] == 5 && skladba[5] == 6 && skladba[6] == 7 && skladba[7] == 8
	   ){
		printf("uzlazno\n");
	}
	else if ( 
	     skladba[0] == 8 && skladba[1] == 7 && skladba[2] == 6 && skladba[3] == 5 &&
	     skladba[4] == 4 && skladba[5] == 3 && skladba[6] == 2 && skladba[7] == 1
	   ){
		printf("silazno\n");
	}
	else { 	
		printf("razlozeno\n");
	}

	return 0;
}
