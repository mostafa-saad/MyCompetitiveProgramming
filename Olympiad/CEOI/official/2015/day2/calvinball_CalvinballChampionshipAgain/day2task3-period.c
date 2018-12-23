#include <stdio.h>

int main (void)
{
  int i, j;

  printf ("3\n");
  for (j = 0; j < 3; j++)
    {
      const char *sep;

      sep = "";
      for (i = 0; i < 99999; i++)
	if (i % 3 == j)
	  {
	    printf ("%s%d", sep, i + 1);
	    sep = " ";
  	  }
      printf ("\n");
    }

  return 0;
}
