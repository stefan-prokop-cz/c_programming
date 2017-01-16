/**
 * Na vstup prijde: Souradnice nepritele ve slozenych zavorkach tj. { [1 , 1] , [2, 10] , [10, 20] }.
 * Techto bude maximalne 1000000.
 * Pote prijde vzdy zavorka s jednim bodem tj. [ 3 , 4 ]. Za kazdym bodem se vypise stredni hodnota (median)
 * vzdalenosti tohoto bodu od souradnic nepritele.
 * Vystup musi byt desetinne cislo, vstup je cislo cele.
 *
 * Chybove hlaseni se vypisuje pokud:
 * Nektery oddelovac je chybny.
 * Neni zadana zadna souradnice nepritele.
 * Nektera souradnice neni cislo.
 *
 * Priklad chodu programu:
 *
 * Nepritel:
 * { [1, 1], [2,10] , [-10, 20] }
 * Cile:
 * [10,10]
 * Stredni hodnota: 12.7279221
 * [3, 4]
 * Stredni hodnota: 6.08276253
 * [0,1]
 * Stredni hodnota: 9.21954446
 * [5,abc]
 * Nespravny vstup.
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX 1000000

int cmp(const void *a, const void *b) {
    double x = *(double *) a;
    double y = *(double *) b;

    if(x == y) {
        return 0;
    } else if(x > y) {
        return 1;
    } else {
        return -1;
    }
}

int main() {
    int souradnice[MAX][2], test, x, y, count = 0, a, b;
    char character, lz, carka, pz, end;

    printf("Nepritel:\n");
    if(scanf(" %c", &character) != 1 || character != '{') {
        printf("Nespravny vstup.\n");
        return 1;
    }

    while((test = scanf(" %c %d %c %d %c %c", &lz, &x, &carka, &y, &pz, &end)) == 6) {
        if(lz != '[' || carka != ',' || pz != ']' || (end != ',' && end != '}')) {
            printf("Nespravny vstup.\n");
            return 1;
        }

        souradnice[count][0] = x;
        souradnice[count][1] = y;
        count++;

        if(end == '}') {
            break;
        }
    }

    if(test != 6) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Cile:\n");
    while(1) {
        test = scanf(" %c %d %c %d %c", &lz, &a, &carka, &b, &pz);

        if(test == EOF) {
            break;
        }

        if(test != 5 || lz != '[' || carka != ',' || pz != ']') {
            printf("Nespravny vstup.\n");
            return 1;
        }

        double hodnoty[count];
        for(int i = 0; i < count; i++) {
            hodnoty[i] = sqrt((a - souradnice[i][0])*(a - souradnice[i][0]) + (b - souradnice[i][1])*(b - souradnice[i][1]));
        }

        qsort(hodnoty, count, sizeof(*hodnoty), cmp);

        if((count % 2) == 1) {
            double result = hodnoty[(count - 1) / 2];
            printf("Stredni hodnota: %d - %f\n", count, result);
        } else {
            double result = hodnoty[(count)/2] + hodnoty[(count + 1)/2];
            printf("Stredni hodnota: %f\n", result);
        }
    }

    return 0;
}