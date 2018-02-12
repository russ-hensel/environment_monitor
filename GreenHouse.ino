// Program description:
//    D:\Russ\0000\Arduino\GreenHouse\Ver3\GreenHouse\GreenHouse.ino
//    An environmental monitor program designed to work with my SmartTerminal and measure the
//    environment in the greenhouse or root cellar
//    greenHouse.h gives the wiring via # defines
//
//    Actually working well
//
//
//
//    Features
//      !! may be messed up with multiple devices, need to decide if we can mix types
//
//
//
// History/Status:  ( most recent at top * done ! pending )
//    
//
//
//
// Compile info:
//
//      Sketch uses 8,118 bytes (25%) of program storage space. Maximum is 32,256 bytes.
//
//      Global variables use 579 bytes (28%) of dynamic memory, leaving 1,469 bytes for local variables. Maximum is 2,048 bytes.
//
//
// Environment:
//		Arduino, compile with arduino.exe  1.6.12
//              Developed on Windows 7 Pro 64 bit => Windows 10
//              Running:
//                  note: include files, they need to be present, should be in downloaded zip
//                  use a terminal emulator on the PC side ( or the arduino serial monitor )
//                  For configuration info see header file (.h), comm rates, ports....  ( for program version see VERSION_ID )
//
//
//
// Author:      russ_hensel http://www.opencircuits.com/User:Russ_hensel
//
//
//
//
// ============================= easy modification using #define 's ================================

#include "GreenHouse.h"      // #defines for this project
#include "SerialCmd.h"       // #defines for SerialCmd

// include the library code:
#include <LiquidCrystal.h>
#include "DHT.h"             // for the temp humidity sensor

// ============================= globals variables ========

SerialCmd     serialCmd;


//array stuff is messed up assumes both sensors are of same type, forgotten begin, perhaps other errors
// DHT           dht_1( DHTPIN_1, DHTTYPE_1 );

//DHT           dht[ NO_DHT ] { { DHTPIN_1, DHTTYPE_1 }, { DHTPIN_1, DHTTYPE_1 } };   // ng if no is not  2
//DHT           dht[ NO_DHT ] { { DHTPIN_1, DHTTYPE_1 } };   // NO_DHT = 1 ng if no is not  can use # define for a few cases

// cannot use the same one twice because of timing of the device.  if you need a fake, put it on another pin, and do not use the pin
// or use a #define for fake sensors

DHT           dht[ NO_DHT ] { { DHTPIN_1, DHTTYPE_1 }, { DHTPIN_1, DHTTYPE_1 } };  // NO_DHT = 2

// initialize the liquid crystal library with the numbers of the interface pins
// LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

LiquidCrystal lcd( LCD_RS, LCD_ENABLE, LCD_D4, LCD_D5, LCD_D6, LCD_D7 );

float         test[ NO_DHT ];
float         dht_temperature[ NO_DHT ];           // temp
float         dht_humid[ NO_DHT ];                 // humidity
int           light;                               // light measurement, currently not scaled .... or implemented on python side

// ============================ begin subroutines ===================
// ----------------------------------------------------------------
// just a little intro for the program
// summary of commands and version
void rptHelp( void ) {

  Serial.println( F("") );
  Serial.println( VERSION_ID  );
  //Serial.println( PY_SEPERATOR );
  Serial.println( F("") );
  Serial.println( F( "# a     aquire t, h data" ) );            // case 'a':           aquire_th();
  Serial.println( F( "# h     report humidity" ) );             // case 'h':           report_h( );
  Serial.println( F( "# l     report light" ) );                // case 'l':           report_l( );
  Serial.println( F( "# t     report temperature" ) );          // case 't':           report_t( );
  Serial.println( F( "# v     version of software" ) );         // case 'v':           report_version();
  Serial.println( F( "# w     help" ) );                        // case 'w':           rptHelp();
  //Serial.println( F( "# x     some experiment" ) );

  return;
}

// other searches       setup()

