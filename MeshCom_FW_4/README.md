<h1 align = "center">🌟LilyGo T-Beam-1W🌟</h1>

## Implementierung - MeshCom FW 4.35l-dd.mm.α
- [x] Start with Fork **FW-Version 4.35k** from [**MeshCom-FW**  ](https://github.com/icssw-org/MeshCom-Firmware)
- [x] **variants** files & include in platformio.ini [variants/LilyGo_T-Beam-1W/*]
- [x] **boards** JSON-Datei [boards/esp32-s3-wroom-1-n16r8.json]
- [x] **pinning** anpassen
- [x] **Display**: SH1106
- [x] **WiFi** als Gateway
- [x] **Webserver**
- [X] **BLE**
- [x] **HW-ID** 51 = TBEAM_1W
- [x] On-Board-**LED** (**`--board led {on|off}`**)
- [x] User-**BUTTON** (**`--button gpio 17 --button on --reboot`**, LongPress = Display on/off, Click = Screens blättern, DoubleClick = Track POS sent, TrippleClick = POS-Anzeige on/off)
- [x] **LoRa**: SX1262 RX
- [≈] **BATT** noch fehlerhaft siehe #11
- [x] **Temperaturmessung** und **Lüfter-Steuerung** [**FW 4.35l.01.22.a**](https://github.com/karamo/MeshCom_4.0_LilyGo_T-Beam-1W/releases/tag/4.35l.01.22.a)  
       (siehe auch https://github.com/karamo/MeshCom_4.0_LilyGo_T-Beam-1W/discussions/6)
- [≈] **LoRa**: SX1262 TX
- [≈] **GPS**: L76K [TinyGPS-Example](https://github.com/karamo/MeshCom_4.0_LilyGo_T-Beam-1W/tree/main/exam2/TinyGPS_Example/firmware) (LAT,LON,ALT,Sats,HDOP,Date, TimeUTC)
- [≈] **OTA** noch ausführlich testen
- [ ] tools/**download_meshcom.py** u.a. noch anpassen
- [ ] Freigabe von **Sensoren**
- [ ] **MQTT** (siehe auch https://github.com/karamo/MeshCom_4.0_LilyGo_T-Beam-1W/discussions/7)

* LoRa RX/TX SX1262 TCXO XY16P354 (400..433..520 MHz)

---
***22.1.2026 by OE3WAS - Wolfgang***

