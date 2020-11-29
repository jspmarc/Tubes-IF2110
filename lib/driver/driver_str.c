#include "boolean.h"
#include "../header/str.h"
#include <stdio.h>

int main(){
    char *string, *stronk;
    string = "CAPEK";
    stronk = "BANGET";
    printf("panjang string: %d\n", strLen(string));
    if(strIsEqual(string,stronk)) printf("string 1 dan 2 sama\n");
    else printf("string 1 dan string 2 tidak sama\n");
    printf("END OF PROGRAM\n");
    return 0;
}
