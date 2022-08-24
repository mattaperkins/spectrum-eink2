// Program to display UDP text on the eink display from Spectrum alarms and notifications.
// in bash  use to send out an alert also can prefix "T" for time updagtes and "P" for phoen updates.
//
// echo `date +%H:%M` this is a test >/dev/udp/203.14.108.254/1234
//
// Matt Perkins .

// undef for local spectrum config 
//#define SPECTRUM_CONFIG 


#include "WiFi.h"
#include "AsyncUDP.h"
#include "Inkplate.h"            //Include Inkplate library to the sketch
#include "Arduino.h"

#ifdef SPECTRUM_CONFIG 
  #include "spectrum-wificonfig.h" 
#else 
  #include "wificonfig.h" 
#endif 



#include "/Users/matt/Documents/Arduino/libraries/InkplateLibrary/Fonts/FreeSansBold24pt7b.h"
#include "/Users/matt/Documents/Arduino/libraries/InkplateLibrary/Fonts/FreeSansBold9pt7b.h"
#include "/Users/matt/Documents/Arduino/libraries/InkplateLibrary/Fonts/FreeSansBold12pt7b.h"
#include "/Users/matt/Documents/Arduino/libraries/InkplateLibrary/Fonts/FreeMonoBold9pt7b.h"


Inkplate display(INKPLATE_3BIT);

