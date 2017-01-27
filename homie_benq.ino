//Homiev1.0 BENQ Remote
#include <Homie.h>

HomieNode projectorNode("projector", "serial benq device");

bool powerHandler(const String& value) {
  if (value != "on" && value != "off") return false;
  
  bool on = (value == "on");
  if(on)Serial.print("\r*pow=on#\r");
  else Serial.print("\r*pow=off#\r");
  
  Homie.setNodeProperty(projectorNode, "power", value); 
}
bool volumeHandler(const String& value) {
  if (value != "mute" && value != "unmute") return false;
  
  bool on = (value == "mute");
  if(on)Serial.print("\r*mute=on#\r");
  else Serial.print("\r*mute=off#\r");
  
  Homie.setNodeProperty(projectorNode, "volume", value); 
  
}
bool sourceHandler(const String& value) {
  if (value != "hdmi" && value != "hdmi2" && value != "ypbr" && value != "vid" && value != "dvia" && value != "dvid" && value != "rgb") return false;
  String command = ("\r*sour="+value+"#\r");
  Serial.print(command);
  Homie.setNodeProperty(projectorNode, "source", value); 
  
}

void setup() {
  Homie.setFirmware("benq-projector", "1.0.0");
  Homie.enableLogging(false);
  Serial.begin(115200);
  Serial.swap();
  projectorNode.subscribe("power", powerHandler);
  projectorNode.subscribe("volume", volumeHandler);
  projectorNode.subscribe("source", sourceHandler);
  Homie.registerNode(projectorNode);
  
  Homie.setup();
}

void loop() {
   Homie.loop();
}
