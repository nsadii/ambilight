//Developed by Rajarshi Roy
int red, green, blue, RpinVal, GpinVal, BpinVal; //red, green and blue values
int RPin = D0; //Red pin 9 has a PWM
int GPin = D1; //Green pin 10 has a PWM
int BPin = D2; //Blue pin 11 has a PWM
int Maxrgb, MaxrgbVal;
void setup()
{
Serial.begin(9600);
  //initial values (no significance)
  int red = 1023;
  int blue = 1023;
  int green = 1023;
  Maxrgb = 0;
  MaxrgbVal = 0;
}
void loop()
{
//protocol expects data in format of 4 bytes
  //(xff) as a marker to ensure proper synchronization always
  //followed by red, green, blue bytes
  if (Serial.available()>=4) {
    if(Serial.read() == 0xff){
      red = Serial.read();
      green= Serial.read();
      blue = Serial.read();
    }
  }
  if (Maxrgb < red){
    Maxrgb = red;
    if (Maxrgb < blue){
      Maxrgb = blue;
      if (Maxrgb < green){
        Maxrgb = green;
      }
    }
  }
  if (MaxrgbVal < Maxrgb){
    MaxrgbVal = Maxrgb;
  }
  RpinVal = (((red-15)*(1023-0))/(MaxrgbVal-15)+0);
  GpinVal = (((green-15)*(550-0))/(MaxrgbVal-15)+0);
  BpinVal = (((blue-15)*(1023-0))/(MaxrgbVal-15)+0);
  //finally control led brightness through pulse-width modulation
  analogWrite (RPin, RpinVal);
  analogWrite (GPin, GpinVal);
  analogWrite (BPin, BpinVal);
  delay(10); //just to be safe
}