#define DELAY_MS                                                                                                       \

  String uversion = "2.1";

  int line = 140;
  const int rele = 23;


  String text0_content = "Spectrum Networks Alert Display";
  int text0_cursor_x = 103;
  int text0_cursor_y = 66;
  const GFXfont *text0_font = &FreeSansBold24pt7b;

  int widget0_h = 00;
  int widget0_m = 00;
  int widget0_center_x = 48;
  int widget0_center_y = 60;
  int widget0_size = 64;
  int widget0_r0 = (double)widget0_size / 2 * 0.55;
  int widget0_r1 = (double)widget0_size / 2 * 0.65;
  int widget0_r2 = (double)widget0_size / 2 * 0.9;
  int widget0_r3 = (double)widget0_size / 2 * 1.0;
  String text1_content = "Matt Perkins V0.0   - 255.255.255.255";


  int text1_cursor_x = 103;
  int text1_cursor_y = 102;
  const GFXfont *text1_font = &FreeSansBold9pt7b;

  int line0_start_x = 0;
  int line0_start_y = 123;
  int line0_end_x = 1041;
  int line0_end_y = 123;
  int line0_color = 0;
  int line0_thickness = 1;
  int line0_gradient = 0;

  int bitmap0_x = 13;
  int bitmap0_y = 699;
  const int bitmap0_w = 34;
  const int bitmap0_h = 34;
  const uint8_t bitmap0_content[] PROGMEM = {
    0x0, 0x0, 0xbe, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xeb, 0x0, 0x0,
    0x0, 0xe, 0xce, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xe0, 0x0,
    0x0, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0x0,
    0x4, 0xce, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xec, 0xc0,
    0xc, 0xce, 0xce, 0xce, 0xec, 0xee, 0xce, 0xec, 0xee, 0xce, 0xec, 0xee, 0xce, 0xec, 0xec, 0xec, 0xc0,
    0xa, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xa0,
    0xa, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xa0,
    0x8, 0xca, 0xca, 0xca, 0xca, 0xca, 0xca, 0xca, 0xca, 0xca, 0xca, 0xca, 0xca, 0xca, 0xca, 0xca, 0xa1,
    0x8, 0xaa, 0xaa, 0xaa, 0xac, 0xee, 0xea, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0x82,
    0x8, 0xaa, 0xaa, 0xaa, 0xce, 0xee, 0xec, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0x82,
    0x8, 0xaa, 0xaa, 0xaa, 0xce, 0xee, 0xec, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0x82,
    0x6, 0xa8, 0xaa, 0xa8, 0xee, 0xee, 0xee, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0x81,
    0x6, 0x8a, 0x88, 0xa8, 0xee, 0xee, 0xee, 0xa8, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x62,
    0x6, 0x88, 0x88, 0x8a, 0xce, 0xee, 0xee, 0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0x88, 0x62,
    0x6, 0x88, 0x88, 0x88, 0xae, 0xee, 0xec, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x62,
    0x6, 0x88, 0x88, 0x88, 0x8e, 0xee, 0xec, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x61,
    0x6, 0x88, 0x68, 0x88, 0x8a, 0xee, 0xee, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x86, 0x88, 0x68, 0x62,
    0x6, 0x88, 0x88, 0x86, 0x88, 0xce, 0xee, 0xe6, 0x88, 0x88, 0x88, 0x86, 0x88, 0x88, 0x88, 0x88, 0x61,
    0x6, 0x88, 0x86, 0x88, 0x88, 0x8e, 0xee, 0xee, 0x88, 0x68, 0x8c, 0xe8, 0x88, 0x68, 0x88, 0x88, 0x61,
    0x6, 0x86, 0x88, 0x88, 0x88, 0x88, 0xee, 0xee, 0xea, 0x88, 0xce, 0xee, 0xc8, 0x88, 0x86, 0x88, 0x61,
    0x6, 0x88, 0x88, 0x88, 0x88, 0x88, 0xae, 0xee, 0xee, 0xcc, 0xee, 0xee, 0xee, 0x88, 0x88, 0x88, 0x61,
    0x6, 0x88, 0x88, 0x88, 0x88, 0x88, 0x8a, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0x88, 0x88, 0x88, 0x61,
    0x6, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x8e, 0xee, 0xee, 0xee, 0xee, 0xea, 0x88, 0x88, 0x88, 0x61,
    0x6, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0xae, 0xee, 0xee, 0xee, 0xc8, 0x88, 0x88, 0x88, 0x61,
    0x6, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0xcc, 0xcc, 0xc8, 0x88, 0x88, 0x88, 0x88, 0x62,
    0x6, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x62,
    0x6, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x62,
    0x6, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x60,
    0x4, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x60,
    0x0, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x86, 0x20,
    0x0, 0x26, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x82, 0x0,
    0x0, 0x2, 0x26, 0x86, 0x86, 0x86, 0x86, 0x86, 0x86, 0x86, 0x86, 0x88, 0x86, 0x88, 0x64, 0x0, 0x0,
    0x0, 0x0, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2, 0x2, 0x2, 0x20, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  };
  String text2_content = "";
  int text2_cursor_x = 70;
  int text2_cursor_y = 732;
  const GFXfont *text2_font = &FreeSansBold12pt7b;

  int line1_start_x = 0;
  int line1_start_y = 681;
  int line1_end_x = 1061;
  int line1_end_y = 681;
  int line1_color = 5;
  int line1_thickness = 1;
  int line1_gradient = 0;




  AsyncUDP udp;
  void setup()
  {


    display.begin();        // Init library (you should call this function ONLY ONCE)

    Serial.begin(115200);

    // start wifi
    WiFi.disconnect(true);
    WiFi.mode(WIFI_STA);
    WiFi.setHostname(hostname.c_str()); //define hostname
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");


      // Welcome Message and build initital screen.
      text1_content = "Matt Perkins " + uversion + "  -  " + WiFi.localIP().toString();

      display.clearDisplay();
      mainDraw();
      display.display();

    }

    if (udp.listen(1234)) {
      Serial.print("UDP Listening on IP: ");
      Serial.println(WiFi.localIP());
      udp.onPacket([](AsyncUDPPacket packet) {
        Serial.print("UDP Packet Type: ");
        Serial.print(packet.isBroadcast() ? "Broadcast" : packet.isMulticast() ? "Multicast" : "Unicast");
        Serial.print(", From: ");
        Serial.print(packet.remoteIP());
        Serial.print(":");
        Serial.print(packet.remotePort());
        Serial.print(", To: ");
        Serial.print(packet.localIP());
        Serial.print(":");
        Serial.print(packet.localPort());
        Serial.print(", Length: ");
        Serial.print(packet.length()); //dlzka packetu
        Serial.print(", Data: ");
        Serial.write(packet.data(), packet.length());
        Serial.println();
        String myString = (const char*)packet.data();



        packet.printf("Got %u bytes of data", packet.length());


        // Phone Type msg
        switch (myString.charAt(0)) {
          case 'P':
            Serial.println("Phone msg received");
            blankbox();
            myString.remove(0, 1);
            text2_content = myString;
            settime(myString);
            mainDraw();
            break;
          // Time Type msg
          case 'T':
            Serial.println("got time message");
            myString.remove(0, 1);
            settime(myString);
            mainDraw();
            break;

          // Standard message
          default:
            if (line > 680) {
              line = 140;
              display.clearDisplay();
              mainDraw();
            }
            display.setCursor(40, line);
            line = line + 35 ;
            display.setFont(&FreeMonoBold9pt7b);
            display.print(myString);
            settime(myString);
            mainDraw();
        }

        display.display();

      });
    }
  }

  void loop()
  {
    delay(1000);
    udp.broadcast("Anyone here?");
  }



  void mainDraw() {


    display.setFont(text0_font);
    display.setTextColor(0, 7);    display.setTextSize(1);    display.setCursor(text0_cursor_x, text0_cursor_y);
    display.print(text0_content);

    for (int i = 0; i < 60; ++i) {
      if (i % 5 == 0)
        display.drawThickLine(widget0_center_x + widget0_r1 * cos((double)i / 60.0 * 2.0 * 3.14159265),
                              widget0_center_y + widget0_r1 * sin((double)i / 60.0 * 2.0 * 3.14159265),
                              widget0_center_x + widget0_r3 * cos((double)i / 60.0 * 2.0 * 3.14159265),
                              widget0_center_y + widget0_r3 * sin((double)i / 60.0 * 2.0 * 3.14159265), 0, 3);
      else if (widget0_size > 150)
        display.drawLine(widget0_center_x + widget0_r1 * cos((double)i / 60.0 * 2.0 * 3.14159265),
                         widget0_center_y + widget0_r1 * sin((double)i / 60.0 * 2.0 * 3.14159265),
                         widget0_center_x + widget0_r2 * cos((double)i / 60.0 * 2.0 * 3.14159265),
                         widget0_center_y + widget0_r2 * sin((double)i / 60.0 * 2.0 * 3.14159265), 2);
    }
    display.drawThickLine(widget0_center_x,
                          widget0_center_y,

                          widget0_center_x + widget0_r0 * cos((double)(widget0_h - 3.0 + widget0_m / 60.0) / 12.0 * 2.0 * 3.14159265),
                          widget0_center_y + widget0_r0 * sin((double)(widget0_h - 3.0 + widget0_m / 60.0) / 12.0 * 2.0 * 3.14159265), 2, 2);

    display.drawThickLine(widget0_center_x,
                          widget0_center_y,
                          widget0_center_x + widget0_r2 * cos((double)(widget0_m - 15.0) / 60.0 * 2.0 * 3.14159265),
                          widget0_center_y + widget0_r2 * sin((double)(widget0_m - 15.0) / 60.0 * 2.0 * 3.14159265), 2, 2);

    display.setFont(text1_font);
    display.setTextColor(0, 7);    display.setTextSize(1);    display.setCursor(text1_cursor_x, text1_cursor_y);
    display.print(text1_content);

    if (line0_gradient <= line0_color && line0_thickness == 1)
      display.drawLine(line0_start_x, line0_start_y, line0_end_x, line0_end_y, line0_color);
    else if (line0_gradient <= line0_color && line0_thickness != 1)
      display.drawThickLine(line0_start_x, line0_start_y, line0_end_x, line0_end_y, line0_color, line0_thickness);
    else if (line0_gradient > line0_color && line0_thickness == 1)
      display.drawGradientLine(line0_start_x, line0_start_y, line0_end_x, line0_end_y, line0_color, line0_gradient, 1);
    else if (line0_gradient > line0_color && line0_thickness != 1)
      display.drawGradientLine(line0_start_x, line0_start_y, line0_end_x, line0_end_y, line0_color, line0_gradient, line0_thickness);

    display.drawBitmap3Bit(bitmap0_x, bitmap0_y, bitmap0_content, bitmap0_w, bitmap0_h);
    display.setFont(text2_font);
    display.setTextColor(0, 7);    display.setTextSize(1);    display.setCursor(text2_cursor_x, text2_cursor_y);
    display.print(text2_content);

    if (line1_gradient <= line1_color && line1_thickness == 1)
      display.drawLine(line1_start_x, line1_start_y, line1_end_x, line1_end_y, line1_color);
    else if (line1_gradient <= line1_color && line1_thickness != 1)
      display.drawThickLine(line1_start_x, line1_start_y, line1_end_x, line1_end_y, line1_color, line1_thickness);
    else if (line1_gradient > line1_color && line1_thickness == 1)
      display.drawGradientLine(line1_start_x, line1_start_y, line1_end_x, line1_end_y, line1_color, line1_gradient, 1);
    else if (line1_gradient > line1_color && line1_thickness != 1)
      display.drawGradientLine(line1_start_x, line1_start_y, line1_end_x, line1_end_y, line1_color, line1_gradient, line1_thickness);

  }


  // blank phone info box

  void blankbox() {

    int rect0_a_x = 67;
    int rect0_a_y = 693;
    int rect0_b_x = 1012;
    int rect0_b_y = 747;
    int rect0_fill = 1;
    int rect0_radius = -1;
    int rect0_color = 7;

    if (rect0_radius != -1 && rect0_fill != -1)
      display.fillRoundRect(rect0_a_x, rect0_a_y, rect0_b_x - rect0_a_x, rect0_b_y - rect0_a_y, rect0_radius, rect0_color);
    else if (rect0_radius != -1 && rect0_fill == -1)
      display.drawRoundRect(rect0_a_x, rect0_a_y, rect0_b_x - rect0_a_x, rect0_b_y - rect0_a_y, rect0_radius, rect0_color);
    else if (rect0_radius == -1 && rect0_fill != -1)
      display.fillRect(rect0_a_x, rect0_a_y, rect0_b_x - rect0_a_x, rect0_b_y - rect0_a_y, rect0_color);
    else if (rect0_radius == -1 && rect0_fill == -1)
      display.drawRect(rect0_a_x, rect0_a_y, rect0_b_x - rect0_a_x, rect0_b_y - rect0_a_y, rect0_color);


  }

  // update clock verables and blank area where clock is

  void settime(String myString) {


    //blank the clock for a redraw
    int circle0_center_x = 48;
    int circle0_center_y = 64;
    int circle0_fill = 1;
    int circle0_radius = 30;
    int circle0_color = 7;

    if (circle0_fill != -1)
      display.fillCircle(circle0_center_x, circle0_center_y, circle0_radius, circle0_color);
    else
      display.drawCircle(circle0_center_x, circle0_center_y, circle0_radius, circle0_color);


    Serial.write("settime:");


    String shour =  myString.substring(0, 2);
    String smin  =  myString.substring(3, 5);

    widget0_h = shour.toInt();
    widget0_m = smin.toInt();
    if (widget0_h > 12 ) {
      widget0_h = widget0_h - 12;

    }

    Serial.print(shour);
    Serial.print(":");
    Serial.print(smin);
    Serial.println();
  }
