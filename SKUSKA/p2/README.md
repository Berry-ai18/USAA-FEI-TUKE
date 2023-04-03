# P2 Huffmanovo Dekodovanie:

## Zadanie

Na vstupe dostanete Huffmanov strom a zakódovaný reťazec. Dekódujte reťazec zložený z núl a jednotiek na poslednom riadku vstupu.

Huffmanov strom je zapísaný vo formáte preorder. Ľavá strana znamená predponu 0, pravá strana predponu 1.

Huffmanov strom bude zadaný v preorder formáte. Každý uzol bude na samostatnom riadku. Nelistový uzol bude značený ako #, listový uzol bude znak anglickej abecedy alebo cifra.

V prípade, že strom nebude kompletný, vypíšte chybovú správu a ukončite program. V prípade, že nebude možné rozkódovať postupnosť núl a jednotiek, vypíšte chybovú správu a ukončite program.

V príprade, že na posledom riadku sa nachádza iný znak ako nula a jednotka vypíšte o tom správu a ukončite program.

- program pri správnom strome sa správa ako má
- ak je zlý vstup/strom tak to nedokáže rozoznať
- vie detegovať zlé znaky v kóde

## Implementácia

Program obsahuje 2 štruktúry, 3 funkcie a main

- struct tree - štruktúra ktorá obsahuje hodnotu uzla a poduzly

- struct tree *read_tree() - funkcia ktorá načíta a následne vracia strom

- void read_string(char* code) - načítava si posledný riadok na vstupe a uloží ho do premennej code

- void destroy_tree(struct tree *tree) - rekurzivne volá samú seba a uvoľnuje pamäť

- int traverse_tree(struct tree *node, char* code, int start) - funkcia na pohyb po strome 0 = do ľava a 1 = do prava

- int main() - nacitame strom, nacitame kod, následne sa pohybujeme po dlžke Code - 1(newline), ak narazíme na LF alebo CF tak sa nám cyklus zastaví a zavolá sa traverse tree ktorá nám dekóduje náš strom a vypíše dekódovaný string na štandardný 
výstup.

### Zdroje

- moje zadanie fruit expert
- https://student.kemt.fei.tuke.sk/usaa