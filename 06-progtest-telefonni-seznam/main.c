/**
 * 06 - progtest - Telefonni seznam
 *
 * @author Stefan Prokop <prokoste@fit.cvut.cz>
 *
 * Spent time:
 *      03. 12. - Rozmysleni ulohy, programovani nacitani vstupu a validace - 2hod
 *      03. 12. - Programovani ukladani nactenych dat - 1hod 30min
 *      03. 12. - Programovani nacitani dat / vyhledavani - 2hod
 *      04. 12. - Dokonceni praci, testovani, dokonceni nacitani, validace vyuziti pameti (valgrind) - 6hod
 *
 * Total spent time: 11hod 30min
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define LIST_SIZE 20
#define NAME_SIZE 30

/**
 * Struktura uzivatel definujici:
 * - zda byl dany uzivatel jiz vypsan na vystup
 * - jmeno uzivatele
 * - jmeno uzivatele v T9 zapisu
 * - cislo, na ktere zacina uzivatelovo jmeno v T9 formatu / tel. cislo
 * - telefonni cislo
 * - pocet znaku v tel. cisle a jmene
 */
typedef struct {
    int is_in_output;
    int name_characters;
    int phone_characters;
    char * name;
    char * name_T9;
    char start_name_T9;
    char phone_number[21];
    char start_phone_number;
} TUser;

/**
 * Funkce validujici uzivatesky vstup - pokud chce vyhledavat v adresari
 *
 * @param buffer
 * @return
 */
int validateSearching(char * buffer) {
    int buffer_count = 0;

    /**
     * Pokud prvni znaky nejsou otaznik a mezera = neplatne
     */
    if(buffer[0] != '?' || buffer[1] != ' ') {

        return 0;
    }

    /**
     * Pokud uzivatel zadal vice nez 20ti mistne cislo nebo zadana data nejsou v intervalu
     * '0' - '9' = neplatne
     */
    buffer_count = 2;
    while(buffer[buffer_count] != '\n') {
        if(buffer[buffer_count] < '0' || buffer[buffer_count] > '9') {

            return 0;
        }

        buffer_count++;
    }

    return 1;
}

/**
 * Funkce cistici pole struktur a jednotlive alokovane bloky
 *
 * @param users
 * @param count
 */
void clearMainArrays(TUser * users, int count) {
    for(int i = 0; i < count; i++) {
        free(users[i].name_T9);
        free(users[i].name);
    }

    free(users);
}

/**
 * Funkce prevadejici dany znak do T9 formatu
 *
 * @param character
 * @return
 */
char translateIntoT9(char character) {
    character = tolower(character);

    switch(character) {
        case ' ':
            return '1';
        case 'a':
        case 'b':
        case 'c':
            return '2';
        case 'd':
        case 'e':
        case 'f':
            return '3';
        case 'g':
        case 'h':
        case 'i':
            return '4';
        case 'j':
        case 'k':
        case 'l':
            return '5';
        case 'm':
        case 'n':
        case 'o':
            return '6';
        case 'p':
        case 'q':
        case 'r':
        case 's':
            return '7';
        case 't':
        case 'u':
        case 'v':
            return '8';
        case 'w':
        case 'x':
        case 'y':
        case 'z':
            return '9';
        default:
            return '\0';
    }
}

/**
 * Funkce validujici uzivatesky vstup - pokud chce zadat udaje do adresare
 *
 * @param buffer
 * @return
 */
int validateCreating(char * buffer) {
    int buffer_count = 0, numbers = 1;

    /**
     * Pokud prvni znaky nejsou plus a mezera = neplatne
     */
    if(buffer[0] != '+' || buffer[1] != ' ') {

        return 0;
    }

    /**
     * Pokud uzivatel v prvni casti zadal neco jineho nez cislo nebo ve druhe casti
     * zadal neco jineho nez mala / velka pismena = neplatne
     */
    buffer_count = 2;
    while(buffer[buffer_count] != '\n') {

        if(buffer[buffer_count] == ' ') {
            numbers = 0;
            buffer_count++;
        }

        if(numbers == 1) {
            if (buffer_count > 21 || (buffer[buffer_count] < '0' || buffer[buffer_count] > '9')) {

                return 0;
            }
        } else {
            if (buffer[buffer_count] < 'A' || (buffer[buffer_count] > 'Z' && buffer[buffer_count] < 'a') ||
                buffer[buffer_count] > 'z') {

                return 0;
            }
        }

        buffer_count++;
    }

    if(numbers == 1) {

        return 0;
    }

    return 1;
}

