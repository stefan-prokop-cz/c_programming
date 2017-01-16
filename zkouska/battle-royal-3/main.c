/**
 * Nejdříve zadány souřadnice radarů a jejich rozsah ve formátu: { [ 1 , 2] @ 3 , [4,5]@6}.
 * Mohlo jich být až 2000000. Čísla byla desetinná. Mně na to stačil float. Následně byly zadány souřadnice seskoku
 * ve formátu [1,2]. Program měl spočítat, kolika radarům se podařilo seskok zaznamenat.
 * Zde je důležité poznamenat, že porovnávání desetinných čísel je cvičícími doporučené dělat tak, že se jeden od
 * druhého odečte a porovná se to s odchylkou. Já jí měl 1e-3. Náhodná data 100%, mezní hodnoty na 75%.
 * Program končil zadáním EOF místo souřadnic seskoku.
 *
 * Chyby:
 * špatná nebo chybějící závorka
 * nečíselný vstup u čísel
 * rozsah radaru <= 0
 * nebyl zadán žádný radar
 */

#include <stdio.h>
#include <math.h>

#define MAX 2000000
double souradnice[MAX][3];

int main() {

    double x, y, radar, a, b;
    char character, pz, lz, carka, end, zavinac;
    int test, count = 0;

    printf("Souradnice:\n");
    if(scanf(" %c", &character) != 1 || character != '{') {
        printf("Nespravny vstup.\n");
        return 1;
    }

    while((test = scanf(" %c %lf %c %lf %c %c %lf %c", &pz, &x, &carka, &y, &lz, &zavinac, &radar, &end)) == 8) {
        if(pz != '[' || carka != ',' || lz != ']' || zavinac != '@' || (end != ',' && end != '}') || (count + 1) > MAX) {
            printf("Nespravny vstup.\n");
            return 1;
        }

        souradnice[count][0] = x;
        souradnice[count][1] = y;
        souradnice[count][2] = radar;
        count++;

        if(end == '}') {
            break;
        }
    }

    if(test != 8) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Seskok:\n");
    while(1) {
        test = scanf(" %c %lf %c %lf %c", &pz, &a, &carka, &b, &lz);

        if(test == EOF) {
            break;
        }

        int c = 0;
        printf("Zaznamenal radar:\n");
        for(int i = 0; i < count; i++) {
            double vzdalenost = sqrt((a-souradnice[i][0])*(a-souradnice[i][0]) + (b-souradnice[i][1])*(b-souradnice[i][1]));

            if((vzdalenost - souradnice[i][2]) <= 0.00001) {
                printf("[%f, %f] @ %f\n", souradnice[i][0], souradnice[i][1], souradnice[i][2]);
                c++;
            }
        }

        if(c == 0) {
            printf("Zadny.\n");
        }

        if(test != 5 || pz != '[' || lz != ']' || carka != ',') {
            printf("Nespravny vstup.\n");
            return 1;
        }
    }

    return 0;
}