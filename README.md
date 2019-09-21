# esp-line-follower
## Purpose
The goal of the project is to teach beginners into robotics without fearing and over-complicated or expensive parts.
It's indended to be open enough for future experiments and improvements.

## Required skills
* Basic soldering skills.
  A few wires need to be soldered here and there, nothing major.
* Some understanding on how electronic components are connected together
  Just enough to know the difference between "+" and "-", signal and power lines, etc.
* Basic knowledge on Arduino IDE and how sketches are uploaded.

## Required parts
This is the minimum list of required parts. Basically, these are the parts which are being used in this project.
The list should not limit you in case if you wish to add some additional functionality or make other experiments based on that.
* Microcontroller board.
  The project uses ESP8266 NodeMCU board with CP2102. Sometimes that board is referenced as "ESP8266 NodeMCU v2 DevKit".
  There are some variations of ESP8266 NodeMCU board with CH340G chip, but these are too wide to fit into motor driver shield and so can't be used.
* Motor driver shield.
  The shield is based on L293DD chip. A single chip contains four half-bridges which can be connected as two full bridges to drive two motors.
* A pair of Reflective Infrared sensor boards.
  These are sometimes called "Obstacles avoiding infrared sensor board". Each board contains an infrared LED and infrared photodiode.
  There are a lot of variations of those boards. I highly recommend to pick those with a small adjustment, this way it can be adjusted according to the current lighting and surrounding contrast.
* 2WD Robot Chassis.
  Normally, the chassis comes with two motors with built-in reductors, 4*AA battery holder and enough screws and mounting hardware to put everything together. You will still need some additional mounting/screws to put your ESP8266, Motor shield and Infrared sensors.

## Bill Of Materials (BOM)
All prices are approximate and depend on the source where you purchase it. My recommended sources are eBay and AliExpress. You can also find it on Amazon, but it tends to be slightly more expensive. All prices are in USD.

Qnty | Part | Cost | Buy
-- | - | - | -
1 | ESP8266 NodeMCU (CP2102) | $5.00 | [eBay](https://www.ebay.com/itm/183659209296), [AliExpress](https://www.aliexpress.com/item/32716698412.html), [Amazon](https://www.amazon.com/ESP8266-microcontroller-NodeMCU-WiFi-CP2102/dp/B071WRD25D/ref=sr_1_1?keywords=B071WRD25D&qid=1568748259&s=gateway&sr=8-1)
1 | L293DD Motor Shield for ESP8266 NodeMCU | $2.50 | [eBay](https://www.ebay.com/itm/123883947048), [AliExpress](https://www.aliexpress.com/item/32870926299.html), [Amazon](https://www.amazon.com/BeediY-NodeMCU-ESP-12E-ESP8266-Control/dp/B07QVCMM5B/ref=sr_1_1?keywords=B07QVCMM5B&qid=1568748516&s=gateway&sr=8-1)
2 | Infrared sensors | $1.50 | [eBay](https://www.ebay.com/itm/132461910910), [AliExpress](https://www.aliexpress.com/item/4000028730932.html), [Amazon](https://www.amazon.com/HiLetgo-Infrared-Avoidance-Reflective-Photoelectric/dp/B07W97H2WS/ref=sr_1_1?keywords=B07W97H2WS&qid=1568748581&s=gateway&sr=8-1)
1 | 2WD Robot Chassis | $8.00 | [eBay](https://www.ebay.com/itm/263825340577), [AliExpress](https://www.aliexpress.com/item/32766175672.html), [Amazon](https://www.amazon.com/SainSmart-Smart-Chassis-Tracing-Encoder/dp/B072N7QNV9/ref=sr_1_1?keywords=B072N7QNV9&qid=1568748118&s=gateway&sr=8-1)
1 | Various M3 spacers/standoffs/screws | $2.00 | [eBay](https://www.ebay.com/itm/253323075671), [AliExpress](https://www.aliexpress.com/item/32799855557.html), [Amazon](https://www.amazon.com/Yosoo-120pcs-standoff-motherboard-assortment/dp/B01GO2GWWW/ref=sr_1_1?keywords=B01GO2GWWW&qid=1569029665&sr=8-1)

**Total**: about $20

## Connection diagram
![Fritzing](schematic/line-follower-diagram.png)
