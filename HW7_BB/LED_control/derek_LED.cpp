// implementation file
// Modified to include function blink(int num)

#include "derek_LED.h" // stream stream
#include<unistd.h>
using namespace std;

LED::LED(int number){ // class::constructor name
   this->number = number; 
   ostringstream s;    // using a stream to contruct the path
   s << LED_PATH << number;   //append LED number to LED_PATH
   path = string(s.str());    //convert back from stream to string
}

void LED::blink(int num) // NEW
{
cout << "Blinking the LED " << num << " times" << endl;
for (int i=0; i<num; i++){
writeLED("/brightness","1");
sleep(1);
writeLED("/brightness","0");
sleep(1);
}
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

void LED::flash(string delayms = "50"){ 
   cout << "Making LED" << number << " flash." << endl;
   writeLED("/trigger", "timer");
   writeLED("/delay_on", delayms);
   writeLED("/delay_off", delayms);
}

void LED::outputState(){
   ifstream fs;
   fs.open( (path + "/trigger").c_str());
   string line;
   while(getline(fs,line)) cout << line << endl;
   fs.close();
}

LED::~LED(){// destructor
   cout << "destroying the LED with path: " << path << endl;
}
