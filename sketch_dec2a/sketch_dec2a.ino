//digital pins on the NodeMCU board
#define room1LEDpin D3
#define room1FanRelaypin D4
#define room2LEDpin D5
#define room2FanRelaypin D6

//Libraries
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

//WiFi ssid and Password
const char* ssid = "IOT";
const char* passwd = "weWantMarks@40";

//Server object
ESP8266WebServer server(80); 

//String wifi localIp is stored here
String wifiLocal;

bool isLed1,isLed2,isFan1,isFan2;
// // 192.168.186.23
IPAddress ip(192,168,186,152); 
IPAddress gateway(192,168,186,23); 
IPAddress subnet(255,255,255,0); 

String mainPageLoading(){ //mainPage loading function which returns a web-page as a String
String mainPage = "<!DOCTYPE html>\n";
mainPage+="<html lang=\"en\">\n";
mainPage+="<head>\n";
mainPage+="    <meta charset=\"UTF-8\">\n";
mainPage+="    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n";
mainPage+="    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
mainPage+="    <title>Root Page</title>\n";
mainPage+="    <style>\n";
mainPage+="        html{\n";
mainPage+="            font-weight: Serif;\n";
mainPage+="            display: inline-block;\n";
mainPage+="            margin:  0px auto;\n";
mainPage+="        }\n";
mainPage+="        body{\n";
mainPage+="            margin-top: 50px;\n";
mainPage+="        }\n";
mainPage+="        h1{\n";
mainPage+="            color: #444444;\n";
mainPage+="            margin: 50px auto 30px;\n";
mainPage+="            text-align: center;\n";
mainPage+="        }\n";
mainPage+="        h3{\n";
mainPage+="            color: #444444;\n";
mainPage+="            margin-bottom: 3px;\n";
mainPage+="            text-align: center;\n";
mainPage+="        }\n";
mainPage+="        p{\n";
mainPage+="            margin: 5px;\n";
mainPage+="        }\n";
mainPage+="        #Enter{\n";
mainPage+="            display: block;\n";
mainPage+="            width: 80px;\n";
mainPage+="            background-color: #1abc9c;\n";
mainPage+="            border: none;\n";
mainPage+="            color: white;\n";
mainPage+="            text-decoration: none;\n";
mainPage+="            font-size: 25px;\n";
mainPage+="            margin: 0px auto 35px;\n";
mainPage+="            cursor: pointer;\n";
mainPage+="            border-radius: 4px;\n";
mainPage+="            margin-right: 10%;\n";
mainPage+="        }\n";
mainPage+="        .form{\n";
mainPage+="            text-align: end;\n";
mainPage+="        }\n";
mainPage+="        .formDiv{\n";
mainPage+="            margin-right: 60%;\n";
mainPage+="            width: 60%;\n";
mainPage+="            padding-right: 50%;\n";
mainPage+="            padding-top: 10px;\n";
mainPage+="        }\n";
mainPage+="        \n";
mainPage+="    </style>\n";
mainPage+="</head>\n";
mainPage+="<body>\n";
mainPage+="    <h1>Smart Hotel Rooms Automation</h1>\n";
mainPage+="    <h3>Enter the room and its passkey</h3>\n";
mainPage+="    <div class=\"formDiv\">\n";
mainPage+="        <form class=\"form\">\n";
mainPage+="            <label for=\"roomNo\">Room Number:\n";
mainPage+="                <input type=\"text\" id=\"roomName\" name=\"roomName\" ><br><br>\n";
mainPage+="            </label>\n";
mainPage+="            \n";
mainPage+="            <label for=\"passkey\">PassKey:\n";
mainPage+="                <input type=\"password\" id=\"passkey\" name=\"passkey\" ><br><br>\n";
mainPage+="            </label>\n";
mainPage+="            \n";
mainPage+="            <button type=\"button\" id=\"Enter\" onclick=enterRooms()>\n";
mainPage+="                Enter\n";
mainPage+="            </button>\n";
mainPage+="        </form>\n";
mainPage+="    </div>\n";
mainPage+="    <script>\n";
mainPage+="        function enterRooms(){\n";
mainPage+="            const wifiLocal= window.location.host+window.location.pathname;\n";
mainPage+="            var roomName = document.getElementById(\"roomName\");\n";
mainPage+="            var passkey = document.getElementById(\"passkey\");\n";
mainPage+="            if(roomName.value==\"Room1\" && passkey.value==\"Room1\"){\n";
mainPage+="                 window.location.href=\"http://\"+wifiLocal+\"room1\";\n";
mainPage+="            }\n";
mainPage+="            else if(roomName.value=\"Room2\"&& passkey.value==\"Room2\"){\n";
mainPage+="                 window.location.href=\"http://\"+wifiLocal+\"room2\";\n";
mainPage+="            }\n";
mainPage+="            else{\n";
mainPage+="                alert(\"Entered wrong credentials\");\n";
mainPage+="            }\n";
mainPage+="        }\n";
mainPage+="    </script>\n";
mainPage+="</body>\n";
mainPage+="</html>";
return mainPage;
}

