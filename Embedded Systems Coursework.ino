//#define DEBUG

#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();


/*
 Create my own data type to hold house data
 Each house data variable will have 2 elements of the String object- On & Off Times and 1 element of int data type- level.
 */
typedef struct houseData {
    String onTime = "00:00";
    String offTime = "00:00";
    int level = 0;
  } houseDataType;

// Array data structure of my custom data type houseDataType to contain data about the house
houseDataType houseData[19];


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  Serial.println("BASIC");
}


void loop() {
  
  // Enumerate possible states of the finite state machine
  typedef enum {
    Start,
    printHouseData,
    GroundFloor,
    Kitchen,
    KitchenLight,
    KitchenLightOnTime,
    KitchenLightOffTime,
    KitchenLightLevel,
    KitchenHeat,
    KitchenHeatOnTime,
    KitchenHeatOffTime,
    KitchenHeatLevel,
    DiningTableLamp1,
    DiningTableLamp1OnTime,
    DiningTableLamp1OffTime,
    DiningTableLamp1Level,
    Hall,
    HallLight,
    HallLightOnTime,
    HallLightOffTime,
    HallLightLevel,
    HallHeat,
    HallHeatOnTime,
    HallHeatOffTime,
    HallHeatLevel,
    LivingRoom,
    LivingRoomLight,
    LivingRoomLightOnTime,
    LivingRoomLightOffTime,
    LivingRoomLightLevel,
    LivingRoomHeat,
    LivingRoomHeatOnTime,
    LivingRoomHeatOffTime,
    LivingRoomHeatLevel,
    SideTableLamp1,
    SideTableLamp1OnTime,
    SideTableLamp1OffTime,
    SideTableLamp1Level,
    FirstFloor,
    Bedroom1,
    Bedroom1Light,
    Bedroom1LightOnTime,
    Bedroom1LightOffTime,
    Bedroom1LightLevel,
    Bedroom1Heat,
    Bedroom1HeatOnTime,
    Bedroom1HeatOffTime,
    Bedroom1HeatLevel,
    BedsideTableLamp1,
    BedsideTableLamp1OnTime,
    BedsideTableLamp1OffTime,
    BedsideTableLamp1Level,
    DeskLamp,
    DeskLampOnTime,
    DeskLampOffTime,
    DeskLampLevel,
    Bedroom2,
    Bedroom2Light,
    Bedroom2LightOnTime,
    Bedroom2LightOffTime,
    Bedroom2LightLevel,
    Bedroom2Heat,
    Bedroom2HeatOnTime,
    Bedroom2HeatOffTime,
    Bedroom2HeatLevel,
    Bed2Lamp1,
    Bed2Lamp1OnTime,
    Bed2Lamp1OffTime,
    Bed2Lamp1Level,
    Bathroom,
    BathroomLight,
    BathroomLightOnTime,
    BathroomLightOffTime,
    BathroomLightLevel,
    BathroomHeat,
    BathroomHeatOnTime,
    BathroomHeatOffTime,
    BathroomHeatLevel,
    Outside,
    Garden,
    Garage,
    GardenWaterOnTime,
    GardenWaterOffTime,
    GarageLightOnTime,
    GarageLightOffTime,
    GarageLightLevel
  } systemState;
  // put your main code here, to run repeatedly:
  //Static variable to hold the current system state
  static systemState state = Start;
  int n;


  

  // Finite State Machine
  switch (state) {

    // Startup state
    case Start:
      lcd.clear();
      lcd.print("Start");
      n = buttonPress();
      if (n == 5) {
        state = GroundFloor;
      }
      break;

    // Floor Select
    case GroundFloor:
      lcd.clear();
      lcd.print("Ground Floor");
      n = buttonPress();

      if (n == 1 || n == 2) {
        state = Start;
      } else if (n==3) {
        state = FirstFloor;
      }
      else if (n == 4) {
        state = printHouseData;
      }
      else if (n == 5) {
        state = Kitchen;
      } else if (n == 6) {
        printDataToSerial();
        state = GroundFloor;
      }
      break;

    case FirstFloor:
      lcd.clear();
      lcd.print("First Floor");
      n = buttonPress();

      if (n == 1 || n == 2) {
        state = Start;
      }
      else if (n == 3) {
        state = Outside;
      } else if (n == 4) {
        state = GroundFloor;
      }
      else if (n == 5) {
        state = Bedroom1;
      } else if (n == 6) {
        printDataToSerial();
        state = FirstFloor;
      }
      break;

    case Outside:
      lcd.clear();
      lcd.print("Outside");
      n = buttonPress();

      if (n == 1 || n == 2) {
        state = Start;
      }
      else if (n == 3) {
        state = printHouseData;
      } else if (n == 4) {
        state = FirstFloor;
      }
      else if (n == 5) {
        Serial.println("ENHANCED:OUTSIDE");
        state = Garden;
      } else if (n == 6) {
        printDataToSerial();
        state = Outside;
      }
      break;
      
    case printHouseData: 
      lcd.clear();
      lcd.print("Press select to");
      lcd.setCursor(0,1);
      lcd.print("print house data");
      n = buttonPress();

      if (n == 1 || n == 2) {
        state = Start;
      }
      else if (n == 3) {
        state = GroundFloor;
      } else if (n == 4) {
        state = Outside;
      }
      else if (n == 5) {
        printDataToSerial();   
        
      } else if (n == 6) {
        printDataToSerial();
        state = printHouseData;
      }
      break;

    // Ground floor room options
    case Kitchen:
      lcd.clear();
      lcd.print("Kitchen");
      n = buttonPress();
      if (n == 1 || n == 2) {
        state = GroundFloor;
      }
      else if (n == 3) {
        state = Hall;
      }
      else if (n == 4) {
        state = LivingRoom;
      }
      // Select Button Pressed- Not Yet implemented
      else if (n == 5) {
        state = KitchenLight;
      } else if (n == 6) {
        printDataToSerial();
        state = Kitchen;
      }
      break;


    case Hall:

      lcd.clear();
      lcd.print("Hall");
      n = buttonPress();

      if (n == 1 || n == 2) {
        state = GroundFloor;
      }
      else if (n == 3) {
        state = LivingRoom;
      }
      else if (n == 4) {
        state = Kitchen;
      }
      else if (n == 5) {
        state = HallLight;
      } else if (n == 6) {
        printDataToSerial();
        state = Hall;
      }
      break;


    case LivingRoom:
      lcd.clear();
      lcd.print("Living Room");

      n = buttonPress();

      if (n == 1 || n == 2) {
        state = GroundFloor;
      }
      else if (n == 3) {
        state = Kitchen;
      }
      else if (n == 4) {
        state = Hall;
      }
      else if (n == 5) {
        state = LivingRoomLight;
      } else if (n == 6) {
        printDataToSerial();
        state = LivingRoom;
      }
      break;

    //First Floor Room Options
    case Bedroom1:
      lcd.clear();
      lcd.print("Bedroom 1");

      n = buttonPress();

      if (n == 1 || n == 2) {
        state = FirstFloor;
      }
      else if (n == 3) {
        state = Bedroom2;
      }
      else if (n == 4) {
        state = Bathroom;
      }
      else if (n == 5) {
        state = Bedroom1Light;
      } else if (n == 6) {
        printDataToSerial();
        state = Bedroom1;
      }
      break;


    case Bedroom2:
      lcd.clear();
      lcd.print("Bedroom 2");
      n = buttonPress();

      if (n == 1 || n == 2) {
        state = FirstFloor;
      }
      else if (n == 3) {
        state = Bathroom;
      }
      else if (n == 4) {
        state = Bedroom1;
      }
      else if (n == 5) {
        state = Bedroom2Light;
      } else if (n == 6) {
        printDataToSerial();
        state = Bedroom2;
      }
      break;


    case Bathroom:
      lcd.clear();
      lcd.print("Bathroom");
      n = buttonPress();

      if (n == 1 || n == 2) {
        state = FirstFloor;
      }
      else if (n == 3) {
        state = Bedroom1;
      }
      else if (n == 4) {
        state = Bedroom2;
      }
      else if (n == 5) {
        state = BathroomLight;
      } else if (n == 6) {
        printDataToSerial();
        state = Bathroom;
      }
      break;


    // Ground Floor device options
    // Kitchen
    case KitchenLight:
      lcd.clear();
      lcd.print("Kitchen Light");
      n = buttonPress();

      if (n == 1 || n == 2) {
        state = Kitchen;
      }
      else if (n == 3) {
        state = KitchenHeat;
      }
      else if (n == 4) {
        state = DiningTableLamp1;
      }
      else if (n == 5) {
        state = KitchenLightOnTime;
      } else if (n == 6) {
        printDataToSerial();
        state = KitchenLight ;
      }
      break;


    case KitchenHeat:
      lcd.clear();
      lcd.print("Kitchen Heat");
      n = buttonPress();

      if (n == 1 || n == 2) {
        state = Kitchen;
      }
      else if (n == 3) {
        state = DiningTableLamp1;
      }
      else if (n == 4) {
        state = KitchenLight;
      }
      else if (n == 5) {
        state = KitchenHeatOnTime;
      } else if (n == 6) {
        printDataToSerial();
        state = KitchenHeat;
      }
      break;

    case DiningTableLamp1:
      lcd.clear();
      lcd.print("Dining Table");
      lcd.setCursor(0, 1);
      lcd.print("Lamp");
      n = buttonPress();

      if (n == 1 || n == 2) {
        state = Kitchen;
      }
      else if (n == 3) {
        state = KitchenLight;
      }
      else if (n == 4) {
        state = KitchenHeat;
      }
      else if (n == 5) {
        Serial.println("ENHANCED: LAMP");
        state = DiningTableLamp1OnTime;
      } else if (n == 6) {
        printDataToSerial();
        state = DiningTableLamp1;
      }
      break;

    // Hall
    case HallLight:
      lcd.clear();
      lcd.print("Hall Light");
      n = buttonPress();

      if (n == 1 || n == 2) {
        state = Hall;
      }
      else if (n == 3 || n == 4) {
        state = HallHeat;
      } else if (n == 5) {
        state = HallLightOnTime;
      } else if (n == 6) {
        printDataToSerial();
        state = HallLight;
      }
      break;

    case HallHeat:
      lcd.clear();
      lcd.print("Hall Heat");
      n = buttonPress();

      if (n == 1 || n == 2) {
        state = Hall;
      }
      else if (n == 3 || n == 4) {
        state = HallLight;
      } else if (n == 5) {
        state = HallHeatOnTime;
      } else if (n == 6) {
        printDataToSerial();
        state = HallHeat;
      }
      break;

    // Living Room
    case LivingRoomLight:
      lcd.clear();
      lcd.print("Living Room");
      lcd.setCursor(0, 1);
      lcd.print("Light");
      n = buttonPress();

      if (n == 1 || n == 2) {
        state = LivingRoom;
      }
      else if (n == 3) {
        state = LivingRoomHeat;
      } 
      else if (n == 4) {
        state = SideTableLamp1;
      }
      else if (n == 5) {
        state = LivingRoomLightOnTime;
      } else if (n == 6) {
        printDataToSerial();
        state = LivingRoomLight;
      }
      break;

    case LivingRoomHeat:
      lcd.clear();
      lcd.print("Living Room Heat");
      n = buttonPress();

      if (n == 1 || n == 2) {
        state = LivingRoom;
      }
      else if (n == 3) {
        state = SideTableLamp1;
      } 
      else if (n == 4) {
        state = LivingRoomLight;
      }
      else if (n == 5) {
        state = LivingRoomHeatOnTime;
      } else if (n == 6) {
        printDataToSerial();
        state = LivingRoomHeat;
      }
      break;

    
    case SideTableLamp1:
      lcd.clear();
      lcd.print("Side Table");
      lcd.setCursor(0,1);
      lcd.print("Lamp");
      n = buttonPress();

      if (n == 1 || n == 2) {
        state = LivingRoom;
      }
      else if (n == 3) {
        state = LivingRoomLight;
      }
      else if (n == 4) {
        state = LivingRoomHeat;
      } else if (n == 5) {
        Serial.println(F("ENHANCED: LAMP"));
        state = SideTableLamp1OnTime;
      } else if (n == 6) {
        printDataToSerial();
        state = SideTableLamp1;
      }
      break;
    
    // First Floor Device Options
    // Bedroom 1
    case Bedroom1Light:
      lcd.clear();
      lcd.print("Bedroom 1 Light");
      n = buttonPress();

      if (n == 1 || n == 2) {
        state = Bedroom1;
      }
      else if (n == 3) {
        state = Bedroom1Heat;
      }
      else if (n == 4) {
        state = DeskLamp;
      }
      else if (n == 5) {
        state = Bedroom1LightOnTime;
      } else if (n == 6) {
        printDataToSerial();
        state = Bedroom1Light;
      }
      break;

    case Bedroom1Heat:
      lcd.clear();
      lcd.print("Bedroom 1 Heat");
      n = buttonPress();

      if (n == 1 || n == 2) {
        state = Bedroom1;
      }
      else if (n == 3) {
        state = BedsideTableLamp1;
      } 
      else if (n == 4) {
        state = Bedroom1Light;
      }
      else if (n == 5) {
        state = Bedroom1HeatOnTime;
      } else if (n == 6) {
        printDataToSerial();
        state = Bedroom1Heat;
      }
      break; 

    case BedsideTableLamp1:
      lcd.clear();
      lcd.print("Bedside Table");
      lcd.setCursor(0,1);
      lcd.print("Lamp");
      n = buttonPress();

      if (n == 1 || n == 2) {
        state = Bedroom1;
      }
      else if (n == 3) {
        state = DeskLamp;
      }
      else if (n == 4) {
        state = Bedroom1Heat;
      } else if (n == 5) {
        Serial.println(F("ENHANCED: LAMP"));
        state = BedsideTableLamp1OnTime;
      } else if (n == 6) {
        printDataToSerial();
        state = BedsideTableLamp1;
      }
      break;


    case DeskLamp:
      lcd.clear();
      lcd.print("Desk Lamp");
      n = buttonPress();

      if (n == 1 || n == 2) {
        state = Bedroom1;
      }
      else if (n == 3) {
        state = Bedroom1Light;
      }
      else if (n == 4) {
        state = BedsideTableLamp1;
      } else if (n == 5) {
        Serial.println(F("ENHANCED: LAMP"));
        state = DeskLampOnTime;
      } else if (n == 6) {
        printDataToSerial();
        state = DeskLamp;
      }
      break;

    // Bedroom 2
    case Bedroom2Light:
      lcd.clear();
      lcd.print("Bedroom 2 Light");
      n = buttonPress();

      if (n == 1 || n == 2) {
        state = Bedroom2;
      }
      else if (n == 3) {
        state = Bedroom2Heat;
      } 
      else if (n == 4) {
        state = Bed2Lamp1;
      }
      else if (n==5) {
        state = Bedroom2LightOnTime;
      } else if (n == 6) {
        printDataToSerial();
        state = Bedroom2Light;
      }
      break;

    case Bedroom2Heat:
      lcd.clear();
      lcd.print("Bedroom 2 Heat");
      n = buttonPress();

      if (n == 1 || n == 2) {
        state = Bedroom2;
      }
      else if (n == 3) {
        state = Bed2Lamp1;
      } 
      else if (n == 4) {
        state = Bedroom2Light;
      }
      else if (n == 5) {
        state = Bedroom2HeatOnTime;
      } else if (n == 6) {
        printDataToSerial();
        state = Bedroom2Heat;
      }
      break;

    case Bed2Lamp1:
      lcd.clear();
      lcd.print("Bedside Table");
      lcd.setCursor(0,1);
      lcd.print("Lamp");
      n = buttonPress();

      if (n == 1 || n == 2) {
        state = Bedroom2;
      }
      else if (n == 3) {
        state = Bedroom2Light;
      }
      else if (n == 4) {
        state = Bedroom2Heat;
      } else if (n == 5) {
        Serial.println(F("ENHANCED: LAMP"));
        state = Bed2Lamp1OnTime;
      } else if (n == 6) {
        printDataToSerial();
        state = Bed2Lamp1;
      }
      break;

    // Bathroom
    case BathroomLight:
      lcd.clear();
      lcd.print("Bathroom Light");
      n = buttonPress();

      if (n == 1 || n == 2) {
        state = Bathroom;
      }
      else if (n == 3 || n == 4) {
        state = BathroomHeat;
      } else if (n == 5) {
        state = BathroomLightOnTime;
      } else if (n == 6) {
        printDataToSerial();
        state = BathroomLight;
      }
      break;

    case BathroomHeat:
      lcd.clear();
      lcd.print("Bathroom Heat");
      n = buttonPress();

      if (n == 1 || n == 2) {
        state = Bathroom;
      }
      else if (n == 3 || n == 4) {
        state = BathroomLight;
      } else if (n == 5) {
        state = BathroomHeatOnTime;
      } else if (n == 6) {
        printDataToSerial();
        state = BathroomHeat;
      }
      break;



    // House device action options
    // Ground floor
    // Kitchen
    // Kitchen light
    case KitchenLightOnTime:
      lcd.clear();
      lcd.print("Kitchen Light");
      lcd.setCursor(0, 1);
      lcd.print("On Time");
      n = buttonPress();

      if (n == 1 || n == 2) {
        state = KitchenLight;
      }
      if (n == 3) {
        state = KitchenLightOffTime;
      }
      if (n == 4) {
        state = KitchenLightLevel;
      }
      if (n == 5) {
        lcd.clear();
        lcd.print("Enter on time");
        houseData[0].onTime = timeInput();
        #ifdef DEBUG 
          Serial.println(houseData[0].onTime);
        #endif
        state = KitchenLightOnTime;
      } 
      if (n == 6) {
        printDataToSerial();
        state = KitchenLightOnTime;
      }
      break;

      case KitchenLightOffTime:
        lcd.clear();
        lcd.print("Kitchen Light");
        lcd.setCursor(0, 1);
        lcd.print("Off Time");
        n = buttonPress();

        if (n == 1 || n == 2) {
          state = KitchenLight;
        }
        if (n == 3) {
          state = KitchenLightLevel;
        } if (n == 4) {
          state = KitchenLightOnTime;
        }
        if (n == 5) {
          lcd.clear();
          lcd.print("Enter off time");
          houseData[0].offTime = timeInput();
          state = KitchenLightOffTime;
        } 
        if (n == 6) {
        printDataToSerial();
        state = KitchenLightOffTime;
        }
        break;

      case KitchenLightLevel:
        lcd.clear();
        lcd.print("Kitchen Light");
        lcd.setCursor(0, 1);
        lcd.print("Level");
        n = buttonPress();

        if (n == 1 || n == 2) {
          state = KitchenLight;
        }
        if (n == 3) {
          state = KitchenLightOnTime;
        }
        if (n == 4) {
          state = KitchenLightOffTime;
        }
        if (n == 5) {
          lcd.clear();
          lcd.print("Enter Level");
          houseData[0].level = levelInput();
          #ifdef DEBUG 
             Serial.println(houseData[0].level);
          #endif
          state = KitchenLightLevel;
        }
        if (n == 6) {
        printDataToSerial();
        state = KitchenLightLevel;
        }
        break;
        
      // Kitchen Heat
      case KitchenHeatOnTime:
        lcd.clear();
        lcd.print("Kitchen Heat");
        lcd.setCursor(0, 1);
        lcd.print("On Time");
        n = buttonPress();

        if (n == 1 || n == 2) {
          state = KitchenHeat;
        }
        if (n == 3) {
          state = KitchenHeatOffTime;
        }
        if (n == 4) {
          state = KitchenHeatLevel;
        }
        if (n == 5) {
          lcd.clear();
          lcd.print("Enter on time");
          houseData[1].onTime = timeInput();
          state = KitchenHeatOnTime;
        }
        if (n == 6) {
        printDataToSerial();
        state = KitchenHeatOnTime;
        }
        break;

        case KitchenHeatOffTime:
          lcd.clear();
          lcd.print("Kitchen Heat");
          lcd.setCursor(0, 1);
          lcd.print("Off Time");
          n = buttonPress();

          if (n == 1 || n == 2) {
            state = KitchenHeat;
          }
          if (n == 3) {
            state = KitchenHeatLevel;
          }
          if (n == 4) {
            state = KitchenHeatOnTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter off time");
            houseData[1].offTime = timeInput();
            state = KitchenHeatOffTime;
          }
          if (n == 6) {
           printDataToSerial();
           state = KitchenHeatOffTime;
          }
          break;

        case KitchenHeatLevel:
          lcd.clear();
          lcd.print("Kitchen Heat");
          lcd.setCursor(0, 1);
          lcd.print("Level");
          n = buttonPress();
  
          if (n == 1 || n == 2) {
            state = KitchenHeat;
          }
          if (n == 3) {
            state = KitchenHeatOnTime;
          }
          if (n == 4) {
            state = KitchenHeatOffTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter Level");
            houseData[1].level = levelInput();
            state = KitchenHeatLevel;
          }
          if (n == 6) {
            printDataToSerial();
            state = KitchenHeatLevel;
          }
          break;

        case DiningTableLamp1OnTime:
          lcd.clear();
          lcd.print("Table Lamp");
          lcd.setCursor(0, 1);
          lcd.print("On Time");
          n = buttonPress();

          if (n == 1 || n == 2) {
            state = DiningTableLamp1;
          }
          if (n == 3) {
            state = DiningTableLamp1OffTime;
          }
          if (n == 4) {
            state = DiningTableLamp1Level;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter on time");
            houseData[14].onTime = timeInput();
            state = DiningTableLamp1OnTime;
          }
          if (n == 6) {
           printDataToSerial();
           state = DiningTableLamp1OnTime;
          }
          break;

        case DiningTableLamp1OffTime:
          lcd.clear();
          lcd.print("Table Lamp");
          lcd.setCursor(0, 1);
          lcd.print("Off Time");
          n = buttonPress();

          if (n == 1 || n == 2) {
            state = DiningTableLamp1;
          }
          if (n == 3) {
            state = DiningTableLamp1Level;
          }
          if (n == 4) {
            state = DiningTableLamp1OnTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter off time");
            houseData[14].offTime = timeInput();
            state = DiningTableLamp1OffTime;
          }
          if (n == 6) {
           printDataToSerial();
           state = DiningTableLamp1OffTime;
          }
          break;


        case DiningTableLamp1Level:
          lcd.clear();
          lcd.print("Table Lamp");
          lcd.setCursor(0, 1);
          lcd.print("Level");
          n = buttonPress();
  
          if (n == 1 || n == 2) {
            state = DiningTableLamp1;
          }
          if (n == 3) {
            state = DiningTableLamp1OnTime;
          }
          if (n == 4) {
            state = DiningTableLamp1OffTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter Level");
            houseData[14].level = levelInput();
            state = DiningTableLamp1Level;
          }
          if (n == 6) {
            printDataToSerial();
            state = DiningTableLamp1Level;
          }
          break;

       //  Hall Light
      case HallLightOnTime:
        lcd.clear();
        lcd.print("Hall Light");
        lcd.setCursor(0, 1);
        lcd.print("On Time");
        n = buttonPress();

        if (n == 1 || n == 2) {
          state = HallLight;
        }
        if (n == 3) {
          state = HallLightOffTime;
        }
        if (n == 4) {
          state = HallLightLevel;
        }
        if (n == 5) {
          lcd.clear();
          lcd.print("Enter on time");
          houseData[2].onTime = timeInput();
          state = HallLightOnTime;
        }
        if (n == 6) {
          printDataToSerial();
          state = HallLightOnTime;
        }
        break;


        case HallLightOffTime:
          lcd.clear();
          lcd.print("Hall Light");
          lcd.setCursor(0, 1);
          lcd.print("Off Time");
          n = buttonPress();

          if (n == 1 || n == 2) {
            state = HallLight;
          }
          if (n == 3) {
            state = HallLightLevel;
          }
          if (n == 4) {
            state = HallLightOnTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter off time");
            houseData[2].offTime = timeInput();
            state = HallLightOffTime;
          }
          if (n == 6) {
            printDataToSerial();
            state = HallLightOffTime;
          }
          break;

        case HallLightLevel:
          lcd.clear();
          lcd.print("Hall Light");
          lcd.setCursor(0, 1);
          lcd.print("Level");
          n = buttonPress();
  
          if (n == 1 || n == 2) {
            state = HallLight;
          }
          if (n == 3) {
            state = HallLightOnTime;
          }
          if (n == 4) {
            state = HallLightOffTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter Level");
            houseData[2].level = levelInput();
            state = HallLightLevel;
          }
          if (n == 6) {
            printDataToSerial();
            state = HallLightLevel;
           }
          break;

      // Hall Heat
      case HallHeatOnTime:
        lcd.clear();
        lcd.print("Hall Heat");
        lcd.setCursor(0, 1);
        lcd.print("On Time");
        n = buttonPress();

        if (n == 1 || n == 2) {
          state = HallHeat;
        }
        if (n == 3) {
          state = HallHeatOffTime;
        }
        if (n == 4) {
          state =  HallHeatLevel;
        }
        if (n == 5) {
          lcd.clear();
          lcd.print("Enter on time");
          houseData[3].onTime = timeInput();
          state = HallHeatOnTime;
        }
        if (n == 6) {
          printDataToSerial();
          state = HallHeatOnTime;
        }
        break;


        case HallHeatOffTime:
          lcd.clear();
          lcd.print("Hall Heat");
          lcd.setCursor(0, 1);
          lcd.print("Off Time");
          n = buttonPress();

          if (n == 1 || n == 2) {
            state = HallHeat;
          }
          if (n == 3) {
            state = HallHeatLevel;
          }
          if (n == 4) {
            state = HallHeatOnTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter off time");
            houseData[3].offTime = timeInput();
            state = HallHeatOffTime;
          }
          if (n == 6) {
            printDataToSerial();
            state = HallHeatOffTime;
          }
          break;

        case HallHeatLevel:
          lcd.clear();
          lcd.print("Hall Heat");
          lcd.setCursor(0, 1);
          lcd.print("Level");
          n = buttonPress();
  
          if (n == 1 || n == 2) {
            state = HallHeat;
          }
          if (n == 3) {
            state = HallHeatOnTime;
          }
          if (n == 4) {
            state = HallHeatOffTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter Level");
            houseData[3].level = levelInput();
            state = HallHeatLevel;
          }
          if (n == 6) {
            printDataToSerial();
            state = HallHeatLevel;
          }
          break;

       // Living Room
       // Living Room Light
      case LivingRoomLightOnTime:
        lcd.clear();
        lcd.print("Living Room");
        lcd.setCursor(0, 1);
        lcd.print("Light On Time");
        n = buttonPress();

        if (n == 1 || n == 2) {
          state = LivingRoomLight;
        }
        if (n == 3) {
          state = LivingRoomLightOffTime;
        }
        if (n == 4) {
          state = LivingRoomLightLevel;
        }
        if (n == 5) {
          lcd.clear();
          lcd.print("Enter on time");
          houseData[4].onTime = timeInput();
          state = LivingRoomLightOnTime;
        }
        if (n == 6) {
          printDataToSerial();
          state = LivingRoomLightOnTime;
        }
        break;


        case LivingRoomLightOffTime:
          lcd.clear();
          lcd.print("Living Room");
          lcd.setCursor(0, 1);
          lcd.print("Light Off Time");
          n = buttonPress();

          if (n == 1 || n == 2) {
            state = LivingRoomLight;
          }
          if (n == 3) {
            state = LivingRoomLightLevel;
          }
          if (n == 4) {
            state = LivingRoomLightOnTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter off time");
            houseData[4].offTime = timeInput();
            state = LivingRoomLightOffTime;
          }
          if (n == 6) {
            printDataToSerial();
            state = LivingRoomLightOffTime;
          }
          break;

        case LivingRoomLightLevel:
          lcd.clear();
          lcd.print("Living Room");
          lcd.setCursor(0, 1);
          lcd.print("Light Level");
          n = buttonPress();
  
          if (n == 1 || n == 2) {
            state = LivingRoomLight;
          }
          if (n == 3) {
            state = LivingRoomLightOnTime;
          }
          if (n == 4) {
            state = LivingRoomLightOffTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter Level");
            houseData[4].level = levelInput();
            state = LivingRoomLightLevel;
          }
          if (n == 6) {
            printDataToSerial();
            state = LivingRoomLightLevel;
          }
          break;

      // Living Room Heat
      case LivingRoomHeatOnTime:
        lcd.clear();
        lcd.print("Living Room");
        lcd.setCursor(0, 1);
        lcd.print("Heat On Time");
        n = buttonPress();

        if (n == 1 || n == 2) {
          state = LivingRoomHeat;
        }
        if (n == 3) {
          state = LivingRoomHeatOffTime;
        }
        if (n == 4) {
          state = LivingRoomHeatLevel;
        }
        if (n == 5) {
          lcd.clear();
          lcd.print("Enter on time");
          houseData[5].onTime = timeInput();
          state = LivingRoomHeatOnTime;
        }
        if (n == 6) {
          printDataToSerial();
          state = LivingRoomHeatOnTime;
        }
        break;


        case LivingRoomHeatOffTime:
          lcd.clear();
          lcd.print("Living Room");
          lcd.setCursor(0, 1);
          lcd.print("Heat Off Time");
          n = buttonPress();

          if (n == 1 || n == 2) {
            state = LivingRoomHeat;
          }
          if (n == 3) {
            state = LivingRoomHeatLevel;
          }
          if (n == 4) {
            state = LivingRoomHeatOnTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter off time");
            houseData[5].offTime = timeInput();
            state = LivingRoomHeatOffTime;
          }
          if (n == 6) {
            printDataToSerial();
            state = LivingRoomHeatOffTime;
          }
          break;

        case LivingRoomHeatLevel:
          lcd.clear();
          lcd.print("Living Room Heat");
          lcd.setCursor(0, 1);
          lcd.print("Level");
          n = buttonPress();
  
          if (n == 1 || n == 2) {
            state = LivingRoomHeat;
          }
          if (n == 3) {
            state = LivingRoomHeatOnTime;
          }
          if (n == 4) {
            state = LivingRoomHeatOffTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter Level");
            houseData[5].level = levelInput();
            state = LivingRoomHeatLevel;
          }
          if (n == 6) {
            printDataToSerial();
            state = LivingRoomHeatLevel;
          }
          break;

       case SideTableLamp1OnTime:
          lcd.clear();
          lcd.print("Side Lamp");
          lcd.setCursor(0, 1);
          lcd.print("On Time");
          n = buttonPress();

          if (n == 1 || n == 2) {
            state = SideTableLamp1;
          }
          if (n == 3) {
            state = SideTableLamp1OffTime;
          }
          if (n == 4) {
            state = SideTableLamp1Level;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter on time");
            houseData[15].onTime = timeInput();
            state = SideTableLamp1OnTime;
          }
          if (n == 6) {
           printDataToSerial();
           state = SideTableLamp1OnTime;
          }
          break;

        case SideTableLamp1OffTime:
          lcd.clear();
          lcd.print("Side Lamp");
          lcd.setCursor(0, 1);
          lcd.print("Off Time");
          n = buttonPress();

          if (n == 1 || n == 2) {
            state = SideTableLamp1;
          }
          if (n == 3) {
            state = SideTableLamp1Level;
          }
          if (n == 4) {
            state = SideTableLamp1OnTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter off time");
            houseData[15].offTime = timeInput();
            state = SideTableLamp1OffTime;
          }
          if (n == 6) {
           printDataToSerial();
           state = SideTableLamp1OffTime;
          }
          break;


        case SideTableLamp1Level:
          lcd.clear();
          lcd.print("Side Lamp");
          lcd.setCursor(0, 1);
          lcd.print("Level");
          n = buttonPress();
  
          if (n == 1 || n == 2) {
            state = SideTableLamp1;
          }
          if (n == 3) {
            state = SideTableLamp1OnTime;
          }
          if (n == 4) {
            state = SideTableLamp1OffTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter Level");
            houseData[15].level = levelInput();
            state = SideTableLamp1Level;
          }
          if (n == 6) {
            printDataToSerial();
            state = SideTableLamp1Level;
          }
          break;

    // First Floor
    // Bedroom 1
    // Bedroom 1 light
    case Bedroom1LightOnTime:
      lcd.clear();
      lcd.print("Bedroom 1 Light");
      lcd.setCursor(0, 1);
      lcd.print("On Time");
      n = buttonPress();

      if (n == 1 || n == 2) {
        state = Bedroom1Light;
      }
      if (n == 3) {
        state = Bedroom1LightOffTime;
      }
      if (n == 4) {
        state = Bedroom1LightLevel;
      }
      if (n == 5) {
        lcd.clear();
        lcd.print("Enter on time");
        houseData[6].onTime = timeInput();
        state = Bedroom1LightOnTime;
      }
      if (n == 6) {
          printDataToSerial();
          state = Bedroom1LightOnTime;
        }
      break;

      case Bedroom1LightOffTime:
        lcd.clear();
        lcd.print("Bedroom 1 Light");
        lcd.setCursor(0, 1);
        lcd.print("Off Time");
        n = buttonPress();

        if (n == 1 || n == 2) {
          state = Bedroom1Light;
        }
        if (n == 3) {
          state = Bedroom1LightLevel;
        }
        if (n == 4) {
          state = Bedroom1LightOnTime;
        }
        if (n == 5) {
          lcd.clear();
          lcd.print("Enter off time");
          houseData[6].offTime = timeInput();
          state = Bedroom1LightOffTime;
        }
        if (n == 6) {
          printDataToSerial();
          state = Bedroom1LightOffTime;
        }
        break;

      case Bedroom1LightLevel:
          lcd.clear();
          lcd.print("Bedroom 1 Light");
          lcd.setCursor(0, 1);
          lcd.print("Level");
          n = buttonPress();
  
          if (n == 1 || n == 2) {
            state = Bedroom1Light;
          }
          if (n == 3) {
            state = Bedroom1LightOnTime;
          }
          if (n == 4) {
            state = Bedroom1LightOffTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter Level");
            houseData[6].level = levelInput();
            state = Bedroom1LightLevel;
          }
          if (n == 6) {
            printDataToSerial();
            state = Bedroom1LightLevel;
          }
          break;

      // Bedroom 1 Heat
      case Bedroom1HeatOnTime:
        lcd.clear();
        lcd.print("Bedroom 1 Heat");
        lcd.setCursor(0, 1);
        lcd.print("On Time");
        n = buttonPress();

        if (n == 1 || n == 2) {
          state = Bedroom1Heat;
        }
        if (n == 3) {
          state = Bedroom1HeatOffTime;
        } 
        if (n == 4) {
          state = Bedroom1HeatLevel;
        }
        if (n == 5) {
          lcd.clear();
          lcd.print("Enter on time");
          houseData[7].onTime = timeInput();
          state = Bedroom1HeatOnTime;
        }
        if (n == 6) {
          printDataToSerial();
          state = Bedroom1HeatOnTime;
        }
        break;

        case Bedroom1HeatOffTime:
          lcd.clear();
          lcd.print("Bedroom 1 Heat");
          lcd.setCursor(0, 1);
          lcd.print("Off Time");
          n = buttonPress();

          if (n == 1 || n == 2) {
            state = Bedroom1Heat;
          }
          if (n == 3) {
            state = Bedroom1HeatLevel;
          }
          if (n == 4) {
            state = Bedroom1HeatOnTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter off time");
            houseData[7].offTime = timeInput();
            state = Bedroom1HeatOffTime;
          }
          if (n == 6) {
          printDataToSerial();
          state = Bedroom1HeatOffTime;
          }
          break;

        case Bedroom1HeatLevel:
          lcd.clear();
          lcd.print("Bedroom 1 Heat");
          lcd.setCursor(0, 1);
          lcd.print("Level");
          n = buttonPress();
  
          if (n == 1 || n == 2) {
            state = Bedroom1Heat;
          }
          if (n == 3) {
            state = Bedroom1HeatOnTime;
          }
          if (n == 4) {
            state = Bedroom1HeatOffTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter Level");
            houseData[7].level = levelInput();
            state = Bedroom1HeatLevel;
          }
          if (n == 6) {
            printDataToSerial();
            state = Bedroom1HeatLevel;
          }
          break;

       case BedsideTableLamp1OnTime:
          lcd.clear();
          lcd.print("Bedside Lamp");
          lcd.setCursor(0, 1);
          lcd.print("On Time");
          n = buttonPress();

          if (n == 1 || n == 2) {
            state = BedsideTableLamp1;
          }
          if (n == 3) {
            state = BedsideTableLamp1OffTime;
          }
          if (n == 4) {
            state = BedsideTableLamp1Level;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter on time");
            houseData[16].onTime = timeInput();
            state = BedsideTableLamp1OnTime;
          }
          if (n == 6) {
           printDataToSerial();
           state = BedsideTableLamp1OnTime;
          }
          break;

        case BedsideTableLamp1OffTime:
          lcd.clear();
          lcd.print("Bedside Lamp");
          lcd.setCursor(0, 1);
          lcd.print("Off Time");
          n = buttonPress();

          if (n == 1 || n == 2) {
            state = BedsideTableLamp1;
          }
          if (n == 3) {
            state = BedsideTableLamp1Level;
          }
          if (n == 4) {
            state = BedsideTableLamp1OnTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter off time");
            houseData[16].offTime = timeInput();
            state = BedsideTableLamp1OffTime;
          }
          if (n == 6) {
           printDataToSerial();
           state = BedsideTableLamp1OffTime;
          }
          break;


        case BedsideTableLamp1Level:
          lcd.clear();
          lcd.print("Bedside Lamp");
          lcd.setCursor(0, 1);
          lcd.print("Level");
          n = buttonPress();
  
          if (n == 1 || n == 2) {
            state = BedsideTableLamp1;
          }
          if (n == 3) {
            state = BedsideTableLamp1OnTime;
          }
          if (n == 4) {
            state = BedsideTableLamp1OffTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter Level");
            houseData[16].level = levelInput();
            state = BedsideTableLamp1Level;
          }
          if (n == 6) {
            printDataToSerial();
            state = BedsideTableLamp1Level;
          }
          break;

      case DeskLampOnTime:
          lcd.clear();
          lcd.print("Desk Lamp");
          lcd.setCursor(0, 1);
          lcd.print("On Time");
          n = buttonPress();

          if (n == 1 || n == 2) {
            state = DeskLamp;
          }
          if (n == 3) {
            state = DeskLampOffTime;
          }
          if (n == 4) {
            state = DeskLampLevel;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter on time");
            houseData[17].onTime = timeInput();
            state = DeskLampOnTime;
          }
          if (n == 6) {
           printDataToSerial();
           state = DeskLampOnTime;
          }
          break;

        case DeskLampOffTime:
          lcd.clear();
          lcd.print("Desk Lamp");
          lcd.setCursor(0, 1);
          lcd.print("Off Time");
          n = buttonPress();

          if (n == 1 || n == 2) {
            state = DeskLamp;
          }
          if (n == 3) {
            state = DeskLampLevel;
          }
          if (n == 4) {
            state = DeskLampOnTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter off time");
            houseData[17].offTime = timeInput();
            state = DeskLampOffTime;
          }
          if (n == 6) {
           printDataToSerial();
           state = DeskLampOffTime;
          }
          break;


        case DeskLampLevel:
          lcd.clear();
          lcd.print("Desk Lamp Level");
          n = buttonPress();
  
          if (n == 1 || n == 2) {
            state = DeskLamp;
          }
          if (n == 3) {
            state = DeskLampOnTime;
          }
          if (n == 4) {
            state = DeskLampOffTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter Level");
            houseData[17].level = levelInput();
            state = DeskLampLevel;
          }
          if (n == 6) {
            printDataToSerial();
            state = DeskLampLevel;
          }
          break;

      // Bedroom 2
      //  Bedroom 2 Light
      case Bedroom2LightOnTime:
        lcd.clear();
        lcd.print("Bedroom 2 Light");
        lcd.setCursor(0, 1);
        lcd.print("On Time");
        n = buttonPress();

        if (n == 1 || n == 2) {
          state = Bedroom2Light;
        }
        if (n == 3) {
          state = Bedroom2LightOffTime;
        }
        if (n == 4) {
          state = Bedroom2LightLevel;
        }
        if (n == 5) {
          lcd.clear();
          lcd.print("Enter on time");
          houseData[8].onTime = timeInput();
          state = Bedroom2LightOnTime;
        }
        if (n == 6) {
          printDataToSerial();
          state = Bedroom2LightOnTime;
        }
        break;


        case Bedroom2LightOffTime:
          lcd.clear();
          lcd.print("Bedroom 2 Light");
          lcd.setCursor(0, 1);
          lcd.print("Off Time");
          n = buttonPress();

          if (n == 1 || n == 2) {
            state = Bedroom2Light;
          }
          if (n == 3) {
            state = Bedroom2LightLevel;
          }
          if (n == 4) {
            state = Bedroom2LightOnTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter off time");
            houseData[8].offTime = timeInput();
            state = Bedroom2LightOffTime;
          }
          if (n == 6) {
            printDataToSerial();
            state = Bedroom2LightOffTime;
          }
          break;

        case Bedroom2LightLevel:
          lcd.clear();
          lcd.print("Bedroom 2 Light");
          lcd.setCursor(0, 1);
          lcd.print("Level");
          n = buttonPress();
  
          if (n == 1 || n == 2) {
            state = Bedroom2Light;
          }
          if (n == 3) {
            state = Bedroom2LightOnTime;
          }
          if (n == 4) {
            state = Bedroom2LightOffTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter Level");
            houseData[8].level = levelInput();
            state = Bedroom2LightLevel;
          }
          if (n == 6) {
            printDataToSerial();
            state = Bedroom2LightLevel;
          }
          break;

      // Bedroom 2 Heat
      case Bedroom2HeatOnTime:
        lcd.clear();
        lcd.print("Bedroom 2 Heat");
        lcd.setCursor(0, 1);
        lcd.print("On Time");
        n = buttonPress();

        if (n == 1 || n == 2) {
          state = Bedroom2Heat;
        }
        if (n == 3) {
          state = Bedroom2HeatOffTime;
        }
        if (n == 4) {
          state = Bedroom2HeatLevel;
        }
        if (n == 5) {
          lcd.clear();
          lcd.print("Enter on time");
          houseData[9].onTime = timeInput();
          state = Bedroom2HeatOnTime;
        }
        if (n == 6) {
          printDataToSerial();
          state = Bedroom2HeatOnTime;
        }
        break;


        case Bedroom2HeatOffTime:
          lcd.clear();
          lcd.print("Bedroom 2 Heat");
          lcd.setCursor(0, 1);
          lcd.print("Off Time");
          n = buttonPress();

          if (n == 1 || n == 2) {
            state = Bedroom2Heat;
          }
          if (n == 3) {
            state = Bedroom2HeatLevel;
          }
          if (n == 4) {
            state = Bedroom2HeatOnTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter off time");
            houseData[9].offTime = timeInput();
            state = Bedroom2HeatOffTime;
          }
          if (n == 6) {
            printDataToSerial();
            state = Bedroom2HeatOffTime;
          }
          break;

        case Bedroom2HeatLevel:
          lcd.clear();
          lcd.print("Bedroom 2 Heat");
          lcd.setCursor(0, 1);
          lcd.print("Level");
          n = buttonPress();
  
          if (n == 1 || n == 2) {
            state = Bedroom2Heat;
          }
          if (n == 3) {
            state = Bedroom2HeatOnTime;
          }
          if (n == 4) {
            state = Bedroom2HeatOffTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter Level");
            houseData[9].level = levelInput();
            state = Bedroom2HeatLevel;
          }
          if (n == 6) {
            printDataToSerial();
            state = Bedroom2HeatLevel;
          }
          break;

        case Bed2Lamp1OnTime:
          lcd.clear();
          lcd.print("Bedside Lamp");
          lcd.setCursor(0, 1);
          lcd.print("On Time");
          n = buttonPress();

          if (n == 1 || n == 2) {
            state = Bed2Lamp1;
          }
          if (n == 3) {
            state = Bed2Lamp1OffTime;
          }
          if (n == 4) {
            state = Bed2Lamp1Level;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter on time");
            houseData[18].onTime = timeInput();
            state = Bed2Lamp1OnTime;
          }
          if (n == 6) {
           printDataToSerial();
           state = Bed2Lamp1OnTime;
          }
          break;

        case Bed2Lamp1OffTime:
          lcd.clear();
          lcd.print("Bedside Lamp");
          lcd.setCursor(0, 1);
          lcd.print("Off Time");
          n = buttonPress();

          if (n == 1 || n == 2) {
            state = Bed2Lamp1;
          }
          if (n == 3) {
            state = Bed2Lamp1Level;
          }
          if (n == 4) {
            state = Bed2Lamp1OnTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter off time");
            houseData[18].offTime = timeInput();
            state = Bed2Lamp1OffTime;
          }
          if (n == 6) {
           printDataToSerial();
           state = Bed2Lamp1OffTime;
          }
          break;


        case Bed2Lamp1Level:
          lcd.clear();
          lcd.print("Bedside Lamp");
          lcd.setCursor(0, 1);
          lcd.print("Level");
          n = buttonPress();
  
          if (n == 1 || n == 2) {
            state = Bed2Lamp1;
          }
          if (n == 3) {
            state = Bed2Lamp1OnTime;
          }
          if (n == 4) {
            state = Bed2Lamp1OffTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter Level");
            houseData[18].level = levelInput();
            state = Bed2Lamp1Level;
          }
          if (n == 6) {
            printDataToSerial();
            state = Bed2Lamp1Level;
          }
          break;

       // Bathroom
       // Bathroom Light
      case BathroomLightOnTime:
        lcd.clear();
        lcd.print("Bathroom Light");
        lcd.setCursor(0, 1);
        lcd.print("On Time");
        n = buttonPress();

        if (n == 1 || n == 2) {
          state = BathroomLight;
        }
        if (n == 3) {
          state = BathroomLightOffTime;
        }
        if (n == 4) {
          state = BathroomLightLevel;
        }
        if (n == 5) {
          lcd.clear();
          lcd.print("Enter on time");
          houseData[10].onTime = timeInput();
          state = BathroomLightOnTime;
        }
        if (n == 6) {
          printDataToSerial();
          state =BathroomLightOnTime;
        }
        break;


        case BathroomLightOffTime:
          lcd.clear();
          lcd.print("Bathroom Light");
          lcd.setCursor(0, 1);
          lcd.print("Off Time");
          n = buttonPress();

          if (n == 1 || n == 2) {
            state = BathroomLight;
          }
          if (n == 3) {
            state = BathroomLightLevel;
          }
          if (n == 4) {
            state = BathroomLightOnTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter off time");
            houseData[10].offTime = timeInput();
            state = BathroomLightOffTime;
          }
          if (n == 6) {
            printDataToSerial();
            state =BathroomLightOffTime;
         }
          break;

        case BathroomLightLevel:
          lcd.clear();
          lcd.print("Bathroom Light");
          lcd.setCursor(0, 1);
          lcd.print("Level");
          n = buttonPress();
  
          if (n == 1 || n == 2) {
            state = BathroomLight;
          }
          if (n == 3) {
            state = BathroomLightOnTime;
          }
          if (n == 4) {
            state = BathroomLightOffTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter Level");
            houseData[10].level = levelInput();
            state = BathroomLightLevel;
          }
          if (n == 6) {
            printDataToSerial();
            state = BathroomLightLevel;
          }
          break;

      // Bathroom Heat
      case BathroomHeatOnTime:
        lcd.clear();
        lcd.print("Bathroom Heat");
        lcd.setCursor(0, 1);
        lcd.print("On Time");
        n = buttonPress();

        if (n == 1 || n == 2) {
          state = BathroomHeat;
        }
        if (n == 3) {
          state = BathroomHeatOffTime;
        }
        if (n == 4) {
          state = BathroomHeatLevel;
        }
        if (n == 5) {
          lcd.clear();
          lcd.print("Enter on time");
          houseData[11].onTime = timeInput();
          state = BathroomHeatOnTime;
        }
        if (n == 6) {
          printDataToSerial();
          state = BathroomHeatOnTime;
        }
        break;


        case BathroomHeatOffTime:
          lcd.clear();
          lcd.print("Bathroom Heat");
          lcd.setCursor(0, 1);
          lcd.print("Off Time");
          n = buttonPress();

          if (n == 1 || n == 2) {
            state = BathroomHeat;
          }
          if (n == 3) {
            state = BathroomHeatLevel;
          }
          if (n == 4) {
            state = BathroomHeatOnTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter off time");
            houseData[11].offTime = timeInput();
            state = BathroomHeatOffTime;
          }
          if (n == 6) {
            printDataToSerial();
            state = BathroomHeatOffTime;
          }
          break;

        case BathroomHeatLevel:
          lcd.clear();
          lcd.print("Bathroom Heat");
          lcd.setCursor(0, 1);
          lcd.print("Level");
          n = buttonPress();
  
          if (n == 1 || n == 2) {
            state = BathroomHeat;
          }
          if (n == 3) {
            state = BathroomHeatOnTime;
          }
          if (n == 4) {
            state = BathroomHeatOffTime;
          }
          if (n == 5) {
            lcd.clear();
            lcd.print("Enter Level");
            houseData[11].level = levelInput();
            state = BathroomHeatLevel;
          }
          if (n == 6) {
            printDataToSerial();
            state = BathroomHeatLevel;
          }
          break;

      // Outside
      case Garden:
        lcd.clear();
        lcd.print("Garden");
        n = buttonPress();
  
        if (n == 1 || n == 2) {
          state = Outside;
        }
        else if (n == 3 || n == 4) {
          state = Garage;
        }
        else if (n == 5) {
          state = GardenWaterOnTime;
        } else if (n == 6) {
          printDataToSerial();
          state = Garden;
        }
        break;

      case Garage:
        lcd.clear();
        lcd.print("Garage");
        n = buttonPress();
  
        if (n == 1 || n == 2) {
          state = Outside;
        }
        else if (n == 3 || n == 4) {
          state = Garden;
        }
        else if (n == 5) {
          state = GarageLightOnTime;
        } else if (n == 6) {
          printDataToSerial();
          state = Garage;
        }
        break;

     case GardenWaterOnTime:
        lcd.clear();
        lcd.print("Garden Water");
        lcd.setCursor(0, 1);
        lcd.print("On Time");
        n = buttonPress();

        if (n == 1 || n == 2) {
          state = Garden;
        }
        if (n == 3 || n == 4) {
          state = GardenWaterOffTime;
        }
        if (n == 5) {
          lcd.clear();
          lcd.print("Enter on time");
          houseData[12].onTime = timeInput();
          state = GardenWaterOnTime;
        }
        if (n == 6) {
          printDataToSerial();
          state = GardenWaterOnTime;
        }
        break;

      case GardenWaterOffTime:
        lcd.clear();
        lcd.print("Garden Water");
        lcd.setCursor(0, 1);
        lcd.print("Off Time");
        n = buttonPress();

        if (n == 1 || n == 2) {
          state = Garden;
        }
        if (n == 3 || n == 4) {
          state = GardenWaterOnTime;
        }
        if (n == 5) {
          lcd.clear();
          lcd.print("Enter off time");
          houseData[12].offTime = timeInput();
          state = GardenWaterOffTime;
        }
        if (n == 6) {
          printDataToSerial();
          state = GardenWaterOffTime;
        }
        break;

      case GarageLightOnTime:
        lcd.clear();
        lcd.print("Garage Light");
        lcd.setCursor(0, 1);
        lcd.print("On Time");
        n = buttonPress();

        if (n == 1 || n == 2) {
          state = Garage;
        }
        if (n == 3) {
          state = GarageLightOffTime;
        }
        if (n == 4) {
          state = GarageLightLevel;
        }
        if (n == 5) {
          lcd.clear();
          lcd.print("Enter on time");
          houseData[13].onTime = timeInput();
          state = GarageLightOnTime;
        }
        if (n == 6) {
          printDataToSerial();
          state = GarageLightOnTime;
        }
        break;

      case GarageLightOffTime:
        lcd.clear();
        lcd.print("Garage Light");
        lcd.setCursor(0, 1);
        lcd.print("Off Time");
        n = buttonPress();

        if (n == 1 || n == 2) {
          state = Garage;
        }
        if (n == 3) {
          state = GarageLightLevel;
        }
        if (n == 4) {
          state = GarageLightOnTime;
        }
        if (n == 5) {
          lcd.clear();
          lcd.print("Enter on time");
          houseData[13].offTime = timeInput();
          state = GarageLightOffTime;
        }
        if (n == 6) {
          printDataToSerial();
          state = GarageLightOffTime;
        }
        break;

      case GarageLightLevel:
        lcd.clear();
        lcd.print("Garage Light");
        lcd.setCursor(0, 1);
        lcd.print("Level");
        n = buttonPress();

        if (n == 1 || n == 2) {
          state = Garage;
        }
        if (n == 3) {
          state = GarageLightOnTime;
        }
        if (n == 4) {
          state = GarageLightOffTime;
        }
        if (n == 5) {
          lcd.clear();
          lcd.print("Enter Level");
          houseData[13].level = levelInput();
          state = GarageLightLevel;
        }
        if (n == 6) {
          printDataToSerial();
          state = GarageLightLevel;
        }
        break;    
  }
}




