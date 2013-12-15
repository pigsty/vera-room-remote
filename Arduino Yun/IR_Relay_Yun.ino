#include <IRremote.h>
#include <Process.h>

////
//
// Micasaverde and arduino input output interaction 
// original code by @Mic from the Micasaverde forum
// trigger timeouts added by Chris Birkinshaw (@chrisbirkinshaw)
//
////

#include <IRremote.h>

char veraDevId[] = "241";
int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;

#define POWER_CODE 0xC
#define POWER_CODE_ALT 0x1000C
#define EQ_CODE 0xF4
#define EQ_CODE_ALT 0x100F4
#define MUTE_CODE 0xD
#define MUTE_CODE_ALT 0x1000D
#define RW_CODE 0x2B
#define RW_CODE_ALT 0x1002B
#define FF_CODE 0x28
#define FF_CODE_ALT 0x10028
#define PLAY_CODE 0x2C
#define PLAY_CODE_ALT 0x1002C
#define STOP_CODE 0x31
#define STOP_CODE_ALT 0x10031
#define MINUS_CODE 0x21
#define MINUS_CODE_ALT 0x10021
#define PLUS_CODE 0x20
#define PLUS_CODE_ALT 0x10020
#define UP_CODE 0x58
#define UP_CODE_ALT 0x10058
#define DOWN_CODE 0x59
#define DOWN_CODE_ALT 0x10059
#define VOL_UP_CODE 0x10
#define VOL_UP_CODE_ALT 0x10010
#define VOL_DOWN_CODE 0x11
#define VOL_DOWN_CODE_ALT 0x10011
#define LEFT_CODE 0x5A
#define LEFT_CODE_ALT 0x1005A
#define RIGHT_CODE 0x5B
#define RIGHT_CODE_ALT 0x1005B
#define SELECT_CODE 0x5C
#define SELECT_CODE_ALT 0x1005C
#define MENU_CODE 0x40
#define MENU_CODE_ALT 0x10040
#define HOME_CODE 0x54
#define HOME_CODE_ALT 0x10054
#define INFO_CODE 0xF
#define INFO_CODE_ALT 0x1000F
#define BACK_CODE 0xA
#define BACK_CODE_ALT 0x1000A
#define RED_CODE 0x1006D
#define RED_CODE_ALT 0x6D
#define GREEN_CODE 0x1006E
#define GREEN_CODE_ALT 0x6E
#define YELLOW_CODE 0x1006F
#define YELLOW_CODE_ALT 0x6F
#define BLUE_CODE 0x10070
#define BLUE_CODE_ALT 0x70
#define CHUP_CODE 0x10020
#define CHUP_CODE_ALT 0x20
#define CHDOWN_CODE 0x10021
#define CHDOWN_CODE_ALT 0x21
#define N1_CODE 0x1
#define N1_CODE_ALT 0x10001
#define N2_CODE 0x2
#define N2_CODE_ALT 0x10002
#define N3_CODE 0x3
#define N3_CODE_ALT 0x10003
#define N4_CODE 0x4
#define N4_CODE_ALT 0x10004
#define N5_CODE 0x5
#define N5_CODE_ALT 0x10005
#define N6_CODE 0x6
#define N6_CODE_ALT 0x10006
#define N7_CODE 0x7
#define N7_CODE_ALT 0x10007
#define N8_CODE 0x8
#define N8_CODE_ALT 0x10008
#define N9_CODE 0x9
#define N9_CODE_ALT 0x10009
#define N0_CODE 0x0
#define N0_CODE_ALT 0x10000
#define PICTURE_CODE 0xF3
#define PICTURE_CODE_ALT 0x100F3

#define INPUT_SID "urn:micasaverde-com:serviceId:InputSelection1"
#define VOLUME_SID "urn:micasaverde-com:serviceId:Volume1"
#define MEDIA_NAV_SID "urn:micasaverde-com:serviceId:MediaNavigation1"
#define MENU_NAV_SID "urn:micasaverde-com:serviceId:MenuNavigation1"
#define POWER_SID "urn:micasaverde-com:serviceId:DiscretePower1"
#define MISC_SID "urn:micasaverde-com:serviceId:Misc1"
#define TUNING_SID "urn:micasaverde-com:serviceId:Tuning1"
#define NUM_SID "urn:micasaverde-com:serviceId:NumericEntry1"

