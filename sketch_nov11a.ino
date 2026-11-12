#include <LiquidCrystal.h>
#include <Keypad.h>

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const int ledPin = 10;

const char* phoneLetters[] = {
  " ",      // 0
  "._.",    // 1
  "abc2",   // 2
  "def3",   // 3
  "ghi4",   // 4
  "jkl5",   // 5
  "mno6",   // 6
  "pqrs7",  // 7
  "tuv8",   // 8
  "wxyz9"   // 9
};

const char* morseLetters[] = {
  ".-",    // A[cite: 4]
  "-...",  // B[cite: 4]
  "-.-.",  // C[cite: 4]
  "-..",   // D[cite: 4]
  ".",     // E[cite: 4]
  "..-.",  // F[cite: 4]
  "--.",   // G[cite: 4]
  "....",  // H[cite: 4]
  "..",    // I[cite: 4]
  ".---",  // J[cite: 4]
  "-.-",   // K[cite: 4]
  ".-..",  // L[cite: 4]
  "--",    // M[cite: 4]
  "-.",    // N[cite: 4]
  "---",   // O[cite: 4]
  ".--.",  // P[cite: 4]
  "--.-",  // Q[cite: 4]
  ".-.",   // R[cite: 4]
  "...",   // S[cite: 4]
  "-",     // T[cite: 4]
  "..-",   // U[cite: 4]
  "...-",  // V[cite: 4]
  ".--",   // W[cite: 4]
  "-..-",  // X[cite: 4]
  "-.--",  // Y[cite: 4]
  "--.."   // Z[cite: 4]
};

const char* morseNumbers[] = {
  "-----", // 0[cite: 4]
  ".----", // 1[cite: 4]
  "..---", // 2[cite: 4]
  "...--", // 3[cite: 4]
  "....-", // 4[cite: 4]
  ".....", // 5[cite: 4]
  "-....", // 6[cite: 4]
  "--...", // 7[cite: 4]
  "---..", // 8[cite: 4]
  "----."  // 9[cite: 4]
};

char lastKey = '\0';
unsigned long lastPressTime = 0;
const unsigned long timeout = 800; 
int letterIndex = 0;

String inputString = "";
bool isPlaying = false;

void setup() {
  lcd.begin(16, 4);
  lcd.setCursor(0, 0);
  lcd.print("Type & Press #");
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  char key = keypad.getKey();
  
  if (!isPlaying) {
    if (key) {
      if (key >= '2' && key <= '9') {
        int num = key - '0';
        String chars = phoneLetters[num];
        
        if (key == lastKey && (millis() - lastPressTime < timeout)) {
          letterIndex = (letterIndex + 1) % chars.length();
          inputString.remove(inputString.length() - 1);
        } else {
          letterIndex = 0;
          lastKey = key;
        }
        
        inputString += chars[letterIndex];
        lastPressTime = millis();
        
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        lcd.print(inputString);
      } 
      else if (key == '0') {
        if (lastKey == '0' && (millis() - lastPressTime < timeout)) {
          letterIndex = (letterIndex + 1) % 1;
          inputString.remove(inputString.length() - 1);
        } else {
          letterIndex = 0;
          lastKey = '0';
        }
        inputString += ' ';
        lastPressTime = millis();
        
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        lcd.print(inputString);
      }
      else if (key == '1') {
        lastKey = '\0';
        inputString += '1';
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        lcd.print(inputString);
      }
      else if (key == 'D') { // Delete / Correction
        lastKey = '\0';
        if (inputString.length() > 0) {
          inputString.remove(inputString.length() - 1);
          lcd.setCursor(0, 1);
          lcd.print("                ");
          lcd.setCursor(0, 1);
          lcd.print(inputString);
        }
      } 
      else if (key == '#') { // Enter to play
        if (inputString.length() > 0) {
          isPlaying = true;
          lastKey = '\0';
          lcd.setCursor(0, 2);
          lcd.print("Playing Morse...");
          playMorseSequence();
          isPlaying = false;
          inputString = "";
          lcd.setCursor(0, 1);
          lcd.print("                ");
          lcd.setCursor(0, 2);
          lcd.print("Done. Type:#    ");
          lcd.setCursor(0, 3);
          lcd.print("                ");
        }
      } 
      else if (key == '*') { // Clear all
        lastKey = '\0';
        inputString = "";
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(0, 2);
        lcd.print("                ");
        lcd.setCursor(0, 3);
        lcd.print("                ");
      }
    }
    
    if (lastKey != '\0' && (millis() - lastPressTime > timeout)) {
      lastKey = '\0';
    }
  }
}

bool waitWithControl(unsigned long duration) {
  unsigned long start = millis();
  while (millis() - start < duration) {
    char k = keypad.getKey();
    if (k == 'A') { // Abort / Stop execution
      digitalWrite(ledPin, LOW);
      isPlaying = false;
      lcd.setCursor(0, 2);
      lcd.print("Aborted! Type:# ");
      return true;
    }
    if (k == 'C') { // Pause execution
      digitalWrite(ledPin, LOW);
      lcd.setCursor(0, 2);
      lcd.print("Paused (C=Cont) ");
      while (true) {
        char resumeKey = keypad.getKey();
        if (resumeKey == 'C') { // Continue execution
          lcd.setCursor(0, 2);
          lcd.print("Playing Morse...");
          break;
        }
        if (resumeKey == 'A') { // Abort from pause
          isPlaying = false;
          lcd.setCursor(0, 2);
          lcd.print("Aborted! Type:# ");
          return true;
        }
        delay(10);
      }
    }
    delay(10);
  }
  return false;
}

void playMorseSequence() {
  for (int idx = 0; idx < inputString.length() && isPlaying; idx++) {
    char c = inputString[idx];
    const char* morse = "";
    
    if (c >= '0' && c <= '9') {
      morse = morseNumbers[c - '0'];
    } else if (c >= 'a' && c <= 'z') {
      morse = morseLetters[c - 'a'];
    } else if (c >= 'A' && c <= 'Z') {
      morse = morseLetters[c - 'A'];
    } else {
      if (waitWithControl(400)) return;
      continue;
    }
    
    lcd.setCursor(0, 3);
    lcd.print("                ");
    lcd.setCursor(0, 3);
    lcd.print(c);
    lcd.print(": ");
    lcd.print(morse);

    for (int i = 0; morse[i] != '\0' && isPlaying; i++) {
      if (morse[i] == '.') {
        digitalWrite(ledPin, HIGH);
        if (waitWithControl(200)) return;
      } else if (morse[i] == '-') {
        digitalWrite(ledPin, HIGH);
        if (waitWithControl(600)) return;
      }
      digitalWrite(ledPin, LOW);
      if (waitWithControl(200)) return;
    }
    if (waitWithControl(400)) return;
  }
}