/**
 * Funkce overujici, zda se zadany text shoduje s T9 jmenem uzivatele
 *
 * @param user
 * @param search_term
 * @return
 */
int findByUser(TUser user, char * search_term) {
    int count = 0, search_count = 2;

    while(search_term[search_count] != '\n') {
        if(count >= user.name_characters) {

            return 0;
        }

        if(user.name_T9[count] != search_term[search_count]) {

            return 0;
        }

        count++;
        search_count++;
    }

    return 1;
}

/**
 * Funkce overujici, zda se zadany text shoduje s telefonnim cislem
 *
 * @param phone
 * @param search_term
 * @return
 */
int findByPhone(TUser user, char * search_term) {
    int count = 0, search_count = 2;

    while(search_term[search_count] != '\n') {
        if(count >= user.phone_characters) {

            return 0;
        }

        if(user.phone_number[count] != search_term[search_count]) {

            return 0;
        }

        count++;
        search_count++;
    }

    return 1;
}

/**
 * Funkce vracejici hodnotu, zda se dany uzivatel v seznamu jiz nachazi / nenachazi
 *
 * @param users
 * @param phone
 * @param username
 * @param phone_c
 * @param user_c
 * @param list_count
 * @return
 */
int contactExists(TUser * users, char * phone, char * username, int phone_c, int user_c, int list_count) {
    int phone_count = 0, user_count = 0;

    /**
     * Pokud jsme prvni zaznam
     */
    if(list_count == 0) {

        return 0;
    }

    for(int i = 0; i < list_count; i++) {
        phone_count = 0;
        user_count = 0;

        /**
         * Pokud se shoduji delka tel. cisla a delka jmena
         * - porovname uplnou shodu znaku (jmeno a tel. cislo)
         */
        if(users[i].phone_characters == phone_c) {
            if(users[i].name_characters == user_c) {
                for(int j = 0; j < users[i].phone_characters; j++) {
                    if(users[i].phone_number[j] == phone[j]) {
                        phone_count++;
                    }
                }

                for(int j = 0; j < users[i].name_characters; j++) {
                    if(users[i].name[j] == username[j]) {
                        user_count++;
                    }
                }
            }
        }

        /**
         * Pokud je shoda uplna vratime hodnotu 1
         */
        if(user_count == users[i].name_characters && phone_count == users[i].phone_characters) {

            return 1;
        }
    }

    return 0;
}

/**
 * Funkce starajici se o ulozeni dat do seznamu kontaktu
 *
 * @param users
 * @param phones
 * @param buffer
 * @param list_count
 */
void insertData(TUser * users, char * buffer, int * list_count) {
    int buffer_count = 2, character_phone_count = 0, l_count = *list_count, character_user_count = 0;
    users[l_count].name = (char *) malloc(NAME_SIZE * sizeof(*users[l_count].name));
    users[l_count].name_T9 = (char *) malloc(NAME_SIZE * sizeof(*users[l_count].name_T9));

    /**
     * Dokud nenarazim na mezeru, jedna se o cislo
     */
    while (buffer[buffer_count] != ' ') {
        users[l_count].phone_number[character_phone_count] = buffer[buffer_count];
        character_phone_count++;
        buffer_count++;
    }

    buffer_count++;
    users[l_count].start_name_T9 = translateIntoT9(buffer[buffer_count]);

    /**
     * Dokud nenarazim na novy radek, jedna se o jmeno
     */
    while (buffer[buffer_count] != '\n') {
        if(character_user_count % NAME_SIZE == 0) {
            users[l_count].name = (char *) realloc(users[l_count].name, (character_user_count + NAME_SIZE) * sizeof(*users[l_count].name));
            users[l_count].name_T9 = (char *) realloc(users[l_count].name_T9, (character_user_count + NAME_SIZE) * sizeof(*users[l_count].name_T9));
        }

        users[l_count].name[character_user_count] = buffer[buffer_count];
        users[l_count].name_T9[character_user_count] = translateIntoT9(buffer[buffer_count]);
        character_user_count++;
        buffer_count++;
    }

    /**
     * Ulozime uzivatele do pole
     */
    users[l_count].is_in_output = 0;
    users[l_count].name_characters = character_user_count;
    users[l_count].start_phone_number = buffer[2];
    users[l_count].phone_characters = character_phone_count;

    /**
     * Pokud uzivatel jiz existuje, smazeme dany zadnam
     */
    if(contactExists(users, users[l_count].phone_number, users[l_count].name, character_phone_count, character_user_count, l_count) == 1) {
        free(users[l_count].name);
        free(users[l_count].name_T9);
        printf("Kontakt jiz existuje.\n");
    } else {
        printf("OK\n");
        l_count++;
    }

    *list_count = l_count;
}

