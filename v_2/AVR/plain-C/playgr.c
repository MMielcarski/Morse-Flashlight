#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    char nap1[6] = "123";
    char * nap2 = "456";

    strcat(nap1,nap2);

    printf("%s\n",nap1);

 return 0;
}
