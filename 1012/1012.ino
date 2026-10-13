const int buttonPin = 2;    // 按鈕接腳 (D2)
const int redPin = 9;       // 紅色接腳 (D9)
const int greenPin = 10;    // 綠色接腳 (D10)
const int bluePin = 11;     // 藍色接腳 (D11)

int buttonState = HIGH;
int lastButtonState = HIGH;
int colorIndex = 0;          // 顏色狀態索引

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); 
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

 
  setColor(255, 255, 255);
  Serial.begin(9600);
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;


      if (buttonState == LOW) {
        colorIndex = (colorIndex + 1) % 7; 
        changeColor(colorIndex);
        Serial.print("目前顏色代號：");
        Serial.println(colorIndex);
      }
    }
  }

  lastButtonState = reading;
}

void changeColor(int index) {
  switch (index) {
    case 0: setColor(0, 255, 255);   // 紅色
            break;
    case 1: setColor(255, 0, 255);   // 綠色
            break;
    case 2: setColor(255, 255, 0);   // 藍色
            break;
    case 3: setColor(0, 0, 255);     // 黃色
            break;
    case 4: setColor(0, 255, 0);     // 紫色
            break;
    case 5: setColor(255, 0, 0);     // 白色
            break;
    case 6: setColor(255, 255, 255); // 關閉
            break;
  }
}

void setColor(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}