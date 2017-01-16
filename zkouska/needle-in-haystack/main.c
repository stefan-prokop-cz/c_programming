/**
 * Realizujte funkci, která najde všechny výskyty posloupnosti reprezentované spojovým seznamem „needle“ ve spojovém
 * seznamu „hayStack“.
 * Funkce bude vracet dynamicky alokované pole ukazatelů na prvky seznamu „hayStack“, kde začíná hledaná posloupnost,
 * poslední prvek pole bude vždy NULL (pokud program nenalezne žádný výskyt, vrací NULL).
 * Byl k tomu obrázek, v praxi šlo o to, že třeba spoják „hayStack“ měl prvky postupně 1-2-1-2-3-4-1-2-3-8 a
 * „needle“ byl 1-2-3, a funkce by měla vracet pole, kde bude ukazatel na třetí prvek „hayStack“, ukazatel na sedmý
 * prvek „hayStack“ a NULL.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct TNode {
    struct TNode * p_Next;
    int m_Value;
} TNODE;

int global_count = 0;

TNODE * init() {
    TNODE * node = (TNODE * ) malloc(sizeof(*node));
    node->p_Next = NULL;

    return node;
}

void insertNode(TNODE * nodes, int value) {
    if(nodes) {
        TNODE *tmp = nodes;
        while (tmp->p_Next) {
            tmp = tmp->p_Next;
        }

        tmp->p_Next = init();
        tmp->m_Value = value;
    }
}

void readNodes(TNODE * nodes) {
    TNODE * tmp = nodes;
    while (tmp->p_Next) {
        printf("%d ", tmp->m_Value);
        tmp = tmp->p_Next;
    }

    printf("\n");
}

TNODE ** search(TNODE * hayStack, TNODE * needle) {
    if(!hayStack || !needle) {
        return NULL;
    }

    int alloc = 10, c = 0, node_position = 0, needles = 0;
    int * result_positions = (int *) malloc(alloc * sizeof(*result_positions));
    TNODE ** res = (TNODE **) malloc(alloc * sizeof(*res));
    TNODE * hayStack_tmp = hayStack;

    TNODE * n = needle;
    while (n->p_Next) {
        needles++;
        n = n->p_Next;
    }

    while (hayStack_tmp->p_Next) {
        if(hayStack_tmp->m_Value == needle->m_Value) {
            TNODE * result = hayStack_tmp;
            TNODE * needle_tmp = needle;
            TNODE * hayStack_tmp2 = hayStack_tmp;
            int count_res = 0;

            while(needle_tmp->p_Next) {
                if(needle_tmp->m_Value == hayStack_tmp2->m_Value) {
                    count_res++;
                }

                if(hayStack_tmp2->p_Next) {
                    hayStack_tmp2 = hayStack_tmp2->p_Next;
                    needle_tmp = needle_tmp->p_Next;
                }
            }

            if(needles == count_res) {
                c++;
                if(c >= alloc - 1) {
                    alloc += 10;
                    res = (TNODE **) realloc(res, (alloc * sizeof(*res)));
                    result_positions = (int *) realloc(result_positions, (alloc * sizeof(*result_positions)));
                }

                result_positions[c] = node_position;
                res[c] = result;
            }
        }

        node_position++;
        hayStack_tmp = hayStack_tmp->p_Next;
    }

    for(int i = 1; i <= c; i++) {
        printf("position: %d\n", result_positions[i]);
    }

    free(result_positions);

    if(c <= 0) {
        return NULL;
    }

    global_count = c;
    return res;
}

void freeData(TNODE * node) {
    TNODE * tmp = node;

    while (tmp) {
        TNODE * tnode = tmp->p_Next;
        free(tmp);
        tmp = tnode;
    }
}

int main() {

    int number;
    TNODE * hayStack = init();
    TNODE * needle = init();

    printf("HayStack:\n");
    while(scanf(" %d", &number) == 1) {
        insertNode(hayStack, number);
    }

    printf("Needle:\n");
    while(scanf(" %d", &number) == 1) {
        insertNode(needle, number);
    }

    TNODE ** result = search(hayStack, needle);

    if(global_count > 0) {
        free(result);
    }

    freeData(hayStack);
    freeData(needle);

    return 0;
}