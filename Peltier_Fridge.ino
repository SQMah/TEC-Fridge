#include <LiquidCrystal.h>
#include <TimerOne.h>
#include <PID_v1.h>

//Temperature variables - LM35
float temperature = 18.00;
int temperatureReading;
int temperatureSensor = 0;
float targetTemperature = 18.00;
float temperatureRegister;

//H-Bridge variables
int pwmPin = 10;
int dirPin = 7;

//PWM & PID variables
double Setpoint, Input;
volatile double Output;

//Define the aggressive and conservative Tuning Parameters
double aggKp=4, aggKi=0.2, aggKd=1;
double consKp=1, consKi=0.05, consKd=0.25;

PID fridgePID(&Input, &Output, &Setpoint, consKp, consKi, consKd, REVERSE);

// Initialise LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int loopNum = 0;

void setup() {
  Serial.begin(9600);

  //LCD
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Peltier");
  lcd.setCursor(0,1);
  lcd.print("Controller 1.0");
  
  // Setup temperature probe
  analogReference(INTERNAL);

  //Setup H-Bridge
  digitalWrite(dirPin, HIGH);
  
  // Change PWM frequency to 16KHz
  Timer1.initialize(62); //62 microsecond pulse period
  Timer1.attachInterrupt(pidLoop);

  //PID
  fridgePID.SetOutputLimits(300, 1023); //Timer1 library takes 0-1023 for analog write
  fridgePID.SetMode(AUTOMATIC);

  temperatureReading = analogRead(temperatureSensor);
  temperature = temperatureReading / 13.31;
}

void loop() {
  // Reading temperature
  temperatureRegister = (analogRead(temperatureSensor) / 13.31) + temperatureRegister;

  if (loopNum == 20000) {
    temperature = temperatureRegister / 20000;
    temperatureRegister = 0.00;
  }
  
  //PID
  Setpoint = targetTemperature;
  Input = temperature;

  double gap = abs(Setpoint-Input); //distance away from setpoint
  if(gap < 2)
  {  //we're close to setpoint, use conservative tuning parameters
     // fridgePID.SetTunings(consKp, consKi, consKd);
     fridgePID.SetTunings(aggKp, aggKi, aggKd);
  }
  else
  {
     //we're far from setpoint, use aggressive tuning parameters
     fridgePID.SetTunings(aggKp, aggKi, aggKd);
  }

  fridgePID.Compute();

  if (loopNum == 20000) {
    loopNum = 0;
    
    lcd.clear();

    // First row
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print("/");
    lcd.print(targetTemperature);

    //Second row
    lcd.setCursor(0,1);
    lcd.print("Power:");
    lcd.print((Output/1023) * 100);
    lcd.print("%");
  }
  
  loopNum = loopNum + 1;
}

void pidLoop() { // Repeats every 62 microseconds
  Timer1.pwm(pwmPin, Output);
}