// ---------- Main ----------
void loop()   {

    unsigned char   debugStr;
    unsigned char   locCmd;
    int             cmdPriorNbr;
    uint8_t         z_pin;    // pin for z command

    serialCmd.tryRecCmd( );

    // stopFlag not used now just old junk
    if ( serialCmd.stopFlag  )   {
      //Serial.print( F( "# Stopped" ) );
      //Serial.println( "" );
      serialCmd.stopFlag  = 0;
      serialCmd.gotCmd    = 0;
    }
    if ( serialCmd.gotCmd  )   {
      //Serial.print( "cmd = "  );
      //Serial.print( serialCmd.cmdPrior );
      //Serial.print( "\r" );

      locCmd   = serialCmd.cmdPrior[0];     // in case access is expensive
      // lower case the command as necessary // combine with above and make sub, possibly inline !! check this for special char
      if ( locCmd < 97 ) {
        locCmd += 32;
      }
      cmdPriorNbr   = serialCmd.parseCmdNbr( serialCmd.cmdPrior );
      // decode command
      switch ( locCmd )  {
        case 'a':    //
            aquire_th();
            break;
        case 'h':    //
            report_h( );
            break;
        case 'l':    //
            report_l( );
            break;
         case 't':    //
            report_t( );
            break;
         case 'v':
            report_version();
            break;

         case 'w':  // what? report help
            rptHelp();
            break;

        default:
          Serial.print( F( "!Bad Command = " ) );
          Serial.print( serialCmd.cmdPrior );
          //Serial.print( "\n\r" );
          Serial.println( F("") );
        }

      serialCmd.gotCmd    = 0;
    }
}

// ----------------------------------------------------------------
void  bootLcd( void ){
    Serial.println( "boot lcd takes a few seconds" );
    delay( 500 );
    lcd.begin(16, 2);
    delay( 500 );
    lcd.begin(16, 2);

    lcd.clear();
    lcd.setCursor(0, 0 );
    lcd.print( "hello LCD" );
    Serial.println( "boot lcd end" );
}
// ----------------------------------------------------------------

void lcdWrite( String a, int b ) {

    lcd.clear();

    lcd.setCursor(0, 0 );
    lcd.print( a );

    lcd.setCursor(0, 1);
    lcd.print( b, 10 );     // 10 for base 10
    //print the number of seconds since reset:
    //lcd.print(millis()/1000);
    //lcd.setCursor(0, 0); // top left
    //lcd.setCursor(15, 0); // top right
    //lcd.setCursor(0, 1); // bottom left
    //lcd.setCursor(15, 1); // bottom right
    return;
}

// ------------------------------------------------------

void aquire_th()  {
     // acquire the data, bad values are -99.
     bool   ok;
     float  data;

     ok      = true;
     for ( int i = 0; i < NO_DHT; i++) {

        data   = dht[ i ].readHumidity( false );
        if  ( isnan( data ) ){
            data   = -99.;
            ok = false;
        }
        dht_humid[ i ]      =  data;

        // Read temperature;  Fahrenheit -- because of timing must use different pins for 2 devices
        data   = dht[ i ].readTemperature( true, false  );
        if  ( isnan( data ) ) {
            data   = -99.;
            ok     = false;
        }
        dht_temperature[ i ] = data;

    }
    // Check if any reads failed
//    if  ( ok ) {
//        Serial.println("ok");
//    }else  {
//        Serial.println("ng");
//    }
    Serial.println("ok");
    return;
}

// ------------------------------------------------------
void report_h( )   {

    for ( int i = 0; i < NO_DHT; i++) {
       Serial.print( dht_humid[ i ] );
       Serial.print( " " );
    }
    Serial.println( "" );
}
// ------------------------------------------------------
void report_t( )   {
    for ( int i = 0; i < NO_DHT; i++) {
       Serial.print( dht_temperature[ i ] );
       Serial.print( " " );
    }
    Serial.println( "" );
}
// ------------------------------------------------------
void report_l( )   {

// read the pressure on some pin
// int readPressureRaw( int APin ) {

  //int sensorValue;    // unsigned int a bit better
  //int pressure;
  light = analogRead( LIGHT_PIN );     // 1024 is max

  Serial.println( light );
  return;
}
// ------------------------------------------------------
void report_version( )   {
    Serial.println( VERSION_ID  );
}

// ---------- begin setup ----------
void setup()   {

      Serial.begin( BAUD_RATE );

      serialCmd             = SerialCmd();
      serialCmd.resetCmd(  );

      //pinMode( TIME_CHECK_PIN, OUTPUT );
      delay( 1000 );   // serial init just in case
      // rptHelp( );
      Serial.println( F("") );

      bootLcd();
      // dht_1.begin();
      for ( int i = 0; i < NO_DHT; i++) {
          dht[i].begin();
     }

      // delay( 1000 );
      Serial.println("DHTxx setup!");
      report_version();
}


// ======================= eof ==============================























