# Zatemnjevanje svetlečih diod

Za razvojno ploščico napišite sistemsko programsko opremo, ki bo ob pritisku na tipko zamenjala svetlost svetlečih diod.

Implementacija naj upošteva naslednje zahteve:

Strojna programska oprema
konfiguracija GPIO priklopov:
priklop PA0 (modri gumb) kot vhod
priklopi PD12 in PD14 (svetleče diode) kot PWM izhod časovnika TMR4
priklopi PD13 in PD15 (svetleče diode) kot ročni PWM
10 stopenj svetilnosti (4 točke):
imeti morate 10 stopenj svetilnosti
stopnja 1 (ali 0) pomeni da so svetleče diode ugasnjene
stopnja 10 (ali 9) pomeni da svetleče diode svetijo z vašo največjo možno svetlostjo
vrstni red spremembe (5 točke):
ob posameznem pritisku na gumb se mora svetlost spreminjati od najmanjše do največje in nazaj do najmanjše svetilnosti
iz maksimalne svetlosti ne smemo preskočiti na ugasnjene svetleče diode
upoštevanje nelinearnosti človeškega vida (5 točke):
upoštevajte da ljudje ne zaznavamo linearno povečevanje svetlosti
svetlost, oziroma čas prižgane svetleče diode, ne smemo povečevati enakomerno
sprememba le ob pritisku na gumb (2 točke):
ob enem pritisku na gumb se lahko zamenja le ena kombinacija
sprememba se lahko zgodi ALI ob pritisku na gumb ALI ob sprostitvi gumba
čas samega pritiska na gumb ne sme vplivati na spremembo
uporaba časovnika za štetje (5 točke):
priklop PA0 (modri gumb) nastavite kot vhod časovnika TIM2
nastavite časovnik TIM2 da prejme zunanjo uro
uporabite časovnik TIM2 za štetje števila pritiskov gumba
lastna implementacija PWM (9 točk)
čas periode naj bo manj od 2 ms
za štetje delovnega cikla uporabite časovnik TMR2 TIM3 z ustrezno konfiguracijo
Poročilo (10 točk)
Z logičnim analizatorjem izmerite kratke odseke krmilnega PWM signala vseh svetlečih diod pri največji, srednji in najmanjši svetilnosti. Vsak odsek naj zajema vsaj 10 ciklov PWM signala.

V poročilu nato analizirajte stabilnost PWM signala, ki vam ga je generiral časovnik TMR4 in tistega, ki ste ga generirali sami s pomočjo časovnika TMR2 TIM3. Zanima nas povprečna dolžina periode in odstopanje (minimum in maksimum), ter povprečna dolžina delovnega cikla ter njegovo odstopanje (minimum in maksimum).

V poročilo izpostavite morebitne razlike med vgrajenim in ročno generiranim PWM signalom.

Oddaja
Prevedeno sistemsko programsko opremo oddajte v formatu .hex.

V arhivu naloga.zip oddajte naslednjo strukturo:

mapa "Core" (iz korenskega imenika projekta z vsemi podmapami in datotekami)
prevedena sistemska programska oprema (v formatu .hex)
poročilo (v formatu .pdf)