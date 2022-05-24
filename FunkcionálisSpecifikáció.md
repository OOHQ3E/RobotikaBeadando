# Funkcionális specifikáció

## 1. Vágyálomrendszer leírása

A projektunk egy kis távirányítós autó lenne, amit webes felületen keresztül lehet irányítani - mikrokontroller pedig egy NodeMCU és egy Arduino Micro lenne.

## 2. Alkatrész lista:

### Minden alkatrész be lett szerezve

* 1db DC motor
* 1db szervó motor
* 1db L293D H-híd
* 4db Kerék
* 1db NodeMCU (ESP8266MOD)
* 1db Arduino Micro
* 1db hangszóró
* 1db ultrahangos közelségmérő
* **1 színű ledek:**
  * 2db piros
  * 3db sárga
* ellenállások ledekhez
* jumper kábelek

## 3. Használati esetek (működés)

* Webfelületen:
  * gomb lenyomásra előre
  * gomb lenyomásra hátra - (tolató jelző lámpa be/ki kapcsol, tolatóradar közelségérzékelővel: minél közelebb kerül, annál gyakrabban sípol)
  * gomb lenyomásra jobbra
  * gomb lenyomásra balra  
  * gomb lenyomásra duda megszólaltatása
  * csúszka állításával sebesség
  
## 4. Képernyőtervek (sematikus rajz és CAD tervrajz)

Eredeti Fritzing fájl a /img mappában megtalálható, mint 'robotikaFritzing_bb.fzz'

### 4.1: Sematikus rajz:

![SematikusRajz](https://github.com/OOHQ3E/RobotikaBeadando/blob/main/img/sematikus%20rajz.png)
 
### 4.2: CAD tervrajz:

![CADRajz](https://github.com/OOHQ3E/RobotikaBeadando/blob/main/img/robotikaFritzing_bb.png)

## 5. Forgatókönyvek (állapotátmenet gráf)

### 5.1: jelölések

#### 5.1.1 Állapotok jelölése:
 
 * A motor iránya alapján:
   * N: nem megy sehova
   * F: előre megy
   * B: hátra megy
 * A kormányzás alapján:
   * M: középen van a kormány
   * L: a kormány balra fordul
   * R: a kormány jobbra fordul
 * A duda állapota alapján:
   * 0: hamis, nem szól
   * 1: igaz, szól

#### 5.1.2 Gomblenyomások jelölése:
 
 * f: előre
 * b: hátra
 * r: jobbra
 * l: balra
 * h: duda
 
 ### 5.2 Állapotátmenet gráfok:
 
 #### Az állapotátmenet gráfok szét lettek szedve szempontok alapján, hogy átláthatóbbak legyenek:
 
 #### 5.2.1: A motor forgási iránya, tolatóradar jelzési állapottal együtt:
 
 Jelölések a csúcspontokban: \[motorállapot\]\[radarállapot\]
 
 ![MotorAllapot](https://github.com/OOHQ3E/RobotikaBeadando/blob/main/img/allapoatmenet_01_motorirany.png)
 
 Ezen felül a motor sebességét is be lehet állítani egy csúszka segítségével.
 
 #### 5.1.2: A kormány állása:
 
 ![KormanyAllapot](https://github.com/OOHQ3E/RobotikaBeadando/blob/main/img/allapoatmenet_02_kormanyzas.png)
 
 #### 5.1.3: Duda:
 
  ![DudaAllapot](https://github.com/OOHQ3E/RobotikaBeadando/blob/main/img/allapoatmenet_03_duda.png)
  
 Hogy ha a duda és a tolatóradar jelzése egyszerre igaz állapotban van, akkor más frekvencián szólal meg a hangszóró.
  
