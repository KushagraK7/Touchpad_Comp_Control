/*
 * Arduino code to control multiple keyboard shortcuts using a PS/2 touchpad.
 * 
 * Made by Tech Build:https://www.youtube.com/channel/UCNy7DyfhSD9jsQEgNwETp9g?sub_confirmation=1
 */
#include <Keyboard.h>
#include<ps2.h>

PS2 mouse(A0, A1);//PS2 mouse(Clock, Data);

#define statLED 13//LED on pin 13 will light up whenever touchpad registers any difference in reading.

#define A 2
#define B 3
#define C 4
#define D 5
#define E 6
#define F 7
#define G 8

char mstat;
char mx;
char my;
int m, x, y;
int p = 0, f = 0;
int func = 0;
int brit = 255;

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

void display(int num = -1)
{

  if (num == 0)
  {
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    digitalWrite(D, 1);
    digitalWrite(E, 1);
    digitalWrite(F, 0);
    digitalWrite(G, 1);
  } else if (num == 1) {
    digitalWrite(A, 0);
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    digitalWrite(D, 0);
    digitalWrite(E, 0);
    digitalWrite(F, 0);
    digitalWrite(G, 0);
  } else if (num == 2) {
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(C, 0);
    digitalWrite(D, 1);
    digitalWrite(E, 1);
    digitalWrite(F, 1);
    digitalWrite(G, 0);
  } else if (num == 3) {
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    digitalWrite(D, 1);
    digitalWrite(E, 0);
    digitalWrite(F, 1);
    digitalWrite(G, 0);
  } else if (num == 4) {
    digitalWrite(A, 0);
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    digitalWrite(D, 0);
    digitalWrite(E, 0);
    digitalWrite(F, 1);
    digitalWrite(G, 1);
  } else if (num == 5) {
    digitalWrite(A, 1);
    digitalWrite(B, 0);
    digitalWrite(C, 1);
    digitalWrite(D, 1);
    digitalWrite(E, 0);
    digitalWrite(F, 1);
    digitalWrite(G, 1);
  } else if (num == 6) {
    digitalWrite(A, 1);
    digitalWrite(B, 0);
    digitalWrite(C, 1);
    digitalWrite(D, 1);
    digitalWrite(E, 1);
    digitalWrite(F, 1);
    digitalWrite(G, 1);
  } else if (num == 7) {
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    digitalWrite(D, 0);
    digitalWrite(E, 0);
    digitalWrite(F, 0);
    digitalWrite(G, 0);
  } else if (num == 8) {
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    digitalWrite(D, 1);
    digitalWrite(E, 1);
    digitalWrite(F, 1);
    digitalWrite(G, 1);
  } else if (num == 9) {
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    digitalWrite(D, 1);
    digitalWrite(E, 0);
    digitalWrite(F, 1);
    digitalWrite(G, 1);
  } else if (num == 10) {
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    digitalWrite(D, 0);
    digitalWrite(E, 1);
    digitalWrite(F, 1);
    digitalWrite(G, 1);
  } else if (num == 11) {
    digitalWrite(A, 0);
    digitalWrite(B, 0);
    digitalWrite(C, 1);
    digitalWrite(D, 1);
    digitalWrite(E, 1);
    digitalWrite(F, 1);
    digitalWrite(G, 1);
  } else if (num == 12) {
    digitalWrite(A, 1);
    digitalWrite(B, 0);
    digitalWrite(C, 0);
    digitalWrite(D, 1);
    digitalWrite(E, 1);
    digitalWrite(F, 0);
    digitalWrite(G, 1);
  } else if (num == 13) {
    digitalWrite(A, 0);
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    digitalWrite(D, 1);
    digitalWrite(E, 1);
    digitalWrite(F, 1);
    digitalWrite(G, 0);
  } else if (num == 14) {
    digitalWrite(A, 1);
    digitalWrite(B, 0);
    digitalWrite(C, 0);
    digitalWrite(D, 1);
    digitalWrite(E, 1);
    digitalWrite(F, 1);
    digitalWrite(G, 1);
  } else if (num == 15) {
    digitalWrite(A, 1);
    digitalWrite(B, 0);
    digitalWrite(C, 0);
    digitalWrite(D, 0);
    digitalWrite(E, 1);
    digitalWrite(F, 1);
    digitalWrite(G, 1);
  } else {
    digitalWrite(A, 0);
    digitalWrite(B, 0);
    digitalWrite(C, 0);
    digitalWrite(D, 0);
    digitalWrite(E, 0);
    digitalWrite(F, 0);
    digitalWrite(G, 0);
  }
}

void setup() {
  // put your setup code here, to run once:

  Keyboard.begin();

  Serial.begin(9600);

  pinMode(statLED, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);

  //Initializing the PS/2 touchpad
  mouse.write(0xff);  // reset
  mouse.read();  // ack byte
  mouse.read();  // blank */
  mouse.read();  // blank */
  mouse.write(0xf0);  // remote mode
  mouse.read();  // ack
  delayMicroseconds(100);

  display(func);

  for (brit = 255; brit >= 190; brit--)
  {
    analogWrite(9, brit);
    delay(30);
  }

}

void loop() {
  // put your main code here, to run repeatedly:

  Read();

  Serial.print(m);
  Serial.print("\t");
  Serial.print(x);
  Serial.print("\t");
  Serial.println(y);

  if (m != 8) digitalWrite(statLED, HIGH);
  else digitalWrite(statLED, LOW);

  if (x > 0 && y > -4 && y < 4) p++;


  if (x < 0 && y > -4 && y < 4) p--;


  if (y > 10 && x > -4 && x < 4) f++;


  if (y < -10 && x > -4 && x < 4) f--;


  if (f >= 3)
  {
    if (func == 4) func = 0;
    else func++;
    f = 0;
  }

  if (f <= -3)
  {
    if (func == 0) func = 4;
    else func--;
    f = 0;
  }

  display(func);

  if (m == 9) Keyboard.releaseAll();

  if (func == 0)
  {
    if (p >= 2 && brit > 0)
    {
      brit--;
      p = 0;
    }

    if (p <= -2 && brit < 255)
    {
      brit++;
      p = 0;
    }
  }

  if (func == 1)
  {
    if (p >= 2)
    {
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_PAGE_UP);
      Keyboard.releaseAll();

      p = 0;
    }

    if ( p <= -2)
    {
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_PAGE_DOWN);
      Keyboard.releaseAll();

      p = 0;
    }
  }

  if (func == 2)
  {
    if (p >= 8)
    {
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press(KEY_TAB);
      Keyboard.release(KEY_TAB);

      p = 0;
    }

    if (p <= -8)
    {
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press(KEY_TAB);
      Keyboard.release(KEY_LEFT_SHIFT);
      Keyboard.release(KEY_TAB);


      p = 0;
    }
  }

  if(func == 3)
  {
    if (p >= 8)
    {
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_TAB);
      Keyboard.release(KEY_TAB);

      p = 0;
    }

    if (p <= -8)
    {
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press(KEY_TAB);
      Keyboard.release(KEY_LEFT_SHIFT);
      Keyboard.release(KEY_TAB);


      p = 0;
    }
  }

  if (func == 4)
  {
    if(p >= 2)
    {
      Keyboard.press(KEY_UP_ARROW);
      Keyboard.release(KEY_UP_ARROW);

      p = 0;
    }

    if(p <= -2)
    {
      Keyboard.press(KEY_DOWN_ARROW);
      Keyboard.release(KEY_DOWN_ARROW);

      p = 0;
    }
  }


  analogWrite(9, brit);

}
