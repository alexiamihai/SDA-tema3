TEMA 3 - GRAFURI

STRUCTURI:
1. structura nod - contine numarul nodului, costul si un pointer catre vecinul
sau, pentru graful neorientat
2. structura noduri - contine numarul nodului scorul, adancimea, distanta
(costul), numele si un pointer catre vecinul sau, pentru graful orientat
3. structura graf - contine numarul de noduri si lista de adiacenta a grafului
(pentru graful neorientat)
4. structura graf_orientat - contine numarul de noduri si lista de adiacenta
a grafului (pentru graful orientat)

FUNCTII PENTRU CELE 2 TIPURI DE GRAFURI:
1. initializeaza_graf() si initializeaza_graf_orientat() -
functii care initializeaza un graf neorientat, respectiv unul orientat, alocand
memoria necesara pentru lista de adiacenta si initializand-o cu valori nule.

2. adauga_nod() si adauga_nod2 - functii care adauga un nod in lista de
adiacenta a grafului neorientat, respectiv a celui orientat, atribuindu-i
valorile corespunzatoare, precum numarul, costul si vecinii.

3. adauga_muchie() si adauga_muchie2() - functii care adauga o muchie intre 2
noduri din graf, fie bidirectionala, in cazul grafului neorientat, fie
unidirectionala, in cazul celui orientat. Nodul j este adaugat in lista de
adiacenta a nodului i, iar nodul i este adaugat in lista de adiacenta a nodului
j, in cazul grafului neorientat. In cazul grafului orientat, nodul j este
adaugat in lista de adiacenta a nodului i.

4. free_graf() si free_graf_orientat() - functii care elibereaza memoria
alocata pentru lista de adiacenta a grafului neorientat, respectiv a celui
orientat.

FUNCTII PENTRU CERINTA 1:

1. dfs() - functie care realizeaza parcurgerea in adancime a grafului
neorientat, pornind de la un nod specificat ca parametru. Marcheaza nodurile
vizitate si calculeaza numarul de noduri din componenta conexa curenta, iar apoi
apeleaza recursiv functia pentru fiecare vecin nevizitat al nodului curent.

2. componente_conexe() - functie care calculeaza numarul de componente conexe
ale grafului neorientat, apeland functia dfs() pentru fiecare nod nevizitat.
Am utilizat dfs() pentru a gasi toate componentele conexe si am salvat parintele
si numarul de noduri din fiecare componenta conexa.

3. algoritm_prim() - functie care implementeaza algoritmul lui prim pentru
determinarea arborelui minim de acoperire, adica a unui drum de cost minim in
graful neorientat. Am initializat un vector de vizitati, pentru a marca nodurile
vizitate si un vector de costuri, pentru a retine costul minim al drumului de la
nodul de start la fiecare nod. Am initializat costul minim al drumului de la
nodul de start la el insusi cu 0, iar costul minim al drumului de la nodul de
start la celelalte noduri cu o valoare foarte mare. Am parcurs apoi graful
pentru a determina costul minim al drumului, cautand nodul cu costul minim si
actualizand costul minim al drumului de la nodul de start la fiecare nod
adiacent.

FUNCTII PENTRU CERINTA 2:

1. dijkstra() - functie care implementeaza algoritmul lui dijkstra pentru a
determina drumul de scor minim intre 2 noduri in graful orientat. Am cautat
nodurile de start si de final, transmise ca siruri de caractere, in matricea in
care am retinut numele tuturor nodurilor grafului. Pentru fiecare nod am
determinat scorurile si distantele minime, utilizand vectori de scoruri,
distante si parinti, initializati cu valori foarte mari, respectiv cu -1.
In cazul in care am gasit un drum de la start la end, am reconstruit calea,
retinand numele nodurilor intr-un vector, folosindu-ma de pozitiile numelor in
matricea de siruri pentru a le recunoaste dupa indicele lor. In cazul in care nu
am gasit un drum de la start la end, costul total, retinut in parametrul
distanta, se va intoarce in main cu o valoare foarte mare, ce va indica faptul
ca nu exista drum de la start la end.

MAIN:

    Am verificat mai intai cerinta care trebuie rezolvata.
    Pentru cerinta 1:
    Am citit numarul de noduri si numarul de muchii ale grafului neorientat si
am alocat memorie pentru graf si pentru o matrice in care am retinut numele
obiectivelor. Am citit apoi numele obiectivelor si le-am retinut in matricea de
siruri, verificand mai intai daca numele fusese deja adaugat in matrice si
retinand indicele asociat numelui, pentru a putea adauga apoi muchia in graf.
    Am apelat functia componente_conexe() pentru a calcula numarul de componente
conexe ale grafului neorientat si am afisat numarul determinat in fisier.
    Am calculat costul total al renovarii drumului, pentru fiecare componenta
conexa, utilizand algoritmul lui prim, salvand costurile determinate intr-un
vector. Inainte de a afisa valorile determinate, am sortat vectorul.
    Pentru cerinta 2:
    Am citit numarul de noduri si numarul de muchii ale grafului orientat si
am alocat memorie pentru graf si pentru o matrice in care am retinut numele
nodurilor. Am initializat graful si am adaugat nodurile si muchiile
corespunzatoare, folosind un procedeu asemanaor celui de la cerinta 1.
    Am citit apoi adancimile fiecarui nod si le-am retinut in cadrul structurii,
pentru fiecare nod, cautand nodul in lista de adiacenta a grafului.
    Am citit apoi greutatea comoarei.
    Am calculat scorul fiecarui nod din lista de adiacenta, folosind formula
data.
    Am verificat, mai intai, daca exista o cale de la "Corabie" la "Insula",
apeland functia dijkstra(), care returneaza o valoare mare pentru parametrul
cost_total, in cazul in care nu poate determina un drum. In cazul in care nu
exista drumul, am afisat un mesaj care semnaleaza acest lucru si am terminat
executia programului.
    In cazul in care exista, am apelat functia dijkstra() pentru a determina
drumul de scor minim de la "Insula" la "Corabie", retinand in vectorul
cale drumul determinat. In cazul in care, nu exista o cale intre cele 2 noduri,
am afisat un mesaj care semnaleaza acest lucru si am oprit executia programului.
Altfel, am calculat adancimea minima de pe calea determinata, excluzand nodurile
de start si stop, care au adancimea 1. Am afisat apoi, calea de la "Insula" la
"Corabie", adancimea minima si costul total al caii. Am calculat numarul de
drumuri necesare pentru a transporta comoara, impartind greutatea comoarei la
adancimea minimaa de pe calea determinata, rotunjind rezultatul la urmatorul
numar intreg.
    Am eliberat memoria alocata pentru graf si pentru matricea de siruri.
