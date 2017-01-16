#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct TResult
{
    TResult   * m_Next;
    int         m_ID;
    char      * m_Name;
} TRESULT;
#endif /* __PROGTEST__ */

/**
 * Databaze uzivatelu
 * note: Uzivatele vkladat na zacatek spojoveho seznamu
 */
typedef struct TUSER {
    TUSER *next;
    TUSER *parent_1;
    TUSER *parent_2;
    int id;
    char *name;
    int in_output;
} TUSER;

/**
 * Ukazatel na zacatek spojoveho seznamu - TUSER
 */
typedef struct TLIST {
    TUSER *head;
} TLIST;

/**
 * Ukazatel na zacatek spojoveho seznamu - TResult
 */
typedef struct TResultList {
    TRESULT *head;
} TResultList;

TLIST *list;
TResultList *result_list;
TResultList *common;

/**
 * Funkce overujici, zda je databaze / seznam vysledku prazdny nebo ne
 *
 * @return
 */
int isEmpty(int user) {

    if (user == 1) {

        return list->head == NULL;
    } else {

        return result_list->head == NULL;
    }
}

void freeData(TResultList * result) {
    if(result->head) {
        TRESULT *tmp;
        TRESULT *res;
        res = result->head;

        while (res) {
            tmp = res->m_Next;
            free(res->m_Name);
            free(res);
            res = tmp;
        }

        free(tmp);
    }

    result->head = NULL;
}

/**
 * Funkce vracejici informaci, zda jsou zadane udaje korektni a muze byt vytvoren novy uzivatel
 *
 * @param id
 * @param parent_1_id
 * @param parent_2_id
 * @return
 */
int validateData(int id, int parent_1_id, int parent_2_id) {
    if (isEmpty(1)) {

        return 1;
    }

    if (id <= 0 || parent_1_id < 0 || parent_2_id < 0 || (parent_1_id != 0 && parent_1_id == parent_2_id)) {

        return 0;
    }

    TUSER *tmp = list->head;
    int parent_1 = 0, parent_2 = 0;

    if (parent_1_id == 0) {
        parent_1 = 1;
    }

    if (parent_2_id == 0) {
        parent_2 = 1;
    }

    while (tmp) {
        if (tmp->id == id) {

            return 0;
        }

        if (parent_1 != 1 && tmp->id == parent_1_id) {
            parent_1 = 1;
        }

        if (parent_2 != 1 && tmp->id == parent_2_id) {
            parent_2 = 1;
        }

        tmp = tmp->next;
    }

    if (parent_1 == 0 || parent_2 == 0) {

        return 0;
    }

    return 1;
}

/**
 * Funkce vypisujici spojovy seznam - TRESULT
 * note: k testovacim ucelum
 */
void readResults() {
    if (isEmpty(0)) {

        return;
    }

    TRESULT *tmp = result_list->head;

    while (tmp) {
        printf("%s, %d\n", tmp->m_Name, tmp->m_ID);
        tmp = tmp->m_Next;
    }
}

void readResults2() {
    if (!common->head) {

        return;
    }

    TRESULT *tmp = common->head;

    while (tmp) {
        printf("%s, %d\n", tmp->m_Name, tmp->m_ID);
        tmp = tmp->m_Next;
    }
}

/**
 * Funkce vypisujici spojovy seznam - TUSER
 * note: k testovacim ucelum
 */
void readUsers() {
    if (isEmpty(1)) {

        return;
    }

    TUSER *tmp = list->head;

    while (tmp) {
        printf("%s, %d\n", tmp->name, tmp->id);
        tmp = tmp->next;
    }
}

TUSER *getUser(int id) {
    if (isEmpty(1)) {

        return NULL;
    }

    TUSER *user = list->head;

    while (user) {
        if (user->id == id) {

            return user;
        }

        user = user->next;
    }

    return NULL;
}

/**
 * Funkce pridavajici do TResult nalezeneho uzivatele
 *
 * @param result
 * @param user
 */
void addResult(TUSER *user, TResultList * resultList) {
    if (user) {
        TRESULT *result;
        result = (TRESULT *) malloc(sizeof(TRESULT));
        result->m_Next = resultList->head;
        resultList->head = result;
        resultList->head->m_ID = user->id;
        resultList->head->m_Name = (char *) malloc((1 + strlen(user->name)) * sizeof(char));
        strcpy(resultList->head->m_Name, user->name);
    }
}

