import serial
import time

# Establece la conexión con Arduino
arduino_port = 'COM3'  # Cambia esto según el puerto en el que esté conectado tu Arduino
baud_rate = 9600
ser = serial.Serial(arduino_port, baud_rate)
time.sleep(3)

# Lista de acciones y parámetros
USER_INPUT = [("AS", "25", "0", "0", "0", "0", "0"), ("C", "13", "11", "30", "0", "0", "0"),
              ("A", "0", "0", "0", "0", "0", "0"),
              ("S", "0", "0", "0", "0", "0", "0"), ("TB", "4", "4", "4", "7", "6", "5"),
              ("H", "50", "0", "0", "0", "0", "0"),
              ("MB", "8", "7", "6", "0", "0", "0"), ("Left", "10", "0", "0", "0", "0", "0"),
              ("Right", "10", "0", "0", "0", "0", "0"), ("Forward", "10", "0", "0", "0", "0", "0"),
              ("Backward", "10", "0", "0", "0", "0", "0"), ("RB", "5", "10", "7", "0", "0", "0"),
              ("Tleft", "13", "0", "0", "0", "0", "0"), ("Tright", "13", "0", "0", "0", "0", "0")]

while USER_INPUT:  # Mientras la lista USER_INPUT no esté vacía
    action, parameter1, parameter2, parameter3, parameter4, parameter5, parameter6 = USER_INPUT[
        0]  # Obtiene la acción y el parámetro actual

    if action in ("A", "S"):
        ser.write(action.encode())
        time.sleep(1.8)
        if ser.in_waiting > 0:
            data = ser.readline().decode('utf-8').strip()
            print("Ejecutando:", data)
        USER_INPUT.pop(0)

    if action in ("C", "MB", "RB"):
        act = action + "," + parameter1 + "," + parameter2 + "," + parameter3
        ser.write(act.encode())
        time.sleep(1.8)
        if ser.in_waiting > 0:
            data = ser.readline().decode('utf-8').strip()
            print("Ejecutando:", data)
        USER_INPUT.pop(0)

    if action in "TB":
        act = action + "," + parameter1 + "," + parameter2 + "," + parameter3 + "," + parameter4 + "," + parameter5\
              + "," + parameter6
        ser.write(act.encode())
        time.sleep(1.8)
        if ser.in_waiting > 0:
            data = ser.readline().decode('utf-8').strip()
            print("Ejecutando:", data)
        USER_INPUT.pop(0)

    if action in ("H", "AS"):
        act = action + "," + parameter1
        ser.write(act.encode())
        time.sleep(1.8)
        if ser.in_waiting > 0:
            data = ser.readline().decode('utf-8').strip()
            print("Ejecutando:", data)
        USER_INPUT.pop(0)

    if action in ("Left", "Right", "Forward", "Backward", "Tleft", "Tright"):
        for _ in range(int(parameter1)):
            ser.write(action.encode())  # Convertir la cadena en bytes antes de enviarla
            time.sleep(2)
            if ser.in_waiting > 0:
                data = ser.readline().decode('utf-8').strip()
                print("Ejecutando:", data, int(_)+1)
        USER_INPUT.pop(0)

time.sleep(1)  # Pequeña pausa entre envíos
