/*Preda Ioan Alexandru*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#ifndef _LISTA_GENERICA_
#define _LISTA_GENERICA_

typedef struct listacuvinte
{
    void* info;
    struct listacuvinte *urm;
}TCelulaG,*TLG;

typedef int (*TFElem)(void*);     /* functie prelucrare element */
typedef int (*TFCmp)(void*, void*); /* functie de comparare doua elemente */
typedef void (*TF)(void*);     /* functie afisare/eliberare un element */

/* functii lista generica */
int Ins_IncLG(TLG*, void*);  /*- inserare la inceput reusita sau nu (1/0) -*/
void DistrugeLG(TLG* aL, TF fe); /* distruge lista */
/* afiseaza elementele din lista, folosind o functie de tip TFAfi */
void Afisare(TLG*al, TF afiel, TF afi2);
void InsOrdLG(TLG *aL,void *ae,int (*comp)(void*, void*));
void* CautaLG(TLG L,void *x,int (*fcmp)(void*,void*));
#endif