int checkAncestors2(TUSER * user) {
    TRESULT *result;
    result = common->head;

    while (result) {
        if (result->m_ID == user->id) {

            return 1;
        }

        result = result->m_Next;
    }

    return 0;
}

int checkAncestors(TUSER * user) {
    TRESULT *result;
    result = result_list->head;

    while (result) {
        if (result->m_ID == user->id) {

            return 1;
        }

        result = result->m_Next;
    }

    return 0;
}

/**
 * Funkce hledajici a ukladajici nalezene predky
 *
 * @param user
 */
void getAncestors(TUSER *user) {
    if(!user) {

        return;
    }

    if(checkAncestors(user) != 1) {
        addResult(user, result_list);
    }

    if(user->parent_1) {
        getAncestors(user->parent_1);
    }

    if(user->parent_2) {
        getAncestors(user->parent_2);
    }

    if(!user->parent_1 && !user->parent_2) {

        return;
    }
}

/**
 * Funkce hledajici a ukladajici nalezene predky
 *
 * @param user
 */
void getAncestors2(TUSER *user) {
    if(!user) {

        return;
    }

    if(checkAncestors(user) != 1) {
        addResult(user, result_list);
    }

    if(user->parent_1) {
        getAncestors2(user->parent_1);
    }

    if(user->parent_2) {
        getAncestors2(user->parent_2);
    }

    if(!user->parent_1 && !user->parent_2) {

        return;
    }
}

void getAncestors3(TUSER *user) {
    if(!user) {

        return;
    }

    if(checkAncestors2(user) != 1) {
        addResult(user, common);
    }

    if(user->parent_1) {
        getAncestors3(user->parent_1);
    }

    if(user->parent_2) {
        getAncestors3(user->parent_2);
    }

    if(!user->parent_1 && !user->parent_2) {

        return;
    }
}

int search(int id) {
    int count = 0;
    TRESULT * result;
    result = result_list->head;

    while (result) {
        if(result->m_ID == id) {
            count++;
        }

        result = result->m_Next;
    }

    return count;
}

int makeResult() {
    if(!common->head || !result_list->head) {

        return 0;
    }

    TRESULT * r;
    r = result_list->head;

    while (r) {
        if(!r->m_Next) {
            break;
        }

        r = r->m_Next;
    }

    r->m_Next = common->head;
    common->head = NULL;
    TUSER * user;
    user = list->head;
    int count = 0;

    while (user) {
        if(search(user->id) == 2) {
            addResult(user, common);
            count++;
        }

        user = user->next;
    }

    if(count == 0) {

        return 0;
    }

    freeData(result_list);
    result_list->head = common->head;

    return 1;
}

void      Init             ( void )
{
    list = (TLIST *) malloc(sizeof(TLIST));
    result_list = (TResultList *) malloc(sizeof(TResultList));
    common = (TResultList *) malloc(sizeof(TResultList));
    list->head = NULL;
    result_list->head = NULL;
    common->head = NULL;
}
void      Done             ( void )
{
    freeData(result_list);
    freeData(common);

    TUSER * head;
    TUSER * tmp;
    head = list->head;

    while (head) {
        tmp = head->next;
        free(head->name);
        free(head);
        head = tmp;
    }

    free(tmp);
    free(list);
    free(result_list);
    free(common);
}
int       Register         ( int               ID,
                             const char      * name,
                             int               ID1,
                             int               ID2 )
{
    if (validateData(ID, ID1, ID2) == 1) {
        if (isEmpty(1)) {
            list->head = (TUSER *) malloc(sizeof(TUSER));
            list->head->next = NULL;
        } else {
            TUSER *tmp;
            tmp = (TUSER *) malloc(sizeof(TUSER));
            tmp->next = list->head;
            list->head = tmp;
        }

        list->head->id = ID;
        list->head->name = (char *) malloc((1 + strlen(name)) * sizeof(*list->head->name));
        strcpy(list->head->name, name);
        list->head->parent_1 = getUser(ID1);
        list->head->parent_2 = getUser(ID2);
        list->head->in_output = 0;

        return 1;
    }

    return 0;
}
TRESULT * Ancestors        ( int               ID )
{
    freeData(result_list);
    freeData(common);

    if (isEmpty(1) || ID <= 0) {
        freeData(result_list);

        return result_list->head;
    }

    TUSER *tmp = list->head;

    while(tmp) {
        if(tmp->id == ID) {
            getAncestors(tmp->parent_1);
            getAncestors(tmp->parent_2);

            break;
        }

        tmp = tmp->next;
    }

    return result_list->head;
}

