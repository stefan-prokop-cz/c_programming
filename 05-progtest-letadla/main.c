/**
 * 05 - progtest - Letadla
 *
 * @author Stefan Prokop <prokoste@fit.cvut.cz>
 *
 * Spent time:
 *      26. 11. - Rozmysleni zadani, nacteni dat, ladeni - 2hod
 *      29. 11. - Realokovani pole, pridani dat do pole se stejnym indexem, naivni reseni vyhledavani shody signalu - 1hod 15min
 *      01. 12. - Programovani rekurzivni funkce (tentokrat pomoci cyklu) - 4hod 30min
 *      02. 12. - Programovani rekurzivni funkce, ladeni - 3hod
 *
 * Total spent time: 10hod 45min
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Definice pocatecnich velikosti pro inicializaci poli
 */
#define RADAR_SIZE 10
#define RADAR_MESSAGE_SIZE 50

typedef struct {
    int is_in_output;
    int index;
    int messages_count;
    long int * messages;
} TRadar;

/**
 * Funkce, ktera se stara o uvolneni pametovych bloku
 *
 * @param radars
 * @param count
 */
void clearArray(TRadar * radars, int * count) {
    for(int i = 0; i < *count; i++) {
        free(radars[i].messages);
    }
    free(radars);
}

/**
 * Funkce porovnavajici, zda zadane ID radaru jiz v poli existuje
 *
 * @param radars
 * @param count
 * @param index
 * @param position
 * @return
 */
int isIndexDefined(TRadar * radars, int * count, int * index, int * position) {
    for(int i = 1; i <= *count; i++) {
        if(*index == radars[i - 1].index) {
            *position = i;

            return 1;
        }
    }

    return 0;
}

/**
 * Rekurzivni volani starajici se o nalezeni / nenalezeni spravneho indexu, kde se dana pole shoduji a nasledne
 * vyhodnoceni, zda jsou si tato pole rovna
 *
 * @param radars
 * @param i
 * @param j
 * @param first
 * @param second
 * @param c
 * @param total_c
 * @param second_z
 * @return
 */
int compareRadars(TRadar * radars, int i, int j, int first, int second, int c, int total_c, int second_z) {

    /**
     * 1) Pokud je total count vetsi nebo roven poli, znamena to, ze jsme dosahli shody na celem poli
     * 2) Pokud je count (c) nebo zalozni druhy index pole vetsi nebo roven velikosti pole, tak jsme shody nedosahli
     *      v zadnem pruchodu
     * 3) Jinak vracime vysledek rekurzivne volame a vracime jeden z predeslych dvou pripadu
     */
    if(total_c >= radars[i].messages_count) {
        return 1;
    } else if(c >= radars[i].messages_count || second_z >= radars[i].messages_count) {
        return 0;
    } else {
        /**
         * Pokud jsem v poli zprav dosahl na urov velikosti pole, musim zacit od 0
         */
        if(second >= radars[j].messages_count) {
            second = 0;
        }

        /**
         * Pokud se zpravy rovnaji
         * - posunu index obou poli
         * - count (c) zvednu o jednicku
         * - total count zvednu take o jednicku - pro pozdejsi porovnavani
         *
         * Pokud se zpravy nerovnaji
         * - prvni pole zacnu hledat znovu od 0 indexu
         * - total count a count (c) vynuluji (zacinam od znovu)
         * - posunu si zalozni index druhe zpravy na dalsi pozici, abych nehledal porad na stejnych indexech
         */
        if(radars[i].messages[first] == radars[j].messages[second]) {
            first++;
            second++;
            c++;
            total_c++;
            return compareRadars(radars, i, j, first, second, c, total_c, second_z);
        } else {
            first = 0;
            total_c = 0;
            second_z++;
            second = second_z;
            c = 0;
            return compareRadars(radars, i, j, first, second, c, total_c, second_z);
        }
    }
}

/**
 * Funkce vyhledavajici stejne signaly
 * - dale vypisuje stejne signaly a zaverecny vypis
 *
 * @param radars
 * @param count
 */
void findSameSignals(TRadar * radars, int * count) {
    printf("Unikatni zpravy:\n");

    /**
     * Prochazim obe pole a porovnavam, zda se jejich zpravy rovnaji
     */
    for(int i = 0; i < *count; i++) {

        if(radars[i].is_in_output != 1) {
            printf("%d", radars[i].index);
        }

        for(int j = i + 1; j < *count; j++) {
            if(radars[i].messages_count == radars[j].messages_count) {
                int compare = compareRadars(radars, i, j, 0, 0, 0, 0, 0);

                if(compare == 1 && radars[j].is_in_output != 1) {
                    printf(", %d", radars[j].index);
                    radars[j].is_in_output = 1;
                }
            }
        }

        if(radars[i].is_in_output != 1) {
            printf("\n");
            radars[i].is_in_output = 1;
        }
    }
}

