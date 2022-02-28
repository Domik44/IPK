Author: Dominik Pop  
Login:  xpopdo00  
Email:  xpopdo00@stud.fit.vutbr.cz  
VUT FIT, 2 BIT  
  
# Základní popis:  
- Program vytváří jednoduchý HTTP server, který čeká na požadaky typu GET.  
- Je schopný podat odpověd na 3 typy požadavků:  
>                            1) GET /hostname -> vypíše jméno hostitele  
>                            2) GET /cpu-name -> vypíše jméno procesoru  
>                            3) GET /load     -> vypíše procentuální využití procesoru  
- Na všechny ostatní požadavky vypisuje chybovou zprávu.  

# Použití:  
- Aplikace se spouští přes terminál příkazem './hinfosvc <číslo portu>'.  
- Při spuštění jsou zjištěny všechny odpovědi na 3 možné požadavky, pak je vytvořen server a ten čeká na dané požadavky.  
- Požadavky se mohou serveru zasílat 2 způsoby:  
>                            1) přes 2. terminál   
>                                |-> příkaz 'curl http://localhost:<číslo portu>/<požadavek>'  
>                            2) přes prohlížeč     
>                                |-> zadáním 'localhost:<číslo portu>/<požadavek>'  
- Server pak vypíše odpověd na zadaný požadavek do terminálu/prohlížeče.
- Po vypsání odpovědi server čeká na další požadavek.  
- Čekání je možné ukončit klávesovou zkratkou 'CTRL + C'.

  
# Příklady:  
## Spuštění přes dva terminály:  
>        Terminál_1: spuštění aplikace  
>            -> ./hinfosvc 12345  
>        Terminál_2: zadání požadavků  
>            -> curl http://localhost:12345/cpu-name  
>            <- "jméno procesoru"  
>            -> curl http://localhost:12345/hostname  
>            <- "jméno hostitele"  
>        Terminál_1: ukončení  
>            -> 'CTRL + C'  
    
## Spuštění přes prohlížeč:  
>        Terminál: spuštění aplikace  
>            -> ./hinfosvc 12345  
>        Prohlížeč:  
>            -> localhost:12345/load  
>            <- "využití procesoru v %"  
>        Terminál: ukončení  
>            -> 'CTRL + C'  