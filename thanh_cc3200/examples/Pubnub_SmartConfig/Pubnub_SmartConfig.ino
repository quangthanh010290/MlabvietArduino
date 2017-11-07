#include <SPI.h>
#include <WiFi.h>
#include <PubNub.h>
const int subLedPin = GREEN_LED;
const int pubLedPin = YELLOW_LED;
const int pubLedPin1 = RED_LED;
const int buttonPin = PUSH2;
volatile int state = LOW;
volatile int flag = LOW;
int count = 0;
char ssid[] = "Robotbase";
// your network password
char password[] = "Do@nket201234";
char pubkey[] = "pub-c-f5c67fc9-fdcf-412c-bd91-8c7db8b9de55";
char subkey[] = "sub-c-5b88d540-d6e3-11e5-8256-0619f8945a4f";
char channel[] = "hello_world";
char pnData[2];
void setup()
{
  
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting WiFi SmartConfig");
//  WiFi.startSmartConfig();
WiFi.begin(ssid, password);
	while ( WiFi.status() != WL_CONNECTED) {
		// print dots while we wait to connect
		Serial.print(".");
		delay(300);
	}

  Serial.print("Connected to SSID: ");
  Serial.println(WiFi.SSID());
  while (WiFi.localIP() == INADDR_NONE) {
    // print dots while we wait for an ip addresss
    Serial.print(".");
    delay(300);
  }
  Serial.println("\nIP Address obtained");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  pinMode(subLedPin, OUTPUT);
  pinMode(pubLedPin, OUTPUT);
  pinMode(pubLedPin1, OUTPUT);
  digitalWrite(subLedPin, LOW);
  digitalWrite(pubLedPin, LOW);
  digitalWrite(pubLedPin1, LOW);
  PubNub.begin(pubkey, subkey);
  Serial.println("PubNub set up");
  WiFiClient *client;
  client = PubNub.history(channel);
  if (!client) {
	Serial.println("history error");
	delay(1000);
	return;
  }
  while (client->connected()) {
	while (client->connected() && !client->available()) ; // wait
        pnData[0] = pnData[1];
	pnData[1] = client->read();
	Serial.print(pnData[1]);
 }
 Serial.print("data =");
 if(pnData[0] == '1'){
   digitalWrite(subLedPin, HIGH);
   digitalWrite(pubLedPin, HIGH);
   digitalWrite(pubLedPin1, HIGH);
   state = HIGH;
 }
 else {
    digitalWrite(subLedPin, LOW);
    digitalWrite(pubLedPin, LOW);
    digitalWrite(pubLedPin1, LOW);
    state = LOW;
 }
 client->stop();
 Serial.println();
 pinMode(PUSH2, INPUT_PULLUP);
 attachInterrupt(PUSH2, blink, FALLING);
}

void loop()
{
  // put your main code here, to run repeatedly:
  PubSubClient *pclient = PubNub.subscribe(channel);
	if (!pclient) {
		Serial.println("subscription error");
		delay(1000);
		return;
	}
	while (pclient->wait_for_data(1)) {
                count++;
		char c = pclient->read();
                if(c == '1'){
                  Serial.print("Turn On Led");
                  digitalWrite(subLedPin, HIGH);
	          digitalWrite(pubLedPin, HIGH);
                  digitalWrite(pubLedPin1, HIGH);
                  state = HIGH;
                  break;
                }
                if(c == '0'){
                  Serial.print("Turn Off Led");
                  digitalWrite(subLedPin, LOW);
	          digitalWrite(pubLedPin, LOW);
                  digitalWrite(pubLedPin1, LOW);
                  state = LOW;
                  break;
                }
                if(count >=1000)
                {
                    count =0;
                    break;
                    Serial.println("Break");                
                }
	}
	pclient->stop();
	Serial.println("OK");
  if (flag == HIGH){
    
    Serial.println("button press");
    WiFiClient *client;
    if (state == HIGH){
    client = PubNub.publish(channel, "0");
    state = LOW;
    }else
    {
      client = PubNub.publish(channel, "1");
      state = HIGH;
    }
    
    if (!client) {
		Serial.println("publishing error");
    }
    while (client->connected()) {
		while (client->connected() && !client->available()) ; // wait
		char c = client->read();
		Serial.print(c);
	}
    client->stop();
    flag = LOW;
  }
  }
void blink()
{
  delay(10);
  if(digitalRead(PUSH2) == LOW){
    flag = HIGH;
    
  }
  
}
