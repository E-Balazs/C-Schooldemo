#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "morzekod.h"

/**
 * @brief A jelek, amelyekből a morzekód felépül
 *
 */
//static char jelek[3];




/**
 * @brief Létrehoz egy új táblát
 *
 * @return KodTabla* egy Kodtabla, ha van hely NULL ha nincs.
 */
KodTabla *UjTabla(void){
    KodTabla *tabla = malloc(sizeof(KodTabla));
    MorzeKar *elso = malloc(sizeof(MorzeKar));
    MorzeKar *utolso = malloc(sizeof(MorzeKar));
    elso->karakter = '\0';
    utolso->karakter = '\0';

    utolso->nxt = NULL;
    elso->lst = NULL;

    elso->nxt = utolso;
    utolso->lst = elso;

    tabla->eleje = elso;
    tabla->vege = utolso;
    tabla->maxkod = 0;
    tabla->count = 0;
    return tabla;
}

/** \brief Létrehoz egy új elemet
 *
 * \param
 * \param
 * \return
 *
 */
MorzeKar *UjKar(char kar, char* kodolt){
    MorzeKar *uj = malloc(sizeof(MorzeKar));
    if(!uj){
        perror("Elfogyott a memoria.");
        return NULL;
    }
    uj->karakter = kar;
    uj->kod = malloc(sizeof(char) * (strlen(kodolt)+1));
    strcpy(uj->kod, kodolt);

    return uj;
}

/**
 * @brief Kitürli a lista összes elemét, de a lista megmarad.
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
    Tabla->count = 0;

}

/**
 * @brief Megkeres egy karakterű elemet a listában. Lineáris, mert
 *
 * @param tabla A kódtábla, amely a karaktereket tartalmazza
 * @param kar A keresett karakter
 * @return Morzekar* Ha van, ->karakter == kar, ha nincs akkor NULL
 */
MorzeKar *KarKeres(KodTabla *tabla, char kar){
    kar = toupper(kar);
    MorzeKar *ki = tabla->eleje->nxt;
    while(ki != tabla->vege){
        if(ki->karakter == kar)
        return ki;
        ki = ki->nxt;
    }
    perror("A megadott karakterhez nincs kod");
    return NULL;
}

/**
 * @brief Megkeres egy karakterű elemet a listában. Lineáris, mert
 *
 * @param tabla A kódtábla, amely a karaktereket tartalmazza
 * @param kar A keresett karakter
 * @return Morzekar* Ha van, ->karakter == kar, ha nincs akkor NULL
 */
MorzeKar *KodKeres(KodTabla *tabla, char* kod){
    MorzeKar *ki = tabla->eleje->nxt;
    int kodhossz = strlen(kod);
    while(ki != tabla->vege){
        int epphossz = strlen(ki->kod);
        if(epphossz == kodhossz){
            epphossz = 0;
            for(int i = 0; i < kodhossz; i++){
                if(ki->kod[i] == kod[i]) epphossz++;
                else break;
            }
            if(epphossz == kodhossz) return ki;
        }
        ki = ki->nxt;
    }
    perror("A megadott kodu karakter nem letezik");
    return NULL;
}


void ListaDestroy(KodTabla *Tabla){
    ListaClear(Tabla);
    free(Tabla->eleje);
    free(Tabla->vege);
    free(Tabla);
}
/*int ListaLength(KodTabla *tabla){
    int db = 0;
    MorzeKar *szamlalo = tabla->eleje;
    while(szamlalo->nxt != tabla->vege)
        db++;
    return db;
}
*/

/**
 * @brief Beszúr egy elemet a helyére
 *
 * @param Tabla
 * @param elem
 * @return true
 * @return false
 */
static bool Beszur(KodTabla *Tabla, MorzeKar *elem){
    char betu = elem->karakter;
    MorzeKar *vizsgalt = Tabla->eleje->nxt;
    while(vizsgalt != Tabla->vege && vizsgalt->karakter < betu)//végigmegyünk a tömbön, vagy amíg magunknál nagyobbat nem találunk
        vizsgalt = vizsgalt->nxt;

    if(vizsgalt->karakter == betu)
        return false;
    vizsgalt->lst->nxt = elem;
             elem->nxt = vizsgalt;

        elem->lst = vizsgalt->lst;
    vizsgalt->lst = elem;
    int kodhossz = strlen(elem->kod);
    if(Tabla->maxkod < kodhossz) Tabla->maxkod = kodhossz;
    Tabla->count++;
    return true;
}


/**
 * @brief Beolvassa a kódtáblát
 *
 * @param hely
 * @return KodTabla*
 */
KodTabla *Tbeolvas(char* hely){
    FILE *olv = fopen(hely, "r");
    if(!olv){
        perror("Hiba a beolvasaskor");
        return NULL;
    }
    KodTabla *ki = UjTabla();

    //majd feof-nál breakelek
    while(true){
        char k, *eppkod;
        int epphossz = ki->maxkod == 0 ? 51 : ki->maxkod;
        eppkod = malloc(epphossz * sizeof(char));
        if(!eppkod){
            perror("Elfogyott a memoria.");
            ListaDestroy(ki);
            fclose(olv);
            return NULL;
        }
        k = fgetc(olv);
        char miez = fgetc(olv);
        int olvi = 0;
        for(char epp = fgetc(olv); feof(olv) == 0 && epp != '\n' && epp != '\0'; epp = fgetc(olv)){
            if(olvi == epphossz){ //ha tele a pillanatnyi string
                char * ujhely = malloc((epphossz +50) * sizeof(char));      //új, nagyobb string
                if(!ujhely){
                    perror("Elfogyott a memoria.");
                    ListaDestroy(ki);
                    fclose(olv);
                    return NULL;
                }
                for(int masolo = 0; masolo < epphossz; masolo++)
                    ujhely[masolo] = eppkod[masolo];        //nem lehet strcopy, mert nincs \0 a végén, max ha progon belülről módosítom
                free(eppkod);
                eppkod = ujhely;
                epphossz += 50;
            }
            eppkod[olvi] = epp;
            olvi++;
        }
        if(feof(olv)){
            free(eppkod);
            break;
        }
        eppkod[olvi] = '\0';
        if(k == ' ' && strlen(eppkod) > 1){
            perror("A szóköz kódja csak 1 karaktert tartalmazhat.");
            ListaDestroy(ki);
            fclose(olv);
            return NULL;
        }

        MorzeKar *eppelem = UjKar(toupper(k),eppkod);
        free(eppkod);
        if(!eppelem){
            ListaDestroy(ki);
            fclose(olv);
            return NULL;
        }
        Beszur(ki, eppelem);    //létrehozzuk a karaktert, és rögtön bezúrjuk a táblába
        if(feof(olv)) break;
    }


    fclose(olv);
    return ki;
}
