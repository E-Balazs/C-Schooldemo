#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "adat.h"

/**
 * @brief A jelek, amelyekből a morzekód felépül
 * 
 */
static char jelek[3];

/**
 * @brief Egy karakter.
 * 
 */
typedef struct MorzeKar{
    ///
    char karakter;
    char *kod;
    struct MorzeKar *lst;
    struct MorzeKar *nxt;

} MorzeKar;

/**
 * @brief 
 * 
 */
typedef struct KodTabla{
    MorzeKar *eleje;
    MorzeKar *vege;
} KodTabla;
/**
 * @brief 
 * 
 * @param Tabla a tábla, amit üríteni kell
 */
void ListaClear(KodTabla *Tabla){
    if(Tabla->eleje->nxt == Tabla->vege)
        return;
    Tabla->vege->lst->nxt = NULL;
    MorzeKar *futo = Tabla->eleje->nxt;
    while(futo != NULL){
        MorzeKar *epp = futo->nxt;
        free(futo);
        futo = epp;
    }
    Tabla->vege->lst = Tabla->eleje;
    Tabla->eleje->nxt = Tabla->vege;

}


void ListaDestroy(KodTabla *Tabla){
    ListaClear(Tabla);
    free(Tabla->eleje);
    free(Tabla->vege);
    free(Tabla);
}

int ListaLength(KodTabla *tabla){
    int db = 0;
    MorzeKar *szamlalo = tabla->eleje;
    while(szamlalo->nxt != tabla->vege)
        db++;
    return db;
}
/**
 * @brief Beszúr egy elemet a tábla elejére
 * 
 * @param Tabla 
 * @param elem 
 * @return true 
 * @return false 
 */
bool Beszur(KodTabla *Tabla, MorzeKar *elem){
    char betu = elem->karakter;
    MorzeKar *vizsgalt = Tabla->eleje->nxt;
    while(vizsgalt != Tabla->vege && vizsgalt->karakter < betu)
        vizsgalt = vizsgalt->nxt;

    vizsgalt->lst->nxt = elem;
             elem->nxt = vizsgalt;

        elem->lst = vizsgalt->lst;
    vizsgalt->lst = elem;
}

