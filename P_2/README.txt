Popis:
	Jedná se o síťový analyzátor packetů, který po spuštění čeká na komunikaci na specifikovaném rozhraní a 
zachytává pakety. Následné packety zpracovává a vypisuje o nich informace na standartní výstup.

Příklad překladu:
	-> make

Příklad spuštění:
	-> ./ipk-sniffer [-i rozhraní | --interface rozhraní] {-p ­­port} {[--tcp|-t] [--udp|-u] [--arp] [--icmp] } {-n num}

Seznam odevzdaných souborů:
	-> README.txt
	-> manual.pdf
	-> Makefile
	-> ipk-sniffer.c
	-> ipk-sniffer.h
	-> arguments.c