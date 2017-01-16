//
// Created by stefi on 28.11.16.
//

#include <stdio.h>

int main() {

    for(int i = 0; i < 100; i++) {
        printf("%d : [", i);
        for(int j = 0; j < 2500; j++) {
            if(j == 0) {
                printf("%d", j);
            } else {
                printf(",%d", j);
            }
        }
        printf("]\n");
    }

    for(int i = 0; i < 150; i++) {
        printf("%d : [", i);
        for(int j = 0; j < 400; j++) {
            if(j == 0) {
                printf("%d", j);
            } else {
                printf(",%d", j);
            }
        }
        printf("]\n");
    }

    return 0;
}

