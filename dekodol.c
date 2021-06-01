#include <stdio.h>
#include <stdbool.h>
#include "dekodol.h"
#include "morzekod.h"




//kódtábla beolvasása       [-]
//kódolt szöveg beolvasása  [-]
//kódolt szöveg dekódolása  [-]
//dekódolt szöveg kiírása   [-]



int Dekodol(KodTabla *Tabla, char *kodolt, char *kiir){
    FILE *olv = fopen(kodolt, "rt");
    if(!olv) return 1;
    FILE *ir = fopen(kiir, "wt");
    if(!ir) return 1;
    char* puffer = malloc(Tabla->maxkod * sizeof(char));
    int karszam = 0;
    char koz = KarKeres(Tabla, ' ')->kod;
    for(char olvc = fgetc(olv); feof(olv); olvc = fgetc(olv), karszam++){
        if(olvc == koz){
            puffer[karszam+1] = '\0';
            MorzeKar *ir = KodKeres(Tabla, puffer);
            if(!ir){
                    fclose(kiir);
                    fclose(olv);
                    return 2;
            }
            fputc(ir->karakter, kiir);
            fputc(' ', kiir);
            }
        else{
            puffer[karszam] = olvc;
        }
    }
    fclose(kiir);
    fclose(olv);
    return 0;

}