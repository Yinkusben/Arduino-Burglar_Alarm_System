#include <Keypad.h> //Libraries needed
#include <virtuabotixRTC.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

#define BUZZ A0
#define PIR1 A1
#define PIR2 A2
#define PIR3 A3
#define PIR4 13 
#define REED A6


#define EEPROM_TIME_ADDR 0
#define EEPROM_PHONE_ADDR 50 

LiquidCrystal_I2C LCD(0x27,16,2);

virtuabotixRTC myRTC(2, 3, 4); //Wiring of the RTC (CLK,DAT,RST)
                               //If you change the wiring change the pins here also

const byte numRows= 4; //number of rows on the keypad
const byte numCols= 4; //number of columns on the keypad

//keymap defines the key pressed according to the row and columns just as appears on the keypad
char keymap[numRows][numCols]= 
{
{'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'}, 
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};


byte rowPins[numRows] = {12, 11, 10, 9}; //Rows 0 to 3 //if you modify your pins you should modify this too
byte colPins[numCols]= {8, 7, 6, 5}; //Columns 0 to 3

//initializes an instance of the Keypad class
Keypad keypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

bool sensor[5];
bool alarmStatus = false;

struct trigTime {
  uint8_t hour;
  uint8_t min;
};

struct trigTime startTime;
struct trigTime stopTime;

String phoneNum = "+234xxxxxxxxxx"; // To store SMS phone number

enum screenPages {
  HOME,
  TRIG_TIME,
  TIME,
  PHONE,
};


char keypressed; // variable to store key presses

bool screenClear = false; //. THis variable is used as a flag to prevent the i2c LCD from flickering, when we
//We will only do LCD.clear() whemever we transition from one screen to another

const unsigned long backlitTime = 10000;
unsigned long backlitPrev = 0;
unsigned long scrTimeOut = 20000;
unsigned long scrTimeOut_prev = 0;

uint8_t readSensors() {
  //sensor[0] = digitalRead(REED);
  sensor[0] = digitalRead(PIR1);
  sensor[1] = digitalRead(PIR2);
  sensor[2] = digitalRead(PIR3);
  sensor[3] = digitalRead(PIR4);

  static uint8_t motionCount = 0;

  for (int i=0; i<=sizeof(sensor)/sizeof(sensor[0]); i++)
      {
        if (sensor[i] == HIGH)
          {
            //sset timer to millis
            // increament motioncounter
          }
      }

  uint8_t result = 0;

  for (int i=0; i<=sizeof(sensor)/sizeof(sensor[0])-1; i++){
    if (sensor[i] == HIGH)
      result++;
  }

  return result;
}

void send_sms() {

}

void alarm() {

}

//unsigned long time_and_date(uint8_t di)

