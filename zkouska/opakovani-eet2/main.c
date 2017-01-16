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

int getValue(int index) {
    switch (index) {
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

int getIndex(int castka) {
    switch (castka) {
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

void setArrayToDefault(int * array) {
    for(int i = 0; i < MAX; i++) {
        array[i] = 0;
    }
}

int main() {
    char lz, pz;
    int cena, kasa[MAX], test, pocet, castka, help_kasa[MAX], mezivysledek = 0, spropitne = 0;

    setArrayToDefault(kasa);
    setArrayToDefault(help_kasa);

    while(1) {
        if ((test = scanf("%d %c", &cena, &lz)) != 2 || cena <= 0 || lz != '[') {
            if(test == EOF) {
                break;
            }

            printf("Nespravny vstup.\n");
            return 1;
        }

        while (1) {
            test = scanf("%d x %d Kc %c", &pocet, &castka, &pz);

            if (test != 3 || pocet <= 0 || castka <= 0 || (pz != ',' && pz != ']')) {
                printf("Nespravny vstup.\n");
                return 1;
            }

            int index = getIndex(castka);

            if (index != -1) {
                help_kasa[index] = pocet;
                mezivysledek += (pocet * castka);
            } else {
                printf("Nespravny vstup.\n");
                return 1;
            }

            if (pz == ']') {
                break;
            }
        }

        if(cena > mezivysledek) {
            printf("Nedostatecna hotovost.\n");
        } else {
            int is_first = 1;
            printf("Kasa: [");
            for(int i = 0; i < MAX; i++) {
                kasa[i] += help_kasa[i];

                if(kasa[i] > 0) {
                    if (is_first) {
                        is_first = 0;
                        printf(" %dx%d Kc", kasa[i], getValue(i));
                    } else {
                        printf(", %dx%d Kc", kasa[i], getValue(i));
                    }
                }
            }
            printf(" ]\n");

            spropitne += (mezivysledek - cena);
            printf("Spropitne: %d\n", spropitne);
        }

        mezivysledek = 0;
        setArrayToDefault(help_kasa);
    }

    return 0;
}