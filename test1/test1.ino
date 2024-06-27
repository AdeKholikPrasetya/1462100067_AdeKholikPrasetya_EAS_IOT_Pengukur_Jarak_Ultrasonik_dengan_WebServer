#include <EtherCard.h> // Library untuk menggunakan Ethernet shield

#define STATIC 1  // Set menjadi 1 untuk menonaktifkan DHCP dan menggunakan alamat IP statis

#if STATIC
// Alamat IP untuk interface Ethernet
static byte myip[] = { 192, 168, 0, 100 };
// Alamat IP gateway
static byte gwip[] = { 192, 168, 0, 0 };
#endif
// Alamat MAC untuk Arduino
static byte mymac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };
byte Ethernet::buffer[500]; // Buffer Ethernet

const int trigPin = 7; // Pin trig untuk HC-SR04
const int echoPin = 6; // Pin echo untuk HC-SR04

void setup() {
  Serial.begin(9600); // Inisialisasi komunikasi serial dengan baud rate 9600
  pinMode(trigPin, OUTPUT); // Set pin trig sebagai output
  pinMode(echoPin, INPUT);  // Set pin echo sebagai input
  
  ether.begin(sizeof Ethernet::buffer, mymac, SS); // Inisialisasi Ethernet dengan ukuran buffer dan alamat MAC
  ether.staticSetup(myip, gwip); // Set IP statis dan gateway
}

long readUltrasonicDistance() {
  // Mengirimkan pulsa ultrasonik
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Mengukur durasi pantulan pulsa
  long duration = pulseIn(echoPin, HIGH);
  // Menghitung jarak dari durasi pulsa
  long distance = duration * 0.034 / 2;
  return distance;
}

void loop() {
  long distance = readUltrasonicDistance(); // Membaca jarak dari sensor ultrasonik
  char distanceString[6]; // Buffer untuk mengkonversi nilai jarak ke string
  itoa(distance, distanceString, 10); // Konversi nilai jarak ke string

  char htmlResponse[250]; // Buffer untuk respon HTML
  // Membuat respon HTML dengan nilai jarak
  sprintf(htmlResponse, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n"
                        "<html>\r\n"
                        "<head>\r\n"
                        "<meta http-equiv='refresh' content='3'>\r\n"
                        "</head>\r\n"
                        "<body>\r\n"
                        "Distance: %s cm\r\n"
                        "</body>\r\n"
                        "</html>\r\n", distanceString);

  // Memeriksa paket yang masuk
  word pos = ether.packetLoop(ether.packetReceive());
  if (pos) {
    // Menunjuk data paket
    char *data = (char *)Ethernet::buffer + pos;
    // Menyalin respon HTML ke buffer Ethernet
    memcpy(ether.tcpOffset(), htmlResponse, strlen(htmlResponse));
    // Mengirim balasan HTTP server dengan panjang respon HTML
    ether.httpServerReply(strlen(htmlResponse));
  }
}
