/*Preda Ioan Alexandru*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "thash.h"
#include "tlg.h"

typedef struct cuvinte
{
	char *s;
	int nr;
} TCuvinte;
typedef struct lungime
{
	int lung;
	TLG cuv;
} TLungime;
int cmpAlfa(void *e1, void *e2)
{
	TCuvinte *cuv1 = (TCuvinte *)e1;
	TCuvinte *cuv2 = (TCuvinte *)e2;
	if (strcmp(cuv1->s, cuv2->s) == 0)
		return 1;
	return 0;
}
int codHash(void *elem)
{
	char *s1 = (char *)elem;
	if (*s1 >= 'a' && *s1 <= 'z')
		return *s1 - 'a';
	else if (*s1 >= 'A' && *s1 <= 'Z')return *s1 - 'A';
	return 30;

}
int cmpLungime(void *e1, void *e2)
{
	TCuvinte *cuv1 = (TCuvinte *)e1;
	TCuvinte *cuv2 = (TCuvinte *)e2;
	return strlen(cuv1->s) - strlen(cuv2->s);
}
void eliberarecuvant(void *element1)
{
	free(((TCuvinte *)element1)->s);
	free((TCuvinte *)element1);
}
void eliberaresir(void *element2)
{
	DistrugeLG(&((TLungime *)element2)->cuv, eliberarecuvant);
	free((TLungime *)element2);
}
void afisarecuvinte(void *element)
{
	TCuvinte *cuvant = (TCuvinte *)element;
	printf("%s/%d, ", cuvant->s, cuvant->nr);
}

void afisarecuvinte2(void *element)
{
	TCuvinte *cuvant = (TCuvinte *)element;
	printf("%s/%d", cuvant->s, cuvant->nr);
}
void afisir(void *elem)
{
	TLungime *cuvi = (TLungime *)elem;
	printf("(%d:", cuvi->lung);
    TLG lis = cuvi->cuv;
	Afisare(&lis, afisarecuvinte, afisarecuvinte2);
    printf(")");
}
void afisarelitera(TH *a, void *c, void *x)
{
	int cod = a->h(c), x1 = *(char *)x - 48,sum = 0;
	char litera = *(char *)c;
	TLG sir1 = (TLG)a->v[cod];
	for (; sir1 != NULL; sir1 = sir1->urm)
	{
		TLungime *sir2 = (TLungime *)(sir1->info);
		if (sir2->lung == x1)
		{
			TLG lista1 = (TLG)sir2->cuv;
			for (; lista1 != NULL; lista1 = lista1->urm)
			{
				TCuvinte *cuvant = (TCuvinte *)(lista1->info);
				
					if(sum == 0)printf("(%d:",sir2->lung);
					else printf(", ");
					sum++;
					printf("%s/%d",cuvant->s, cuvant->nr);
					
				
			}
			if(sum != 0)printf(")\n");
		}
	}
}
void afisarelungime(TH *a, void *lit)
{
    char *s1 = (char *)lit;
	int x = atoi(s1), sum,sum1;
	int i;
	for(i = 0; i < a->M; i++)
	{ 
		TLG p = a->v[i];
		sum = 0;
		for (; p != NULL; p = p->urm)
		{  
			TLungime *cuvant = (TLungime *)p->info;
			TLG cuvant1 = (TLG)cuvant->cuv;
			sum1 = 0;
			for(;cuvant1 != NULL;cuvant1 = cuvant1->urm){
			
			TCuvinte *cuvant2 = (TCuvinte *)cuvant1->info;
			if (cuvant2->nr <= x)
			{    
				
				if (sum == 0){
					printf("pos%d: ", i);
				    sum++;
				}
				if (sum1 == 0){
					printf("(%d: ",cuvant->lung);
					sum1++;
				}
				else printf(", ");
				printf("%s/%d",cuvant2->s,cuvant2->nr);
				
			}
			
			}
			if(sum1 != 0)printf(")");
		}
		if(sum != 0)printf("\n");
	}
}
int complistamica(void *element1, void *element2)
{
	TCuvinte *cuvant1 = (TCuvinte *)element1;
	TCuvinte *cuvant2 = (TCuvinte *)element2;
	if (cuvant1->nr - cuvant2->nr <= 0)
		return 0;
	return -1;
}

void inserareintabela(TH *a, char *cuvant, int cod, int l)
{
	TCuvinte *listacuvinte = (TCuvinte *)malloc(sizeof(TCuvinte));
	listacuvinte->s = malloc(sizeof(char) * (strlen(cuvant) + 1));
	memcpy(listacuvinte->s, cuvant, strlen(cuvant) + 1);
	listacuvinte->nr = 1;
	TLG listasecundara = NULL;
	Ins_IncLG(&listasecundara, (void *)listacuvinte);
	TLungime *listaprincipala = (TLungime *)malloc(sizeof(TLungime));
	listaprincipala->lung = l;
	listaprincipala->cuv = listasecundara;
	Ins_IncLG(&(a->v[cod]), (void *)listaprincipala);
}
void insereaincuv(TLG *cuv, char *cuvant)
{
	TCuvinte *listacuv = (TCuvinte *)malloc(sizeof(TCuvinte));
	listacuv->s = malloc(sizeof(char) * (strlen(cuvant) + 1));
	memcpy(listacuv->s, cuvant, strlen(cuvant) + 1);
	listacuv->nr = 1;
	Ins_IncLG(cuv, (void *)listacuv);
}
int cmpCuv(void *s1, void *s2)
{
	TCuvinte *cuv1 = (TCuvinte *)s1;
	TCuvinte *cuv2 = (TCuvinte *)s2;
	if (strcmp(cuv1->s, cuv2->s) != 0)
		return 0;
	return 1;
}

int comparaCuv(void *s1, void *s2)
{
	TCuvinte *cuv1 = (TCuvinte *)s1;
	TCuvinte *cuv2 = (TCuvinte *)s2;
    if(cuv1->nr < cuv2->nr) return 1;
        else if(cuv1->nr > cuv2->nr) return 0;
        else
        {
            if(strcmp(cuv1->s, cuv2->s)<0) return 0;
                else return 1;
        }
}

int compararelungime(void *element1, void *element2)
{
	TLungime *sir1 = (TLungime *)element1;
	TLungime *sir2 = (TLungime *)element2;
	if (sir1->lung >= sir2->lung)
		return 0;
	return 1;
}

void interschimbare(void *s1, void *s2)
{
    TCuvinte *cuv1 = (TCuvinte *)s1;
	TCuvinte *cuv2 = (TCuvinte *)s2;
    TCuvinte aux;
    aux = *cuv1;
    *cuv1 = *cuv2;
    *cuv2 = aux;
}
void interschimbareMare(void *s1, void *s2)
{
    TLungime *cuv1 = (TLungime *)s1;
	TLungime *cuv2 = (TLungime *)s2;
    TLungime aux;
    aux = *cuv1;
    *cuv1 = *cuv2;
    *cuv2 = aux;
}

int main(int argc, char *input[])
{
	int i;
	TH *h1 = NULL;
	size_t M = ('Z' - 'A') + 1, len = 0;
	h1 = (TH *)InitTH(M, codHash);
	FILE *f = fopen(input[1], "rt");
	char *line = NULL, *p = NULL;
	while (getline(&line, &len, f) != -1)
	{
		p = strtok(line, " 125");
        
		if (strcmp(p, "insert") == 0)
		{
			p = strtok(NULL, "  125");
			if(codHash(p) != 30){
			while (p)
			{
				if (strlen(p) >= 3)
				{
					int cod = codHash(p);
					if (p[strlen(p) - 1] == '\n')p[strlen(p) - 1] = '\0';
                    if (!((p[strlen(p) - 1] >= 'a' && p[strlen(p) - 1] <= 'z') || 
                    (p[strlen(p) - 1] >= 'A' && p[strlen(p) - 1] <= 'Z'))) p[strlen(p) - 1] = '\0';
						int lungime = strlen(p);
						if (h1->v[cod] == NULL)
							inserareintabela(h1, p, cod, lungime);
						else
						{
							TLG sir1 = (TLG)h1->v[cod];
							int aparitie = 0;
							for (; sir1 != NULL; sir1 = sir1->urm)
							{
								TLungime *lista1 = (TLungime *)(sir1->info);
								if (lista1->lung == lungime)
								{
									aparitie = 1;
									TLG sir2 = (TLG)lista1->cuv;
									int aparitie1 = 0;
									for (; sir2 != NULL; sir2 = sir2->urm)
									{
										TCuvinte *cuvinte1 = (TCuvinte *)(sir2->info);
										if (strcmp(cuvinte1->s, p) == 0)
										{
											aparitie1++;
											cuvinte1->nr++;
										}
									}
									if (!aparitie1)
										insereaincuv(&(lista1->cuv), p);
                                    TLG l1 = (TLG)lista1->cuv, lista2;
                                    for (; l1 != NULL; l1 = l1->urm)
                                    {
                                        lista2 = l1;
                                        for (; lista2 != NULL; lista2 = lista2->urm)
                                        {

                                            if (comparaCuv(l1->info, lista2->info))
                                                interschimbare(l1->info, lista2->info);
                                        }
                                    }
                                }
								
							}
                            if (!aparitie)
									inserareintabela(h1, p, cod, lungime);
						}
					
				}
				p = strtok(NULL,"  125");
			}
		}
		}
		else if (strcmp(p, "print") == 0 || strcmp(p, "print\n") == 0)
		{
			p = strtok(NULL, "  ");
			int j;
			 for(j = 0; j < M; j++)
                {
                    TLG  listaMare = h1->v[j];
                    for(; listaMare!=NULL; listaMare= listaMare->urm)
                    {
                        TLungime * TL = (TLungime*) listaMare->info;
                        TLG lista1 = TL->cuv, lista2;
                        for (; lista1 != NULL; lista1 = lista1->urm)
                        {
                            lista2 = lista1;
                            for (; lista2 != NULL; lista2 = lista2->urm)
                            {

                                if (comparaCuv(lista1->info, lista2->info)) interschimbare(lista1->info, lista2->info);
                            }
                        }
                    }
                    listaMare = h1->v[j];
                    TLG listaMica;
                    for(; listaMare!=NULL; listaMare= listaMare->urm)
                    {
                        listaMica = listaMare;
                        for(; listaMica!=NULL; listaMica= listaMica->urm)
                        {
                            if (!compararelungime(listaMare->info, listaMica->info)) interschimbareMare(listaMare->info, listaMica->info);
                        }
                    }
                    
                }
			if (p == NULL)
            {
               
                AfiTH(h1, afisir);
            }
			
			else if ((p[0] >= 'A' && p[0] <= 'Z') || (p[0] >= 'a' && p[0] <= 'z'))
			{
                int cod = codHash((void *)p);
				char *s = p;
				p = strtok(NULL, " ");
				afisarelitera(h1,(void *)s, (void *)p);
			}
			else if (p[0] >= '0' && p[0] <= '9')
				afisarelungime(h1,(void*) p);
		}
	}
	free(line);
	DistrTH(&h1, eliberaresir);

  
}
