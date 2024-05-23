#include <Servo.h>

char python;
Servo myServo;
bool objectDetected = false;  // Nesne tespit edildi mi?
unsigned long lastDetectionTime = 0;  // Son tespit zamanını saklamak için
const long waitTime = 10000;  // 10 saniye bekleme süresi

void setup() {
  Serial.begin(9600);
  myServo.attach(2);
}

void loop() {
  if (Serial.available() > 0) {
    python = Serial.read();
    if (python == 'e' && !objectDetected) {
      objectDetected = true;  // Nesne tespit edildi
      myServo.write(180);  // Servo motoru hareket ettir
      lastDetectionTime = millis();  // Tespit zamanını kaydet
    }
  }

  // Eğer nesne tespit edildiyse ve belirlenen süre geçtiyse
  if (objectDetected && millis() - lastDetectionTime >= waitTime) {
    myServo.write(90);  // Servo motoru eski konumuna döndür
    objectDetected = false;  // Nesne tespit edilmedi olarak güncelle
  }
}
