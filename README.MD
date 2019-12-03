#  HUEMIDIfi  
#### WebApp · API · Open Hardware

HUEMIDIfi development board is a pocket musical IoT device. It produces MIDI data that can be directed via an onboard web service, allowing multiple human and machine clients to collaborate effortlessly in real-time.

MIDI messages broadcasted by the device are generated according to its state, which is continuously monitored and set by all webapp instances. This is achieved via simple POST-request based API.

<!-- 
```mermaid
graph LR
A[USER: 1 to N] -- http API  Call --> HUEMIDIFI((HUEMIDIfi Dev Board))
HUEMIDIFI -- state  response -->  A
HUEMIDIFI -- MIDI <br> Data --> D{MIDI DEVICE:  1 to N}
``` -->
HUEMIDIfi is an open and extensible platform that encourages freely shared creativity. This device is an attempt to lower the difficulty threshold for entry into the world of MIDI, an omnipresent technology that is nearly 40 years old. A modifiable, scalable multi-user research platform that introduces the flexibility of the Web2.0-style human-machine interaction to the realm of MIDI — a part of a collaborative vision of the ways human potential can be realized.

HUEMIDIfi allows for a broad range of artistic techniques and approaches sharing a deep historical context, such as Aleatoricism and Musique concrète, serialism and procedural group collaboration in the spirit of John Cage and John Zorn. But most importantly, it offers exceptional accessibility for various electronic musical instruments, multi-user control, interactivity, and a flexibility of interface design.


### IoT WebApp

Parameter changes are sent one at a time as they are being set by the user. After each change the UI state is updated upon server response. The JSON answer represents the remote state including the applied changes. The 4MB flash size limit of the ESP32 offers a fair challenge to create an elegant, pared-down, modern UI.

### Remote API calls

Machine-to-Machine communication works similarly: API calls are encapsulated in POST requests. JSON formatted output allows easy parsing by both humans and machines. The WebApp implements this communication technique by means of AJAX.

### Prototyping kit

Huemidifi is an attempt to lower the threshold of experiencing the legacy of MIDI (a technology that is nearly 40 years old). A modifiable, scalable multi user compatible research platform that introduces the flexibility of web 2.0 based human & machine interaction to the realms of MIDI.

## Downloads
### Firmware and webapp source code

HUEMIDIfi firmware development is in the hot phase. Revisions are being rolled out daily. The code is provided under the terms of 'GPLv2.0-ONLY' licence.

[GNU General Public License, Version 2](https://www.gnu.org/licenses/old-licenses/gpl-2.0.html)
### Hardware fabrication files

All fabrication data is provided in Gerber format and was created and exported with EasyEDA Online Editor.

Both hardware versions were tested with JLCPCB production service. The hardware plans are provided under the terms of 'OHLv1.2' licence.

[Huemidifi development board v1.0](https://huemidi.fi/downloads/HUEMIDIFI_ESP32_MIDI_DEV_BOARD_v1_0_Gerber.zip)  
[Huemidifi development board v1.2](https://huemidi.fi/downloads/HUEMIDIFI_ESP32_MIDI_DEV_BOARD_v1_2_Gerber.zip)  
[CERN Open Hardware License, Version 1.2](https://ohwr.org/project/licenses/wikis/cern-ohl-v1.2)

### 3D Printable Enclosure

Is now available for download. Note that it is only compatible with the hardware v1.2. Upcomming changes will be published on Tinkercad

The enclosure files are provided under the terms of 'OHLv1.2' licence.

[Tinkercad: most recent version](https://www.tinkercad.com/things/7Y2Hgf3RJaH-huemidificasev12)  
[Initial beta version](https://huemidi.fi/downloads/HUEMIDIFI_CASE_1_2_STL_OBJ.zip)  
[CERN Open Hardware License, Version 1.2](https://ohwr.org/project/licenses/wikis/cern-ohl-v1.2)
## Get in touch

Please submit your feature requests and bug reports via:

[Github](https://github.com/Aznbai)  
[Tinkercad](https://www.tinkercad.com/users/1t4P1FlOPvg-aznbai)  
[Instagram](https://www.instagram.com/nebenfach.in.offenbach/)  


This project is dedicated to Margret Mattern
