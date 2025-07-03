// กำหนดขา ESP32 ที่เชื่อมต่อกับแต่ละ Segment ของ 7-Segment Display
// *** สำคัญ: ขาเหล่านี้ต้องตรงกับการต่อวงจรใน Wokwi ของคุณเป๊ะๆ ***
const int segA = 19; // sevseg1:A -> esp:19
const int segB = 18; // sevseg1:B -> esp:18
const int segC = 5;  // sevseg1:C -> esp:5
const int segD = 17; // sevseg1:D -> esp:17
const int segE = 16; // sevseg1:E -> esp:16
const int segF = 4;  // sevseg1:F -> esp:4
const int segG = 0;  // sevseg1:G -> esp:0 (ระวัง: GPIO0 อาจมีปัญหาในการอัปโหลดในบางสถานการณ์ แต่ลองใช้ดูก่อน)


// สร้างอาเรย์เพื่อเก็บรูปแบบการเปิด-ปิด Segment สำหรับแต่ละตัวเลข (0-9)
// สำหรับ 7-Segment แบบ Common Cathode: HIGH = เปิด, LOW = ปิด
// ลำดับของ segment ในแต่ละแถว: A, B, C, D, E, F, G
byte seven_segment_patterns_CC[10][7] = {
  //   A    B    C    D    E    F    G
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW},   // 0
  {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW},    // 1
  {HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH},   // 2
  {HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH},   // 3
  {LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH},    // 4
  {HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH},   // 5
  {HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH},  // 6
  {HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW},    // 7
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH}, // 8
  {HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH}   // 9
};

void setup() {
  // กำหนดขา ESP32 ทั้งหมดที่ใช้เป็น OUTPUT
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);

  // เริ่ม Serial Monitor สำหรับ Debug (ถ้าจำเป็น)
  Serial.begin(115200);
}

void loop() {
  // วนลูปนับเลขตั้งแต่ 0 ถึง 9
  for (int digit = 0; digit <= 9; digit++) {
    Serial.print("Displaying: ");
    Serial.println(digit); // แสดงตัวเลขที่กำลังจะแสดงบน Serial Monitor

    displayDigit(digit); // เรียกฟังก์ชันแสดงผลตัวเลข
    delay(1000);         // หน่วงเวลา 1 วินาที (1000 มิลลิวินาที = 1 วินาที)
  }
}

// ฟังก์ชันสำหรับแสดงตัวเลขบน 7-Segment Display
void displayDigit(int digit) {
  // ตรวจสอบให้แน่ใจว่า digit อยู่ในช่วง 0-9
  if (digit >= 0 && digit <= 9) {
    digitalWrite(segA, seven_segment_patterns_CC[digit][0]);
    digitalWrite(segB, seven_segment_patterns_CC[digit][1]);
    digitalWrite(segC, seven_segment_patterns_CC[digit][2]);
    digitalWrite(segD, seven_segment_patterns_CC[digit][3]);
    digitalWrite(segE, seven_segment_patterns_CC[digit][4]);
    digitalWrite(segF, seven_segment_patterns_CC[digit][5]);
    digitalWrite(segG, seven_segment_patterns_CC[digit][6]);
  }
}
