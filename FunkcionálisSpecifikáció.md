# Funkcionális specifikáció

## 1. Vágyállomrendszer leírása

A projektunk egy kis távirányítós autó lenne, amit webes felületen keresztül lehet irányítani - mikrokontroller pedig NodeMCU lenne.

## 2. Igényelt alkatrészek

### 2.1 Kell:

* DC motor - 2db kellene
* L293D H-híd - 1db kellene
* Kerekek - 4db kellene

### 2.2 Van saját / elhanyagolható beszerzés fontossága (van az egyetemen biztosan):

* NodeMCU - (van saját, ESP8266MOD)
* ellenállások ledekhez
* **1 színű ledek:**
  * 2db piros (van saját is)
  * 3db sárga (van saját is)

## 3. Használati esetek (működés)

### 3.1 Egyik fajta elképzelés

* Webfelületen:
  * gomb lenyomásra előre
  * gomb lenyomásra hátra - (tolató jelző lámpa be/ki kapcsol)
  * gomb lenyomásra jobbra
  * gomb lenyomásra balra  

### 3.2 Másik fajta elképzelés

* Webfelületen:
  * gomb használattal előre/hátra fele menet kiválasztása - (tolató jelző lámpa be/ki kapcsol ez alapján)
  * slider használatával:
    * sebesség beállítása
    * kormányzás    

## 4. Képernyőtervek (sematikus ábra és CAD tervrajz)

## 5. Forgatókönyvek (állapotátmenet gráf)
