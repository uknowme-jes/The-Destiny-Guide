import serial
import pyttsx3
import time

engine = pyttsx3.init()
ser = serial.Serial('COM4', 9600)

def say_message(message):
    engine.say(message)
    engine.runAndWait()

while True:
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').strip()
        
        print(f"Received: {line}")
        if line == "BUZZER_STOP":
            time.sleep(1) 
            say_message("Hold your steering wheel properly. Drive Safely.")

        elif line == "COLLISION_DETECTED":
            time.sleep(1)
            say_message("Collision Detected")
