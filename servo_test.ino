#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

#define led1 D2
#define led2 D3
const char* ssid = "Atastsousse";
const char* password = "helloworld";

ESP8266WebServer server(80);
Servo servoMoteur;
void setup() {
  // put your setup code here, to run once:
  pinMode(led1, OUTPUT);
  Serial.begin(115200); // start the serial
  WiFi.softAP(ssid, password); // create access point
  Serial.printf("ssid: %  \n",ssid);
  Serial.printf("password: %  \n",password);
  IPAddress IP = WiFi.softAPIP(); // create adress ip
  Serial.printf("ip adress: %");
  Serial.println(IP);
  server.begin();
  Serial.printf("server started");
  server.on("/",response);
  server.on("/control",indexPage);
  servoMoteur.attach(A0); 
  server.on("/up", servoUp);
  server.on("/down", servoDown);
}
void response(){
  server.send(200,"text/html", "<h1>You are connected</h1>");
}

String indexPage(){
      String pageindex = "<!!DOCTYPE html>";
          pageindex += "<html>";
          pageindex += "<button><a href=\"/up\">UP</a></button>";
          pageindex += "<button><a href=\"/down\">DOWN</a></button>";
          pageindex += "</html>";
      server.send(200,"text/html",pageindex);
  }
void ledOne(){
  digitalWrite(led1, HIGH);
  delay(15);
  digitalWrite(led1, LOW);
  }
void ledTwo(){
  digitalWrite(led2, HIGH);
  delay(15);
  digitalWrite(led2, LOW);
  }
void servoUp(){
  for (int p = 0 ; p <= 180; p++){  //p: Position
    
    servoMoteur.write(p);
    ledOne();
    delay(15);
  }
  server.send(200, "html/text", indexPage());
}

void servoDown(){
  for (int p = 180; p >= 0; p--){
    servoMoteur.write(p);
    ledTwo();
    delay(15);
    }
  server.send(200, "html/text", indexPage());
}
void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();  
}
