#ifndef MORZEKOD_H_INCLUDED
#define MORZEKOD_H_INCLUDED


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
 * @brief Morzekód-karaktereket tartalmazó tábla
 *
 */
typedef struct KodTabla{
    MorzeKar *eleje;
    MorzeKar *vege;
    int maxkod;
    int count;
} KodTabla;

KodTabla *UjTabla(void);

/**
 * @brief Megkeres egy karakterű elemet a listában. Lineáris, mert 
 * 
 * @param tabla A kódtábla, amely a karaktereket tartalmazza
 * @param kar A keresett karakter
 * @return Morzekar* Ha van, ->karakter == kar, ha nincs akkor NULL
 */

MorzeKar *KarKeres(KodTabla *tabla, char kar);
/**
 * @brief Megkeres egy karakterű elemet a listában. Lineáris, mert 
 * 
 * @param tabla A kódtábla, amely a karaktereket tartalmazza
 * @param kar A keresett karakter
 * @return Morzekar* Ha van, ->karakter == kar, ha nincs akkor NULL
 */

MorzeKar *KodKeres(KodTabla *tabla, char* kod);
/**
 * @brief Beolvassa a kódtáblát
 *
 * @param hely
 * @return KodTabla*
 */
KodTabla *Tbeolvas(char* hely);

void ListaDestroy(KodTabla *Tabla);

#endif // MORZEKOD_H_INCLUDED