/**
 * Funkce vyhledavajici kontakt
 * - zobrazuje na vystup vyhledane kontakty
 *
 * @param users
 * @param list_count
 * @param search_term
 */
void findContacts(TUser * users, int * list_count, char * search_term) {
    int count = 0, l_count = *list_count, i;
    char first_search_letter = search_term[2];

    /**
     * Hledame podle jmena uzivatele
     */
    for(i = 0; i < l_count; i++) {
        users[i].is_in_output = 0;

        if(first_search_letter == users[i].start_name_T9) {
            if(findByUser(users[i], search_term) == 1) {
                users[i].is_in_output = 1;
                count++;
            }
        }
    }

    /**
     * Hledame podle uzivatelova tel. cisla
     */
    for(i = 0; i < l_count; i++) {
        if(first_search_letter == users[i].start_phone_number) {
            if(findByPhone(users[i], search_term) == 1) {
                if(users[i].is_in_output != 1) {
                    users[i].is_in_output = 1;
                    count++;
                }
            }
        }
    }

    /**
     * Vysledne shody zobrazime v pozadovanem formatu na vystup
     */
    if(count > 10) {
        printf("Celkem: %d\n", count);
    } else {
        for(i = 0; i < l_count; i++) {
            if(users[i].is_in_output == 1) {
                for(int j = 0; j < users[i].phone_characters; j++) {
                    printf("%c", users[i].phone_number[j]);
                }
                printf(" ");
                for(int j = 0; j < users[i].name_characters; j++) {
                    printf("%c", users[i].name[j]);
                }
                printf("\n");
            }
        }
        printf("Celkem: %d\n", count);
    }
}

/**
 * Funkce nacitajici uzivatelsky vstup
 * - vola validacni funkce a funkce starajici se o zapis / vypis pozadovanych dat
 */
void readInput() {	// getline zmenit
    TUser * users;
    char * buffer;
    int list_count = 0, buffer_size = 0;
    users = (TUser *) malloc(LIST_SIZE * sizeof(*users));

    /**
     * Nacitam dokud je neco na vstupu
     * 1) validacni funkce overi, zda je zadany vstup validni
     * 2) zavola se funkce, ktera ulozi / vyhleda data
     * - pokud validace selze, vypise se chybove hlaseni
     */
    while(getline(buffer, buffer_size, stdin) != NULL) {
        if(buffer[0] == '+') {
            if(validateCreating(buffer) == 1) {
                if(list_count % LIST_SIZE == 0) {
                    users = (TUser *) realloc(users, (list_count + LIST_SIZE) * sizeof(*users));
                }

                insertData(users, buffer, &list_count);
            } else {
                printf("Nespravny vstup.\n");
            }
        } else if(buffer[0] == '?') {
            if(validateSearching(buffer) == 1) {
                findContacts(users, &list_count, buffer);
            } else {
                printf("Nespravny vstup.\n");
            }
        } else {
            printf("Nespravny vstup.\n");
        }

        free(buffer);
        buffer_size = 0;
    }

    if(!feof(stdin)) {
        printf("Nespravny vstup.\n");
    }

    clearMainArrays(users, list_count);
}

int main(int argc, char * argv []) {
    readInput();
    return 0;
}
