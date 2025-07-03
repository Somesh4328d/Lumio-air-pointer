import serial
import pyautogui 
import time

pyautogui.FAILSAFE = False  # Disable PyAutoGUI failsafe
MOVE_SPEED = 50#djust for smoothness

# Function to connect to Arduino via USB
def connect_arduino(port="COM6", baudrate=9600):
    while True:
        try:
            arduino = serial.Serial(port, baudrate, timeout=1)
            print("✅ Connected to Arduino via USB")
            return arduino
        except serial.SerialException:
            print("⚠️ Arduino not detected. Retrying in 5 seconds...")
            time.sleep(5)

# Initialize USB Serial connection
arduino = connect_arduino()

dragging = False  # Track dragging state

while True:
    try:
        data = arduino.readline().decode().strip()
        if data:
            print(f"📩 Received: {data}")

            # Mouse Movement
            if data == "MOUSE_LEFT":
                pyautogui.move(-MOVE_SPEED, 0)
            elif data == "MOUSE_RIGHT":
                pyautogui.move(MOVE_SPEED, 0)
            elif data == "MOUSE_UP":
                pyautogui.move(0, -MOVE_SPEED)
            elif data == "MOUSE_DOWN":
                pyautogui.move(0, MOVE_SPEED)

            # Click and Drag Functions
            elif data == "LEFT_CLICK":
                pyautogui.click()
            elif data == "DOUBLE_CLICK":
                pyautogui.doubleClick()
            elif data == "RIGHT_CLICK":
                pyautogui.click(button='right')

            # Drag and Drop Handling
            elif data == "DRAG_START":
                if not dragging:
                    pyautogui.mouseDown()
                    dragging = True
            elif data == "DRAG_STOP":
                if dragging:
                    pyautogui.mouseUp()
                    dragging = False

    except serial.SerialException:
        print("❌ USB disconnected! Attempting to reconnect...")
        arduino = connect_arduino()  # Reconnect Arduino

    except UnicodeDecodeError:
        print("⚠️ Received corrupted data. Ignoring...")
