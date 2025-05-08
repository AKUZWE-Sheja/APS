#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10

MFRC522 rfid(SS_PIN, RST_PIN); // Create MFRC522 instance

void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for Serial to initialize
  SPI.begin();
  Serial.println("SPI Initialized");
  rfid.PCD_Init();
  Serial.println("MFRC522 Reader Initialized");
  Serial.print("Reader Version: ");
  rfid.PCD_DumpVersionToSerial(); // Print reader version
  if (rfid.PCD_PerformSelfTest()) {
    Serial.println("Self-test passed");
  } else {
    Serial.println("Self-test failed");
  }
  Serial.println("Scan an RFID card to see its UID...");
}

void loop() {
  // Check if a new card is present
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  // Check if the card's UID can be read
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Print the UID
  Serial.print("Card UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();

  // Halt PICC (card) and stop encryption
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  delay(1000); // Delay before the next scan
}


