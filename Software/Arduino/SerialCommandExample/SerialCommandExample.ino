//
// SerialCommandExample
//
// Example of Arduino-style serial command interpreter in the style of the EDF AVR code
// Receive command strings with backspace-editing and parse string into tokens
//

// NOTE:  uses external files my_gets.ino and parse.ino


void setup() {
  // initialize serial communications at 9600 bps (though the speed seems to be ignored)
  Serial.begin(9600);
}


// maximum number of command arguments to parse
#define MAXARG 5

// these are global so they are included in the report of variable size use
static char buff[80];
static char* argv[MAXARG];
static unsigned iargv[MAXARG];

void loop() {

  // send a prompt, wait for it to be transmitted
  Serial.write(">");    
  Serial.flush();
  
  // read a ststring into buff with editing
  my_gets( buff, sizeof(buff));
  
  // echo the string read
  Serial.println( buff);

  // parse into text and integer tokens (see parse.ino)
  int n = parse( buff, argv, iargv, MAXARG);

  // print the results for debugging
  Serial.print( "parsed tokens: ");
  Serial.println( n);
  if( n) {
    for( int i=0; i<n; i++)  {
      Serial.print( i);
      Serial.print( " str: \"");
      Serial.print( argv[i]);
      Serial.print( "\" int:");
      Serial.print( iargv[i]);
      Serial.print( " 0x");
      Serial.println( iargv[i], HEX);
    }
      
  }
}
