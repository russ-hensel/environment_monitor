
this is the readme.h file of additional documentation 

Ver4   -- so far mostly a cleanup and new serial cmd code 



========= also dead code and notes =======================

// Uncomment whatever type you're using!
//#define DHTTYPE_1 DHT11      // DHT 11   
//#define DHTTYPE_2 DHT11      // DHT 11

//#define DHTTYPE_1 DHT22        // DHT 22  
#define DHTTYPE_1 DHT22        // DHT 22
#define DHTTYPE_2 DHT22        // DHT 22

//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321  white?  -- supposed to be more accurate than 11 -- may be more sens - favor in purchase 
//#define DHTTYPE DHT21   // DHT 21   DHT21(AM2301)

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
//        case 'c':  // capture the ir n times
//            cmdPriorNbr   = serialCmd.parseCmdNbr( serialCmd.cmdPrior );
//            if ( cmdPriorNbr == 0 ) {
//              cmdPriorNbr = 1;
//            }
//            for ( int i = 1; i <= cmdPriorNbr; i++) {
//                //getIr( );
//                //printAsPyArray();
//                //Serial.print( i );
//            }
//            Serial.println( F("# Capture complete")  );
//            break;
            


