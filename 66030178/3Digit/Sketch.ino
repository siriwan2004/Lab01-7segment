// Segment pins: A, B, C, D, E, F, G
int segPins[] = {19, 18, 5, 17, 16, 4, 0};

// Digit control pins: D1 (left), D2 (middle), D3 (right)
int digitPins[] = {21, 22, 23};  // Corresponding to DIG1, DIG2, DIG3

// Segment encoding for digits 0–9
int numToSegment[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(segPins[i], OUTPUT);
  }

  for (int i = 0; i < 3; i++) {
    pinMode(digitPins[i], OUTPUT);
  }
}

void displayNumber(int number) {
  int digits[3];
  digits[0] = number / 100;         // Hundreds
  digits[1] = (number / 10) % 10;   // Tens
  digits[2] = number % 10;          // Units

  for (int i = 0; i < 3; i++) {
    // ปิดทุก digit ก่อน
    for (int j = 0; j < 3; j++) {
      digitalWrite(digitPins[j], HIGH); // HIGH = OFF (common cathode)
    }

    // ตั้งค่าสำหรับเลขที่จะโชว์
    for (int s = 0; s < 7; s++) {
      digitalWrite(segPins[s], numToSegment[digits[i]][s]);
    }

    // เปิด digit ที่ต้องการแสดง
    digitalWrite(digitPins[i], LOW); // LOW = ON

    delay(5); // แสดงแต่ละ digit สั้นๆ (multiplexing)
  }
}

void loop() {
  static int number = 0;
  displayNumber(number);

  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate >= 1000) {  // อัปเดตทุก 1 วินาที
    number = (number + 1) % 1000;       // นับ 0-999 วน
    lastUpdate = millis();
  }
}

