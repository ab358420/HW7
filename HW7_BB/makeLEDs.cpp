/** Simple On-board LED flashing program - written by Derek Molloy
*    simple OOP  struture for the Exploring BeagleBone book
*
*    This program uses all four LEDS and can be executed in three ways:
*         makeLEDs on
*         makeLEDs off
*         makeLEDs flash  (flash at time delay intervals)
*         makeLEDs status (get the trigger status)
*
* Written by Derek Molloy for the book "Exploring BeagleBone: Tools and 
* Techniques for Building with Embedded Linux" by John Wiley & Sons, 2014
* ISBN 9781118935125. Please see the file README.md in the repository root 
* directory for copyright and GNU GPLv3 license information.            */

#include<iostream>
#include<fstream>// to write into file
#include<string>
#include<sstream>// stream stream
using namespace std;

#define LED_PATH "/sys/class/leds/beaglebone:green:usr" // no number three for user b/c using code to affect all LEDs

// declaration of class = interface
class LED{ // has private and public items
   private: // no one is allowed to change them except people a part of the class
	   // has two  private fields below
      string path;
      int number;
      // virtual in front of function means function can be overwritten
      virtual void writeLED(string filename, string value);
      virtual void removeTrigger();
   public: // public can see and call/use services
      LED(int number); // constructor, uses name of class, reserving space in memory and uses it, has no return type
      virtual void turnOn();
      virtual void turnOff();
      virtual void flash(string delayms);
      virtual void outputState();
      virtual ~LED(); // destructor, function that releases memory reserved
};

LED::LED(int number){ // class::constructor name
   this->number = number; // pointer to class, means private variable number is equal to number in constructor
   // much easier with C++11 using to_string(number)
   ostringstream s;    // using a stream to contruct the path
   // declare output string stream
   s << LED_PATH << number;   //append LED number to LED_PATH
   // << stream operator
   path = string(s.str());    //convert back from stream to string
   // str() is string class, path becomes a string type that has path and a number
}

void LED::writeLED(string filename, string value){
   ofstream fs;// output fstream fs
   fs.open((path + filename).c_str());
   fs << value;
   fs.close();
}

void LED::removeTrigger(){
   writeLED("/trigger", "none");
}

void LED::turnOn(){
   cout << "Turning LED" << number << " on." << endl; // tells which LED number
   removeTrigger();
   writeLED("/brightness", "1");
}

void LED::turnOff(){
   cout << "Turning LED" << number << " off." << endl;
   removeTrigger();
   writeLED("/brightness", "0");
}

void LED::flash(string delayms = "50"){ // makes fifty the default value if no value is passed
   cout << "Making LED" << number << " flash." << endl;
   writeLED("/trigger", "timer");
   writeLED("/delay_on", delayms);
   writeLED("/delay_off", delayms);
}

void LED::outputState(){
   ifstream fs;
   fs.open( (path + "/trigger").c_str());
   // concatenates, path becomes stream, c_str() changes path to string
   string line;
   while(getline(fs,line)) cout << line << endl;
   fs.close();
}

LED::~LED(){// destructor
   cout << "destroying the LED with path: " << path << endl;
}

int main(int argc, char* argv[]){
   if(argc!=2){
	cout << "Usage is makeLEDs <command>" << endl;
        cout << "   command is one of: on, off, flash or status" << endl;
	cout << " e.g. makeLEDs flash" << endl;
   }
   cout << "Starting the makeLEDs program" << endl;
   string cmd(argv[1]); // create command string
// first object oriented notion below: (for 4 objects) 
 LED leds[4] = { LED(0), LED(1), LED(2), LED(3) }; // class LED, declaring objects = and array that has four elements of type LED
   // LED[four] has [LED0|LED1|LED2|LED3]
   for(int i=0; i<=3; i++){
      if(cmd=="on")leds[i].turnOn(); // turn on all LEDs in sequence
      else if(cmd=="off")leds[i].turnOff();
      else if(cmd=="flash")leds[i].flash("100"); //default is "50"
      else if(cmd=="status")leds[i].outputState();
      else{ cout << "Invalid command!" << endl; }
   }
   cout << "Finished the makeLEDs program" << endl;
   return 0;
}
