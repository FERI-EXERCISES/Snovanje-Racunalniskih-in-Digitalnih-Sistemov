# Odskakovanje

Za razvojno ploščico napišite sistemsko programsko opremo, ki bo zaznavala in odpravljala odskakovanje tipke ("debouncing").

Strojna programska oprema
Implementacija naj upošteva naslednje zahteve:

konfiguracija GPIO priklopov:
priklop PA0 (modri gumb) kot vhod
priklop PD14 (svetleča dioda) kot izhod
priklop PD15 (svetleča dioda) kot izhod
konfiguracija časovnika:
izbran časovnik nastavite, da boste lahko zaznavali (vzorčili) dogodke enakomerno 1-krat na milisekundo
ali uporabite "virtualni gumb" ali prekinitve ali ..., naj bo vzorčenje enakomerno
odstranjevanje odskakovanja (8 točke):
ob zaznanem pritisku gumba izvedite odstranjevanje odskakovanja ("debouncing"):
upoštevaje novo stanje gumba, ko je stanje stabilno vsaj 8 ms
če je novo stanje "pritisnjen gumb" prižgite svetlečo diodo PD14
če je novo stanje "spuščen gumb" ugasnite svetlečo diodo PD14
zaznava pritiskov (12 točke):
implementirajte razločevanje kratkega in dolgega pritiska:
za kratek pritisk upoštevajte pritisk gumba med 20 ms in 84 ms
za dolgi pritisk upoštevajte pritisk gumba med 250 ms in 850 ms
ob zaznanem kratkem pritisku prižgite svetlečo diodo PD15
ob zaznanem dolgem pritisku ugasnite svetlečo diodo PD15
če ne zaznate ne enega ne drugega, potem ohranite stanje svetleče diode
Oddaja
Prevedeno sistemsko programsko opremo oddajte v formatu .hex.

V arhivu naloga.zip oddajte naslednjo strukturo:

mapa "Core" (iz korenskega imenika projekta z vsemi podmapami in datotekami)
prevedena sistemska programska oprema (v formatu .hex)