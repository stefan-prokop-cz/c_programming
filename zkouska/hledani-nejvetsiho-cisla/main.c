/**
 * Úkolem je realizovat funkci, která dokáže nalézt největší číslo v poli. Komplikací je, že čísla jsou
 * reprezentovaná jako spojový seznam jejich cifer. Předpokládáme jednosměrné spojové seznamy. Prvek spojového
 * seznamu ukládá znak - jednu cifru zápisu čísla. Čísla jsou ukládána směrem od řádu jednotek k vyšším řádům
 * (řád jednotek je na začátku spojového seznamu). Požadovaná funkce dostane pole s odkazy na takové čísla
 * (spojové seznamy) a počet prvků v poli. Jejím výsledkem bude spojový seznam, který reprezentuje největší číslo
 * v zadaném poli.
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct TItem {
    struct TItem * m_Next;
    char           m_Digit;
} TITEM;

TITEM* createItem(char digit, TITEM * next) {
    TITEM * n = (TITEM*) malloc(sizeof(*n));
    n->m_Digit = digit;
    n->m_Next = next;
    return n;
}

void deleteList(TITEM * list) {
    while (list) {
        TITEM * tmp = list;
        list = list->m_Next;
        free(tmp);
    }
}

TITEM * maxOf(TITEM ** x, int nr) {
    int * max_numbers = (int *) malloc(nr * sizeof(int));
    int result = 0, count = 0, max, max_index;

    for(int i = 0; i < nr; i++) {
        count = 0;
        result = 0;
        TITEM * item = x[i];
        while(item) {
            int number = (int) (((int) item->m_Digit) * pow(10, count));
            result += number;
            count++;
            item = item->m_Next;
        }
        max_numbers[i] = result;
    }

    for(int i = 0; i < nr; i++) {
        if(i == 0) {
            max = max_numbers[0];
            max_index = 0;
        } else {
            if(max < max_numbers[i]) {
                max = max_numbers[i];
                max_index = i;
            }
        }
    }

    free(max_numbers);

    return x[max_index];
}

void readData(TITEM ** item, int count) {
    for(int j = 0; j < count; j++) {
        printf("%d ", j);
        TITEM * titem = item[j];
        while (titem) {
            printf("-> %d ", (int) titem->m_Digit);
            titem = titem->m_Next;
        }
        printf("\n");
    }
}

void freeData(TITEM ** item, int count) {
    for(int i = 0; i < count; i++) {
        deleteList(item[i]);
    }
    free(item);
}

int main() {

    int max = 1, count = 0, alloc = 1;
    TITEM ** item = (TITEM **) malloc(max * sizeof(TITEM));

    for(int j = 0; j < 3; j++) {
        if(max + 1 >= alloc) {
            alloc += max;
            item = (TITEM **) realloc(item, alloc * sizeof(TITEM));
        }

        switch (j) {
            case 0:
                for (int i = 1; i < 10; i++) {
                    if(i == 1) {
                        item[j] = createItem((char) i, NULL);
                    } else {
                        item[j] = createItem((char) i, item[j]);
                    }
                }
                break;
            case 1:
                for (int i = 9; i > 0; i--) {
                    if(i == 9) {
                        item[j] = createItem((char) i, NULL);
                    } else {
                        item[j] = createItem((char) i, item[j]);
                    }
                }
                break;
            case 2:
                for (int i = 2; i <= 6; i++) {
                    if(i == 2) {
                        item[j] = createItem((char) i, NULL);
                    } else {
                        item[j] = createItem((char) i, item[j]);
                    }
                }
                break;
            default:
                break;
        }

        count++;
    }

    readData(item, count);

    TITEM ** result = (TITEM **) malloc(sizeof(TITEM));
    result[0] = maxOf(item, count);
    printf("RESULT:\n");
    readData(result, 1);
    printf("-------------------------------\n");
    free(result);
    freeData(item, count);
    return 0;
}