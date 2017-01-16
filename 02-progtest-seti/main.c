/**
 * 02 - progtest - SETI
 *
 * @author Stefan Prokop <prokoste@fit.cvut.cz>
 *
 * Spent time:
 *      06.11. - Rozmysleni reseni, algoritmus reseni jedne rovnice o dvou neznamych - 8hod
 *      07.11. - Reseni jedne rovnice o dvou neznamych - 6hod
 *      08.11. - Programovani zakladniho reseni - 3hod
 *
 * Total spent time: 17hod
 */

#include <stdio.h>
#include <math.h>

/**
 * Funkce vracejici cislo odpovidajici zadanemu znaku
 * - pomoci znaku tak, jak jsou ulozeny v ASCII tabulce (za sebou) mame moznost vyjadrit
 * ciselne jejich hodnotu - v tomto pripade 2^n, kde n odpovida cislu zadanemu znaku
 * - viz 5. proseminar - prevody mezi soustavami
 *
 * @param signal
 * @return int
 */
long long int getNumberFromCharacter(char * signal) {

    if(*signal >= 'a' && *signal <= 'z') {

        return pow(2, *signal - 'a');
    }

    return -1;
}

/**
 * Funkce vytvarejici a vypocitavajici rovnici
 * - ze zadani je mozne vykoukat rovnici ve tvaru (2*prefix + zacatek_zpravy) * celk_velikost_zpravy * x, tato
 * rovnice se musi dat do pomeru s druhou rovnici, ktera bude ve stejnem tvaru
 * - v nasem pripade hledame promenne x a y, ktere pozdeji dosadime do vyse zminene rovnice a dostaneme tak pozadovany
 * vysledek
 *
 * @param remain_first
 * @param start_message_first
 * @param remain_second
 * @param start_message_second
 * @return
 */
long long int createEquation(long long int * remain_first, long long int * start_message_first, long long int * remain_second,
    long long int * start_message_second) {

    long long int i, a, b, c, eq_first, eq_second, x = 0;
    a = (*remain_first) + (*start_message_first);
    c = (2 * (*remain_first) + (*start_message_first)) - (2 * (*remain_second) + (*start_message_second));
    b = (*remain_second) + (*start_message_second);

    /**
     * Reseni rovnice spociva v dosazovani vhodnych cisel v intervalu od 0 do delitele teto rovnice (z vyjadrene
     * promenne)
     * - pokud nalezneme takove x, jez je po dosazeni do rovnice beze zbytku tato rovnice delitelna danym delitelem,
     * pak mame reseni pro promennou, dosadime a vypocteme druhou promennou, pak dosadime znovu na zacatek a vypocteme
     * puvodni rovnice, jde o rovnici, takze vysledky porovname a odesleme dobu synchronizace
     * - v pripade, ze se v pruchodu cyklem nevyskytne cislo, ktere je delitelne, pak rovnice nema reseni a zpravy tak
     * nelze sesynchronizovat
     */
    for(i = 0; i < (((*start_message_second) + (*remain_second))); i++) {
        x = i;
        long long int y = ((a * x) + c);

        if((y % b) == 0) {
            x = i;
            y = y / b;

            eq_first = (2 * (*remain_first) + (*start_message_first)) + (((*remain_first) + (*start_message_first)) * x);
            eq_second = (2 * (*remain_second) + (*start_message_second)) + (((*remain_second) + (*start_message_second)) * y);

            if(eq_first == eq_second) {

                return eq_first;
            } else {

                return -1;
            }
        }
    }

    return -1;
}

long long int createEquation3(long long int * remain_first, long long int * start_message_first, long long int * remain_second,
                             long long int * start_message_second, long long int * remain_third, long long int * start_message_third) {

    long long int i, j, a, b, c, d, eq_first, eq_second, eq_third, x = 0, z = 0;
    a = (*remain_first) + (*start_message_first);
    d = (2 * (*remain_first) + (*start_message_first)) - (2 * (*remain_second) + (*start_message_second)) - (2 * (*remain_third) + (*start_message_third));
    b = (*remain_second) + (*start_message_second);
    c = (*remain_third) + (*start_message_third);

    for(i = 0; i <= (((*start_message_second) + (*remain_second))); i++) {
        x = i;
        for(j = 0; j <= (((*start_message_second) + (*remain_second))); j++) {
            z = j;
            long long int y = ((a * x) - (c * z) + d);
            printf("x = %d\n", x);
            printf("y = %d\n", z);

            if ((y % b) == 0) {
                y = y / b;

                eq_first = (2 * (*remain_first) + (*start_message_first)) +
                           (((*remain_first) + (*start_message_first)) * x);
                eq_second = (2 * (*remain_second) + (*start_message_second)) +
                            (((*remain_second) + (*start_message_second)) * y);
                eq_third = (2 * (*remain_third) + (*start_message_third)) +
                            (((*remain_third) + (*start_message_third)) * z);

                if (eq_first == eq_second && eq_second == eq_third) {

                    return eq_first;
                }
            }
        }
    }

    return -1;
}

