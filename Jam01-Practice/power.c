#include <stdio.h>

int power(int base, int exp){
    if(exp == 0){
        return 1;
    }
    else if(exp == 1){
        return base;
    }
    else{
        int i;
        int a = base;
        for(i=2; i <= exp; i++){
            a = a * base;
        }
        return a;
    }
}

int main(){
    int result;
    result = power(2,0);
    printf("%d\n", result);
    
    return 0;
}