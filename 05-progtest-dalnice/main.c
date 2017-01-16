/**
 * 05 - progtest - Dalnice
 *
 * @author Stefan Prokop <prokoste@fit.cvut.cz>
 *
 * Spent time:
 *
 * Total spent time:
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WEIGHT_SIZE 10

int compare(char * text) {
    int checked = 0;
    char cmp[3][10] = {{"construct"}, {"limits"}, {"load"}};

    for(int i = 0; i < (int) strlen(cmp[2]); ++i) {
        if(text[i] == cmp[2][i]) {
            checked++;
        }
    }

    if(checked >= 4) {
        if((int) strlen(text) > (int) strlen(cmp[2]) && (text[4] != '\t' && text[4] != '\n' && text[4] != ' ' && text[4] != '\0')) {
            return 0;
        }

        return 3;
    }

    checked = 0;
    for(int i = 0; i < (int) strlen(cmp[1]); ++i) {
        if(text[i] == cmp[1][i]) {
            checked++;
        }
    }

    if(checked >= 6) {
        if((int) strlen(text) > (int) strlen(cmp[2]) && (text[6] != '\t' && text[6] != '\n' && text[6] != ' ' && text[6] != '\0')) {
            return 0;
        }

        return 2;
    }

    checked = 0;
    for(int i = 0; i < (int) strlen(cmp[0]); ++i) {
        if(text[i] == cmp[0][i]) {
            checked++;
        }
    }

    if(checked >= 9) {
        if((int) strlen(text) > (int) strlen(cmp[2]) && (text[9] != '\t' && text[9] != '\n' && text[9] != ' ' && text[9] != '\0')) {
            return 0;
        }

        return 1;
    }

    return 0;
}
/*
int loadConstruct(int * weight, int * count) {


    free(weight);
    return 0;
}

int loadLimits(int * weight, int * count) {


    //free(weight);
    return 0;
}

int loadData(int * weight, int * count) {

    //free(weight);
    return 0;
}
*/
int main(int argc, char * argv []) {
    char text[10];
    int min, max, result, br = 0;
    int cmp, c;
    int count = 0;
    int start_index;
    char character;
    int index;
    int construct_count = count;
    int allocated = 0;
    int * weight = NULL;
    weight = (int *) malloc(WEIGHT_SIZE * sizeof(*weight));

    printf("Prikazy:\n");

    while(scanf("%s", text) != EOF) {
        cmp = compare(text);

        if(cmp == 1) {
            br = 0;

            if((scanf(" %c", &character) == 1) && character == '[') {
                while ((c = scanf("%d %c", &index, &character)) == 2) {
                    if(index <= 0) {
                        printf("Nespravny vstup.\n");
                        br = 1;

                        break;
                    }

                    if(construct_count == allocated) {
                        if(allocated > 50) {
                            allocated = construct_count * WEIGHT_SIZE;
                        } else {
                            allocated = construct_count + WEIGHT_SIZE;
                        }

                        weight = (int *) realloc(weight, allocated * sizeof(int));
                    }

                    /**
                     * Kontrola vstupu na pozadovane hodnoty
                     */
                    if (character != ',' && character != ']') {
                        printf("Nespravny vstup.\n");
                        br = 1;

                        break;
                    } else if (character == ']') {
                        weight[construct_count] = index;
                        construct_count++;

                        break;
                    }

                    weight[construct_count] = index;
                    construct_count++;
                }

                if((c == EOF && character != ']') || c != 2) {
                    printf("Nespravny vstup.\n");

                    break;
                }

                if(br == 1) {
                    break;
                }

                count = construct_count;
            }
        } else if(cmp == 2) {
            br = 0;

            if ((c = scanf("%d %c", &start_index, &character) == 2) && character == '[' && start_index >= 0) {
                if (start_index >= count) {
                    printf("Nespravny vstup.\n");

                    break;
                }

                while (scanf("%d %c", &index, &character) == 2) {
                    if (start_index >= count || index <= 0) {
                        printf("Nespravny vstup.\n");
                        br = 1;

                        break;
                    }

                    /**
                     * Kontrola vstupu na pozadovane hodnoty
                     */
                    if (character != ',' && character != ']') {
                        br = 1;

                        break;
                    } else if (character == ']') {
                        weight[start_index] = index;
                        start_index++;

                        break;
                    }

                    weight[start_index] = index;
                    start_index++;
                }

                if((c == EOF && character != ']') || (c != 2 && character != ']')) {
                    printf("Nespravny vstup.\n");

                    break;
                }

                if(br == 1) {
                    printf("Nespravny vstup.\n");
                    
                    break;
                }
            }
        } else if(cmp == 3) {
            if ((scanf("%d %d", &min, &max) == 2) && min < count && max < count && min >= 0 && min <= max && count > 0) {
                result = weight[min];

                for (int i = min; i <= max; i++) {
                    if (i > min && result > weight[i]) {
                        result = weight[i];
                    }
                }

                printf("Maximalni naklad: %d\n", result);
            } else {
                printf("Nespravny vstup.\n");

                break;
            }
        } else {
            printf("Nespravny vstup.\n");

            break;
        }
    }

    free(weight);
    return 0;
}
