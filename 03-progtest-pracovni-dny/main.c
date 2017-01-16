/**
 * 03 - progtest - Pracovni dny
 *
 * @author Stefan Prokop <prokoste@fit.cvut.cz>
 *
 * Spent time:
 *      12.11. - Overeni platnosti zadanych hodnot - 45min
 *      12.11. - Programovani a ladeni funkce IsWorkDay - 15min
 *      12.11. - Programovani naivniho reseni a vylepseneho algoritmu, ktery skace po mesicich - 3hod
 *      13.11. - Dokonceni naivniho reseni a testovani - 1.5hod
 *      13.11. - Uprava casti kodu, moznosti zrychleni aplikace - 30min
 *
 * Total spent time: 6hod
 */

#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#include <time.h>
#endif /* __PROGTEST__ */

/**
 * Metoda urcujici, zda je zadany rok rokem prestupnym
 *
 * @param year
 * @return
 */
int isLeapYear(int year) {

    if (year % 4000 != 0) {
        if ((year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0))) {

            return 1;
        } else {

            return 0;
        }
    } else {

        return 0;
    }
}

/**
 * Funkce vracejici pocet dni v mesici
 *
 * @param m
 * @param y
 * @return
 */
int getDaysInMonth(int m, int y) {
    int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(m == 2) {
        if(isLeapYear(y) == 1) {

            return 29;
        }
    }

    return days_in_month[m - 1];
}

/**
 * Funkce overujici platnost zadanych datumu
 * - overuje, zda zadane datumy patri do intervalu a jsou tak platnym datumem
 *
 * @param y
 * @param m
 * @param d
 * @return
 */
int checkValues(int y, int m, int d) {

    return (y >= 2000 && m >= 1 && m <= 12 && d >= 1 && d <= getDaysInMonth(m, y));
}

/**
 * Funkce vracejici hodnotu, zda zadany datum je / neni statnim svatkem
 *
 * @param m
 * @param d
 * @return
 */
int isHoliday(int m, int d) {

    return ((m == 1 && d == 1) || (m == 5 && d == 1) || (m == 5 && d == 8) || (m == 7 && d == 5) || (m == 7 && d == 6) ||
            (m == 9 && d == 28) || (m == 10 && d == 28) || (m == 11 && d == 17) || (m == 12 && d == 24) ||
            (m == 12 && d == 25) || (m == 12 && d == 26));
}

int IsWorkDay ( int y, int m, int d )
{
    /**
     * Prevod zadaneho datumu do struktury tm pro lepsi praci s datumem
     */
    char date_text[100];
    struct tm date;

    sprintf(date_text, "%d%s%d%s%d", d, "/", m, "/", y);
    strptime(date_text, "%d/%m/%Y", &date);

    int day_of_week = date.tm_wday;

    if(checkValues(y, m, d) == 0) {

        return 0;
    }

    /**
     * Pokud se nejedna o sobotu nebo o nedeli nebo o statni svatek, pak vratime 1
     */
    if(day_of_week != 6 && day_of_week != 0 && isHoliday(m, d) == 0) {

        return 1;
    } else {

        return 0;
    }
}

