#include <BluetoothSerial.h> 
#include <LiquidCrystal.h>
#include <Keypad.h>

const int rs = 33, en = 22, d4 = 23, d5 = 25, d6 = 26, d7 = 32;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Parameters for Bluetooth interface
char key ;
BluetoothSerial ESP_BT; 

const int Size = 5;
const char password[Size] = {'1','0','A','5','8'};
char ReadPassword[16];
int i = 0;
int CheckNoOfDigits=0;

/*
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {21, 19, 18, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {27, 14, 12, 13}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );  // struct to pass (keys , rowpins,rows and cols) values to it 
*/

void setup() {
  ESP_BT.begin(115200);
  ESP_BT.begin("ESP32_Keypad"); //Name of your Bluetooth interface -> will show up on your phone

  lcd.begin(16, 2);
  lcd.setCursor(1,0);
  lcd.print("Enter Password");
  lcd.setCursor(0, 1);
  
}

void loop() {

  
  //  char key = keypad.getKey();
    if (ESP_BT.available()) 
  {
     key = ESP_BT.read(); //Read the data you received from bluetooth keypad
    
     
     
    if(key)
    {
    if(key!='#')
    {
      lcd.print('*');
      ReadPassword[i]= key;
      i++;      
    }
    else if (key == '#')
    {
      if(i>5 || i<5)
      {
        InvalidPassword();
         
      }
      else 
      {
 
        for(int pass=0 ;pass <5;pass++)
        {
          if(ReadPassword[pass]== password[pass])
          {
            CheckNoOfDigits++;
          }
        }
            switch(CheckNoOfDigits)
            {
              case 5:
              ValidPassword();
              break;
              default:
              InvalidPassword();
              break;
              
            }
        } 
    }
    }
    }
}

void ValidPassword()
{
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Thank you");
              delay(10000);
              i=0;
              CheckNoOfDigits = 0;
              lcd.clear();
              lcd.setCursor(1,0);
              lcd.print("Enter Password");
              lcd.setCursor(0,1);
  }
  
void InvalidPassword()
{
             lcd.clear();
             lcd.setCursor(1,0);
             lcd.print("Wrong Password");
             lcd.setCursor(4,1);
             lcd.print("Try Again");
             delay(3000);
              i=0;
              CheckNoOfDigits = 0;
              lcd.clear();
              lcd.setCursor(1,0);
              lcd.print("Enter Password");
              lcd.setCursor(0,1); 
}
