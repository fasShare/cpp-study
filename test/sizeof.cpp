#include <stdio.h>
#include <stdlib.h>

#define elem_sizeof(T) ((size_t)((T*)0 + 1))

#define array_sizeof(T) ((size_t)(&T+1)-(size_t)(&T))

int main(int argc, char *argv[]) {
    int n;
   
    scanf("%d",&n);

    int arr[n];
    
    int a = elem_sizeof(n++);
    int b = array_sizeof(arr);
    
    printf("a = %d\n", a);
    printf("b = %d\n", a);

    return 0;
}