int CountWorkDays ( int y1, int m1, int d1,
                    int y2, int m2, int d2,
                    int * cnt )
{
    /**
     * Prevod zadaneho datumu na strukturu
     */
    int count = 0;
    char date_text[100];
    struct tm date;

    sprintf(date_text, "%d%s%d%s%d", d1, "/", m1, "/", y1);
    strptime(date_text, "%d/%m/%Y", &date);

    int day_of_week = date.tm_wday;

    /**
     * Porovnani nespravnosti zadanych datumu (overeni, zda prvni rok neni vetsi nez druhy atp.)
     */
    if(y2 < y1 || ((y2 == y1) && (m2 < m1)) || ((y2 == y1) && (m2 == m1) && (d2 < d1))) {

        return 0;
    }

    if(checkValues(y1, m1, d1) == 0 || checkValues(y2, m2, d2) == 0) {

        return 0;
    }

    /**
     * Pokud pocitame pouze pro jeden den
     */
    if(d1 == d2 && m1 == m2 && y1 == y2) {
        if(day_of_week != 6 && day_of_week != 0 && isHoliday(m1, d1) == 0) {
            count++;
        }
    } else {
        /**
         * Vypocet pro vice nez jeden den
         */
        int days_in_month = getDaysInMonth(m1, y1);

        while (1) {

            /**
             * Pokud se nejedna o sobotu, nedeli nebo statni svatek, pricteme pracovni den
             */
            if(day_of_week != 6 && day_of_week != 0 && isHoliday(m1, d1) == 0) {
                count++;
            }

            /**
             * iterujeme dny / mesice / roky + overeni preteceni roku a mesicu
             */
            d1++;
            day_of_week++;

            if(day_of_week >= 7) {
                day_of_week = 0;
            }

            if (d1 > days_in_month) {
                d1 = 1;
                m1++;
                days_in_month = getDaysInMonth(m1, y1);
            }

            if (m1 == 13) {
                m1 = 1;
                y1++;
                days_in_month = getDaysInMonth(m1, y1);
            }

            /**
             * Pokud se datumy rovnaji vyskocime z cyklu
             */
            if (y1 == y2 && m1 == m2 && d1 == d2) {

                break;
            }
        }

        /**
         * Dopocitani zbyleho dne
         */
        sprintf(date_text, "%d%s%d%s%d", d2, "/", m2, "/", y2);
        strptime(date_text, "%d/%m/%Y", &date);
        day_of_week = date.tm_wday;

        if(day_of_week != 6 && day_of_week != 0 && isHoliday(m2, d2) == 0) {
            count++;
        }
    }

    *cnt = count;
    return 1;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    int cnt;

    assert ( IsWorkDay ( 2016, 11, 11 ) );
    assert ( ! IsWorkDay ( 2016, 11, 12 ) );
    assert ( ! IsWorkDay ( 2016, 11, 17 ) );
    assert ( ! IsWorkDay ( 2016, 11, 31 ) );
    assert ( IsWorkDay ( 2016,  2, 29 ) );
    assert ( ! IsWorkDay ( 2004,  2, 29 ) );
    assert ( ! IsWorkDay ( 2001,  2, 29 ) );
    assert ( ! IsWorkDay ( 1996,  1,  1 ) );
    assert ( CountWorkDays ( 2016, 11,  1,
                             2016, 11, 30, &cnt ) == 1
             && cnt == 21 );
    assert ( CountWorkDays ( 2016, 11,  1,
                             2016, 11, 17, &cnt ) == 1
             && cnt == 12 );
    assert ( CountWorkDays ( 2016, 11,  1,
                             2016, 11,  1, &cnt ) == 1
             && cnt == 1 );
    assert ( CountWorkDays ( 2016, 11, 17,
                             2016, 11, 17, &cnt ) == 1
             && cnt == 0 );
    assert ( CountWorkDays ( 2016,  1,  1,
                             2016, 12, 31, &cnt ) == 1
             && cnt == 254 );
    assert ( CountWorkDays ( 2015,  1,  1,
                             2015, 12, 31, &cnt ) == 1
             && cnt == 252 );
    assert ( CountWorkDays ( 2000,  1,  1,
                             2016, 12, 31, &cnt ) == 1
             && cnt == 4302 );
    assert ( CountWorkDays ( 2001,  2,  3,
                             2016,  7, 18, &cnt ) == 1
             && cnt == 3911 );
    assert ( CountWorkDays ( 2014,  3, 27,
                             2016, 11, 12, &cnt ) == 1
             && cnt == 666 );
    assert ( CountWorkDays ( 2001,  1,  1,
                             2000,  1,  1, &cnt ) == 0 );
    assert ( CountWorkDays ( 2001,  1,  1,
                             2015,  2, 29, &cnt ) == 0 );

    return 0;
}
#endif /* __PROGTEST__ */