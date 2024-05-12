# Uporaba GPIO priklopov

Za razvojno ploščico napišite sistemsko programsko opremo, ki bo ob pritisku na tipko zamenjala kombinacijo prižganih svetlečih diod.

Implementacija naj upošteva naslednje zahteve:

konfiguracija GPIO priklopov:

priklop PA0 (modri gumb) kot vhod
priklopi PD12 - PD15 (svetleče diode) kot izhod
prižiganje svetlečih diod (5 točke):

ob pritisku na gumb naj se spremeni kombinacija prižganih diod
kombinacije so lahko naključne
prikazati morate vsaj 5 različnih kombinacij
sprememba le ob pritisku na gumb (5 točke):

ob enem pritisku na gumb se lahko zamenja le ena kombinacija
sprememba se lahko zgodi ALI ob pritisku na gumb ALI ob sprostitvi gumba
čas samega pritiska na gumb ne sme vplivati na spremembo
Prevedeno sistemsko programsko opremo oddajte v formatu .hex.

Poročilo (10 točk)
Z logičnim analizatorjem izmerite logične nivoje gumba in diod pri prehodu iz enega stanja v drugo. Iz grafov poskusite odčitati koliko časa preteče med pritiskom gumba in popolno zamenjavo stanja.

Pripravite poročilo z diagrami (zaslonskimi posnetki rezultatov logičnega analizatorja) in označbami iz katerih bo razviden prehod in vaša meritev časa.

Oddaja
V arhivu naloga.zip oddajte naslednjo strukturo:

mapa "Core" (iz korenskega imenika projekta z vsemi podmapami in datotekami)
prevedena sistemska programska oprema (v formatu .hex)
poročilo v pdf formatu (porocilo.pdf)