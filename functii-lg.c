/*Preda Ioan Alexandru*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "tlg.h"
int Ins_IncLG(TLG *aL,void *x)
{
    TLG aux = malloc(sizeof(TCelulaG));
    if(!aux)
    {
        printf("Alocarea a esuat");
        return 0;
    }
    aux->info = x;
    aux->urm = *aL;
    *aL = aux;
    return 1;
}
size_t lungime(TLG *aL)
{
    TLG p = *aL;
    size_t l = 0;
    for(; !p; p = p->urm)
    l++;
    return l;
}
void Afisare(TLG* aL, TF afiEL, TF afi2)
{
	if(!*aL) {
        printf("Lista vida\n");
        return;
    }

	for(; *aL; aL = &(*aL)->urm) {
		if((*aL)->urm == NULL) afi2((*aL)->info);
		else afiEL((*aL)->info);
    }
}
void DistrugeLG(TLG* aL, TF free_elem) /* distruge lista */
{
	while(*aL != NULL)
    {
        TLG aux = *aL;     /* adresa celulei eliminate */
        if (!aux)
            return;

        free_elem(aux->info);  /* elib.spatiul ocupat de element*/
        *aL = aux->urm;    /* deconecteaza celula din lista */
        free(aux);   /* elibereaza spatiul ocupat de celula */
    }
}
void InsOrdLG(TLG *aL,void *x,int (*comp)(void *,void *))
{
    TLG L = *aL,ant = NULL;
    TLG celula = malloc(sizeof(TCelulaG));
    if(!celula)
         return;
    celula->info = x;
    celula->urm = NULL;

    for(;L != NULL;ant = L,L = L->urm){
    if(comp(x,L->info) < 0)
    {
        celula->urm = L;
        if(ant == NULL){*aL = celula;}
        else 
        {
            ant->urm = celula;
        }
        return;
    } 
    }
    if(ant == NULL)
    {
        *aL = celula;
    }
    else
    {
        ant->urm = celula;
    }
}
void *CautaLG(TLG L,void *x,int (*fcmp)(void *,void *))
{
    TLG p = L;
    for(;L != NULL;L = L->urm){
        if(fcmp(x,L->info) == 1)return L->info;
    }
    return NULL;
}