int main(int argc, char * argv []) {

    long long int remain_first = 0, remain_second = 0, start_message_first = 0, start_message_second = 0,
            remain_third = 0, start_message_third = 0;

    long long int synchronization = 0;
    char signal;
    int separator = 0, new_message = 0, count = 0;

    printf("Zpravy:\n");

    /**
     * Nacitame uzivatelsky vstup dokud neni signalizovan EOF
     */
    while(scanf("%c", &signal) != EOF) {

        /**
         * Pokud je zadany znak jiny nez ten, ktery uznavame, jedna se o nespravny vstup
         */
        if(signal == ' ' || (signal == '\n' && separator == 0)) {
            printf("Nespravny vstup.\n");

            return 1;
        }

        /**
         * - signalizace pro separator - oddeleni prefixu a zacatku zpravy
         * - signalizace nove radky pro uvedomeni si, ze zaciname dalsi rovnici
         */
        if(signal == '|') {
            separator++;
        }

        if(signal == '\n') {
            separator = 0;
            new_message++;
        }

        /**
         * V pripade, ze nacitame platne znaky
         */
        if(signal != EOF && signal != '\n' && signal != '|') {

            /**
             * Neplatny vstup v pripade, ze mame vice separatoru v jedne zprave
             */
            if(separator > 1) {
                printf("Nespravny vstup.\n");

                return 1;
            }

            int value = getNumberFromCharacter(&signal);

            /**
             * Pokud selze prevod hodnoty na cislo - uzivatel zadal nespravny znak
             */
            if(value == -1) {
                printf("Nespravny vstup.\n");

                return 1;
            }

            /**
             * Ukladani vyslednych cisel do vyhrazenych promennych
             * - separator == 1 - ukladame k zacatku zpravy + uvazime nacteni nove radky pro ukladani do druhe rovnice
             */
            if(separator == 1) {
                if(new_message == 1) {
                    start_message_second += value;
                } else if(new_message == 2) {
                    start_message_third += value;
                } else {
                    start_message_first += value;
                }
            } else {
                if(new_message == 1) {
                    remain_second += value;
                } else if(new_message == 2) {
                    remain_third += value;
                } else {
                    remain_first += value;
                }
            }
        }

        count++;
    }

    if(new_message >= 3 && start_message_third != 0 && remain_third != 0) {
        printf("asasasasasaas\n");
        /**
         * Overeni moznych situaci, kdy by mohla byt synchronizace == 0
         */
        if((remain_first == 0 && remain_second == 0 && remain_third) || (start_message_third == 0 && start_message_first == 0 && start_message_second == 0) ||
           (remain_third == 0 && remain_first == 0 && remain_second == start_message_first && start_message_second == 0) ||
           (remain_third == 0 && remain_first == start_message_second && remain_second == 0 && start_message_first == 0) ||
           (remain_first == 0 && start_message_second == 0) || (remain_second == 0 && start_message_first == 0)) {
            printf("Synchronizace za: 0\n");

            return 0;
        }

        /**
         * Pokud se rovnaji prefixy, pak je zprava synchronizovana po hodnote prefixu
         */
        if(remain_first == remain_second) {
            printf("Synchronizace za: %lld\n", remain_first);

            return 0;
        }

        synchronization = createEquation3(&remain_first, &start_message_first, &remain_second, &start_message_second, &remain_third, &start_message_third);

        /**
         * Zobrazime vysledek
         */
        if(synchronization == -1) {
            printf("Nelze dosahnout.\n");
        } else {
            printf("Synchronizace za: %lld\n", synchronization);
        }

        return 0;
    }

    /**
     * Pokud uzivatel zadal pouze separator nebo mene jak 2 rovnice = chyba vstupu
     */
    if(((remain_second == 0) && (start_message_second == 0)) || count <= 1) {
        printf("Nespravny vstup.\n");

        return 1;
    }

    /**
     * Overeni moznych situaci, kdy by mohla byt synchronizace == 0
     */
    if((remain_first == 0 && remain_second == 0) || (start_message_first == 0 && start_message_second == 0) ||
            (remain_first == 0 && remain_second == start_message_first && start_message_second == 0) ||
            (remain_first == start_message_second && remain_second == 0 && start_message_first == 0) ||
            (remain_first == 0 && start_message_second == 0) || (remain_second == 0 && start_message_first == 0)) {
        printf("Synchronizace za: 0\n");

        return 0;
    }

    /**
     * Pokud se rovnaji prefixy, pak je zprava synchronizovana po hodnote prefixu
     */
    if(remain_first == remain_second) {
        printf("Synchronizace za: %lld\n", remain_first);

        return 0;
    }

    /**
     * Zjistime synchronizaci z funkce pro vypocet rovnice
     */
    synchronization = createEquation(&remain_first, &start_message_first, &remain_second, &start_message_second);

    /**
     * Zobrazime vysledek
     */
    if(synchronization == -1) {
        printf("Nelze dosahnout.\n");
    } else {
        printf("Synchronizace za: %lld\n", synchronization);
    }

    return 0;
}
