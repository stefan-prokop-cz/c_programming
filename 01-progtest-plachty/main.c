/**
 * 01 - progtest - Plachty
 *
 * @author Stefan Prokop <prokoste@fit.cvut.cz>
 *
 * Spent time:
 *      29. 10. - Navrh, priprava dokumentu - 20min
 *      30. 10. - Rozmysleni zadani, programovani - 4hod 45min
 *      31. 10. - Programovani funkce pro vypocet plachet - 2hod
 *      31. 10. - Ladeni vstupnich a vystupnich hodnot - 3hod
 *      31. 10. - Doladeni zaveru - 45min
 *
 * Total spent time: 10hod 50min
 */

#include <stdio.h>
#include <math.h>

#define EPSILON 0.00000001

/**
 * Funkce vracejici pocet kusu latky, ktere je treba pouzit pro vyplneni plachty
 * Parametry x, y symbolizuji vysku a sirku latky
 *
 * @param fabric_width
 * @param fabric_height
 * @param overlap
 * @param sail_width
 * @param sail_height
 * @return int
 */
long int getFabricCount(double fabric_width, double fabric_height, double overlap, double sail_width, double sail_height) {
    double fabric_sum = 0, sail_sum = sail_height * sail_width, fabric_count_width = 0, fabric_count_height = 0;
    long int fabric_count = 0;
    int is_first_row = 1, is_first_fabric = 1;

    /**
     * Pojedu dokud neni obsah latek vetsi nebo roven obsahu plachty
     */
    while(fabs(fabric_sum - sail_sum) > EPSILON) {

        /**
         * Pokud jsem prvni latka, pak nactu vychozi hodnoty, oznacim prvni radek a pripoctu pouzitou latku
         * Pokud nejsem prvni latka
         *      - zkoumam, zda jsem v prvnim radku, pokud ano odecitam pouze preryv latek
         *      - pokud nejsem v prvnim radku
         *          + zkoumam, zda jsem prvni latka v dalsim sloupci, pokud ano, odectu prekryv od vysky,
         *              sirku nastavim znovu na pocatecni hodnotu
         *          + pokud nejsem prvni latka v rade, tak pricitam sirku a od te odectu prekryv
         */
        if(fabric_count == 0) {
            fabric_count_width += fabric_width;
            fabric_count_height += fabric_height;
            is_first_fabric = 0;
            is_first_row = 1;
            fabric_count++;
        } else {
            if(is_first_row == 1) {
                fabric_count_width += fabric_width - overlap;
                fabric_count++;
            } else {
                if(is_first_fabric == 1) {
                    fabric_count_height += fabric_height - overlap;
                    fabric_count_width = fabric_width;
                    is_first_fabric = 0;
                    fabric_count++;
                } else {
                    fabric_count_width += fabric_width - overlap;
                    fabric_count++;
                }
            }
        }

        /**
         * Pokud je sirka spojene latky vetsi nez sirka plachty, odectu prebyvajici latku a nastavim novy radek
         */
        if(fabric_count_width >= sail_width) {
            fabric_count_width -= (fabric_count_width - sail_width);
            is_first_row = 0;
            is_first_fabric = 1;
        }

        /**
         * Pokud je vyska spojene latky vetsi nez vyska plachty, odectu prebyvajici latku od plachty
         */
        if(fabric_count_height >= sail_height) {
            fabric_count_height -= (fabric_count_height - sail_height);
        }

        fabric_sum = fabric_count_height * fabric_count_width;
    }

    return fabric_count;
}

int main(int argc, char * argv []) {
    double fabric_width, fabric_height, sail_width, sail_height, overlap, fabric_sum, sail_sum;

    /**
     * Nacteni hodnot latky - porovnani, zda je > 0
     */
    printf("Velikost latky:\n");

    if(scanf("%lf%lf", &fabric_width, &fabric_height) == 2 && fabric_width > 0 && fabric_height > 0) {

        /**
         * Nacteni hodnot plachty - porovnani, zda je > 0
         */
        printf("Velikost plachty:\n");

        if(scanf("%lf%lf", &sail_width, &sail_height) == 2 && sail_width > 0 && sail_height > 0) {

            fabric_sum = fabric_height * fabric_width;
            sail_sum = sail_height * sail_width;

            if(fabric_sum >= sail_sum) {
                printf("Pocet kusu latky: %d\n", 1);

                return 0;
            }

            /**
             * Nacteni velikosti prekryvu - porovnani, zda je >= 0
             */
            printf("Prekryv:\n");

            if(scanf("%lf", &overlap) == 1 && overlap >= 0) {

                long int first_count = -1, second_count = -1;
                int is_out = 0;

                /**
                 * Otestuji velikost prekryvu a zadane sirky a vysky latky
                 */
                if(fabric_width > overlap) {
                    first_count = getFabricCount(fabric_width, fabric_height, overlap, sail_width, sail_height);
                } else {
                    is_out++;
                }

                if(fabric_height > overlap) {
                    second_count = getFabricCount(fabric_height, fabric_width, overlap, sail_width, sail_height);
                } else {
                    is_out++;
                }

                /**
                 * Pokud je prekryv vyssi u kazde z uvedenych velikost, pak takova plachta nelze vyrobit
                 */
                if(is_out >= 2) {
                    printf("Nelze vyrobit.\n");

                    return 1;
                }

                if(first_count != -1 && second_count != -1) {

                    /**
                     * Zobrazim nejlepsi moznou variantu
                     */
                    if(first_count >= second_count) {
                        printf("Pocet kusu latky: %ld\n", second_count);
                    } else {
                        printf("Pocet kusu latky: %ld\n", first_count);
                    }
                } else if(first_count == -1) {
                    printf("Pocet kusu latky: %ld\n", second_count);
                } else if(second_count == -1) {
                    printf("Pocet kusu latky: %ld\n", first_count);
                }

            } else {
                printf("Nespravny vstup.\n");

                return 1;
            }
        } else {
            printf("Nespravny vstup.\n");

            return 1;
        }
    } else {
        printf("Nespravny vstup.\n");

        return 1;
    }

    return 0;
}
