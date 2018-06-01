# Uživatelská část

## Popis
Program poskytuje simulaci pro deskovou hru 7 Wonder od Antonie Bauzy. Je předpokládána základní znalost pravidel. [Stručné video.](https://www.youtube.com/watch?v=E2z2TIBYlV0) [Podrobná pravidla.](http://rprod.com/uploads/file/7WONDERS_RULES_CZ_COLOR.pdf) Program obsahuje jednoduchou umělou inteligenci, která zahraje náhodnou kartu, kterou může postavit.

## Ovládání
Po vytvoření třídy GameEngine a nastavení počtu hráčů a počtu lidských hráčů pomocí parametrů konstruktoru lze odstartovat hru zavoláním metody StartTheGame. Příkazy se zadávají pomocí konzole. Většina příkazů má parametr index, který odpovídá indexu karty, vypsané na konzoli.

### Příkazy

*play X* - zahraje kartu s indexem X

*discard X* - zahodí kartu s indexem X

*wonder X* - postaví část Divu kartou s indexem X

*stats left/right/me* - zobrazí statistiky levého souseda/hráče/pravého souseda

*info X* - zobrazí informace o kartě s indexem X

*exit* - ukončí hru


# Programátorská část

## Popis základních tříd

### Engine
Tato třída v sobě obsahuje veškeré informace o hře - hráče, jejich ruce a další. Stará se o synchronizaci - zahrání karet a finanční transakce probíhá zároveň na konci každého kola. Stejně tak vypočítává skóre hráčů, včetně distribuce bodů za vojenské výhry/prohry. V metodě PresentCardToAI je obsažena umělá inteligence.


### Cards
Třída BaseCards je šablonou, ze které dědí všechny ostatní karty - obsahuje několik virtuálních metod, které jsou implementovány konkrétními kartami. Karty se také dělí na několik typů, každá z nich má svoji šablonu. To umožňuje snadné parametrizování konkrétní karty.
Metoda CardEffect popisuje, jaký efekt má karta na hráče, funkce ScorePoints pak vrátí počet bodů, který karta přinesla. 

### Player
Obsahuje informace o hráči - kolik má peněz, ukazatele na jeho sousedy, dostupné suroviny a další. 

### Wonders
Jednotlivé části divů jsou implementovány jako karta. V základní verzi hry mají všechny divy stejnou první a poslední část divu. Stejně tak některé divy poskytují stejný efekt, jako některá budova, je tedy využito metody CardEffect příslušné budovy.

### GameUtilities
Obsahuje implementace pomocných datových struktur, jako je ResourceVector a ScienceVector a výčtové typy některých vlastností karet.

### CardGenerator
Slouží pro vygenerování příslušných karet v závislosti na počtu hráčů.





