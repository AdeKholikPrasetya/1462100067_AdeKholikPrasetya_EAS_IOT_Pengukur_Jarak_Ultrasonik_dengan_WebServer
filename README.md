# 1462100067_AdeKholikPrasetya_EAS_IOT_Pengukur_Jarak_Ultrasonik_dengan_WebServer

# Pengukur Jarak Ultrasonik dengan Web Server

Proyek ini menggunakan Arduino untuk mengukur jarak menggunakan sensor ultrasonik (HC-SR04) dan menampilkan jarak tersebut pada halaman web yang di-host oleh Arduino dengan Ethernet shield.

## Komponen

•	Arduino Uno
•	LED-BIGY
•	Ground
•	Power
•	ENC28J60
•	ULTRASONIC SENSOR
•	POT-HG


## Pemasangan

- **HC-SR04**:
  - VCC ke Arduino 5V
  - GND ke Arduino GND
  - Trig ke Arduino Pin Digital 7
  - Echo ke Arduino Pin Digital 6
- **Ethernet Shield**:
  - Dipasangkan ke Arduino

## Penjelasan Kode

### Pustaka

Proyek ini menggunakan pustaka EtherCard untuk menangani Ethernet shield. Anda perlu menginstal pustaka ini sebelum mengunggah kode ke Arduino.

### Konfigurasi IP Statis

Proyek ini menggunakan konfigurasi IP statis. Alamat IP, gateway, dan alamat MAC didefinisikan dalam kode:

```cpp
#define STATIC 1  // set to 1 to disable DHCP (adjust myip/gwip values below)
#if STATIC
static byte myip[] = { 192, 168, 0, 100 }; // Alamat IP
static byte gwip[] = { 192, 168, 0, 0 };   // Alamat IP Gateway
#endif
static byte mymac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 }; // Alamat MAC
