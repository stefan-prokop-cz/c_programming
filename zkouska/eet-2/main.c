/**
 * Úkolem je vytvořit program pokladny pro elektronickou evidenci tržeb. Na vstupu je nejdříve zadána částka k
 * zaplacení a pak následuje počet bankovek a jejich nominální hodnota. Pokud přijatá částka převyšuje hodnotu nákupu,
 * jejich rozdíl je započítán jako spropitné. Po každém platném vstupu se píše aktulní počet bankovek každé hodnoty,
 * které jsou aktuálně v pokladně obsaženy a výše spropitného. Bankovky se vypisují sestupně podle jejich nominální
 * hodnoty (5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5, 2, 1). Pokud je celková přijatá částka nižší než
 * požadovaná, program to oznámí, přijaté bankovky nezapočítá a pokračuje.
 *
 * 185 [ 1x100 Kc, 4x20 Kc, 1x5 Kc ]
 * Kasa: [ 1x100 Kc, 4x20 Kc, 1x5 Kc ]
 * Spropitné: 0
 * 100 [ 1x100 Kc, 1x1 Kc ]
 * Kasa: [ 2x100 Kc, 4x20 Kc, 1x5 Kc, 1x1 Kc ]
 * Spropitné: 1
 * 1000 [ 1x500 Kc ]
 * Nedostatecna hotovost.
 * 6 [ 1x5000 Kc, 1x1 Kc, 1x1 Kc, 1x1 Kc, 1x1 Kc, 1x1 Kc, 1x1 Kc ]
 * Kasa: [ 1x5000 Kc, 2x100 Kc, 4x20 Kc, 1x5 Kc, 7x1 Kc ]
 * Spropitné: 5001
 */

#include <stdio.h>

#define MAX 12

int validateNumber(int bankovka) {
    switch(bankovka) {
        case 5000:
            return 1;
        case 2000:
            return 1;
        case 1000:
            return 1;
        case 500:
            return 1;
        case 200:
            return 1;
        case 100:
            return 1;
        case 50:
            return 1;
        case 20:
            return 1;
        case 10:
            return 1;
        case 5:
            return 1;
        case 2:
            return 1;
        case 1:
            return 1;
        default:
            return 0;
    }
}

int getIndex(int bankovka) {
    switch(bankovka) {
        case 5000:
            return 0;
        case 2000:
            return 1;
        case 1000:
            return 2;
        case 500:
            return 3;
        case 200:
            return 4;
        case 100:
            return 5;
        case 50:
            return 6;
        case 20:
            return 7;
        case 10:
            return 8;
        case 5:
            return 9;
        case 2:
            return 10;
        case 1:
            return 11;
        default:
            return -1;
    }
}

int getValue(int index) {
    switch(index) {
        case 0:
            return 5000;
        case 1:
            return 2000;
        case 2:
            return 1000;
        case 3:
            return 500;
        case 4:
            return 200;
        case 5:
            return 100;
        case 6:
            return 50;
        case 7:
            return 20;
        case 8:
            return 10;
        case 9:
            return 5;
        case 10:
            return 2;
        case 11:
            return 1;
        default:
            return -1;
    }
}

int main() {
    int price, test, count, bankovka, kasa[MAX], help_kasa[MAX], mezivysledek = 0, close = 0, spropitne = 0;
    char lz, carka;

    for(int i = 0; i < MAX; i++) {
        kasa[i] = 0;
        help_kasa[i] = 0;
    }

    while(1) {
        if(!close) {
            if ((test = scanf("%d %c", &price, &lz)) != 2 || price <= 0 || lz != '[') {
                if (test == EOF) {
                    return 0;
                }

                printf("Nespravny vstup.\n");
                return 1;
            }

            while (1) {
                test = scanf("%d x %d Kc %c", &count, &bankovka, &carka);

                if (test != 3 || (carka != ',' && carka != ']')) {
                    printf("Nespravny vstup.\n");
                    return 1;
                }

                if (validateNumber(bankovka)) {
                    mezivysledek += (count * bankovka);
                    help_kasa[getIndex(bankovka)] += count;
                } else {
                    printf("Nespravny vstup.\n");
                    return 1;
                }

                if (carka == ']') {
                    close = 1;
                    break;
                }
            }
        } else {
            close = 0;

            if(mezivysledek >= price) {
                int counter = 0;
                printf("Kasa: [");
                for(int i = 0; i < MAX; i++) {
                    kasa[i] += help_kasa[i];
                    if(kasa[i] > 0) {
                        if(counter == 0) {
                            printf(" %dx%d Kc", kasa[i], getValue(i));
                        } else {
                            printf(", %dx%d Kc", kasa[i], getValue(i));
                        }

                        counter++;
                    }
                }
                printf(" ]\n");

                if(mezivysledek == price) {
                    printf("Spropitne: 0\n");
                } else {
                    spropitne += (mezivysledek - price);
                    printf("Spropitne: %d\n", spropitne);
                }
            } else {
                printf("Nedostatecna hotovost.\n");
            }

            mezivysledek = 0;
            for(int i = 0; i < MAX; i++) {
                help_kasa[i] = 0;
            }
        }
    }
}