void setting(uint8_t page){
  switch (page){
    char option;

    case 0:
      LCD.clear();
      LCD.setCursor(0, 0);
      (alarmStatus == true)? LCD.print("Turn OFF now?") : LCD.print("Turn ON now?");
      LCD.setCursor(0, 1);
      LCD.print("B: No    C: Yes");

      option = keypad.waitForKey();

      if (option =='C' && alarmStatus == false){
        alarmStatus = true;
        LCD.clear();
        LCD.print("Alarm ACTIVATED!");
        delay(1000);
       }

       else if (option =='C' && alarmStatus == true){
        alarmStatus = false;
        LCD.clear();
        LCD.print("Alarm is OFF");
        delay(1000);
       }
       LCD.clear();

      break;

    case 1:
      LCD.clear();
      LCD.setCursor(0, 0);
      LCD.print("1: Set ON time");
      LCD.setCursor(0, 1);
      LCD.print("2: Set OFF time");

      option = keypad.waitForKey();
        
      if (option == '1' || option == '2')
      {
        LCD.clear();
        LCD.setCursor(0, 0);
        (option == '1')? LCD.print("   Set ON Time  ") : LCD.print(" Set OFF Time  ");
        LCD.setCursor(7, 1);
        LCD.print(":");

        char key[4];

        for (int i = 0; i<=3; i++){
          key[i] = keypad.waitForKey();
          
          if(key[i] - 48 >= 0 && key[i] - 48 <= 9){ // Checks if key pressed is a number
              (i < 2)? LCD.setCursor(i+5, 1) : LCD.setCursor(i+6, 1);
              LCD.print(key[i]);
          }
          else if(key[i] == 'B'){
            return; // Abort the settings and Go back
          }
          else {
            i--; //Repeat the iteration if the key is not a number
          }
        }
        delay(500);

        int hr1 = (key[0]-48)*10;
        int hr2 = key[1] - 48;
        int hour = hr1+hr2;

        int min1 = (key[2]- 48) * 10;
        int min2 = key[3] - 48;
        int minute = min1+min2;

        if (hour > 24 || minute > 60){
          LCD.clear();
          LCD.print("Invalid Time!");
          delay(1000);
          return;
        }

        if (option == '1') {
          startTime.hour = hour;
          startTime.min = minute;
          EEPROM.put(0, startTime);
        } else{
          stopTime.hour = hour;
          stopTime.min = minute;
          EEPROM.put(sizeof(startTime), stopTime);
        }
        
        LCD.clear();
        LCD.print("Saved !");
        delay(1000);
      }
        else if (option == 'B'){
          LCD.clear();
          return;
        }
        else {
          LCD.clear();
          LCD.print("Invalid option");
          delay(1000);
      }

     break;

    case 2:
      LCD.clear();
      LCD.setCursor(0,0);
      LCD.print("Set Time & Date?");
      LCD.setCursor(0, 1);
      LCD.print("B:(No)  C:(Yes)");

      option = keypad.waitForKey();
      if (option == 'C') 
      {
          LCD.clear();
          LCD.print("   Setup Date   ");
          delay(1000);
          LCD.clear();
          LCD.print("DD/MM/YYYY:");
          LCD.setCursor(0,1);
          LCD.print("  /  /    ");
          LCD.setCursor(0,1);

          char date[8];

          for (int i = 0; i<=7; i++)
          {
            date[i] = keypad.waitForKey();
          
            if (date[i] - 48 >= 0 && date[i] - 48 <= 9)
            {
              if (i<2) LCD.setCursor(i,1);
              else if(i>=2 && i<=3) LCD.setCursor(i+1,1);
              else if(i>=4) LCD.setCursor(i+2,1);
              LCD.print(date[i]); // Checks if key pressed is a number
            }
            else if(date[i] == 'B') return; // Abort the settings and Go back
            else i--; //Repeat the iteration if the key is not a number
          }
          delay(500);
          LCD.clear();
          LCD.print("Set Time HR:MIN");
          LCD.setCursor(7, 1);
          LCD.print(":");

          char time[4];
          
          for (int i = 0; i<=3; i++)
          {
            time[i] = keypad.waitForKey();
          
            if (time[i] - 48 >= 0 && time[i] - 48 <= 9)
            { 
              (i < 2)? LCD.setCursor(i+5, 1) : LCD.setCursor(i+6, 1);
              LCD.print(time[i]); // Checks if key pressed is a number
            }
            else if(time[i] == 'B') return; // Abort the settings and Go back
            else i--; //Repeat the iteration if the key is not a number
          }
          
          //the keys pressed are stored into chars I convert them to int then i did some multiplication to get the code as an int of xxxx

          int d1 = (date[0]-48)*10;
          int d2 = date[1]-48;
          int N_day=d1+d2;

          int m1 = (date[2]-48)*10;
          int m2 = date[3]-48;
          int N_month=m1+m2;

          int y1 = (date[4]-48)*1000; 
          int y2 = (date[5]-48)*100;
          int y3 = (date[6]-48)*10;
          int y4 = date[7]-48;
          int N_year=y1+y2+y3+y4;

          int h1 = (time[0]-48)*10;
          int h2 = time[1]-48;
          int N_hour=h1+h2;

          int mins1 = (time[2]-48)*10;
          int mins2 = time[3]-48;
          int N_minutes=mins1+mins2;

          myRTC.setDS1302Time(22, N_minutes, N_hour, 1, N_day, N_month, N_year);
          //once we're done setting the date and time we transfer to values to the RTC module
          //the 22 stands for seconds you can add a setup for it too if you want
          //the 1 stands for day of the week, as long I don't show it on the screen I don't change it

          LCD.clear();
          LCD.print("Saved!");
          delay(1000);
      }

      LCD.clear();

      break;

    case 3:
      LCD.clear();
      LCD.setCursor(0, 0);
      LCD.print("Change Number:  ");

      char num[10];

      for (uint8_t i=0; i<=10; i++){
        num[i] = keypad.waitForKey();

        if (num[i]-48>=0 && num[i]-48<=9){
          LCD.setCursor(i, 1);
          LCD.print(num[i]);
          Serial.println(i);
        }
        else if (num[i] == 'B'){
          LCD.clear();
          return;
        }
        else if(num[i] == 'D'){
          LCD.setCursor(i-1, 1);
          LCD.print(' ');
          i = i-2;
        }
        else {
          i--;
        }
        }

      delay(500);

      for (int i=0; i<=9; i++){
        phoneNum[i+4] = num[i+1]; //This ensures the number is in +234xx(Nigera code) format;
        EEPROM.update(EEPROM_PHONE_ADDR + i, num[i+1]);
      }

      LCD.clear();
      LCD.setCursor(0, 0);
      LCD.print("Saved !");
      delay(1000);
      LCD.clear();

      break;

  }

  backlitPrev = millis();
}

