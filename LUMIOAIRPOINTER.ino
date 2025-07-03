#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;

// Sensitivity settings
const int movementThreshold = 3000;  // Minimum movement to trigger a command
const int deadzone = 1000;           // Ignore small, unintended movements

const int leftButton = 3;   // Pin D3 for left-click / drag
const int rightButton = 4;  // Pin D4 for right-click

bool isDragging = false;
unsigned long pressStartTime = 0;
unsigned long lastClickTime = 0;
const int dragThreshold = 400;   // Long press duration (in ms) for drag
const int doubleClickThreshold = 300; // Max time between clicks for double-click

void setup() {
    Serial.begin(9600);
    pinMode(leftButton, INPUT_PULLUP);
    pinMode(rightButton, INPUT_PULLUP);
    
    Wire.begin();
    mpu.initialize();
    
    if (!mpu.testConnection()) {
        Serial.println("MPU6050 connection failed!");
        while (1);
    }
    
    Serial.println("MPU6050 initialized.");
}

void loop() {
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    // Apply deadzone to filter out small jitters
    if (abs(gx) < deadzone) gx = 0;
    if (abs(gy) < deadzone) gy = 0;

    // Mouse movement logic (UP/DOWN is inverted)
    if (gx > movementThreshold) Serial.println("MOUSE_RIGHT");
    else if (gx < -movementThreshold) Serial.println("MOUSE_LEFT");

    if (gy > movementThreshold) Serial.println("MOUSE_UP");
    else if (gy < -movementThreshold) Serial.println("MOUSE_DOWN");

    // Detect left button press state
    bool leftPressed = digitalRead(leftButton) == LOW;

    if (leftPressed) {
        if (pressStartTime == 0) {
            pressStartTime = millis();  // Start timing press
        } else if (millis() - pressStartTime > dragThreshold && !isDragging) {
            isDragging = true;
            Serial.println("DRAG_START");
        }
    } else {  
        if (pressStartTime > 0) {
            unsigned long pressDuration = millis() - pressStartTime;

            if (isDragging) {
                Serial.println("DRAG_STOP"); // Stop dragging
                isDragging = false;
            } else if (millis() - lastClickTime < doubleClickThreshold) {
                Serial.println("DOUBLE_CLICK");  // Double-click detected
                lastClickTime = 0;  // Reset double-click timer
            } else if (pressDuration < dragThreshold) {
                Serial.println("LEFT_CLICK");  // Normal click
                lastClickTime = millis();  // Save click time for double-click check
            }
            pressStartTime = 0;  // Reset press timer
        }
    }

    // Right-click detection
    if (digitalRead(rightButton) == LOW) {
        Serial.println("RIGHT_CLICK");
        delay(100);  // Debounce
    }

    delay(60);  // Slight delay for stability
}