String room1Loading(bool isLed1,bool isFan1){ //room1 loading function which returns a web-page as a String
String room1= "<!DOCTYPE html>\n";
room1+="<html lang=\"en\">\n";
room1+="<head>\n";
room1+="    <meta charset=\"UTF-8\">\n";
// room1+="    <meta http-equiv=\"refresh\" content=\"2\">\n";
room1+="    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n";
room1+="    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
room1+="    <title>Room1</title>\n";
room1+="    <style>\n";
room1+="        html{\n";
room1+="            font-weight: Serif;\n";
room1+="            display: inline-block;\n";
room1+="            margin:  0px auto;\n";
room1+="            text-align: center;\n";
room1+="        }\n";
room1+="        body{\n";
room1+="            margin-top: 50px;\n";
room1+="        }\n";
room1+="        h1{\n";
room1+="            color: #444444;\n";
room1+="            margin: 50px auto 30px;\n";
room1+="        }\n";
room1+="        h3{\n";
room1+="            color: #444444;\n";
room1+="            margin-bottom: 3px;\n";
room1+="        }\n";
room1+="        p{\n";
room1+="            margin: 5px;\n";
room1+="        }\n";
room1+="        input[type=submit]{\n";
room1+="            background-color: #1abc9c;\n";
room1+="            border: none;\n";
room1+="            font-size: large;\n";
room1+="            color: white;\n";
room1+="            padding: 10px;\n";
room1+="        }";
room1+="    </style>\n";
room1+="</head>\n";
room1+="<body>\n";
room1+="    <h1>Smart Hotel Rooms Automation</h1>\n";
room1+="    <h3>Room1</h3>\n";
room1+="    <p id=\"bulbRoom1\">Bulb</p>\n";
room1+="    <form action=\"/room1/LED\" method=\"POST\">\n";
room1+="        <input type=\"submit\" value=\"Toggle LED\" id=\"ledButton\" accesskey=\"l\">\n";
room1+="    </form>\n";
room1+="     \n";
room1+="    <p>Fan</p>\n";
room1+="    <form action=\"/room1/FAN\" method=\"POST\">\n";
room1+="        <input type=\"submit\" value=\"Toggle FAN\" id=\"fanButton\" accesskey=\"f\">\n";
room1+="    </form>";
room1+="  <script>\n";
room1+="        var inputLed1= document.getElementById('ledButton');\n";
room1+="        var inputFan1 = document.getElementById('fanButton');\n";
// room1+="        inputFan1.style.backgroundColor=\"#1abc9c\";\n";
if(!isLed1){
room1+="            inputLed1.style.backgroundColor=\"#1abc9c\";\n";
}
if(isLed1){
room1+="            inputLed1.style.backgroundColor=\"red\";\n";
}
if(isFan1){
room1+="            inputFan1.style.backgroundColor=\"#1abc9c\";\n";
}
if(!isFan1){
room1+="            inputFan1.style.backgroundColor=\"red\";\n";
}
room1+="  </script>";
room1+="</body>\n";
room1+="</html>";
return room1;
}

