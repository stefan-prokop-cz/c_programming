/**
 * Úkolem je implementovat 2 funkce, TITEM * StringToList ( const char* ) a void FreeList ( TITEM * ). Funkce
 * StringToList dostane parametrem string, který rozdělí na jednotlivá slova, která uloží do spojového seznamu
 * struktur TITEM. Vrací tento spojový seznam, je potřeba alokovat pamět a zkopirovat data. V nápovědě bylo ještě,
 * že máme pro odhalení bílých znaků mezi slovy použít funkci isspace. Funkce FreeList uvolní paměť alokovanou
 * funkcí StringToList.
 */

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <wctype.h>

typedef struct TItem {
    struct TItem * m_Next;
    char *m_Word;
}TITEM;

TITEM * init(char * word) {
    TITEM *item = (TITEM *) malloc(sizeof(*item));
    item->m_Word = word;
    item->m_Next = NULL;

    return item;
}

void createItem(char * word, TITEM * item, int c) {
    TITEM * new_item = init(word);
    TITEM * tmp = item;

    while(tmp->m_Next) {
        tmp = tmp->m_Next;
    }

    tmp->m_Next = new_item;
}

TITEM* StringToList( const char* string )
{
    TITEM * item = NULL;
    int count = 0, c = 0, first_item = 1;
    char character = string[count];
    char * word = (char *) malloc(strlen(string + 1) * sizeof(*word));

    while(character != '\0') {
        if(!iswspace((wint_t) character)) {
            word[c] = character;
            c++;
        } else {
            if (c > 0 && word[0] != '\0') {
                if (first_item) {
                    item = init(word);
                    first_item = 0;
                } else {
                    createItem(word, item, c);
                }

                word = (char *) realloc(NULL, strlen(string + 1) * sizeof(*word));
                c = 0;
            }
        }

        count++;
        character = string[count];
    }

    TITEM * tmp = item;

    while(tmp) {
        printf("%s", tmp->m_Word);
        tmp = tmp->m_Next;
    }

    printf("\n");

    free(word);
    return item;
}

void FreeList ( TITEM* List )
{
    TITEM * tmp = List;

    while(tmp) {
        TITEM * next = tmp->m_Next;
        free(tmp->m_Word);
        free(tmp);
        tmp = next;
    }

    free(tmp);
}

int main() {
    FreeList(StringToList("  Toto   je muj\ntestovaci \tassert\n\n\n"));

    return 0;
}