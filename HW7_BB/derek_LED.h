// header file

#include<iostream>
#include<fstream>// to write into file
#include<string>
#include<sstream>// stream stream
using namespace std;

#define LED_PATH "/sys/class/leds/beaglebone:green:usr"

class LED{ // has private and public items
   private: 
      string path;
      int number;
      virtual void writeLED(string filename, string value);
      virtual void removeTrigger();
   public: // public can see and call/use services
      LED(int number); // constructor
      virtual void turnOn();
      virtual void turnOff();
      virtual void flash(string delayms);
      virtual void outputState();
      virtual ~LED(); // destructor, function that releases memory reserved
};