// Function to monitor button presses and return an integer which can be interpreted in the FSM
int buttonPress() {
  static uint8_t oldButtonState;
  uint8_t newButtonState;
  int n;

  while (true) {
    oldButtonState = lcd.readButtons();

    // Button Up
    if (oldButtonState & BUTTON_UP) {
      bool buttonHeld = true;
      while (buttonHeld) {
        newButtonState = lcd.readButtons();
        if (newButtonState != oldButtonState) {
          #ifdef DEBUG
            Serial.println("Button Up");
          #endif
          return n = 1;
        }
      }
    }

    else if (oldButtonState & BUTTON_DOWN) {
      bool buttonHeld = true;
      while (buttonHeld) {
        newButtonState = lcd.readButtons();
        if (newButtonState != oldButtonState) {
          #ifdef DEBUG
            Serial.println("Button Down");
          #endif
          return n = 2;
        }
      }
    }

    else if (oldButtonState & BUTTON_RIGHT) {
      bool buttonHeld = true;
      while (buttonHeld) {
        newButtonState = lcd.readButtons();
        if (newButtonState != oldButtonState) {
          #ifdef DEBUG
            Serial.println("Button Right");
          #endif
          return n = 3;
        }
      }
    }

    else if (oldButtonState & BUTTON_LEFT) {
      bool buttonHeld = true;
      while (buttonHeld) {
        newButtonState = lcd.readButtons();
        if (newButtonState != oldButtonState) {
          #ifdef DEBUG
            Serial.println("Button Left");
          #endif
          return n = 4; 
        }
      }
    }

    else if (oldButtonState & BUTTON_SELECT) {
      bool buttonHeld = true;
      while (buttonHeld) {
        newButtonState = lcd.readButtons();
        if (newButtonState != oldButtonState) {
          #ifdef DEBUG
            Serial.println("Button Select");
          #endif
          return n = 5;
        }
      }
    }

   else if (Serial.available() > 0 && Serial.read() == 'Q') {
    Serial.println(F("ENHANCED: QUERY")  );
    return n = 6;
   }

  }
}


