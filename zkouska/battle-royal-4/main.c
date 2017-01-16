/**
 * Satelit pořizuje snímky nepřátelského území a zaznamenává svoji pozici nad Zemí v okamžiku snímkování.
 * Následně jsou na snímku identifikované nepřátelské jednotky, pro každou jednotku je zjištěna pozice uvnitř snímku.
 * Program dostane na vstupu mnoho takových satelitních snímků. Satelitní snímky se mohou překrývat – je možné, že
 * daná jednotka je zaznamenaná na více snímcích. Může se taky stát, že daná jednotka se objeví pouze na některých
 * překrývajících se snímcích (byla dobře maskovaná). Úkolem programu je určit celkový počet nepřátelských jednotek.
 * Vstupem programu je seznam satelitních snímků. Každý snímek začíná souřadnicí pozice satelitu (v hranatých
 * závorkách, celá čísla) a je následován seznamem nepřátelských jednotek (souřadnice zapsané jako celá čísla,
 * souřadnice v hranatých závorkách, seznam je uzavřen do složených závorek). Celkem je na vstupu max. 2000000
 * nepřátelských jednotek. Výstupem programu je celkový počet nepřátelských jednotek. Program musí správně započítat
 * jednotky, které se vyskytují na více snímcích. Pokud je v průběhu načítání vstupu detekována chyba,
 * zobrazte chybové hlášení a program ukončete. Za chybu se považuje:
 *
 * neceločíselné zadání souřadnice
 * chybí nebo přebývají oddělovače (závorky, čárky)
 * Ukázka:
 *
 * Snimky:
 * [ 5, 10 ] { [ 10, -5 ], [ 10, 20 ], [ -15, 15 ] } [0,10]{} [25,15] {[-10,15],[-5,-20]}
 * Celkem jednotek: 4
 *
 * Snimky:
 * [5,5]{[ 3 , 3 ]} [5,5]{[-3,5],[3,3]}
 * Celkem jednotek: 2
 *
 * Snimky:
 * [3,7] [ 2,1]
 * Nespravny vstup.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double od_nuly[2000000];
double od_bodu[2000000];

typedef struct {
    int x, y, count, **jednotky;
}TSNIMKY;

int main() {
    int test, x, y, first = 0, alloc = 1, jednotky_alloc = 1, pruchod = 0, eof = 0, count = 0;
    char lz, carka, pz, start, end;
    TSNIMKY * tsnimky = (TSNIMKY *) malloc(alloc * sizeof(*tsnimky));

    while(1) {
        if(first == 0) {
            printf("Snimky:\n");
        }

        while (1) {
            if ((test = scanf(" %c %d %c %d %c %c", &lz, &x, &carka, &y, &pz, &start)) != 6 || lz != '[' ||
                carka != ',' || pz != ']' || start != '{') {
                if (test == EOF) {
                    if(first == 0) {
                        return 0;
                    }

                    first = 0;
                    eof = 1;
                    break;
                }

                printf("Nespravny vstup.\n");
                return 1;
            }

            if(count >= alloc) {
                alloc += 10;
                tsnimky = (TSNIMKY *) realloc(tsnimky, alloc * sizeof(*tsnimky));
            }

            tsnimky[count].x = x;
            tsnimky[count].y = y;
            tsnimky[count].count = 0;

            while (1) {
                test = scanf(" %c %d %c %d %c %c", &lz, &x, &carka, &y, &pz, &end);

                if (test != 6 || lz != '[' || carka != ',' || pz != ']' || (end != ',' && end != '}')) {
                    if(lz == '}') {
                        break;
                    }

                    printf("Nespravny vstup.\n");
                    return 1;
                }

                if(pruchod == 0) {
                    tsnimky[count].jednotky = (int **) malloc(jednotky_alloc * sizeof(*tsnimky[count].jednotky));
                } else if(pruchod >= jednotky_alloc) {
                    jednotky_alloc += 10;
                    tsnimky[count].jednotky = (int **) realloc(tsnimky[count].jednotky, jednotky_alloc * sizeof(*tsnimky[count].jednotky));
                }

                tsnimky[count].jednotky[pruchod] = (int *) malloc(2 * sizeof(*tsnimky[count].jednotky[pruchod]));
                tsnimky[count].jednotky[pruchod][0] = x;
                tsnimky[count].jednotky[pruchod][1] = y;
                tsnimky[count].count = pruchod;

                if(end == '}') {
                    break;
                }

                pruchod++;
            }

            first++;
            count++;
            pruchod = 0;
            jednotky_alloc = 1;
        }

        if(eof == 1) {
            int c = 0, counter = 0;
            eof = 0;

            for(int i = 0; i < count; i++) {
                if(tsnimky[i].count > 0) {
                    for (int j = 0; j <= tsnimky[i].count; j++) {
                        double vzdalenost_od_nuly = sqrt((tsnimky[i].jednotky[j][0])*(tsnimky[i].jednotky[j][0]) + (tsnimky[i].jednotky[j][1])*(tsnimky[i].jednotky[j][1]));
                        double vzdalenost_od_bodu = sqrt((tsnimky[i].x - tsnimky[i].jednotky[j][0])*(tsnimky[i].x - tsnimky[i].jednotky[j][0]) + (tsnimky[i].y - tsnimky[i].jednotky[j][1])*(tsnimky[i].y - tsnimky[i].jednotky[j][1]));

                        od_nuly[c] = vzdalenost_od_nuly;
                        od_bodu[c] = vzdalenost_od_bodu;
                        c++;
                    }
                }
            }

            for(int i = 0; i < c; i++) {
                for(int j = (i + 1); j < c; j++) {

                    printf("%f - %f + %f, %f\n", od_nuly[i], od_bodu[i], od_bodu[j],fabs(od_bodu[i] - od_bodu[j]) - od_nuly[i]);
                    if((fabs(od_bodu[i] - od_bodu[j]) - od_nuly[i]) >= 0.001 && (fabs(od_bodu[i] - od_bodu[j]) - od_nuly[i]) <= 0.01) {
                        counter++;
                    }
                }
            }

            printf("Celkem jednotek: %d\n", counter);

            for(int i = 0; i < count; i++) {
                if(tsnimky[i].count > 0) {
                    for (int j = 0; j <= tsnimky[i].count; j++) {
                        free(tsnimky[i].jednotky[j]);
                    }

                    free(tsnimky[i].jednotky);
                }
            }

            free(tsnimky);
        }
    }
}