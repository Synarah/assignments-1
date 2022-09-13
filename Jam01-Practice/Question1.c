#include <stdio.h>
struct Snack{
    char name[32];
    int quantity;
    float cost;
};
int main(){
    printf("%lu\n",sizeof(struct Snack));
    return 0;
}