// Collects and validates user input of type String in the form HH:MM
String timeInput() {
  String userInputTime;
  while (true) {
    if (Serial.available() > 0) {
      userInputTime = Serial.readString();

      if (userInputTime.length() == 6) {
        char char1, char2, char3, char4, char5;
        char1 = userInputTime[0];
        char2 = userInputTime[1];
        char3 = userInputTime[2];
        char4 = userInputTime[3];
        char5 = userInputTime[4];
        int no1, no2, no3, no4;
        no1 = char1 - '0';
        no2 = char2 - '0';
        no3 = char4 - '0';
        no4 = char5 - '0';
        
        
        if (char3 == ':') {
          if (no1 == 0 || no1 == 1) {
            if (no2 >= 0 && no2 <= 9) {
              if (no3 >= 0 && no3 <=5) {
                if (no4 >= 0 && no4 <= 9) {
                  return userInputTime;
                } else {
                  Serial.println(F("Please enter a valid time in the format HH:MM"));
                } 
                } else {
                  Serial.println(F("Please enter a valid time in the format HH:MM"));
                } 
              } else {
                  Serial.println(F("Please enter a valid time in the format HH:MM"));
              } 
            
          } else if (no1 == 2) {
            if (no2 >= 0 && no2 <= 3) {
              if (no3 >= 0 && no3 <=5) {
                if (no4 >= 0 && no4 <= 9) {
                  return userInputTime; 
                } else {
                  Serial.println(F("Please enter a valid time in the format HH:MM"));
                } 
                } else {
                  Serial.println(F("Please enter a valid time in the format HH:MM"));
                } 
              } else {
                  Serial.println(F("Please enter a valid time in the format HH:MM"));
              } 
            } else {
              Serial.println(F("Please enter a valid time in the format HH:MM"));
            
          }
        } else {
          Serial.println(F("Please enter a valid time in the format HH:MM"));
        }
      } else {
        Serial.println(F("Please enter a valid time in the format HH:MM"));
      }
    }
  }
}


