#define BLYNK_TEMPLATE_ID           "TMPLkRa7osKi"
#define BLYNK_DEVICE_NAME           "Robot"
#define BLYNK_AUTH_TOKEN            "F5kA7akB3_W2iqMIT9pBgRQTpPwXgvF3"

#define sensor D0
// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "vu0607";
char pass[] = "06072000";
int i;
int zone;
WidgetLED ledConnect(V0);
WidgetLED zone1(V1);
WidgetLED zone2(V2);
WidgetLED zone3(V3);
WidgetLED zone4(V4);
WidgetLED zone5(V5);

BlynkTimer timer;

// V0 LED Widget is blinking
void blinkLedWidget()
{
  if (ledConnect.getValue()) {
    ledConnect.off();
  } else {
    ledConnect.on();
  }
}

void zone1Display(int state) {
  if (state == 1) {
    zone1.on();
  } else if (state == 0) {
    zone1.off();
  }
}

void zone2Display(int state) {
  if (state == 1) {
    zone2.on();
  } else if (state == 0) {
    zone2.off();
  }
}

void zone3Display(int state) {
  if (state == 1) {
    zone3.on();
  } else if (state == 0) {
    zone3.off();
  }
}

void zone4Display(int state) {
  if (state == 1) {
    zone4.on();
  } else if (state == 0) {
    zone4.off();
  }
}

void zone5Display(int state) {
  if (state == 1) {
    zone5.on();
  } else if (state == 0) {
    zone5.off();
  }
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  i = 0;

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  timer.setInterval(1000L, blinkLedWidget);
}

void loop()
{
  Blynk.run();
  timer.run();
  if(digitalRead(sensor) == 1) {
    i = i + 1
    while(digitalRead == 1) {}
    }
  if ( i == 0 ) {
    zone1Display(0);
    zone2Display(0);
    zone3Display(0);
    zone4Display(0);
    zone5Display(0);
  }
  if ( i == 1 ) {
    zone1Display(1);
  }

  if ( i == 2 ) {
    zone2Display(1);
  }
  if ( i == 3 ) {
    zone3Display(1);
  }
  if ( i == 4 ) {
    zone4Display(1);
  }
  if ( i == 5 ) {
    zone5Display(1);
  }
  delay(50);
  Blynk.run();
  timer.run();
}
