# Uporaba naprave CDC

Za razvojno ploščico napišite sistemsko programsko opremo, ki bo preko povezave CDC iz PC-ja prejemala ukaze in jih tudi izvrševala.

Napišite tudi programsko opremo na računalniku, ki bo komunicirala s ploščico in delovala kot čelni del (ang. frontend).

Strojna programska oprema, ang. firmware (40 točk)
Implementacija naj upošteva naslednje zahteve:

konfiguracija GPIO priklopov:
priklopi PD12 - PD15 (svetleče diode) kot izhod
konfiguracija naprave CDC (1 točka):
opisni niz produkta (PRODUCT_STRING) naj bo: 27312
prejem ukazov (9 točk):
ukaz se naj izvede po potrditvi z tipko ENTER
se pravi po prejetju znaka "new line" (\n - unix) ALI "carriage return" (\r - windows)
3 točke
podprite delno prejemanje ukazov
predvidevajte, da lahko ukaz dobivate znak po znak (počasi, preko tipkovnice) ali pa v celoti naenkrat (hitro, iz programa)
6 točke
implementirajte osnovne ukaze (6 točk):
LED_ON
ukaz prižge vse svetleče diode (PD12 - PD15)
LED_OFF
ukaz ugasne vse svetleče diode (PD12 - PD15)
LED_XX_ON
kjer XX označuje prižig svetleče diode
implementirajte po ključu: če XX == 12, prižgi svetlečo diodo na priklopu PD12, ...
LED_XX_OFF
kjer XX označuje ugasnitev svetleče diode
implementirajte po ključu: če XX == 12, ugasni svetlečo diodo na priklopu PD12, ...
implementirajte ukaz za trenutno stanje (8 točk):
STANJE
ukaz naj izpiše trenutno stanje LED luči
izpiše LED_XX_ON če dioda XX sveti
izpiše LED_XX_OFF če dioda XX ne sveti
primer izpisa: LED_12_ON LED_13_OFF LED_14_OFF LED_15_ON
implementirajte napredni ukaz (12 točk):
ANIMACIJA_ON
ukaz sproži spreminjanje kombinacije prižganih svetlečih diod
hitrost animacije naj bo 1 sprememba na sekundo
kombinacije so lahko naključne
prikazati morate vsaj 5 različnih kombinacij
ANIMACIJA_OFF
ukaz ustavi spreminjaje kombinacij prižganih svetlečih diod
ukaz naj pusti prižgano zadnjo prikazano kombinacijo
implementirajte ukaz za pomoč (2 točki):
HELP
ukaz naj izpiše vse vaše implementirane ukaze
oblikujte ukaz za pomoč (2 točk):
izpis ukaza HELP naj bo oblikovan:
izpis naj bo v obliki "UKAZ - opis"
vsak ukaz z razlago naj bo izpisan v novi vrstici (začetek izpisa naj bo poravnan na levo stran)
po izpisu pomoči izpišite še dodatno prazno vrstico
Čelni del (20 točk)
Za krmiljenje ploščice pripravite ukazni program v pythonu. Program naj uporabi knjižnico pyserial za pošiljanje ukazov in branje odgovorov.

navodila za uporabo (2 točk):
Če podamo zastavico --help naj program izpiše navodila za uporabo.

$ python3 main.py --help
...
Pomoč bi naj izpisala vse možne zastavice čelne aplikacije in kratke opise za njihovo uporabo.

Vklop in izklop LED luči (10 točk):
Kadar podamo zastavico --led vklopimo ali izklopimo svetleče diode. Željeno kombinacijo nadziramo z 4 simboli v argumentu zastavice. Če podamo X se dioda izklopi, če podamo O se vklopi.

Primer:

$ python3 main.py --led XOXO # prižge diodi 13 in 15
Ukaz naj minimizira število potrebnih ukazov. Za vzorec OOXO potrebujemo samo dva ukaza: LED_ON, LED_14_OFF.

Vklop in izklop animacije (3 točk):
Kadar podamo zastavico --animacija on program ploščici pošlje ukaz ANIMACIJA_ON. Kadar podamo zastavico --animacija off program ploščici pošlje ukaz ANIMACIJA_OFF.

Primer:

$ python3 main.py --animacija on
$ python3 main.py --animacija off
Spremljanje stanja (5 točk):
Kadar podamo zastavico --stanje program prične spremljati stanje diod na ploščici.

S frekvenco 10 Hz naj vzorči stanje (ploščici pošlje ukaz STANJE in prebere odgovor). Prvo stanje vedno izpiše, nato pa izpiše stanje le ob spremembi. Če je leta vklopljena izpiše O, če je izklopljena izpiše X.

Program prekinemo z kombinacijo tipk ctrl+c (to bi moralo preprosto delati).

Primer:

$ python3 main.py --stanje
XXXX
OXOX
XOXO
OOOO
Oddaja
Prevedeno sistemsko programsko opremo oddajte v formatu .hex.

V arhivu naloga.zip oddajte naslednjo strukturo:

mapa "Core" (iz korenskega imenika projekta z vsemi podmapami in datotekami)
mapa "USB_DEVICE" (iz korenskega imenika projekta z vsemi podmapami in datotekami)
prevedena sistemska programska oprema (v formatu .hex)
čelni program za krmiljenje main.py