// Collects and validates user input of an intger type and between 0 and 100
int levelInput() {
  int level;
  while (true) {
    if (Serial.available() > 0) {
      level = Serial.parseInt();
      if (level >= 0 && level <= 100) {
        return level;
      } else {
        Serial.println(F("Please enter a valid level between 0 and 100"));
      }
    }
  }
}

// Prints all house data to serial monitor
void printDataToSerial() {
        //Kitchen Light
        Serial.print(F("Ground/Kitchen/Light/Main/On:"));
        Serial.print((String)houseData[0].onTime);
        Serial.print(F("Ground/Kitchen/Light/Main/Off:"));
        Serial.print((String)houseData[0].offTime);
        Serial.print(F("Ground/Kitchen/Light/Main/Level:"));
        Serial.println((String)houseData[0].level);

        // Kitchen Heat
        Serial.print(F("Ground/Kitchen/Heat/Main/On:"));
        Serial.print((String)houseData[1].onTime);
        Serial.print(F("Ground/Kitchen/Heat/Main/Off:"));
        Serial.print((String)houseData[1].offTime);
        Serial.print(F("Ground/Kitchen/Heat/Main/Level:"));
        Serial.println((String)houseData[1].level);

        // Kitchen Lamp 1
        Serial.print(F("Ground/Kitchen/Lamp/Dining Table/On:"));
        Serial.print((String)houseData[14].onTime);
        Serial.print(F("Ground/Kitchen/Lamp/Dining Table/Off:"));
        Serial.print((String)houseData[14].offTime);
        Serial.print(F("Ground/Kitchen/Lamp/Dining Table/Level:"));
        Serial.println((String)houseData[14].level);

        // Hall Light
        Serial.print(F("Ground/Hall/Light/Main/On:"));
        Serial.print((String)houseData[2].onTime);
        Serial.print(F("Ground/Hall/Light/Main/Off:"));
        Serial.print((String)houseData[2].offTime);
        Serial.print(F("Ground/Hall/Light/Main/Level:"));
        Serial.println((String)houseData[2].level);

        // Hall Heat
        Serial.print(F("Ground/Hall/Heat/Main/On:"));
        Serial.print((String)houseData[3].onTime);
        Serial.print(F("Ground/Hall/Heat/Main/Off:"));
        Serial.print((String)houseData[3].offTime);
        Serial.print(F("Ground/Hall/Heat/Main/Level:"));
        Serial.println((String)houseData[3].level);

        // Living Room Light
        Serial.print(F("Ground/Living Room/Light/Main/On:"));
        Serial.print((String)houseData[4].onTime);
        Serial.print(F("Ground/Living Room/Light/Main/Off:"));
        Serial.print((String)houseData[4].offTime);
        Serial.print(F("Ground/Living Room/Light/Main/Level:"));
        Serial.println((String)houseData[4].level);

        // Living Room Heat
        Serial.print(F("Ground/Living Room/Heat/Main/On:"));
        Serial.print((String)houseData[5].onTime);
        Serial.print(F("Ground/Living Room/Heat/Main/Off:"));
        Serial.print((String)houseData[5].offTime);
        Serial.print(F("Ground/Living Room/Heat/Main/Level:"));
        Serial.println((String)houseData[5].level);

        // Living Room Lamp 1
        Serial.print(F("Ground/Living Room/Lamp/Side Table/On:"));
        Serial.print((String)houseData[15].onTime);
        Serial.print(F("Ground/Living Room/Lamp/Side Table/Off:"));
        Serial.print((String)houseData[15].offTime);
        Serial.print(F("Ground/Living Room/Lamp/Side Table/Level:"));
        Serial.println((String)houseData[15].level);

        // Bedroom 1 Light
        Serial.print(F("First/Bedroom 1/Light/Main/On:"));
        Serial.print((String)houseData[6].onTime);
        Serial.print(F("First/Bedroom 1/Light/Main/Off:"));
        Serial.print((String)houseData[6].offTime);
        Serial.print(F("First/Bedroom 1/Light/Main/Level:"));
        Serial.println((String)houseData[6].level);

        // Bedroom 1 Heat
        Serial.print(F("First/Bedroom 1/Heat/Main/On:"));
        Serial.print((String)houseData[7].onTime);
        Serial.print(F("First/Bedroom 1/Heat/Main/Off:"));
        Serial.print((String)houseData[7].offTime);
        Serial.print(F("First/Bedroom 1/Heat/Main/Level:"));
        Serial.println((String)houseData[7].level);

        // Bedroom 1 Lamp 1
        Serial.print(F("First/Bedroom 1/Lamp/Bedside Light 1/On:"));
        Serial.print((String)houseData[16].onTime);
        Serial.print(F("First/Bedroom 1/Lamp/Bedside Light 1/Off:"));
        Serial.print((String)houseData[16].offTime);
        Serial.print(F("First/Bedroom 1/Lamp/Bedside Light 1/Level:"));
        Serial.println((String)houseData[16].level);

        //Bedroom 2 Desk Lamp
        Serial.print(F("First/Bedroom 1/Lamp/Desk Lamp/On:"));
        Serial.print((String)houseData[17].onTime);
        Serial.print(F("First/Bedroom 1/Lamp/Desk Lamp/Off:"));
        Serial.print((String)houseData[17].offTime);
        Serial.print(F("First/Bedroom 1/Lamp/Desk Lamp/Level:"));
        Serial.println((String)houseData[17].level);

        // Bedroom 2 Light
        Serial.print(F("First/Bedroom 2/Light/Main/On:"));
        Serial.print((String)houseData[8].onTime);
        Serial.print(F("First/Bedroom 2/Light/Main/Off:"));
        Serial.print((String)houseData[8].offTime);
        Serial.print(F("First/Bedroom 2/Light/Main/Level:"));
        Serial.println((String)houseData[8].level);

        // Bedroom 2 Heat
        Serial.print(F("First/Bedroom 2/Heat/Main/On:"));
        Serial.print((String)houseData[9].onTime);
        Serial.print(F("First/Bedroom 2/Heat/Main/Off:"));
        Serial.print((String)houseData[9].offTime);
        Serial.print(F("First/Bedroom 2/Heat/Main/Level:"));
        Serial.println((String)houseData[9].level);    

        // Bedroom 2 Lamp 1
        Serial.print(F("First/Bedroom 2/Lamp/Bedside Light 1/On:"));
        Serial.print((String)houseData[18].onTime);
        Serial.print(F("First/Bedroom 2/Lamp/Bedside Light 1/Off:"));
        Serial.print((String)houseData[18].offTime);
        Serial.print(F("First/Bedroom 2/Lamp/Bedside Light 1/Level:"));
        Serial.println((String)houseData[18].level);

        // Bathroom Light
        Serial.print(F("First/Bathroom/Light/Main/On:"));
        Serial.print((String)houseData[10].onTime);
        Serial.print(F("First/Bathroom/Light/Main/Off:"));
        Serial.print((String)houseData[10].offTime);
        Serial.print(F("First/Bathroom/Light/Main/Level:"));
        Serial.println((String)houseData[10].level);

        // Bathroom Heat
        Serial.print(F("First/Bathroom/Heat/Main/On:"));
        Serial.print((String)houseData[11].onTime);
        Serial.print(F("First/Bathroom/Heat/Main/Off:"));
        Serial.print((String)houseData[11].offTime);
        Serial.print(F("First/Bathroom/Heat/Main/Level:"));
        Serial.println((String)houseData[11].level);

        // Garden Water
        Serial.print(F("Outside/Garden/Water/Main/On:"));
        Serial.print((String)houseData[12].onTime);
        Serial.print(F("Outside/Garden/Water/Main/Off:"));
        Serial.print((String)houseData[12].offTime);

        // Garage Light
        Serial.print(F("Outside/Garage/Light/Main/On:"));
        Serial.print((String)houseData[13].onTime);
        Serial.print(F("Outside/Garage/Light/Main/Off:"));
        Serial.print((String)houseData[13].offTime);
        Serial.print(F("Outside/Garage/Light/Main/Level:"));
        Serial.println((String)houseData[11].level);
}
