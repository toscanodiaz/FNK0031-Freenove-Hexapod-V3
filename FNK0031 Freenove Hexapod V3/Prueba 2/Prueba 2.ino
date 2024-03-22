#include <FNHR.h>
#include <stdlib.h>
FNHR robot;

void setup() {
  Serial.begin(9600);  // Inicia la comunicación serial a 9600 baudios
  robot.Start();

  Serial.println("P")
}

void loop() {
 if (Serial.available() > 0) {  // Si hay datos disponibles para leer
    String data = Serial.readStringUntil('\n');   // Lee la cadena completa hasta encontrar un salto de línea
    
    // Verifica si el primer componente es "H"
    if (data.charAt(0) == 'H' || (data.charAt(0) == 'A' && data.charAt(1) == 'S')) {
      // Divide el string en partes usando la coma como delimitador
      int commaIndex = data.indexOf(',');
      if (commaIndex != -1) {
        String action = data.substring(0, commaIndex);  // Extrae el primer componente ("H")
        String parameter = data.substring(commaIndex + 1);  // Extrae el segundo componente ("2")
        float parameter1 = atof(parameter.c_str());
        executeCommand(action,parameter1,0,0,0,0,0);
        Serial.println(data);
      }
    } else if ((data.charAt(0) == 'R' && data.charAt(1) == 'B') || (data.charAt(0) == 'M' && data.charAt(1) == 'B') || (data.charAt(0) == 'C')) {
      // Divide el string en partes usando la coma como delimitador
      int commaIndex1 = data.indexOf(',');
        int commaIndex2 = data.indexOf(',', commaIndex1 + 1);
        int commaIndex3 = data.indexOf(',', commaIndex2 + 1);

        if (commaIndex1 != -1 && commaIndex2 != -1 && commaIndex3 != -1) {
            String action = data.substring(0, commaIndex1); // Extrae el primer componente 
            String parametro = data.substring(commaIndex1 + 1, commaIndex2); // Extrae el segundo componente 
            String parametro2 = data.substring(commaIndex2 + 1, commaIndex3); // Extrae el tercer componente 
            String parametro3 = data.substring(commaIndex3 + 1); // Extrae el cuarto componente
            
            float parameter1 = atof(parametro.c_str());
            float parameter2 = atof(parametro2.c_str());
            float parameter3 = atof(parametro3.c_str());

            executeCommand(action, parameter1, parameter2, parameter3, 0, 0, 0);
            Serial.println(data);
        }
    } else if (data.charAt(0) == 'T' && data.charAt(1) == 'B') {
      // Divide el string en partes usando la coma como delimitador
      int commaIndex1 = data.indexOf(',');
      int commaIndex2 = data.indexOf(',', commaIndex1 + 1);
      int commaIndex3 = data.indexOf(',', commaIndex2 + 1);
      int commaIndex4 = data.indexOf(',', commaIndex3 + 1);
      int commaIndex5 = data.indexOf(',', commaIndex4 + 1);
      int commaIndex6 = data.indexOf(',', commaIndex5 + 1);

      if (commaIndex1 != -1 && commaIndex2 != -1 && commaIndex3 != -1 && commaIndex4 != -1 && commaIndex5 != -1 && commaIndex6 != -1) {
          String action = data.substring(0, commaIndex1); // Extrae el primer componente 
          String parametro = data.substring(commaIndex1 + 1, commaIndex2); // Extrae el segundo componente 
          String parametro2 = data.substring(commaIndex2 + 1, commaIndex3); // Extrae el tercer componente 
          String parametro3 = data.substring(commaIndex3 + 1, commaIndex4); // Extrae el cuarto componente
          String parametro4 = data.substring(commaIndex4 + 1, commaIndex5); // Extrae el quinto componente
          String parametro5 = data.substring(commaIndex5 + 1, commaIndex6); // Extrae el sexto componente
          String parametro6 = data.substring(commaIndex6 + 1); // Extrae el séptimo componente
              
          float parameter1 = atof(parametro.c_str());
          float parameter2 = atof(parametro2.c_str());
          float parameter3 = atof(parametro3.c_str());
          float parameter4 = atof(parametro4.c_str());
          float parameter5 = atof(parametro5.c_str());
          float parameter6 = atof(parametro6.c_str());

          executeCommand(action, parameter1, parameter2, parameter3, parameter4, parameter5, parameter6);
          Serial.println(data);
      }
    } else {
      executeCommand(data,0,0,0,0,0,0);
      Serial.println(data);
    }
  }
}

void executeCommand(const String& command, int p1, int p2, int p3, int p4, int p5, int p6) {
  if (command == "A") {
    active();
  } else if (command == "S") {
    sleep();
  } else if (command == "Tleft") {
    tleft();
  } else if (command == "Tright") {
    tright();
  } else if (command == "H") {
    bodyheight(p1); // aquí deberías pasar el valor correcto de altura
  } else if (command == "C") {
    crawl(p1,p2,p3);
  } else if (command == "MB") {
    movebody(p1, p2, p3); // aquí deberías pasar los valores correctos de x, y, z
  } else if (command == "RB") {
    rotatebody(p1,p2,p3); // aquí deberías pasar los valores correctos de x, y, z
  } else if (command == "AS") {
    actionspeed(p1); // aquí deberías pasar el valor correcto de velocidad
  } else if (command == "TB") {
    twistbody(p1,p2,p3,p4,p5,p6);
  } else if (command == "Forward") {
    forward();
  } else if (command == "Backward") {
    backward();
  } else if (command == "Left") {
    left();
  } else if (command == "Right") {
    right();
  }
}

void active() {
  robot.ActiveMode();
}

void sleep() {
  robot.SleepMode();
}

void forward() {
  robot.CrawlForward();
}

void backward() {
  robot.CrawlBackward();
}

void left() {
  robot.CrawlLeft();
}

void right() {
  robot.CrawlRight();
}

void tright() {
  robot.TurnRight();
}

void tleft() {
  robot.TurnLeft();
}

void bodyheight(float height) {
  robot.ChangeBodyHeight(height);
}

void crawl(float x, float y, float angle) {
  robot.Crawl(x, y, angle);
}

void movebody(float x, float y, float z) {
  robot.MoveBody(x, y, z);
}

void rotatebody(float x, float y, float z) {
  robot.RotateBody(x, y, z);
}

void twistbody(float xMove, float yMove, float zMove, float xRotate, float yRotate, float zRotate) {
  robot.TwistBody(xMove, yMove, zMove, xRotate, yRotate, zRotate);
}

void actionspeed(float speed) {
  robot.SetActionSpeed(speed);
}