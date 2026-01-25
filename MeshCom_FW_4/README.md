<h1 align = "center">🌟LilyGo T-Beam-1W🌟</h1>

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
- [x] **BATT** noch fehlerhaft [siehe #11](https://github.com/karamo/MeshCom_4.0_LilyGo_T-Beam-1W/issues/11)
- [x] **Temperaturmessung** und **Lüfter-Steuerung** (siehe auch https://github.com/karamo/MeshCom_4.0_LilyGo_T-Beam-1W/discussions/6)
- [x] **LoRa**: SX1262 [Transmit-Interrupt-Example](https://github.com/karamo/MeshCom_4.0_LilyGo_T-Beam-1W/tree/main/examples2/Transmit_Interrupt)
- [x] **GPS**: L76K (LAT,LON,ALT,Sats,HDOP,Date, TimeUTC)
- [x] --setboostedgain {on|off}
- [x] --txpower {2..15} für gefundenem SX1261 [**FW 4.35l.01.24.a**](https://github.com/karamo/MeshCom_4.0_LilyGo_T-Beam-1W/releases/tag/4.35l.01.24.a) 
- [ ] **OTA** noch ausführlich testen
- [ ] tools/**download_meshcom.py** u.a. noch anpassen
- [ ] Freigabe von **Sensoren** (über Zusatzplatine bzw. QWICC-Stecker I²C)
- [ ] **MQTT** (siehe auch https://github.com/karamo/MeshCom_4.0_LilyGo_T-Beam-1W/discussions/7)

---
***25.1.2026 by OE3WAS - Wolfgang***

