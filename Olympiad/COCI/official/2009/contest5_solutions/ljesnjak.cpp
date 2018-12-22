#include <cstdio>
#include <cstring>

int main( void ) {
    char ulaz[128];
    scanf("%s", ulaz);
   
    int slova = 0;
    for( int i=0; ulaz[i]!='\0'; ++i, ++slova ) {
        const char *nizovi[] = {"c-", "c=", "d-", "dz=", "lj", "nj", "s=", "z="};
        for ( int j=0; j<8; ++j )
            if ( strncmp(ulaz+i, nizovi[j], strlen(nizovi[j])) == 0 )
                i += strlen(nizovi[j])-1;
    }
    printf("%d\n", slova);
    return 0;
}