String room2Loading(bool isLed2,bool isFan2){//room2 loading function which returns a web-page as a String
String room2="<!DOCTYPE html>\n";
room2+="<html lang=\"en\">\n";
room2+="<head>\n";
room2+="    <meta charset=\"UTF-8\">\n";
// room2+="    <meta http-equiv=\"refresh\" content=\"2\">\n";
room2+="    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n";
room2+="    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
room2+="    <title>Room2</title>\n";
room2+="    <style>\n";
room2+="        html{\n";
room2+="            font-weight: Serif;\n";
room2+="            display: inline-block;\n";
room2+="            margin:  0px auto;\n";
room2+="            text-align: center;\n";
room2+="        }\n";
room2+="        body{\n";
room2+="            margin-top: 50px;\n";
room2+="        }\n";
room2+="        h1{\n";
room2+="            color: #444444;\n";
room2+="            margin: 50px auto 30px;\n";
room2+="        }\n";
room2+="        h3{\n";
room2+="            color: #444444;\n";
room2+="            margin-bottom: 3px;\n";
room2+="        }\n";
room2+="        p{\n";
room2+="            margin: 5px;\n";
room2+="        }\n";
room2+="        input[type=submit]{\n";
room2+="            background-color: #1abc9c;\n";
room2+="            border: none;\n";
room2+="            font-size: large;\n";
room2+="            color: white;\n";
room2+="            padding: 10px;\n";
room2+="        }";
room2+="    </style>\n";
room2+="</head>\n";
room2+="<body>\n";
room2+="    <h1>Smart Hotel Rooms Automation</h1>\n";
room2+="    <h3>Room2</h3>\n";
room2+="    <p id=\"bulbRoom1\">Bulb</p>\n";
room2+="    <form action=\"/room2/LED\" method=\"POST\">\n";
room2+="        <input type=\"submit\" value=\"Toggle LED\" id=\"ledButton\" accesskey=\"f\">\n";
room2+="    </form>\n";
room2+="     \n";
room2+="    <p>Fan</p>\n";
room2+="    <form action=\"/room2/FAN\" method=\"POST\" >\n";
room2+="        <input type=\"submit\" value=\"Toggle FAN\" id=\"fanButton\" accesskey=\"f\">\n";
room2+="    </form>\n";
room2+="  <script>\n";
room2+="        var inputLed2= document.getElementById('ledButton');\n";
room2+="        var inputFan2 = document.getElementById('fanButton');\n";
// room2+="        inputFan2.style.backgroundColor=\"#1abc9c\";\n";
if(!isLed2){
room2+="            inputLed2.style.backgroundColor=\"#1abc9c\";\n";
}
if(isLed2){
room2+="            inputLed2.style.backgroundColor=\"red\";\n";
}
if(isFan2){
room2+="            inputFan2.style.backgroundColor=\"#1abc9c\";\n";
}
if(!isFan2){
room2+="            inputFan2.style.backgroundColor=\"red\";\n";
}
room2+="  </script>";
room2+="</body>\n";
room2+="</html>";
return room2;
}


void setup_Wifi(){
	Serial.println("Connecting to "); //decoration
	Serial.println(ssid);

  WiFi.mode(WIFI_STA);
	WiFi.begin(ssid,passwd);//actual connection to Wi-Fi is initialized

	while(WiFi.status() != WL_CONNECTED){ //checking for whether this has completed to Wifi
		delay(1000);
		Serial.print(".");
	}

	Serial.println("Wifi connected...!"); //decoration after connecting to WiFi
	Serial.print("Got IP: ");
	Serial.println(WiFi.localIP());
  if (!MDNS.begin("esp8266")) {             // Start the mDNS responder for esp8266.local
    Serial.println("Error setting up MDNS responder!");
  }
  Serial.println("mDNS responder started");
  
  wifiLocal = WiFi.localIP().toString();
}

