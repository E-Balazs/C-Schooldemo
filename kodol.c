#include <stdio.h>
#include <stdbool.h>
#include "kodol.h"
#include "morzekod.h"


//nyers szöveg beolvasása   
//nyers szöveg kódolása     
//kódolt szöveg kiírása


int Kodol(KodTabla *Tabla, char *szovegfajl, char *kiir){
    FILE *olv = fopen(szovegfajl, "rt");
    if(!olv) return 1;
    FILE *ir = fopen(kiir, "wt");
    if(!ir) return 1;
    
    for(char olvc = fgetc(olv); feof(olv); olvc = fgetc(olv)){
        MorzeKar *epp = KarKeres(Tabla,olvc);
        if(!epp)return 2;   //itt majd be kell kérni, ha nincs éppen karakter
        int kodhossz = strlen(epp->kod);
        for(int i = 0; i < kodhossz; i++)
            fputc(epp->kod[i], kiir);
    }
    return 0;

}