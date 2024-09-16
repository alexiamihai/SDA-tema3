#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* am reprezentat graful neorientat pt cerinta 1 printr-o lista de adiacenta
fiecare nod are un nume, un numar asociat, un cost si o lista de vecini */

typedef struct nod
{
    char nume[20];
    int nr;
    int cost;
    struct nod *next;
} nod;

typedef struct graf
{
    int n;
    nod **lista;
} graf;

/*  am reprezentat graful orientat pt cerinta 2 printr-o lista de adiacenta
fiecare nod are un nume, un numar asociat, un scor, o adancime, o distanta
asociata si o lista de vecini */

typedef struct noduri
{
    char nume[20];
    int nr;
    float scor;
    int adancime;
    int distanta;
    struct noduri *next;
} noduri;

typedef struct graf_orientat
{
    int n;
    noduri **lista2;
} graf_orientat;

// functie pentru initializarea grafului neorientat
void initializeaza_graf(graf *g, int n)
{
    int i;
    g->n = n;
    // am alocat memorie pentru lista de adiacenta
    g->lista = calloc(n, sizeof(nod *));
    for (i = 0; i < n; i++)
    {
        g->lista[i] = NULL;
    }
}
// functie pentru adaugarea unui nod in graful neorientat
nod *adauga_nod(graf *g, int i, int cost)
{
    // am alocat memorie pentru nod si am salvat in campurile structurii datele
    nod *nou = calloc(1, sizeof(nod));
    nou->nr = i;
    nou->cost = cost;
    nou->next = NULL;
    return nou;
}
// functie pentru adaugarea unei muchii in graful neorientat
void adauga_muchie_bi(graf *g, int i, int j, int cost)
{
    // am adaugat nodul j in lista de vecini a nodului i si invers
    nod *nou = adauga_nod(g, i, cost);
    nou->next = g->lista[j];
    g->lista[j] = nou;
    nod *nou2 = adauga_nod(g, j, cost);
    nou2->next = g->lista[i];
    g->lista[i] = nou2;
}
// functie pentru parcurgerea in adancime a grafului neorientat
void dfs(graf *g, int i, int vizitat[], int *noduri)
{
    // am marcat nodul curent ca fiind vizitat
    vizitat[i] = 1;
    // am incrementat numarul de noduri din componenta conexa curenta
    (*noduri)++;
    // am accesat lista de vecini a nodului curent
    nod *aux = g->lista[i];
    while (aux != NULL)
    {
        // daca vecinul nu a fost vizitat, am aplicat dfs pe el
        if (vizitat[aux->nr] == 0)
        {
            dfs(g, aux->nr, vizitat, noduri);
        }
        aux = aux->next;
    }
}
// functie pentru determinarea componentelor conexe ale grafului neorientat
void componente_conexe(graf *g, int *nr_componente, int parinti[], int noduri[])
{
    int vizitati[g->n];
    int i;
    *nr_componente = 0;
    // am initializat vectorul de vizitati cu 0
    for (i = 0; i < g->n; i++)
    {
        vizitati[i] = 0;
    }
    // am parcurs graful si am aplicat dfs pe nodurile nevizitate
    for (i = 0; i < g->n; i++)
    {
        if (vizitati[i] == 0)
        {
            // am salvat parintele si numarul de noduri din componenta
            // conexa curenta
            parinti[*nr_componente] = i;
            noduri[*nr_componente] = 0;
            (*nr_componente)++;
            dfs(g, i, vizitati, &noduri[*nr_componente - 1]);
        }
    }
}
// functie pentru determinarea costului minim al drumului
void algoritm_prim(graf *g, int *cost_total, int sursa, int noduri)
{
    int i, j, k, min, cost;
    int vizitat[g->n], costuri[g->n];
    // am initializat vectorii de vizitati cu 0 si cel de costuri cu 99999
    for (i = 0; i < g->n; i++)
    {
        vizitat[i] = 0;
        costuri[i] = 99999;
    }
    // am marcat nodul sursa ca vizitat si am initializat costul de la sursa la
    // el insusi cu 0
    costuri[sursa] = 0;
    // am parcurs graful pentru a determina costul minim al drumului
    for (i = 0; i < noduri; i++)
    {
        min = 99999;
        for (j = 0; j < g->n; j++)
        {
            // am cautat nodul nevizitat cu costul minim de la sursa
            if (vizitat[j] == 0 && costuri[j] < min)
            {
                min = costuri[j];
                k = j;
            }
        }
        // am marcat nodul gasit ca vizitat si am adaugat costul la costul total
        vizitat[k] = 1;
        cost = costuri[k];
        *cost_total = (*cost_total) + cost;
        // am actualizat costurile vecinilor nodului gasit
        nod *aux = g->lista[k];
        while (aux != NULL)
        {
            // am verificat daca vecinul nu a fost vizitat si daca costul este
            // mai mic decat valoarea din vectorul de costuri
            if (vizitat[aux->nr] == 0 && aux->cost < costuri[aux->nr])
            {
                costuri[aux->nr] = aux->cost;
            }
            aux = aux->next;
        }
    }
}
// functie pentru initializarea grafului orientat
void initializeaza_graf_orientat(graf_orientat *g, int n)
{
    int i;
    g->n = n;
    // am alocat memorie pentru lista de adiacenta
    g->lista2 = calloc(n, sizeof(noduri *));
    for (i = 0; i < n; i++)
    {
        g->lista2[i] = NULL;
    }
}
// functie pentru adaugarea unui nod in graful orientat
noduri *adauga_nod2(graf_orientat *g, char nume[], int distanta, int k)
{
    // am alocat memorie pentru nod si am salvat in campurile structurii datele
    noduri *nou = calloc(1, sizeof(noduri));
    strcpy(nou->nume, nume);
    nou->distanta = distanta;
    nou->nr = k;
    nou->next = NULL;
    return nou;
}
// functie pentru adaugarea unei muchii in graful orientat
void adauga_muchie_uni(graf_orientat *g, char nume1[], char nume2[],
 int distanta, int i, int j)
{
    // am adaugat nodul j in lista de vecini a nodului i
    noduri *nou2 = adauga_nod2(g, nume2, distanta, j);
    nou2->next = g->lista2[i];
    g->lista2[i] = nou2;
}
// functie pentru determinarea drumului de scor minim
void dijkstra(graf_orientat *g, char start[], char end[], char **cale,
 int *lungime_cale, char **siruri, int *distanta)
{
    int i, j, k, start_nr, end_nr = -1;
    float scoruri[g->n];
    int distante[g->n], prev[g->n], vizitat[g->n];
    *lungime_cale = 0;
    // am initializat vectorii de scoruri, distante, parinti si vizitati
    for (i = 0; i < g->n; i++)
    {
        distante[i] = 99999;
        scoruri[i] = 99999;
        prev[i] = -1;
        vizitat[i] = 0;
    }
    // am cautat nodul de start si am initializat scorul si distanta lui cu 0
    for (i = 0; i < g->n; i++)
    {
        if (strcmp(siruri[i], start) == 0)
        {
            scoruri[i] = 0;
            start_nr = i;
            distante[i] = 0;
            break;
        }
    }
    // am parcurs graful pentru a determina drumul de scor minim
    for (i = 0; i < g->n; i++)
    {
        // am initializat scorul minim cu o valoare foarte mare
        float min_scor = 99999;
        k = -1;
        // am cautat nodul nevizitat cu scorul minim
        for (j = 0; j < g->n; j++)
        {
            if (vizitat[j] == 0 && scoruri[j] < min_scor)
            {
                min_scor = scoruri[j];
                k = j;
            }
        }
        // daca nu s-a gasit niciun nod nevizitat, am iesit din bucla
        if (k == -1)
        {
            break;
        }
        // altfel, am marcat nodul gasit ca vizitat
        vizitat[k] = 1;
        // am actualizat scorurile vecinilor nodului gasit
        noduri *aux = g->lista2[k];
        while (aux != NULL)
        {
            // am verificat daca vecinul nu a fost vizitat si daca scorul poate
            // fi imbunatatit
            if (vizitat[aux->nr] == 0)
            {
                if (scoruri[k] + aux->scor < scoruri[aux->nr])
                {
                    scoruri[aux->nr] = scoruri[k] + aux->scor;
                    // am actualizat si distanta si parintele
                    distante[aux->nr] = distante[k] + aux->distanta;
                    prev[aux->nr] = k;
                }
            }
            aux = aux->next;
        }
    }

    for (i = 0; i < g->n; i++)
    {
        // am cautat nodul de end si am salvat distanta pana la el, ce va fi
        // trimisa ca parametru in main
        if (strcmp(siruri[i], end) == 0)
        {
            if (scoruri[i] == 99999)
            {
                *distanta = 99999;
            }
            else
            {
                *distanta = distante[i];
                end_nr = i;
            }
            break;
        }
    }
    // daca s-a gasit drum pana la nodul final, am construit calea de la end
    // la start
    if (end_nr != -1)
    {
        // am parcurs vectorul de parinti pana la nodul de start
        while (end_nr != start_nr)
        {
            // am retinut numele fiecarui nod din cale
            strcpy(cale[*(lungime_cale)], siruri[end_nr]);
            (*lungime_cale)++;
            // am actualizat nodul curent cu parintele sau
            end_nr = prev[end_nr];
        }
        // am retinut numele nodului de start
        strcpy(cale[*(lungime_cale)], siruri[start_nr]);
        (*lungime_cale)++;
    }
}
// functie pentru eliberarea memoriei alocata pentru graful neoerientat
void free_graf(graf *g)
{
    int i;
    nod *aux, *aux2;
    for (i = 0; i < g->n; i++)
    {
        aux = g->lista[i];
        while (aux != NULL)
        {
            aux2 = aux;
            aux = aux->next;
            free(aux2);
        }
    }
    free(g->lista);
    free(g);
}
// functie pentru eliberarea memoriei alocata pentru graful orientat
void free_graf_orientat(graf_orientat *g)
{
    int i;
    noduri *aux, *aux2;
    for (i = 0; i < g->n; i++)
    {
        aux = g->lista2[i];
        while (aux != NULL)
        {
            aux2 = aux;
            aux = aux->next;
            free(aux2);
        }
    }
    free(g->lista2);
    free(g);
}
// functie pentru eliberarea memoriei alocate pentru matricea de siruri
void free_matrice(char **nume, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        free(nume[i]);
    }
    free(nume);
}