void handleRoot(){//handle the request when the request is to get mainPage
	Serial.println("You called root page");
	String s = mainPageLoading();
	server.send(200,"text/html",s);//Send web page
}
void handleRoom1(){//handle the request when the request is to get room1 page
	Serial.println("You entered room1");
  isLed1=digitalRead(room1LEDpin);
  isFan1=digitalRead(room1FanRelaypin);
	String s = room1Loading(isLed1,isFan1);
	server.send(200,"text/html",s);
}
void handleRoom2(){//handle the request when the request is to get room2 page
	Serial.println("You entered room2");
  isLed2=digitalRead(room2LEDpin);
  isFan2=digitalRead(room2FanRelaypin);
	String s = room2Loading(isLed2,isFan2);
	server.send(200,"text/html",s);
}
void handle_led1(){
  digitalWrite(room1LEDpin,!digitalRead(room1LEDpin));      // Change the state of the LED1
  server.sendHeader("Location","/room1");        // Add a header to respond with a new location for the browser to go to the home page again
  Serial.println("LED1 changed the state");
  server.send(303);  
}
void handle_led2(){
  digitalWrite(room2LEDpin,!digitalRead(room2LEDpin));      // Change the state of the LED2
  server.sendHeader("Location","/room2");        // Add a header to respond with a new location for the browser to go to the home page again
  Serial.println("LED2 changed the state");
  server.send(303); 
}
void handle_fan1(){
  digitalWrite(room1FanRelaypin,!digitalRead(room1FanRelaypin));      // Change the state of the Fan1
  server.sendHeader("Location","/room1");        // Add a header to respond with a new location for the browser to go to the home page again
  Serial.println("Fan1 changed the state");
  server.send(303); 
}
void handle_fan2(){
  digitalWrite(room2FanRelaypin,!digitalRead(room2FanRelaypin));      // Change the state of the Fan2
  server.sendHeader("Location","/room2");        // Add a header to respond with a new location for the browser to go to the home page again
  Serial.println("Fan2 changed the state");
  server.send(303); 
}
void handle_NotFound(){ //if request page is not found
  server.send(404, "text/plain", "Not found");
}

void setup(){
	Serial.begin(9600);//serial begin
  WiFi.config(ip,gateway,subnet);
	setup_Wifi();//setting WiFi
	
	//Declaring the pins
	pinMode(room1LEDpin,OUTPUT);
	pinMode(room1FanRelaypin,OUTPUT);
	pinMode(room2LEDpin,OUTPUT);
	pinMode(room2FanRelaypin,OUTPUT);
	
	//Defining the pins modes
  digitalWrite(room1LEDpin,LOW);
  digitalWrite(room1FanRelaypin,HIGH);
  digitalWrite(room2LEDpin,LOW);
  digitalWrite(room2FanRelaypin,HIGH);

	//defining what to do when the request are being requested
	server.on("/", handleRoot);
	server.on("/room1",HTTP_GET, handleRoom1);
	server.on("/room2",HTTP_GET,handleRoom2);
  server.on("/room1/LED", HTTP_POST, handle_led1);
  server.on("/room2/LED", HTTP_POST, handle_led2);
  server.on("/room1/FAN", HTTP_POST, handle_fan1);
  server.on("/room2/FAN", HTTP_POST, handle_fan2);
  server.onNotFound(handle_NotFound);
	
 
	//begin the server
	server.begin();
	Serial.println("HTTP server has started");//decoration
  
}

void loop(){
    server.handleClient();//handle the requests in a loop
}
