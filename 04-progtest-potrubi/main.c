/**
 * 04 - progtest - Potrubi
 *
 * @author Stefan Prokop <prokoste@fit.cvut.cz>
 *
 * Spent time:
 *      22. 11. - rozmysleni ulohy - 30min
 *      22. 11. - programovani ulohy - 1hod
 *      22. 11. - testovani, ladeni aplikace - 30min
 *
 * Total spent time: 2hod
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 2000

/**
 * Funkce pocitajici mozne kombinace slozeni potrubi
 *
 * @param pipes
 * @param n
 * @param pipe
 * @return
 */
int findPipes(int * pipes, int n, int pipe) {
    int count = 0, result = 0;

    /**
     * V cyklu porovname zda se hledana hodnota rovna jiz hodnote v poli nebo dale zanorujeme na druhy a treti level
     * - dale pri kazdem spravnem porovnani inkrementujeme celkovy vysledek (count)
     */
    for(int i = 0; i < n; i++) {
        result = pipes[i];

        if(result > pipe) {
            break;
        } else if(result == pipe) {
            printf("%d = %d\n", pipe, pipes[i]);
            count++;
        }

        for(int j = i; j < n; j++) {
            result = pipes[i] + pipes[j];

            if(result > pipe) {
                break;
            } else if(result == pipe) {
                printf("%d = %d + %d\n", pipe, pipes[i], pipes[j]);
                count++;
            }

            for(int k = j; k < n; k++) {
                result = pipes[i] + pipes[j] + pipes[k];

                if(pipe == result) {
                    printf("%d = %d + %d + %d\n", pipe, pipes[i], pipes[j], pipes[k]);
                    count++;
                } else if(result > pipe) {
                    break;
                }
            }
        }
    }

    return count;
}

/**
 * Porovnavaci funkce pro qsort
 * - viz. priklady ze 7. cviceni nebo 6. proseminar
 *
 * @param a
 * @param b
 * @return
 */
int compare(const void * a, const void * b) {

    return (*(int *) a) - (*(int *) b);
}

/**
 * Funkce volajici qsort pro serazeni pole cisel
 *
 * @param array
 * @param n
 */
void sortArray(int * array, int n) {
    qsort(array, n, sizeof(*array), compare);
}

/**
 * Funkce porovnavajici, zda se zadany prvek jiz v poli nachazi
 *
 * @param array
 * @param n
 * @param needle
 * @return
 */
int isInArray(int * array, int n, int needle) {
    for (int i = 0; i < n; i++) {
        if(needle == array[i]) {

            return 1;
        }
    }

    return 0;
}

int main(int argc, char * argv []) {

    int index = 0, pipe, scanf_result;
    int pipes[MAX_SIZE];

    printf("Delky trubek:\n");

    /**
     * Nacteni dat - potrubi
     */
    while ((scanf_result = scanf("%d", &pipe))) {
        /**
         * Pokud nacteme 0 vyskocime z nacitani potrubi
         */
        if(pipe == 0) {
            break;
        }

        /**
         * Osetreni neplatnych vstupu
         */
        if(index > MAX_SIZE || pipe < 0 || isInArray(pipes, index, pipe)) {
            printf("Nespravny vstup.\n");

            return 1;
        }

        /**
         * Ulozeni nactenych dat do pole
         */
        pipes[index] = pipe;
        index++;
    }

    /**
     * Seradime pole od nejmensich prvku po nejvetsi
     */
    sortArray(pipes, index);

    /**
     * Zkontrolujeme, s jakym statusem skoncilo predchozi nacitani - validace
     */
    if(scanf_result != 1 || index == 0) {
        printf("Nespravny vstup.\n");

        return 1;
    }

    printf("Potrubi:\n");

    /**
     * Nacitani dat - vyhledavani potrubi
     */
    while(scanf("%d", &pipe) == 1) {
        /**
         * Validace dat
         */
        if(pipe <= 0) {
            printf("Nespravny vstup.\n");

            return 1;
        }

        /**
         * Konecny vypis nalezenych kombinaci
         */
        printf("Celkem: %d\n", findPipes(pipes, index, pipe));
    }

    /**
     * Osetreni zadani konce vstupu
     */
    if(!feof(stdin)) {
        printf("Nespravny vstup.\n");

        return 1;
    }

    return 0;
}