/**
 * Funkce radici strukturu TRadar podle velikosti prvku v poli radar.message
 * - inspirace v reseni prikladu ze cviceni - cv 10
 *
 * @param radars
 * @param count
 */
int sortRadars(const void * obj1, const void * obj2)
{
    TRadar * a = (TRadar *) obj1;
    TRadar * b = (TRadar *) obj2;

    if (a->messages_count < b->messages_count)
        return -1;
    else if (a->messages_count > b->messages_count)
        return 1;

    return 0;
}

/**
 * Funkce nacitajici uzivatelem zadana data
 *
 * @return 1|0 (1 - uspesne nacteni, 0 - chyba vstupu)
 */
int readMessage(TRadar * radars, int * count) {
    TRadar radar;

    int index, c, radar_count = *count, message_count = 0, position = 0;
    char char1, char2;

    radars = (TRadar *) malloc(RADAR_SIZE * sizeof(*radars));

    /**
     * Nacteni indexu, dvojtecky a zacatku pole ([) - nacitam, dokud neni EOF
     */
    while((c = scanf("%d %c %c", &index, &char1, &char2)) != EOF) {
        if(index < 0) {
            printf("Nespravny vstup.\n");
            clearArray(radars, &radar_count);

            return 0;
        }

        if(isIndexDefined(radars, &radar_count, &index, &position) == 0) {
            message_count = 0;
            position = 0;
            radar.messages = (long int *) malloc(RADAR_MESSAGE_SIZE * sizeof(long int));
        }

        /**
         * Pokud nenacteme pozadovane hodnoty a pocet pozadovanych hodnot -> chyba vstupu
         */
        if (c == 3) {
            if(char1 != ':' || char2 != '[') {
                printf("Nespravny vstup.\n");
                clearArray(radars, &radar_count);

                return 0;
            }

            radar.index = index;
            radar.is_in_output = 0;

            if(position > 0) {
                message_count = radars[position - 1].messages_count;
                radars[position - 1].messages = (long int *) realloc(radars[position - 1].messages, (message_count + RADAR_MESSAGE_SIZE) * sizeof(long int));
            }

            /**
             * Nacteni hodnot do pole a znaku za cislem (, / ])
             */
            while ((c = scanf("%d %c", &index, &char1)) == 2) {
                if(((message_count % RADAR_MESSAGE_SIZE) == 0) && position <= 0) {
                    radar.messages = (long int *) realloc(radar.messages, (message_count + RADAR_MESSAGE_SIZE) * sizeof(long int));
                } else if(((message_count % RADAR_MESSAGE_SIZE) == 0) && position > 0) {
                    radars[position - 1].messages = (long int *) realloc(radars[position - 1].messages, (message_count + RADAR_MESSAGE_SIZE) * sizeof(long int));
                }

                /**
                 * Kontrola vstupu na pozadovane hodnoty
                 */
                if (char1 != ',' && char1 != ']') {
                    printf("Nespravny vstup.\n");
                    clearArray(radars, &radar_count);

                    return 0;
                } else if (char1 == ']') {
                    if(position <= 0) {
                        radar.messages[message_count] = index;
                    } else {
                        radars[position - 1].messages[message_count] = index;
                    }

                    break;
                }

                if(position <= 0) {
                    radar.messages[message_count] = index;
                } else {
                    radars[position - 1].messages[message_count] = index;
                }

                message_count++;
            }

            if(position <= 0) {
                radar.messages_count = message_count + 1;
                radars[radar_count] = radar;
                radar_count++;
            } else {
                radars[position - 1].messages_count = message_count + 1;
            }

            if((radar_count % RADAR_SIZE) == 0) {
                radars = (TRadar *) realloc(radars, (radar_count + RADAR_SIZE) * sizeof(*radars));
            }

            if (c != 2) {
                printf("Nespravny vstup.\n");
                clearArray(radars, &radar_count);

                return 0;
            }
        } else {
            printf("Nespravny vstup.\n");
            clearArray(radars, &radar_count);

            return 0;
        }
    }

    if(c == EOF && char1 != ']') {
        printf("Nespravny vstup.\n");
        clearArray(radars, &radar_count);

        return 0;
    }

    *count = radar_count;

    qsort(radars, radar_count, sizeof(*radars), sortRadars);
    findSameSignals(radars, &radar_count);
    clearArray(radars, &radar_count);
    return 1;
}

int main(int argc, char * argv []) {
    TRadar * radars = (TRadar *) malloc(1 * sizeof(*radars));

    int count = 0;

    printf("Zpravy:\n");

    readMessage(radars, &count);

    free(radars);
    return 0;
}