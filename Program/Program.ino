#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED Display Settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Rotary Encoder Pins
#define ENCODER_CLK 2  // Interrupt Pin
#define ENCODER_DT  3  // Digital Pin
#define ENCODER_SW  4  // Button Pin

// Fan Control Pin
#define FAN_PWM 9

// Global Variables
volatile int encoderPos = 128;  // Fan speed (0-255)
bool fanState = true;  // ON/OFF state
int lastStateCLK;
bool buttonPressed = false;

// Interrupt Service Routine for Encoder
void encoderISR() {
    int stateCLK = digitalRead(ENCODER_CLK);
    if (stateCLK != lastStateCLK) {
        if (digitalRead(ENCODER_DT) != stateCLK) {
            encoderPos = constrain(encoderPos + 10, 0, 255);
        } else {
            encoderPos = constrain(encoderPos - 10, 0, 255);
        }
    }
    lastStateCLK = stateCLK;
}

// Function to check if the encoder button was pressed (debounced)
bool isButtonPressed() {
    if (digitalRead(ENCODER_SW) == LOW) {
        delay(50); // Debounce
        if (digitalRead(ENCODER_SW) == LOW) {
            buttonPressed = !buttonPressed;  // Toggle fan ON/OFF
            while (digitalRead(ENCODER_SW) == LOW);  // Wait for release
            return true;
        }
    }
    return false;
}

// Function to initialize the OLED
void initDisplay() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Check I2C address with scanner if needed
        Serial.println("SSD1306 allocation failed");
        for (;;);
    }
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
}

// Function to update the display
void updateDisplay() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Fan Speed:");
    
    display.setCursor(0, 30);
    display.print(map(encoderPos, 0, 255, 0, 100));  // Convert to %
    display.print("%");

    display.setCursor(0, 50);
    display.print(fanState ? "Fan: ON" : "Fan: OFF");

    display.display();
}

void setup() {
    Serial.begin(9600);

    // Set pin modes
    pinMode(ENCODER_CLK, INPUT);
    pinMode(ENCODER_DT, INPUT);
    pinMode(ENCODER_SW, INPUT_PULLUP);
    pinMode(FAN_PWM, OUTPUT);

    // Attach interrupt for rotary encoder
    attachInterrupt(digitalPinToInterrupt(ENCODER_CLK), encoderISR, CHANGE);

    lastStateCLK = digitalRead(ENCODER_CLK);

    initDisplay();
}

void loop() {
    // Check button press to toggle fan ON/OFF
    if (isButtonPressed()) {
        fanState = !fanState;
    }

    // Control fan speed
    if (fanState) {
        analogWrite(FAN_PWM, encoderPos);
    } else {
        analogWrite(FAN_PWM, 0);
    }

    // Update OLED display
    updateDisplay();

    delay(100);
}
