#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "morzekod.h"

//félig VSCode-al csináltam, mert egy csomó hibár rögtön jelez
//lehet, hogy írok pár felesleges listafüggvényt, de ha nincsenek meg, az zavar, mert c#-ban - amit tanultam - csomó minden volt.

//Feladatok:
    //adatszerkezet [+]
    //I/O:          [/] v
    //Kódolás:      [/]  >Optimális eset először
    //Dekódolás:    [/] ^
    //hibakezekés:  [/]

//a kodolt és a dekodolt majd egybeteszem, és a hibakezelésnek/menürendszernek lesz még egy külön .c(ami nem class mert itt nincsenek olyanok)

/** \brief A fő függvény
 *
 * \param paraméterek száma
 * \param paramétertömb
 * \return hibakód
 *
 */

int Kodol(KodTabla *Tabla, char *szovegfajl, char *irfajl){
    FILE *folv = fopen(szovegfajl, "rt");
    if(!folv) return 1;
    FILE *ir = fopen(irfajl, "wt");
    if(!ir) return 1;

    for(char folvc = fgetc(folv); !feof(folv); folvc = fgetc(folv)){
        MorzeKar *epp = KarKeres(Tabla,folvc);
        if(!epp)return 2;   //itt majd be kell kérni, ha nincs éppen karakter
        int kodhossz = strlen(epp->kod);
        for(int i = 0; i < kodhossz; i++)
            fputc((int)epp->kod[i], ir);
        fputc(' ', ir);
    }
    fclose(ir);
    fclose(folv);
    return 0;

}

int Dekodol(KodTabla *Tabla, char *kodolt, char *irfajl){
    FILE *folv = fopen(kodolt, "rt");
    if(!folv) return 1;
    FILE *fir = fopen(irfajl, "wt");
    if(!fir) return 1;
    char* puffer = malloc(Tabla->maxkod * sizeof(char));
    int karszam = 0;
    char koz = (KarKeres(Tabla, ' ')->kod[0]);
    for(char folvc = fgetc(folv); !feof(folv); folvc = fgetc(folv), karszam++){
        if(folvc == ' '){
            puffer[karszam] = '\0';
            MorzeKar *ir = KodKeres(Tabla, puffer);
            if(!ir){
                    fclose(fir);
                    fclose(folv);
                    return 2;
            }
            fputc(ir->karakter, fir);
            karszam = -1;
        }
        else{
            puffer[karszam] = folvc;
        }
    }
    fclose(fir);
    fclose(folv);
    return 0;

}

int main(int argc, char *argv[])
{
    //miért nem lehet switchen belül deklarálni? :(
    if(argc < 4 || argc > 5){
        printf("Morze kódoló/dekódoló 0.1 By Endrődi Balazs\n"
            "Hasznalat:\n morze -enc tablafajl szovegfajl [kimenet]\n"
            "\t megadott szovegfalj morzeve alakitasa. A kimenet parameter opcionalis, nelkule szovegfajl.mrz lesz.\n"
            " morze -dec tablafajl morzefajl [kimenet]\n"
            "\t megadott kodolt morzefajl szovegge visszaalakitasa. A kimenet parameter opcionalis, nelkule morzefajl.mrz lesz.\n"
            "A .mrz fajlok egyszeru szovegfajlok.");

    }
    else{
        int tblbe = strlen(argv[2]);
        char* tblnev = malloc((tblbe+1)*sizeof(char));
        //strcpy(tblnev, ".\\");
        strcpy(tblnev, argv[2]);
        KodTabla *tabla = Tbeolvas(tblnev);
        if(!tabla){
            return 2;
        }
        int hosszbe = strlen(argv[3]);
        int hosszki = argc == 4 ? strlen(argv[3])+7 : strlen(argv[4]);
        char* benev = malloc((hosszbe+7)*sizeof(char));
        char* kinev = malloc((hosszki+7)*sizeof(char));
        //strcpy(benev, ".\\");
        //strcpy(kinev, ".\\");
        strcpy(benev, argv[3]);
        if(argc == 4){
            strcpy(kinev, argv[3]);
            strcat(kinev,".mrz");
        }
        else
            strcpy(kinev, argv[5]);

        if(strcmp(argv[1], "-enc") == 0){   //kódolás
            if(Kodol(tabla, benev,kinev)){
                free(benev);
                free(kinev);
                ListaDestroy(tabla);
                return 0;
            }
            else{
                ListaDestroy(tabla);
                free(benev);
                free(kinev);
                return 1;
            }
        }
        else if(strcmp(argv[1], "-dec") == 0){   //kódolás
            if(Dekodol(tabla, benev,kinev)){
                ListaDestroy(tabla);
                free(benev);
                free(kinev);
                return 0;
            }
            else{
                ListaDestroy(tabla);
                free(benev);
                free(kinev);
                return 1;
            }
        }
    }
    return 0;
}
