AcSeDo
======
The aim of Accessible Secured Domotic is to provide a complete frameworks of tools to permit the configuration of any home automation with security, inexpensive cost, little knowledge.
#Tools:
  - Acsedo online module generator
Based on user needs permit to generate the module configuration file and the server part.
  - Acsedo server
Server to manage the differents module of an installation. 
Because our security is based on unique encrytion key, server is internal.
  - Acsedo modules
Modules composed of sensor and actuator.

Acsedo arduino lib for Arduino chip
===================================

This project brings framework for accessible secured home automation over arduino board.

The aim of the project is to have module based on arduino SDK.
This module run a VP (vital platform) an dynamically load bl (business logic) based on a config.json file. 
BL shall be independant from the hardware platform.

#The VP is in charge of: 
  - communication with the websocket server
  - encryption
  - loading/saving the config

# Contents
- VP vital platform for ESP8266
- BLS:
  - GPI -> digital input
  - GPO -> digital output
  - PWM -> pwm
  - SBS -> step by step motor (without easy driver)
  - DHT -> DHT sensor 
# To be done
 - BL RFID
 - BL RGB
 - VP encryption
 - VP set sequence
Installing
----------
-unzip the github directory in your arduino libraries directory

depandencies:

https://github.com/jc19000/arduinoWebSockets
->modify version of advise websocket library to permit method callback instead of function

https://github.com/bblanchon/ArduinoJson
->used for configuration of the VP, configuration of the BL, communication with the websocket server

For ESP8266:https://github.com/esp8266/Arduino

Available versions
------------------
only stagging one

Documentation
-------------
The documentation is available online in the [Acsedo arduino wiki](https://github.com/jc19000/Acsedo_arduino_lib/wiki)

### Issues and support ###

If you encounter an issue, you are welcome to submit it here on Github: https://github.com/jc19000/Acsedo_arduino_lib/issues.
Please provide as much context as possible: version which you are using (you can check it in Boards Manager), your sketch code, serial output, board model, IDE settings (board selection, flash size, etc).

### Contributing

For minor fixes of code and documentation, go ahead and submit a pull request.

Larger changes (rewriting parts of existing code from scratch, adding new functions to the core, adding new libraries) should generally be discussed [in the chat](https://gitter.im/esp8266/Arduino) first.

Feature branches with lots of small commits (especially titled "oops", "fix typo", "forgot to add file", etc.) should be squashed before opening a pull request. At the same time, please refrain from putting multiple unrelated changes into a single pull request.

### License and credits ###

Arduino IDE is developed and maintained by the Arduino team. The IDE is licensed under GPL.

ESP8266 core includes an xtensa gcc toolchain, which is also under GPL.

Esptool written by Christian Klippel is licensed under GPLv2, currently maintained by Ivan Grokhotkov: https://github.com/igrr/esptool-ck.

Espressif SDK included in this build is under Espressif MIT License.

ESP8266 core files are licensed under LGPL.

[SPI Flash File System (SPIFFS)](https://github.com/pellepl/spiffs) written by Peter Andersson is used in this project. It is distributed under MIT license.

[umm_malloc](https://github.com/rhempel/umm_malloc) memory management library written by Ralph Hempel is used in this project. It is distributed under MIT license.
