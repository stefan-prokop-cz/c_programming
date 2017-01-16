/**
 * ZADANI:
 *
 * Na vstupu přijdou souřadnice jednotek nepřítele { [1 , 10] , [1, 5] , [5 , -15] }. Neví se dopředu, kolik jich bude,
 * ale maximálně 1000000. Souřadnice jsou odděleny čárkou, za poslední souřadnicí čárka není, kolem souřadnic jsou
 * složené závorky.
 * Dále chodí jednotlivě souřadnice cílů útoků [ 1 , 10 ]. Za každou souřadnicí program vypíše vzdálenost k
 * nejvzdálenější jednotce nepřítele. Načítání končí při dosažení EOF. Vstupem jsou celá čísla, výstupem desetinné
 * číslo.
 * Přiklad chodu programu:
 *
 * Nepritel:
 * { [1, 10   ], [2,1] , [-10, 20] }
 * Cile:
 * [10,10]
 * Max: 22.36068
 * [3, 4]
 * Max: 20.615528
 * [0,1]
 * Max: 21.470911
 */

#include <stdio.h>
#include <math.h>

#define MAX 1000000

int main() {

    char character, lz, carka, pz, end;
    int x, y, test, count = 0, a, b;
    double max;
    int souradnice[MAX][2];

    printf("Nepritel:\n");
    if(scanf(" %c", &character) != 1 || character != '{') {
        printf("Nespravny vstup.\n");
        return 1;
    }

    while((test = scanf(" %c %d %c %d %c %c", &lz, &x, &carka, &y, &pz, &end)) == 6) {
        if(lz != '[' || carka != ',' || pz != ']' || (end != ',' && end != '}') || count >= MAX) {
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

    if(test != 6 || count >= MAX || end != '}') {
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Cile:\n");
    while(1) {
        test = scanf(" %c %d %c %d %c", &lz, &a, &carka, &b, &pz);

        if(test == EOF) {
            break;
        }

        if(test != 5) {
            printf("Nespravny vstup.\n");
            return 1;
        }

        if(lz != '[' || carka != ',' || pz != ']') {
            printf("Nespravny vstup.\n");
            return 1;
        }

        for(int i = 0; i < count; i++) {
            double vzdalenost = sqrt((a - souradnice[i][0])*(a - souradnice[i][0]) + (b - souradnice[i][1])*(b - souradnice[i][1]));

            if(i == 0) {
                max = vzdalenost;
            }

            if(max < vzdalenost) {
                max = vzdalenost;
            }
        }

        printf("Max: %f\n", max);
    }

    return 0;
}