TRESULT * CommonAncestors  ( int               ID1,
                             int               ID2 )
{
    freeData(result_list);
    freeData(common);

    if (isEmpty(1) || ID1 <= 0 || ID2 <= 0) {
        freeData(result_list);

        return result_list->head;
    }

    if(ID1 == ID2) {

        return Ancestors(ID1);
    }

    TUSER *tmp = list->head;

    while(tmp) {
        if(tmp->id == ID1) {
            getAncestors2(tmp->parent_1);
            getAncestors2(tmp->parent_2);
        }

        if(tmp->id == ID2) {
            getAncestors3(tmp->parent_1);
            getAncestors3(tmp->parent_2);
        }

        tmp = tmp->next;
    }

    if(makeResult() == 0) {
        freeData(result_list);
        freeData(common);

        return result_list->head;
    }

    result_list->head = common->head;
    common->head = NULL;

    return result_list->head;
}
void      FreeResult       ( TRESULT         * res )
{
    freeData(result_list);
    freeData(common);
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    char name[100];
    TRESULT * l;

    Init ();
    assert ( Register ( 1, "John", 0, 0 ) == 1 );
    strncpy ( name, "Jane", sizeof ( name ) );
    assert ( Register ( 2, name, 0, 0 ) == 1 );
    assert ( Register ( 3, "Caroline", 0, 0 ) == 1 );
    assert ( Register ( 4, "Peter", 0, 0 ) == 1 );
    assert ( Register ( 5, "George", 1, 2 ) == 1 );
    assert ( Register ( 6, "Martin", 1, 2 ) == 1 );
    assert ( Register ( 7, "John", 3, 4 ) == 1 );
    assert ( Register ( 8, "Sandra", 3, 4 ) == 1 );
    assert ( Register ( 9, "Eve", 1, 2 ) == 1 );
    assert ( Register ( 10, "Douglas", 1, 4 ) == 1 );
    strncpy ( name, "Phillipe", sizeof ( name ) );
    assert ( Register ( 11, name, 6, 8 ) == 1 );
    strncpy ( name, "Maria", sizeof ( name ) );
    assert ( Register ( 12, name, 5, 8 ) == 1 );
    l = Ancestors ( 11 );
    /*
     * ID=1, name="John"
     * ID=2, name="Jane"
     * ID=3, name="Caroline"
     * ID=4, name="Peter"
     * ID=6, name="Martin"
     * ID=8, name="Sandra"
     */
    FreeResult ( l );
    assert ( Ancestors ( 3 ) == NULL );
    assert ( Ancestors ( 13 ) == NULL );
    l = CommonAncestors ( 11, 12 );
    /*
     * ID=1, name="John"
     * ID=2, name="Jane"
     * ID=3, name="Caroline"
     * ID=4, name="Peter"
     * ID=8, name="Sandra"
     */
    FreeResult ( l );
    l = CommonAncestors ( 10, 9 );
    /*
     * ID=1, name="John"
     */
    FreeResult ( l );
    assert ( CommonAncestors ( 7, 6 ) == NULL );
    l = CommonAncestors ( 7, 10 );
    /*
     * ID=4, name="Peter"
     */
    FreeResult ( l );
    assert ( Register ( 13, "Quido", 12, 11 ) == 1 );
    l = Ancestors ( 13 );
    /*
     * ID=1, name="John"
     * ID=2, name="Jane"
     * ID=3, name="Caroline"
     * ID=4, name="Peter"
     * ID=5, name="George"
     * ID=6, name="Martin"
     * ID=8, name="Sandra"
     * ID=11, name="Phillipe"
     * ID=12, name="Maria"
     */
    FreeResult ( l );
    l = CommonAncestors ( 9, 12 );
    /*
     * ID=1, name="John"
     * ID=2, name="Jane"
     */
    FreeResult ( l );
    assert ( Register ( 1, "Francois", 0, 0 ) == 0 );
    Done ();

    Init ();
    assert ( Register ( 10000, "John", 0, 0 ) == 1 );
    assert ( Register ( 10000, "Peter", 0, 0 ) == 0 );
    assert ( Register ( 20000, "Jane", 10000, 0 ) == 1 );
    assert ( Register ( 30000, "Maria", 10000, 10000 ) == 0 );
    assert ( Register ( 40000, "Joe", 10000, 30000 ) == 0 );
    assert ( Register ( 50000, "Carol", 50000, 20000 ) == 0 );
    Done ();

    return 0;
}
#endif /* __PROGTEST__ */