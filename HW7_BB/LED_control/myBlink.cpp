// main function
// Modified such that LED class instantiates single LED object used to
//    control on-board LED0

// Modified to introduce blink(int num) function

#include "derek_LED.h"

int main(int argc, char* argv[]){
   if(argc!=2){
	cout << "Usage is makeLEDs <command>" << endl;
        cout << "   command is one of: on, off, flash or status" << endl;
	cout << " e.g. makeLEDs flash" << endl;
   }
   cout << "Starting the makeLEDs program" << endl;
   string cmd(argv[1]); // create command string

 LED leds[1] = { LED(0) }; // NEW 

int i=0; // NEW
if(cmd=="on")leds[i].turnOn(); // turn on all LEDs in sequence

else if(cmd=="blink")leds[i].blink(atoi(argv[2])); // NEW 
// atoi = ascii to integer 

else if(cmd=="off")leds[i].turnOff();
 else if(cmd=="flash")leds[i].flash("100"); //default is "50"
 else if(cmd=="status")leds[i].outputState();
 else{ cout << "Invalid command!" << endl; }
   cout << "Finished the makeLEDs program" << endl;
   return 0;
}