#define veraAddress "172.16.1.1"
#define DEBUG true

void setup() {
  if(DEBUG){Serial.println("Running setup");}
  Bridge.begin();
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  readIR();
}


void readIR(){
  if (irrecv.decode(&results)) {
    if(DEBUG){Serial.println(results.value, HEX);}
    relayIR(results.value);
    irrecv.resume(); // Receive the next value
  } 
}

void relayIR(int value) {
  if ((results.value == POWER_CODE) or (results.value == POWER_CODE_ALT)) {
     Serial.write("Power"); 
     veraAction(POWER_SID, "Off");
  }
  if ((results.value == MUTE_CODE) or (results.value == MUTE_CODE_ALT)) {
     Serial.write("Mute"); 
     veraAction(VOLUME_SID, "Mute");  
  }
  if ((results.value == RW_CODE) or (results.value == RW_CODE_ALT)) {
     Serial.write("Rewind"); 
     veraAction(MEDIA_NAV_SID, "Rewind");  
  } 
  if ((results.value == FF_CODE) or (results.value == FF_CODE_ALT)) {
     Serial.write("FastForward"); 
     veraAction(MEDIA_NAV_SID, "FastForward");  
  } 
  if ((results.value == PLAY_CODE) or (results.value == PLAY_CODE_ALT)) {
     Serial.write("Play"); 
     veraAction(MEDIA_NAV_SID, "Play");  
  } 
  if ((results.value == STOP_CODE) or (results.value == STOP_CODE_ALT)) {
     Serial.write("Stop"); 
     veraAction(MEDIA_NAV_SID, "Stop");  
  } 
  if ((results.value == VOL_UP_CODE) or (results.value == VOL_UP_CODE_ALT)) {
     Serial.write("Volume Up"); 
     veraAction(VOLUME_SID, "Up");  
  }
  if ((results.value == VOL_DOWN_CODE) or (results.value == VOL_DOWN_CODE_ALT)) {
     Serial.write("Volume Down"); 
     veraAction(VOLUME_SID, "Down");  
  }
  if ((results.value == LEFT_CODE) or (results.value == LEFT_CODE_ALT)) {
     Serial.write("Left"); 
     veraAction(MENU_NAV_SID, "Left");  
  } 
  if ((results.value == RIGHT_CODE) or (results.value == RIGHT_CODE_ALT)) {
     Serial.write("Right"); 
     veraAction(MENU_NAV_SID, "Right");  
  }
  if ((results.value == UP_CODE) or (results.value == UP_CODE_ALT)) {
     Serial.write("Up"); 
     veraAction(MENU_NAV_SID, "Up");  
  } 
  if ((results.value == DOWN_CODE) or (results.value == DOWN_CODE_ALT)) {
     Serial.write("Down"); 
     veraAction(MENU_NAV_SID, "Down");  
  } 
  if ((results.value == MENU_CODE) or (results.value == MENU_CODE_ALT)) {
     Serial.write("Menu"); 
     veraAction(MENU_NAV_SID, "Menu");  
  }
  if ((results.value == HOME_CODE) or (results.value == HOME_CODE_ALT)) {
     Serial.write("Home"); 
     veraAction(MISC_SID, "Home");  
  }
  if ((results.value == INFO_CODE) or (results.value == INFO_CODE_ALT)) {
     Serial.write("Info"); 
     veraAction(MISC_SID, "Info");  
  }
  if ((results.value == SELECT_CODE) or (results.value == SELECT_CODE_ALT)) {
     Serial.write("Select"); 
     veraAction(MENU_NAV_SID, "Select");  
  }
  if ((results.value == BACK_CODE) or (results.value == BACK_CODE_ALT)) {
     Serial.write("Back"); 
     veraAction(MENU_NAV_SID, "Back");  
  }
  if ((results.value == EQ_CODE) or (results.value == EQ_CODE_ALT)) {
     Serial.write("EQ"); 
     veraAction(MISC_SID, "EQ");  
  }
  if ((results.value == RED_CODE) or (results.value == RED_CODE_ALT)) {
     Serial.write("Red"); 
     veraAction(MISC_SID, "FastextRed");  
  }
  if ((results.value == GREEN_CODE) or (results.value == GREEN_CODE_ALT)) {
     Serial.write("Green"); 
     veraAction(MISC_SID, "FastextGreen");  
  }
  if ((results.value == YELLOW_CODE) or (results.value == YELLOW_CODE_ALT)) {
     Serial.write("Yellow"); 
     veraAction(MISC_SID, "FastextYellow");  
  }
  if ((results.value == BLUE_CODE) or (results.value == BLUE_CODE_ALT)) {
     Serial.write("Blue"); 
     veraAction(MISC_SID, "FastextBlue");  
  }
  if ((results.value == CHUP_CODE) or (results.value == CHUP_CODE_ALT)) {
     Serial.write("ChannelUp"); 
     veraAction(TUNING_SID, "ChannelUp");  
  }
  if ((results.value == CHDOWN_CODE) or (results.value == CHDOWN_CODE_ALT)) {
     Serial.write("ChannelDown"); 
     veraAction(TUNING_SID, "ChannelDown");  
  }
  if ((results.value == N1_CODE) or (results.value == N1_CODE_ALT)) {
     Serial.write("1"); 
     veraAction(NUM_SID, "1");  
  }
  if ((results.value == N2_CODE) or (results.value == N2_CODE_ALT)) {
     Serial.write("2"); 
     veraAction(NUM_SID, "2");  
  }
  if ((results.value == N3_CODE) or (results.value == N3_CODE_ALT)) {
     Serial.write("3"); 
     veraAction(NUM_SID, "3");  
  }
  if ((results.value == N4_CODE) or (results.value == N4_CODE_ALT)) {
     Serial.write("4"); 
     veraAction(NUM_SID, "4");  
  }
  if ((results.value == N5_CODE) or (results.value == N5_CODE_ALT)) {
     Serial.write("5"); 
     veraAction(NUM_SID, "5");  
  }
  if ((results.value == N6_CODE) or (results.value == N6_CODE_ALT)) {
     Serial.write("6"); 
     veraAction(NUM_SID, "6");  
  }
  if ((results.value == N7_CODE) or (results.value == N7_CODE_ALT)) {
     Serial.write("7"); 
     veraAction(NUM_SID, "7");  
  }
  if ((results.value == N8_CODE) or (results.value == N8_CODE_ALT)) {
     Serial.write("8"); 
     veraAction(NUM_SID, "8");  
  }
  if ((results.value == N9_CODE) or (results.value == N9_CODE_ALT)) {
     Serial.write("9"); 
     veraAction(NUM_SID, "9");  
  }
  if ((results.value == N0_CODE) or (results.value == N0_CODE_ALT)) {
     Serial.write("0"); 
     veraAction(NUM_SID, "0");  
  }
  if ((results.value == PICTURE_CODE) or (results.value == PICTURE_CODE_ALT)) {
     Serial.write("PictureMode"); 
     veraAction(MISC_SID, "PictureMode");  
  }
}

void veraAction(String serviceId, String action){
  String url = "http://" ;
  url += veraAddress;
  url += ":3480/data_request?id=lu_action&DeviceNum=" ;
  url += veraDevId ;
  url += "&serviceId=" ;
  url += serviceId ;
  url += "&action=";
  url += action;
  if(DEBUG){Serial.println("Calling URL " + url);}

  Process p;        // Create a process and call it "p"
  p.begin("curl");  // Process that launch the "curl" command
  p.addParameter(url); // Add the URL parameter to "curl"
  p.run();      // Run the process and wait for its termination
}





