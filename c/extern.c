// https://www.youtube.com/watch?v=1Dkfmf4PmvQ&list=PLBlnK6fEyqRhX6r2uhhlubuF5QextdCSM&index=13
/* once delcared is visible to the whole programme
 * delcaration only ,and will go outside each scope until find definitino
 */
#include<stdio.h>
#include"other.c"

int main() {
    {
        extern int var;
    }
    var = 200;
    printf("%d\n",var);
    return 0;
}
