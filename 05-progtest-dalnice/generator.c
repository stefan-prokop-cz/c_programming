#include <stdio.h>

int main() {

    for(int i = 0; i < 2; i++) {
        printf("construct [");
	for(int j = 0; j < 520; j++) {
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
