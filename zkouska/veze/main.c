/**
 * Program, který vytvoří šachovnici n*n (tedy dynamicky). Dále na vstupu dostanete souřadnice, kde se na
 * šachovnici nacházejí věže. Výstupem programu je výpis věží, které se navzájem ohrožují.
 * EDIT Upřesnění zadání: Šachovnici není třeba alokovat, pouze dvojrozměrné pole pro souřadnice. Na vstup
 * příjdou souřadnice věží ve formátu a1 d5 e4500 z5. Souřadnice jsou oddělené mezerami, tabulátory a '\n'
 * které ignorujete a ukončené EOF. Souřadnice musí být validní, tzn [a..z] pro první a kladné celé čislo pro
 * druhou. Výstupem je výpis věží které se navzájem ohrožují
 *
 * Vstup: a1 a5 c5
 * Výstup: a1 - a5, a5 - a1, a5 - c5, c5 - a5
 *
 * Pozor, např pro vstup a1 a2 a3 je výstup a1 - a3 špatně protože mezi nimi leží a2 a nemohou se tedy
 * navzájem ohrožovat.
 */

#include <stdio.h>

#define MAX 26

int checkPosition(char character) {
    switch (character) {
        case 'a':
            return 0;
        case 'b':
            return 1;
        case 'c':
            return 2;
        case 'd':
            return 3;
        case 'e':
            return 4;
        case 'f':
            return 5;
        case 'g':
            return 6;
        case 'h':
            return 7;
        case 'i':
            return 8;
        case 'j':
            return 9;
        case 'k':
            return 10;
        case 'l':
            return 11;
        case 'm':
            return 12;
        case 'n':
            return 13;
        case 'o':
            return 14;
        case 'p':
            return 15;
        case 'q':
            return 16;
        case 'r':
            return 17;
        case 's':
            return 18;
        case 't':
            return 19;
        case 'u':
            return 20;
        case 'v':
            return 21;
        case 'w':
            return 22;
        case 'x':
            return 23;
        case 'y':
            return 24;
        case 'z':
            return 25;
        default:
            return -1;
    }
}

char getPosition(int character) {
    switch (character) {
        case 0:
            return 'a';
        case 1:
            return 'b';
        case 2:
            return 'c';
        case 3:
            return 'd';
        case 4:
            return 'e';
        case 5:
            return 'f';
        case 6:
            return 'g';
        case 7:
            return 'h';
        case 8:
            return 'i';
        case 9:
            return 'j';
        case 10:
            return 'k';
        case 11:
            return 'l';
        case 12:
            return 'm';
        case 13:
            return 'n';
        case 14:
            return 'o';
        case 15:
            return 'p';
        case 16:
            return 'q';
        case 17:
            return 'r';
        case 18:
            return 's';
        case 19:
            return 't';
        case 20:
            return 'u';
        case 21:
            return 'v';
        case 22:
            return 'w';
        case 23:
            return 'x';
        case 24:
            return 'y';
        case 25:
            return 'z';
        default:
            return -1;
    }
}

int main() {
    int veze[MAX][MAX];
    int test, souradnice, i, j;
    char pozice;

    for(i = 0; i < MAX; i++) {
        for(j = 0; j < MAX; j++) {
            veze[i][j] = 0;
        }
    }

    printf("Pozice vezi:\n");
    while((test = scanf(" %c%d", &pozice, &souradnice)) == 2) {
        int position = checkPosition(pozice);

        if(position == -1 || souradnice <= 0 || souradnice > MAX) {
            printf("Nespravny vstup.\n");
            return 1;
        }

        if(veze[position][souradnice - 1] == 0) {
            veze[position][souradnice - 1] = 1;
        } else {
            printf("Nespravny vstup.\n");
            return 1;
        }
    }

    if(test != EOF) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Ohrozuji se:\n");
    for(i = 0; i < MAX; i++) {
        for(j = 0; j < MAX; j++) {
            for(int k = (j + 1); k < MAX; k++) {
                if(veze[i][j] != 0 && veze[i][j] == veze[i][k]) {
                    char position = getPosition(i);
                    printf("%c%d - %c%d\n", position, (j + 1), position, (k + 1));
                    printf("%c%d - %c%d\n", position, (k + 1), position, (j + 1));
                    break;
                }
            }
        }
    }

    for(i = 0; i < MAX; i++) {
        for(j = 0; j < MAX; j++) {
            for(int k = (j + 1); k < MAX; k++) {
                if(veze[j][i] != 0 && veze[j][i] == veze[k][i]) {
                    printf("%c%d - %c%d\n", getPosition(j), (i + 1), getPosition(k), (i + 1));
                    printf("%c%d - %c%d\n", getPosition(k), (i + 1), getPosition(j), (i + 1));
                    break;
                }
            }
        }
    }

    return 0;
}