// HEAT-CUE with smart phone
// Lisa Brolin

// To use the SimbleeForMobile library, you must include this file at the top
// of your sketch. **DO NOT** include the SimbleeBLE.h file, as it will cause
// the library to silently break.
#include <SimbleeForMobile.h>

int led = 3; //output 3 on LilyPad

uint8_t drawText;  //text
uint8_t ui_text;
uint8_t ui_switch;
uint8_t ui_stepper;
uint8_t ui_stepper_value;

void setup()
{
  // Put your setup code here, to run once
  pinMode(3, OUTPUT);  // initialize digital pin 3 on LilyPad as an output.
  Serial.begin(9600);
  Serial.println("Started");
  SimbleeForMobile.begin(); // initializes SimbleeForMobile and sets everything running.
  SimbleeForMobile.deviceName = "Switch"; // Device name
  SimbleeForMobile.advertisementData = "cue"; // Advert or Description

}
void loop()
{
  // Put your main code here, to run repeatedly
  SimbleeForMobile.process();
}

void ui()
{
  // Put your user interface code here.
  //This is the interface that will be uploaded to the mobile platform
  // rendered (presented) as a Graphical User Interface (GUI).
  //Screen with: 320 Screen Height 568 (iPhone 6)

  SimbleeForMobile.beginScreen(WHITE, PORTRAIT); //white background, portrait mode

  //switch
  SimbleeForMobile.drawText(30, 50, "HEAT CUE", BLUE, 45);
  SimbleeForMobile.drawText(30, 120, "Change switch for turning on/off\n", BLACK);
  ui_switch = SimbleeForMobile.drawSwitch(50, 180);
  SimbleeForMobile.setEvents(ui_switch, EVENT_RELEASE);

  //stepper
  SimbleeForMobile.drawText(30, 240, "Adjust temperature\n", BLACK);
  ui_stepper_value = SimbleeForMobile.drawText(30, 360, "0" , BLACK);
  ui_stepper = SimbleeForMobile.drawStepper(50, 300, 75, 0, 10);
  SimbleeForMobile.setEvents(ui_stepper, EVENT_RELEASE);
  SimbleeForMobile.endScreen(); //encapsulate all of the definitions for the objects that are to form part of the user interface.
}

void ui_event (event_t &event)
{
  // Put your event-related code here.
  // callback mechanism by which the GUI on the mobile platform can communicate any actions back into the body of the sketch
  //Serial.println("raise ui_event");

  if (event.type == EVENT_RELEASE && event.id == ui_switch)
  {
    handleSwitchEvents (event);
  }

  if (event.type == EVENT_RELEASE && event.id == ui_stepper)
  {
    handleStepperEvents (event);
  }
}

void handleSwitchEvents (event_t &event)
{
  if (event.id == ui_switch && event.value == 0)
  {
    Serial.println("turn off LED");
    digitalWrite(led, LOW);
  }
  else if (event.id == ui_switch && event.value == 1)
  {
    Serial.println("turn on LED");
    digitalWrite(led, HIGH);
  }
}

void handleStepperEvents (event_t &event)
{
  char buffer[25];
  sprintf(buffer, "Indicator is at %d", event.value);
  SimbleeForMobile.updateText(ui_stepper_value, buffer);
  //Serial.println(ui_stepper_value);
  digitalWrite(led, event.value);
  //Serial.println(event.value);
}