int main(int argc, char *argv[])
{
    int N, M, i, j, k = 0, cost, ok1, ok2, nod1, nod2, nr_componente,
                    cost_total = 0, distanta, a, greutate;
    char obj1[20], obj2[20];
    FILE *f = fopen("tema3.in", "r");
    FILE *f1 = fopen("tema3.out", "w");
    // cazul in care se cere rezolvarea cerintei 1
    if (strcmp(argv[1], "1") == 0)
    {
        fscanf(f, "%d %d", &N, &M);
        // am alocat memorie pentru graful neorientat
        graf *g = calloc(1, sizeof(graf));
        // am alocat memorie pentru matricea in care o sa retin numele
        // obiectivelor
        char **nume = calloc(N, sizeof(char *));
        // am initializat graful
        initializeaza_graf(g, N);
        for (i = 0; i < M; i++)
        {
            // am citit numele obiectivelor si costul drumului dintre ele
            fscanf(f, "%s %s %d", obj1, obj2, &cost);
            // variabilele ok vor arata daca numele se afla deja in matrice
            ok1 = 0;
            ok2 = 0;
            for (j = 0; j < k; j++)
            {
                // daca primul nume se afla deja in matrice, retin pozitia
                if (strcmp(obj1, nume[j]) == 0)
                {
                    ok1 = 1;
                    nod1 = j;
                    break;
                }
            }
            for (j = 0; j < k; j++)
            {
                // daca al doilea nume se afla deja in matrice, retin pozitia
                if (strcmp(obj2, nume[j]) == 0)
                {
                    ok2 = 1;
                    nod2 = j;
                    break;
                }
            }
            // daca primul nume nu se afla in matrice, il adaug si retin pozitia
            if (ok1 == 0)
            {
                nume[k] = malloc(20 * sizeof(char));
                strcpy(nume[k], obj1);
                nod1 = k;
                k++;
            }
            // daca al doilea nume nu se afla in matrice, il adaug si ii
            // retin pozitia
            if (ok2 == 0)
            {
                nume[k] = malloc(20 * sizeof(char));
                strcpy(nume[k], obj2);
                nod2 = k;
                k++;
            }
            // am adaugat muchia in graful neorientat, folosindu-ma de pozitiile
            // retinute
            adauga_muchie_bi(g, nod1, nod2, cost);
        }
        int parinti[g->n], noduri[g->n];
        // am determinat componentele conexe ale grafului si le-am afisat
        componente_conexe(g, &nr_componente, parinti, noduri);
        fprintf(f1, "%d\n", nr_componente);
        int costuri[nr_componente];
        // am determinat costul total pentru fiecare componenta conexa
        // determinata anterior
        for (i = 0; i < nr_componente; i++)
        {
            algoritm_prim(g, &cost_total, parinti[i], noduri[i]);
            // am retinut costul total pentru fiecare componenta conexa intr-un
            // vector
            costuri[i] = cost_total;
            cost_total = 0;
        }
        // am sortat vectorul de costuri
        for (i = 0; i < nr_componente - 1; i++)
        {
            for (j = i + 1; j < nr_componente; j++)
            {
                if (costuri[i] > costuri[j])
                {
                    int aux = costuri[i];
                    costuri[i] = costuri[j];
                    costuri[j] = aux;
                }
            }
        }
        // am afisat costurile in fisier
        for (i = 0; i < nr_componente; i++)
        {
            fprintf(f1, "%d\n", costuri[i]);
        }
        // am eliberat memoria alocata
        free_graf(g);
        free_matrice(nume, N);
    }
    // cazul in care se cere rezolvarea cerintei 2
    else
    {
        k = 0;
        fscanf(f, "%d %d", &N, &M);
        // am alocat memorie pentru graful orientat
        graf_orientat *g1 = calloc(1, sizeof(graf));
        // am alocat memorie pentru matricea in care o sa retin numele nodurilor
        char **siruri = malloc(N * sizeof(char *));
        // am initializat graful orientat
        initializeaza_graf_orientat(g1, N);
        for (i = 0; i < M; i++)
        {
            // am citit numele nodurilor si distanta dintre acestea
            fscanf(f, "%s %s %d", obj1, obj2, &distanta);
            // variabilele ok vor arata daca numele se afla deja in matrice
            ok1 = 0;
            ok2 = 0;
            for (j = 0; j < k; j++)
            {
                // daca primul nume se afla deja in matrice, retin pozitia
                if (strcmp(obj1, siruri[j]) == 0)
                {
                    ok1 = 1;
                    nod1 = j;
                    break;
                }
            }
            for (j = 0; j < k; j++)
            {
                // daca al doilea nume se afla deja in matrice, retin pozitia
                if (strcmp(obj2, siruri[j]) == 0)
                {
                    ok2 = 1;
                    nod2 = j;
                    break;
                }
            }
            // daca primul nume nu se afla in matrice, il adaug si retin pozitia
            if (ok1 == 0)
            {
                siruri[k] = malloc(20 * sizeof(char));
                strcpy(siruri[k], obj1);
                nod1 = k;
                k++;
            }
            // daca al doilea nume nu se afla in matrice, il adaug si ii
            // retin pozitia
            if (ok2 == 0)
            {
                siruri[k] = malloc(20 * sizeof(char));
                strcpy(siruri[k], obj2);
                nod2 = k;
                k++;
            }
            // am adaugat muchia in graful orientat, folosindu-ma de pozitiile
            // retinute
            adauga_muchie_uni(g1, siruri[nod1], siruri[nod2], distanta, nod1,
            nod2);
        }
        for (i = 0; i < N; i++)
        {
            // am citit adancimea fiecarui nod
            fscanf(f, "%s %d", obj1, &a);
            // am cautat nodul in lista de adiacenta si i-am atribuit adancimea
            for (j = 0; j < N; j++)
            {
                noduri *aux = g1->lista2[j];
                while (aux != NULL)
                {
                    if (strcmp(obj1, aux->nume) == 0)
                    {
                        aux->adancime = a;
                        break;
                    }
                    aux = aux->next;
                }
            }
        }
        // am citit greutatea comoarei
        fscanf(f, "%d", &greutate);
        // am calculat scorul fiecarui nod din lista de adiacenta
        for (i = 0; i < M; i++)
        {
            for (j = 0; j < N; j++)
            {
                // am parcurs lista de vecini a fiecarui nod
                noduri *aux = g1->lista2[j];
                while (aux != NULL)
                {
                    // am calculat scorul dupa formula data
                    aux->scor = (float)aux->distanta / (float)aux->adancime;
                    aux = aux->next;
                }
            }
        }
        int min_adancime, lungime_cale = 0;
        cost_total = 0;
        // am alocat memorie pentru calea de la corabie la insula si invers
        char **cale = malloc(N*sizeof(char *));
        for (i = 0; i < N; i++)
        {
            cale[i] = malloc(20*sizeof(char));
        }
        // am determinat calea de la corabie la insula
        dijkstra(g1, "Corabie", "Insula", cale, &lungime_cale, siruri,
         &cost_total);
        // daca nu exista drum de la corabie la insula, afisez mesajul
        // corespunzator
        if (cost_total == 99999)
        {
            fprintf(f1, "Echipajul nu poate ajunge la insula\n");
            free_matrice(cale, N);
            free_matrice(siruri, N);
            free_graf_orientat(g1);
            return 0;
        }
        lungime_cale = 0;
        cost_total = 0;
        // am determinat calea de la insula la corabie
        dijkstra(g1, "Insula", "Corabie", cale, &lungime_cale, siruri,
        &cost_total);
        // daca nu exista drum de la insula la corabie, afisez mesajul
        // corespunzator
        if (cost_total == 99999)
        {
            fprintf(f1,
            "Echipajul nu poate transporta comoara inapoi la corabie\n");
            free_matrice(cale, N);
            free_matrice(siruri, N);
            free_graf_orientat(g1);
            return 0;
        }
        min_adancime = 99999;
        // calculez adancimea minima de pe calea de la insula la corabie,
        // excluzand nodurile de start si de end
        for (i = lungime_cale - 2; i >= 1; i--)
        {
            for (j = 0; j < g1->n; j++)
            {
                // am parcurs lista de vecini a fiecarui nod
                noduri *aux = g1->lista2[j];
                while (aux != NULL)
                {
                    // am cautat nodul in lista de vecini a nodului curent
                    if (strcmp(cale[i], aux->nume) == 0)
                    {
                        // am verificat daca adancimea lui este mai mica decat
                        // minimul curent
                        if (aux->adancime < min_adancime)
                        {
                            min_adancime = aux->adancime;
                        }
                        break;
                    }
                    aux = aux->next;
                }
            }
        }
        // am afisat calea de la insula la corabie
        for (i = lungime_cale - 1; i >= 0; i--)
        {
            fprintf(f1, "%s ", cale[i]);
        }
        fprintf(f1, "\n");
        // am afisat costul total al drumului
        fprintf(f1, "%d\n", cost_total);
        // am afisat adancimea minima
        fprintf(f1, "%d\n", min_adancime);
        int nr_drumuri;
        // am calculat numarul de drumuri necesare pentru a transporta comoara
        nr_drumuri = greutate / min_adancime;
        // daca nu se poate transporta comoara cu numarul de drumuri calculat,
        // incrementez numarul de drumuri
        if (nr_drumuri * min_adancime != greutate)
        {
            nr_drumuri++;
        }
        // am afisat numarul de drumuri necesare
        fprintf(f1, "%d\n", nr_drumuri);
        // am eliberat memoria alocata
        free_matrice(cale, N);
        free_matrice(siruri, N);
        free_graf_orientat(g1);
    }
    fclose(f);
    fclose(f1);
    return 0;
}