<h1 align = "center">🌟LilyGo T-Beam-1W🌟</h1>

* [Implementierung](https://github.com/karamo/MeshCom_4.0_LilyGo_T-Beam-1W/tree/main/MeshCom_FW_4#implementierung---meshcom-fw-435l-ddmm%CE%B1)
* [ADC-Funktion](https://github.com/karamo/MeshCom_4.0_LilyGo_T-Beam-1W/tree/main/MeshCom_FW_4#adc-funktion)
---
## Implementierung - MeshCom FW 4.35l-dd.mm.α
- [x] Start with Fork **FW-Version 4.35k** from [**MeshCom-FW**  ](https://github.com/icssw-org/MeshCom-Firmware)
- [x] **variants** files & include in platformio.ini [variants/LilyGo_T-Beam-1W/*]
- [x] **boards** JSON-Datei [boards/esp32-s3-wroom-1-n16r8.json]
- [x] **pinning** anpassen
- [x] **Display**: SH1106
- [x] **WiFi** als Gateway & **Webserver**
- [X] **BLE**
- [x] **HW-ID** 51 = TBEAM_1W
- [x] On-Board-**LED** (**`--board led {on|off}`**)
- [x] User-**BUTTON** (**`--button gpio 17 --button on --reboot`**, LongPress = Display on/off, Click = Screens blättern, DoubleClick = Track POS sent, TrippleClick = POS-Anzeige on/off)
- [x] **LoRa**: SX1262 [Receive-Interrupt-Example](https://github.com/karamo/MeshCom_4.0_LilyGo_T-Beam-1W/tree/main/examples2/Receive_Interrupt)
- [x] **BATT** [siehe #11](https://github.com/karamo/MeshCom_4.0_LilyGo_T-Beam-1W/issues/11)
- [x] **Temperaturmessung** und **Lüfter-Steuerung** (siehe auch https://github.com/karamo/MeshCom_4.0_LilyGo_T-Beam-1W/discussions/6)
- [x] **LoRa**: SX1262 [Transmit-Interrupt-Example](https://github.com/karamo/MeshCom_4.0_LilyGo_T-Beam-1W/tree/main/examples2/Transmit_Interrupt)
- [x] **GPS**: L76K (LAT,LON,ALT,Sats,HDOP,Date, TimeUTC)
- [x] --setboostedgain {on|off}
- [x] --txpower {2..22} für gefundenem SX1261
- [x] Freigabe aller I²C **Sensoren** (über Zusatzplatine bzw. QWICC-Stecker I²C)
- [x] **OTA**
- [x] **ADC-Funktion** verbessert [**FW 4.35l.01.29.a**](https://github.com/karamo/MeshCom_4.0_LilyGo_T-Beam-1W/releases/tag/4.35l.01.29.a) 
- [ ] tools/**download_meshcom.py** u.a. noch anpassen
- [ ] **`--pong`** Befehl & Verfahren für **Ping-Pong** Modus [#26](https://github.com/karamo/MeshCom_4.0_LilyGo_T-Beam-1W/issues/26)
- [ ] **`--temp`** Befehl für Anzeige der NTC-Temperatur & Fan-Status [#14](https://github.com/karamo/MeshCom_4.0_LilyGo_T-Beam-1W/issues/14)
- [ ] **MQTT** (siehe auch https://github.com/karamo/MeshCom_4.0_LilyGo_T-Beam-1W/discussions/7)

---
## ADC-Funktion

<img width="439" height="297" alt="grafik" src="https://github.com/user-attachments/assets/9bf33132-cbf5-4400-8c8e-1bd232c26ad1" />

<img width="689" height="59" alt="grafik" src="https://github.com/user-attachments/assets/5d6b38a9-76f6-4fa8-b729-2fcb058c1e09" />

<img width="955" height="425" alt="grafik" src="https://github.com/user-attachments/assets/220066d3-4aa3-409a-8f6c-3a484f615e32" />

<img width="581" height="62" alt="grafik" src="https://github.com/user-attachments/assets/ae6fa94b-bdab-42df-ae3f-5d3d6a8bbd43" />




---
***29.1.2026 by OE3WAS - Wolfgang***

