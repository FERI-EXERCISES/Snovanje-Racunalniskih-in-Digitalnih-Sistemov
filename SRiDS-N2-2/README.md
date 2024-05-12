# Uporaba naprave HID

Za razvojno ploščico napišite sistemsko programsko opremo, ki bo demonstrirala uporabo protokola USB HID za tipkovnico.

Strojna programska oprema (ang. firmware)
Implementacija naj upošteva naslednje zahteve:

konfiguracija GPIO priklopov:
priklop PA0 (modri gumb) kot vhod
konfiguracija naprave HID (1 točka):
opisni niz produkta (PRODUCT_STRING) naj bo "KeyboardGhost"
demo tipkovnica preprosto (9 točk):
ob prvem (lihem) pritisku na gumb natipkajte : 27312
časovni zamik med pošiljanjem posameznega znaka naj bo 175 ms
demo tipkovnica napredno (10 točk):
ob drugem (sodem) pritisku na gumb natipkajte ASCII tabelo od 36 do 124 znaka
časovni zamik med pošiljanjem posameznega znaka naj bo 175 ms
POZOR: pretvorba pritiskov v znake je odvisna tudi od izbire jezika tipkovnice v operacijskem sistemu
Oddaja
Prevedeno sistemsko programsko opremo oddajte v formatu .hex.

V arhivu naloga.zip oddajte naslednjo strukturo:

mapa "Core" (iz korenskega imenika projekta z vsemi podmapami in datotekami)
mapa "USB_DEVICE" (iz korenskega imenika projekta z vsemi podmapami in datotekami)
prevedena sistemska programska oprema (v formatu .hex)