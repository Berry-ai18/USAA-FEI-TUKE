

# R2 Kompresor
### Zadanie

Naprogramuj nástroj na kompresiu a dekompresiu. Na kompresiu použite aspoň dva kompresné algoritmy, napr. : Huffmanovo kódovanie, LZ77, LZ78, Run Length kódovanie alebo iný.

Meno vstupného a výstupného súboru načítajte ako argument príkazového riadka. V zadaní by mali byť implementované tieto dve funkcie:

/**
 * Skomprimuje súbor in a zapíše do súboru out. 
 * @arg in smerník na otvorený vstupný súbor (na čítanie)
 * @arg out smerník na otvorený výstupný súbor (na zápis)
 * @return počet bajtov skomprimovaného súboru
 */

int compress(FILE* in, FILE* out);
/**
 * Dekomprimuje súbor in a zapíše do súboru out. 
 * @arg in smerník na otvorený vstupný súbor (na čítanie)
 * @arg out smerník na otvorený výstupný súbor (na zápis)
 * @return počet bajtov dekomprimovaného  súboru
 */
 
void decompress(FILE* in, FILE* out);

Kompresor a dekompresor by mal byť schopný pracovať s ľubovoľným binárnym súborom do 10 MB. Súbor by mal byť po skomprimovaní menší minimálne o 10 percent a po dekomprimovaní by mal byť zhodný s pôvodným súborom. Pri práci s binárnymi súbormi môžete využiť funkcie fopen(), fread() a fwrite().

Na otestovanie kompresora a dekompresora použite súbory z Cantebury corpus.

## Implementácia

Zadanie je robené pomocou Run-Length Encoding algoritmu a z časti LZ77 algoritmu.
Najťažšie bolo obísť dĺžku bufferu pri dekódovaní pretože ak sa skončí buffer v strede čísla alebo vypisovaní neopakujúcich sa charakterov tak treba načítať nový vstupný buffer a pokračovať ďalej.

### Run-Length Encoding

RLE spočíva v zakódovaní opakujúcich sa charakterov pozitívnym číslom a charakterom a neopakujúce sa charaktery su zapísané za negatívnym číslom s číslom charakterov, ktoré sa nemajú opakovať.

### LZ77

LZ77 nie je dobre implementované nakoľko sa mi nepodarilo vhodne vybrať najlepšiu zhodu.

### Funkcie 

int compress(FILE* in, FILE* out) - zoberie vstupný a výstupný súbor a zakomprimuje charaktery zo vstupného súboru a zapíše ich do výstupného súboru pomocou RLE komprimovania

void decompress(FILE* in, FILE* out) - zoberie vstupný a výstupný súbor a dekomprimuje vstupný súbor opačnou metódou RLE komprimovania

Najlepšia komprimácia je dosiahnutá ak vstupný súbor obshauje veľa opakujúcich sa charakterov s minimálnou dĺžkou 3 opakujúce sa charaktery po sebe

### Zdroje

https://student.kemt.fei.tuke.sk/usaa

https://jameshfisher.com/2020/01/08/run-length-encoding-in-c/