void screens(uint8_t * currentScreen) {

  switch (*currentScreen) {

    case HOME:
      if (screenClear){
      LCD.clear();
      screenClear = false;
      }
      LCD.setCursor(0,0);
      LCD.print("Status: ");
      LCD.setCursor(8, 0);
      (alarmStatus == true)? LCD.print("ARMED !") : LCD.print("DISARMED");
      LCD.setCursor(0,1);
      (alarmStatus == true)? LCD.print("Till " + String(stopTime.hour) + ":" + String(stopTime.min)) 
      : LCD.print("Till " + String(startTime.hour) + ":" + String(startTime.min));

      if (keypressed == 'C') {
        setting(0);
      }
      break;

    case TRIG_TIME:
      if (screenClear){
      LCD.clear();
      screenClear = false;
      }
      LCD.setCursor(0,0);
      LCD.print("ON Time: ");
      LCD.setCursor(11, 0);
      LCD.print(String(startTime.hour) + ":" + String(startTime.min));
      LCD.setCursor(0,1);
      LCD.print("OFF Time: ");
      LCD.setCursor(11, 1);
      LCD.print(String(stopTime.hour) + ":" + String(stopTime.min));
      
      if (keypressed == 'C') {
        setting(1);
      }

      break;

    case TIME:
      if (screenClear){
      LCD.clear();
      screenClear = false;
      }
      LCD.setCursor(0,0);
      LCD.print("Time: ");
      LCD.setCursor(6, 0);
      LCD.print(String(myRTC.hours) + ":" + String(myRTC.minutes) + ":" + String(myRTC.seconds));
      LCD.setCursor(0, 1);
      LCD.print("Date: ");
      LCD.setCursor(6, 1);
      LCD.print(String(myRTC.dayofmonth) + "/" + String(myRTC.month) + "/" + String(myRTC.year));

      if(keypressed == 'C')
      {
          setting(2);
      }

      break;

    case PHONE:
      if (screenClear){
      LCD.clear();
      screenClear = false;
      }
      LCD.setCursor(0,0);
      LCD.print("SMS NUMBER");
      LCD.setCursor(0, 1);
      LCD.print(phoneNum);

      if (keypressed == 'C'){
        setting(3);
      }

      break;

    default:
      *currentScreen = HOME;
      break;
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(PIR1, INPUT);
  pinMode(PIR2, INPUT);
  pinMode(PIR3, INPUT);
  pinMode(PIR4, INPUT);
  pinMode(REED, INPUT);
  pinMode(BUZZ, OUTPUT);

  digitalWrite(BUZZ, LOW);

  EEPROM.get(EEPROM_TIME_ADDR, startTime); //Reads the trigger Time stored in the EEPROM
  EEPROM.get(sizeof(startTime), stopTime);

  for(int i=0; i<=9; i++){ // Reads The SMS phone Number stored in the EEPROM
    phoneNum[i+4] = EEPROM.read(EEPROM_PHONE_ADDR + i);
  }
  
  LCD.init();
  LCD.backlight();
  LCD.home();

}

void loop() {
  myRTC.updateTime(); // Get updated Time and Date values from the RTC Module

  static uint8_t screen = HOME; // variable to keep track of differnt screen page

  uint8_t result = readSensors();

  keypressed = keypad.getKey();

  if (keypressed == 'A'){
    screen++;
    screenClear = true;
  }
  if (keypressed == 'B'){
    screen--;
    screenClear = true;
  }

  if (keypressed != NO_KEY)
    {
    backlitPrev = millis();
    scrTimeOut_prev = millis();
    }

  if (millis() - backlitPrev >= backlitTime) LCD.noBacklight();
  else  LCD.backlight();

  if(millis() - scrTimeOut_prev >= scrTimeOut ) screen = HOME; // Make sure the screen returns to HOME is the device is idle for 20sec
   
  screens(&screen);

}