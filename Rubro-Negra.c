#include <stdio.h>
#include <stdlib.h>

struct no{
    int chave;
    int cor; // 0 = RUBRO, 1 = NEGRO
    struct no* pai;
    struct no* esq;
    struct no* dir;
};
typedef struct no NO;

struct rn{
    struct no* raiz;
    struct no* externo;
};
typedef struct rn RN;

NO* criaNO(RN** rn, int x){
    NO* novo = malloc(sizeof(NO));
    novo->chave = x;
    novo->cor = 0;
    novo->dir = (*rn)->externo;
    novo->esq = (*rn)->externo;
    novo->pai = (*rn)->externo;
    return novo;
}


void rotacaoEsq(RN** rn, NO** x){
    printf("Entrei aq...... \n");
    NO* y = (*x)->dir;
    (*x)->dir = y->esq;
    if( (*x)->dir != (*rn)->externo ){
        ((NO*)y->esq)->pai = (*x);
    }
    y->pai = (*x)->pai;
    if( (*x)->pai == (*rn)->externo ){
        (*rn)->raiz = y;
    }else if( (*x) == ((NO*)(*x)->pai)->esq ){
        ((NO*)(*x)->pai)->esq = y;
    }else{
        ((NO*)(*x)->pai)->dir = y;
    }
    y->esq = (*x);
    (*x)->pai = y;
}

void rotacaoDir(RN** rn, NO** x){
    NO* y = (*x)->esq;
    (*x)->esq = y->dir;
    if( (*x)->esq != (*rn)->externo ){
        ((NO*)y->dir)->pai = (*x);
    }
    y->pai = (*x)->pai;
    if( (*x)->pai == (*rn)->externo ){
        (*rn)->raiz = y;
    }else if( (*x) == ((NO*)(*x)->pai)->dir ){
        ((NO*)(*x)->pai)->dir = y;
    }else{
        ((NO*)(*x)->pai)->esq = y;
    }
    y->dir = (*x);
    (*x)->pai = y;
}

void inserirFixup(RN** rn, NO** z){
    while( ((NO*)(*z)->pai)->cor == 0 ){
        if( ((NO*)(*z)->pai) == ((NO*)((NO*)(*z)->pai)->pai)->esq ){
            NO* y = ((NO*)((NO*)(*z)->pai)->pai)->dir;
            if(y->cor == 0){
                y->cor = 1;
                ((NO*)(*z)->pai)->cor = 1;
                (*z) = ((NO*)(*z)->pai)->pai;
                (*z)->cor = 0;
            }else{
                if( (*z) == ((NO*)(*z)->pai)->dir ){
                    (*z) = (*z)->pai;
                    printf("Simples a Esquerda no: %i \n", (*z)->chave);
                    rotacaoEsq( &(*rn), &(*z) );
                }
                ((NO*)(*z)->pai)->cor = 1;
                ((NO*)((NO*)(*z)->pai)->pai)->cor = 0;
                NO * paiPaiZ = ((NO*)(*z)->pai)->pai;
                printf("Dupla a direita no: %i \n", paiPaiZ->chave);
                rotacaoDir( &(*rn), &paiPaiZ );
            }
        }else{
            NO* y = ((NO*)((NO*)(*z)->pai)->pai)->esq;
            if(y->cor == 0){
                ((NO*)(*z)->pai)->cor = 1;
                y->cor = 1;
                (*z) = ((NO*)(*z)->pai)->pai;
                (*z)->cor = 0;
            }else{
                if( (*z) == ((NO*)(*z)->pai)->esq ){
                    (*z) = (*z)->pai;
                    printf("Simples a Direita no: %i \n", (*z)->chave);
                    rotacaoDir( &(*rn), &(*z) );
                }
                ((NO*)(*z)->pai)->cor = 1;
                ((NO*)((NO*)(*z)->pai)->pai)->cor = 0;
                NO * paiPaiZ = ((NO*)(*z)->pai)->pai;
                printf("Dupla a Esquerda no: %i \n", paiPaiZ->chave);
                rotacaoEsq( &(*rn), &paiPaiZ );
            }
        }
    }
    ((NO*)(*rn)->raiz)->cor = 1;
}

void inserir(RN** rn, int chave){
    NO* z = NULL;
    z = criaNO( &(*rn), chave );
    NO* y = (NO*) (*rn)->externo;
    NO* x = (NO*) (*rn)->raiz;
    while( x != (NO*) (*rn)->externo ){
        y = x;
        if(z->chave == x->chave){
            printf("Saporra ja existe... \n");
            x = (NO*) (*rn)->externo;
            y = NULL;
        }else{
            if(z->chave < x->chave){
                x = (NO*) x->esq;
            }else{
                x = (NO*) x->dir;
            }
        }
    }

    if(y != NULL){
        z->pai = (struct NO*) y;
        if( y == (NO*) (*rn)->externo ){
            (*rn)->raiz = (struct NO*) z;
        }else{
            if(z->chave < y->chave){
                y->esq = (struct NO*) z;
            }else{
                y->dir = (struct NO*) z;
            }
        }
        z->esq = (*rn)->externo;
        z->dir = (*rn)->externo;
        z->cor = 0;
        inserirFixup( &(*rn), &z );
    }
}


/*void inserir(RN** rn, int chave){
    NO* z = NULL;
    z = criaNO( &(*rn), chave );
    NO* y = (*rn)->externo;
    NO* x = (*rn)->raiz;
    while(x != (*rn)->externo){
        y = x;
        if(z->chave < x->chave){
            x = x->esq;
        }else{
            x = x->dir;
        }
        z->pai = y;
        if( y == (*rn)->externo ){
            (*rn)->raiz = z;
        }else if(z->chave < x->chave){
            y->esq = z;
        }else{
            y->dir = z;
        }
        z->esq = (*rn)->externo;
        z->dir = (*rn)->externo;
        z->cor = 0;
        inserirFixup(&(*rn), &z);
    }
}*/

void imprimeNo(NO * no, int espacos){

    while (espacos != 0){
        printf(" ");
        espacos--;
    }

    printf("(%d", no->chave);
    if(no->cor == 1){
        printf(", N)");
    }else{
        printf(", R)");
    }

}


void imprimeRN(NO * externo, NO * no, int espacos){

    if(no != externo){
        if(no->dir != externo){
            imprimeRN(externo, no->dir, espacos + 5);
        }

        imprimeNo(no, espacos);
        puts("");

        if(no->esq != externo){
            imprimeRN(externo, no->esq, espacos + 5);
        }
    }
}


int main(){
    RN* rn = malloc(sizeof(RN));
    rn->externo = malloc(sizeof(NO));
    rn->raiz = rn->externo;
    rn->externo->esq = rn->externo;
    rn->externo->dir = rn->externo;
    rn->externo->pai = rn->externo;
    rn->externo->cor = 1;


    int chaves[] = {50, 20, 40, 55, 53};
    for(int i = 0;i < 5;i++){
        inserir(&rn, chaves[i]);
    }
    /*inserir(&rn, 12);
    inserir(&rn, 10);
    inserir(&rn, 15);
    inserir(&rn, 50);
    inserir(&rn, 9);
    inserir(&rn, 14);
    inserir(&rn, 33);
    */

    imprimeRN(rn->externo, rn->raiz, 0);
    //inserir(&rn, 10);

    return 1;
}
