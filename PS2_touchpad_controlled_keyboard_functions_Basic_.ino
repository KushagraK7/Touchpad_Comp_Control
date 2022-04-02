/*
 * Arduino code to control keyboard's arrow keys using a PS/2 touchpad.
 * 
 * Made by Tech Build:https://www.youtube.com/channel/UCNy7DyfhSD9jsQEgNwETp9g?sub_confirmation=1
 */
#include <Keyboard.h>
#include<ps2.h>

PS2 mouse(A0, A1);//PS2 mouse(Clock, Data);

#define statLED 13//LED on pin 13 will light up whenever touchpad registers any difference in reading.

char mstat;
char mx;
char my;
int m, x, y;
int p = 0, f = 0;

void Read()//Function to read data from touchpad.
{
  mouse.write(0xeb);  // give me data!
  mouse.read();      // ignore ack
  mstat = mouse.read();
  mx = mouse.read();
  my = mouse.read();

  m = (int)mstat;
  x = (int)mx;
  y = (int)my;
}



void setup() {
  // put your setup code here, to run once:

  Keyboard.begin();

  //Serial.begin(9600);

  //Initializing the PS/2 touchpad
  mouse.write(0xff);  // reset
  mouse.read();  // ack byte
  mouse.read();  // blank */
  mouse.read();  // blank */
  mouse.write(0xf0);  // remote mode
  mouse.read();  // ack
  delayMicroseconds(100);

}

void loop() {
  // put your main code here, to run repeatedly:

  Read();

  /*//For debugging.
    Serial.print(m);
    Serial.print("\t");
    Serial.print(x);
    Serial.print("\t");
    Serial.println(y);
  */
  if (m != 8) digitalWrite(statLED, HIGH);
  else digitalWrite(statLED, LOW);

  if (x > 0 && y > -20 && y < 20) p++;


  if (x < 0 && y > -20 && y < 20) p--;


  if (y > 0 && x > -20 && x < 20) f++;


  if (y < 0 && x > -20 && x < 20) f--;

  if (p >= 4)
  {
    Keyboard.press(KEY_UP_ARROW);
    Keyboard.release(KEY_UP_ARROW);

    p = 0;
  }

  if (p <= -4)
  {
    Keyboard.press(KEY_DOWN_ARROW);
    Keyboard.release(KEY_DOWN_ARROW);

    p = 0;
  }

  if (f >= 4)
  {
    Keyboard.press(KEY_LEFT_ARROW);
    Keyboard.release(KEY_LEFT_ARROW);

    f = 0;
  }

  if (f <= -4)
  {
    Keyboard.press(KEY_RIGHT_ARROW);
    Keyboard.release(KEY_RIGHT_ARROW);

    f = 0;
  }

  if (m == 0)
  {
    Keyboard.press(KEY_HOME);
    Keyboard.release(KEY_HOME);
  }

}
