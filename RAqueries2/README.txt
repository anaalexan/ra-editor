= Dotazování v relační algebře
Autor: Anastasiia Alexanderova

== Zadání

Vaším cílem je implementovat program, který podporuje RA dotazy nad datovými zdroji. Jednotlivé zdroje (relace, tabulky) 
a výsledky dotazů je možné ukládat do proměnných a tyto proměnné následně využívat v dalších dotazech.

Program musí implementovat následující funkcionality:

- Práce s CSV soubory (především načtení do proměnné a vypsání obsahu).
- Základní operace: projekce a přejmenování (výběr a přejmenování sloupců), selekce (výběr řádků), přirozené a obecné spojení.
- Množinové operace: sjednocení, průnik, rozdíl, kartézský součin.
- Převod dotazu v relační algebře na validní SQL dotaz.
- Jednotlivé proměnné je možné uložit do souboru v (textově čitelné) CSV formě.
- Uložení v rámci proměnných musí být paměťově efektivní. Není dobrý nápad načítat celé CSV do paměti, stejně tak držet v paměti 
    výsledky všech dotazů. Při ukládání proměnné do paměti se musí určit typ dané proměnné. 
    Rozlišujte alespoň CSV soubor (proměnná obsahuje CSV soubor, který je uložen na disku) 
    a složený výraz (kombinace různých proměnných a operací). Obsah souborů načítejte jen pokud je to nutné a pouze ty části, které nutně potřebujete.

Dále aplikace musí zpracovávat výrazy dle jednoho z následujících principů:
- Množinové operace (alespoň sjednocení, průnik, rozdíl a kartézský součin) musí jít vnořovat pomocí závorek (př. ("animals.csv" ∪ X) × Y), 
    závorky mohou být libovolně vnořené. Složitější operace (přijímající parametry) mohou fungovat formou individuálních příkazů 
    bez dalšího skládání (př. A = rename ANIMALS "nazev" → "jmeno").
- Pro zapisování výrazů využijte prefixový (nebo postfixový) zápis, mají tu výhodu, že nevyžadují závorky a snáze se zpracovávají. 
    V tomto případě však veškeré operace a funkce musí jít zapsat v jednom výrazu (př. A = rename CROSS Y UNION "animals.csv" X "nazev" "jmeno").

Kde lze využít polymorfismus? (doporučené)

- reprezentace objektů: tabulka v CSV souboru, výraz, …
- operace: sjednocení, průnik, rozdíl, kartézský součin, …
- formáty importu a exportu: CSV, JSON, XML, SQLite, PostgreSQL …
- uživatelské rozhraní: konzole, ncurses, SDL, OpenGL (různé varianty), …

== Specifikace

Aplikace implementuje dotazování v relační algebře (RA). Uživatel ovládá aplikaci přes menu, ve kterém volí mezi:
- RA editorem pro dotazování nad reálnými daty ve formátu CSV (oddělovač čárky). Podporuje rovněž překlad do SQL.
- RA editorem čistě pro převod RA dotazu do SQL.
- Nápovědou obsahující všechna klíčová slova editoru.

Aplikace očekává od uživatele výrazy v POSTFIX formátu.

Unární operace:
Selekce             - (podmínka)
Projekce            - [názevSloupce1,...,názevSloupceN]
Přejmenování        - <současnýNázevSloupce1,novýNázevSloupce1;...;současnýNázevSloupceN,novýNázevSloupceN>

Binární operace:
Přirozené spojení   - *
Obecné spojení      - O(podmínka)
Průnik              - &
Sjednocení          - +
Rozdíl              - -
Kartézský součin    - x

Funkce:
IMPORT proměnná "názevSouboru.csv"              - uloží do proměnné cestu k souboru obsahující relaci
PRINT proměnná/výraz                            - vytiskne vyhodnocenou relaci výrazu do konzole
EXPORT proměnná/výraz > názevSouboru.csv        - exportuje vyhodnocenou relaci výrazu do CSV souboru zadaného uživatelem (oddělovače čárky)
TRANSLATE proměnná/výraz                        - přeloží RA výraz do validního SQL dotazu a výsledek vytiskne do konzole

Příklad POSTFIX zápisu RA výrazu:
Klasický zápis  -   {LOD*REZERVACE*ZAKAZNIK}(JMENO_Z='Iásón')[JMENO_L → NAZEV_LOD] U "IasonShips.csv"
POSTFIX zápis   -   LOD REZERVACE * ZAKAZNIK * (JMENO_Z='Iásón')[JMENO_L]<JMENO_L;NAZEV_LOD> "IasonShips.csv" +
Dotaz           -   Vyhledá jména lodí, které má rezervované zákazník Iásón, přejmenuje záhlaví sloupce pro jména lodí
                    a sloučí s jinou relací obsahující další lodě rezervované zákazníkem Iásón.
Příklady editoru:
R = LOD REZERVACE * ZAKAZNIK * (JMENO_Z='Iásón')[JMENO_L]<JMENO_L;NAZEV_LOD> "IasonShips.csv" +     - uloží výraz do proměnné
EXPORT R > IasonShips.csv                                                                           - exportuje výslednou relaci do souboru IasonShips.csv

== Polymorfismus

Polymorfismus je aplikován v rámci hierarchie tříd "COperator", jejíž potomci jsou jednotlivé operátory
"CSelection", "CProjection", "CRename", "CNaturalJoin", "CThetaJoin", "CIntersection", "CUnion", "CDifference", "CCrossJoin",
které primárně implementují abstraktní metodu z "COperator" na vyhodnocení operace mezi operandem/y a operátorem.
Polyformismus nám tak usnadní procházení jednotlivých tokenů při algoritmu pro vyhodnocení výrazu a umožní snadné
přidání případných nových operátorů bez zásahu do algoritmu pro vyhodnocení celého výrazu.

Vedlejší polymorfimus je aplikován nad "CMenuBase", který umožňuje zobrazit hlavní nabídku programu "CMainMenu" 
a související okna "CMenuRAeditor", "CMenuRAtoSQL", "CMenuKeywords". Polymorfismus na těchto třídách nám usnadní
vytváření nových menu nebo obrazovek a jejich připojení ke stávající hierarchii.