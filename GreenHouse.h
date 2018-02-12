#define    VERSION_ID         F( "GreenHouse Monitor v4 2017 11 20.01" )
//         recently in D:\Russ\0000\Arduino\GreenHouse\Ver4\GreenHouse\GreenHouse.ino

// all # define options should be defined here 
// this is just to keep them together in a nice way

#ifndef greehhouse_h

#define greehhouse_h

// #include "WProgram.h" 
// #  https://github.com/adafruit/DHT-sensor-library/issues/1   changed 2015 Feb 21  this include is in several of the files
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

//#include <DHT.h>
//#include <DHT_U.h>

// including 19200      9600    19200           
#define    BAUD_RATE          38400      //  9600  19200  38400

// ---------------  configure hardware setup -------------  
#define    LIGHT_PIN          3 

// Uncomment whatever type you're using!
//#define DHTTYPE_1 DHT11      // DHT 11   
//#define DHTTYPE_2 DHT11      // DHT 11

//#define DHTTYPE_1 DHT22        // DHT 22  
#define DHTTYPE_1 DHT22        // DHT 22
#define DHTTYPE_2 DHT22        // DHT 22

//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321  white?  -- supposed to be more accurate than 11 -- may be more sens - favor in purchase 
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

#define NO_DHT   2     // number of dht units -- do not lie messes up the timing 

#define DHTPIN_1 5     // unit 1 data pin   what digital pin we're connected to on unit 1  pin numbering from top back away from you 
#define DHTPIN_2 5     // unit 2 data pain 

// ( DHT 11 Blue ) ( DHT 22  white )
//       1: v+ power / 2: data 3: null/ 4: gnd
//          top view     
//       /-------------/
//       /   o o o o   /
//       /   1 2 3 4   /
//       /-------------/
// data uses a pull up of about  5 K - 10 k

// LCD if used 
                              // old names
#define LCD_RS         13     // register select, pin to digital pin 12
#define LCD_ENABLE     12     // pin to digital pin 11
#define LCD_D4         8      // pin to digital pin 5
#define LCD_D5         9      // pin to digital pin 4
#define LCD_D6         10     // pin to digital pin 3
#define LCD_D7         11     // pin to digital pin 2

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.

// ----------------------------------


    
#endif     // from the top
    

