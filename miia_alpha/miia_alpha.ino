#include <Servo.h>

Servo myservo_0; // left foot
Servo myservo_1; //right foot
Servo myservo_2; //left hip
Servo myservo_3; //right hip

// constant definitions

// change pins according to which servos are connected where
#define LEFT_FOOT A0
#define RIGHT_FOOT A1
#define LEFT_HIP A2
#define RIGHT_HIP A3

// if using a normal led
#define LED_PIN 3

// change pins according to how the RGB LED is connected
#define RED_PIN A4
#define GREEN_PIN A5
#define BLUE_PIN A6

// change to true/false to enable use of bluetooth module
#define BLUETOOTH_COMMS true

// Global variables 
//==================================
// general variables
int Init = 0;
int left_leg,right_leg,left_hip,right_hip;
int increment = 5;
int angle;
int steps;

//this is used for the random number
long randomNumber;

//bluetooth comms variables
byte byteRead;

//array variables
int initial[4] = {90,90,90,90};
int Range[4] = {0,0,0,0};
int NewArray[4] = {0,0,0,0};

// function declarations
//==================================
void sweep_write(int NewArray);//pass
void walk_forward(int steps);//pass - walk is skew because shaft slips
void walk_back(int steps);//pass - walk is skew because shaft slips
void turn_right(int angle);
void turn_right_back(int angle);
void turn_left(int angle);
void turn_left_back(int angle);
void toe_stand(); //pass
void heal_stand(); //pass
void initialpos(); //pass
void left_foot_tap();//pass
void right_foot_tap();//pass
void stand_leg_left();//pass
void stand_leg_right();//pass
void right_foot_wave();//pass
void left_foot_wave(); //pass
void moonwalk_left(); //fail- falls over
void moonwalk_right();//fail- falls over
void half_fwd_hiproll();//pass
void half_bck_hiproll();//pass
void full_hiproll();//pass
void left_hiproll();//pass
void right_hiproll();//pass
void fidget();
void randomFidget();
void bluetoothControl();

// led control
void ledControl(bool state);
void ledHeartBeat(int timeOn, int timeOff, int duration);
void heartBeat();
void setColor(int red, int green, int blue);
void ledRed(void );
void ledGreen(void );
void ledBlue(void );

//this is the setup for the code
void setup() {

  // enable serial comms
  Serial.begin(9600); 

  //configure pin modes
  pinMode(LEFT_FOOT, OUTPUT);
  pinMode(RIGHT_FOOT, OUTPUT);
  pinMode(LEFT_HIP, OUTPUT);
  pinMode(RIGHT_FOOT, OUTPUT);
  
  // configure servos
  myservo_0.attach(LEFT_FOOT);  // attaches the servo on pin 9 to the left leg
  myservo_1.attach(RIGHT_FOOT); //attacges the servo on pin 10 to the right leg  
  myservo_2.attach(LEFT_HIP);  // attaches the servo on pin 11 to the left hip
  myservo_3.attach(RIGHT_HIP); //attacges the servo on pin 10 to the right hip 

  // initialize servo positions
  myservo_0.write(initial[0]);
  myservo_1.write(initial[1]);
  myservo_2.write(initial[2]);
  myservo_3.write(initial[3]); 
  
  //random seed function to make the function start at different places
  randomSeed(analogRead(0));

  if (not BLUETOOTH_COMMS)
  {
    // delay before controllable - add a bluetooth? flag above, if using bluetooth comms don't need this, else, do so MiiA doesn't walk immediately
    delay(10000);
    Serial.println("Waited 10 Seconds!");
  }
  Serial.println("Okay go");  
}
//========================================================
//this is the main code
void loop() {

  if (BLUETOOTH_COMMS)
  {
    bluetoothControl();
  }
  else
  {
    randomFidget();
  }
}

//========================================================
// function definitions 
//========================================================

//bluetoothControl
void bluetoothControl()
{  
  if (Serial.available())
  {
    byteRead = Serial.read();
    Serial.print("Data received: ");   
    Serial.print(byteRead);
    Serial.print("\n");

    //switch(byteRead)
    if (byteRead == 'a'){
      //this will be the walk forward
      steps = 3;
      increment = 5;
      walk_forward(steps);
      byteRead == 0;
    }
    if (byteRead == 'b'){
      //this will be the walk back
      steps = 3;
      increment = 5;
      walk_back(steps);
      byteRead == 0;
    }
    if (byteRead == 'c'){
      //this will be the walk left, however we will use left leg
      stand_leg_left();
      byteRead == 0;      
    }
    if (byteRead == 'd'){
      //this will be the walk right, however we will use right leg
      stand_leg_right();
      byteRead == 0;
    }
    if (byteRead == 'e'){
      //this will be the walk right, however we will use right leg
      initialpos();
      byteRead == 0;
    }
    if (byteRead == 'f'){
      //this will be the walk right, however we will use right leg
      for(int k=0;k<=5;k+=1){
        right_foot_tap();  
      }
      byteRead == 0;
    }
    if (byteRead == 'g'){
      //this will be the walk right, however we will use right leg
      for(int k=0;k<=5;k+=1){
        left_foot_tap();  
      }
      byteRead == 0;
    }
    if (byteRead == 'h'){
      //this will be the walk right, however we will use right leg
       for(int k=0;k<=3;k+=1){
        full_hiproll();
       }
      byteRead == 0;
    }
    if (byteRead == 'i'){
      //this will be the walk right, however we will use right leg
      right_foot_wave();         
      byteRead == 0;
    }
    if (byteRead == 'j'){
      //this will be the walk right, however we will use right leg
      left_foot_wave();
      byteRead == 0;
    }

    if (byteRead == 'k'){
      // led on static
      ledControl(HIGH);      
    }
    if (byteRead == 'l'){
      // led off static
      ledControl(LOW);
    }
    if (byteRead == 'm'){
      heartBeat();
    }
    if (byteRead == 'n'){
      turn_right(40);
    }
    if (byteRead == 'o'){
      turn_right_back(40);

    }
    if (byteRead == 'p'){
      turn_left(40);
    }
    if (byteRead == 'q'){
      turn_left_back(40);
    }
  }    
}

// ledControl
void ledControl(bool state)
{
  digitalWrite(LED_PIN, state);  
}

/* ledHeartBeat
void ledHeartBeat(int timeOn, int timeOff, int duration)
{

  int numLoops = duration / (timeOn+timeOff);
  int count;
  for (count = 0; count < numLoops; count++)
  {
  // led on
  digitalWrite(LED_PIN, HIGH);
  delay(timeOn);

  // led off
  digitalWrite(LED_PIN, LOW);
  delay(timeOff);
  
  }
}*/

// actual heartbeat
void heartBeat()
{
    // loop this
    for (int i = 0; i <5; i++)
    { 
    ledHeartBeat(200, 150, 700);
    ledHeartBeat(0, 750, 750);
    }
    
    // loop this
    for (int i = 0; i < 5; i++)
    {
    ledHeartBeat(200, 150, 700);
    ledHeartBeat(0,500,500);
    }
    // loop this
    for (int i = 0; i < 5; i++)
    {
    ledHeartBeat(200, 100, 600);
    }
    
    // static on i.e. flat line . . . 
    ledHeartBeat(1000, 250, 1250);
    ledHeartBeat(200, 150, 700);
    ledControl(HIGH);
}

// ledHeartBeat
void ledHeartBeat(int timeOn, int timeOff, int duration)
{

  int numLoops = duration / (timeOn+timeOff);
  int count;
  for (count = 0; count < numLoops; count++)
  {
  // led on (choose colour here) -- default is green
  ledGreen();
  delay(timeOn);

  // led off
  ledOff();
  delay(timeOff);
  
  }
}

void setColor(int red, int green, int blue)
{
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);  
}

void ledRed(void){
  setColor(255, 0, 0);
}

void ledGreen(void){
  setColor(0, 255, 0);
}

void ledBlue(void){
  setColor(0, 0, 255);
}

void ledWhite(void){
  setColor(255, 255, 255);
}

void ledOff(void){
  setColor(0,0,0);
}

//Sweep_write

void sweep_write(int NewArray[4]){
  Serial.println("guess I have entered");  
  if(Init == 0){
       Serial.println("I should run once...");    
      //range initalised
      Range[0] = 0;
      Range[1] = 0;
      Range[2] = 0;
      Range[3] = 0;
  
      //initial position of the motors
      initial[0] = 90;
      initial[1] = 90;
      initial[2] = 90;
      initial[3] = 90;
      
      //initial change
      Init = 1;
    }
  Serial.println("passed initialized part");    
  for(int i = 0; i<4; i++){
    
      if (NewArray[i] == -1){
        //NewArray[i] = initial[i];
        Range[i] = 0;
        }
      else{
        Range[i] = abs(NewArray[i] - initial[i]);
        }
    }
    
  int dir[4] = {0,0,0,0};
  for(int k = 0; k<4; k++){
    
    if (NewArray[k]< initial[k]){
      dir[k] = 1; //subtract
      }
    else if ( NewArray[k] > initial[k]){
      dir[k] = 2;//add to the last one
      }
    else{
      dir[k] = 3;//do nothing this is a no write
      }
    }
  //calculating the max range
  int max1 = max(Range[0],Range[1]);
  int max2 = max(Range[2],Range[3]);
  int max3 = max(max1,max2);
  for (int j = 0; j < max3;j+=increment){
    for(int l = 0; l<4; l+=1){
      if (j<Range[l]){
        if(dir[l] == 1){
          initial[l] = initial[l]-increment;
          }
        else if(dir[l] == 2){
          initial[l] = initial[l]+increment;
          }
         else{
          initial[l] = initial[l];
          }
        }
      }
    //this is where we write to the motors 

    Serial.println("This is being written: ");
    Serial.println(initial[0]);

    //servo write
    myservo_0.write(initial[0]);
    myservo_1.write(initial[1]);
    myservo_2.write(initial[2]);
    myservo_3.write(initial[3]);
    //delay(15); 
    }
  }
//initial position=====================
void initialpos(){
  //set the motors to the inital positions
  NewArray[0] = 90;
  NewArray[1] = 90;
  NewArray[2] = 90;
  NewArray[3] = 90;
  Serial.println("enter the position again");
  sweep_write(NewArray);    
  }
//stand on toes ========================
void toe_stand(){
  //stand on toes 
  Serial.println("standing on the toes");
  NewArray[0] = 30;
  NewArray[1] = 150;
  NewArray[2] = -1;
  NewArray[3] = -1;
  Serial.println("enter the position again");
  sweep_write(NewArray);
  }

//stand on heals==========================
void heal_stand(){
  //stand on heals now
  Serial.println("standing on the heals");
  NewArray[0] = 160;
  NewArray[1] = 20;
  NewArray[2] = -1;
  NewArray[3] = -1;
  Serial.println("enter the position again");
  sweep_write(NewArray);
  }
 //left foot tap==========================
 //this function will have to be looped to get the tap working
void left_foot_tap(){
  initialpos();
  //this is the tap
  NewArray[0] = 110;
  NewArray[1] = -1;
  NewArray[2] = -1;
  NewArray[3] = -1;
  Serial.println("enter the position again");
  sweep_write(NewArray);
  }
 //right foot tap========================
 //this function will have to be looped to get the tap working
void right_foot_tap(){
  initialpos();
  //this is the tap
  NewArray[0] = -1;
  NewArray[1] = 70;
  NewArray[2] = -1;
  NewArray[3] = -1;
  Serial.println("enter the position again");
  sweep_write(NewArray);
  }
//stand on left leg======================
void stand_leg_left(){

  NewArray[0] = 120;
  NewArray[1] = 170;
  NewArray[2] = 90;
  NewArray[3] = 90;

  //write to the motors
  sweep_write(NewArray);
  }

//stand on right leg=====================
void stand_leg_right(){

  // this used to fail because the sweep_write() fxn always does the left foot first which upsets the structural balance
  // a quick fix is included below, consisting of two sweep_writes()
  // a better fix: rework sweep_write() to include order of servo writes
  
  NewArray[0] = 90;
  NewArray[1] = 60;
  NewArray[2] = 90;
  NewArray[3] = 90;

  //write to the motors
  sweep_write(NewArray);

  NewArray[0] = 10;
  NewArray[1] = 60;
  NewArray[2] = 90;
  NewArray[3] = 90;

  //write to the motors
  sweep_write(NewArray);
  }
  //right foot wave==========================
void right_foot_wave(){
  stand_leg_left();
  
  for(int i = 0; i<=1; i+=1){
    NewArray[0] = -1;
    NewArray[1] = 70;
    NewArray[2] = -1;
    NewArray[3] = -1;
    //write to the motors
    sweep_write(NewArray);
  
    NewArray[0] = -1;
    NewArray[1] = 120;
    NewArray[2] = -1;
    NewArray[3] = -1;
    //write to the motors
    sweep_write(NewArray);
  }
}

//left foot wave=============================
void left_foot_wave(){
  stand_leg_right();
  
  for(int i = 0; i<=1; i+=1){
    NewArray[0] = 120;
    NewArray[1] = -1;
    NewArray[2] = -1;
    NewArray[3] = -1;
    //write to the motors
    sweep_write(NewArray);
  
    NewArray[0] = 70;
    NewArray[1] = -1;
    NewArray[2] = -1;
    NewArray[3] = -1;
    //write to the motors
    sweep_write(NewArray);
  }
 }
//moonwalk left===============================
void moonwalk_left(){
    initialpos();
    stand_leg_left();
    toe_stand();
    stand_leg_right();
    initialpos();    
  }
//moonwalk right==============================
void moonwalk_right(){
    initialpos();
    stand_leg_right();
    toe_stand();
    stand_leg_left();
    initialpos();
  }
//half fwd hiproll==================================
//this function needs to be looped to work
void half_fwd_hiproll(){
  
  initialpos();
  NewArray[0] = -1;
  NewArray[1] = -1;
  NewArray[2] = 70;
  NewArray[3] = 110;
  //write to the motors
  sweep_write(NewArray);  
  }
//half back hiproll=================================
//this function needs to be looped in order to work
void half_bck_hiproll(){
  
  initialpos();
  NewArray[0] = -1;
  NewArray[1] = -1;
  NewArray[2] = 110;
  NewArray[3] = 70;
  //write to the motors
  sweep_write(NewArray); 
  }
//full hiproll======================================
//this function needs to be looped to work
void full_hiproll(){
  
  NewArray[0] = 90;
  NewArray[1] = 90;
  NewArray[2] = 110;
  NewArray[3] = 70;
  //write to the motors
  sweep_write(NewArray);
  
  NewArray[0] = 90;
  NewArray[1] = 90;
  NewArray[2] = 70;
  NewArray[3] = 110;
  //write to the motors
  sweep_write(NewArray);
  }
//left leg hiproll==================================
//this function needs to be looped to work
void left_hiproll(){
  
  initialpos();
  
  NewArray[0] = -1;
  NewArray[1] = -1;
  NewArray[2] = 70;
  NewArray[3] = -1;
  //write to the motors
  sweep_write(NewArray);
   
  }
//right leg hiproll================================
//this function needs to be looped to work
void right_hiproll(){
  
  initialpos();
  
  NewArray[0] = -1;
  NewArray[1] = -1;
  NewArray[2] = -1;
  NewArray[3] = 110;
  //write to the motors
  sweep_write(NewArray);
  }
//randomfidget===========================
void randomFidget(){

  increment = 3;
  initialpos();
  
  randomNumber = random(1,20);
  delay(randomNumber*1000);
  
  randomNumber = random(1,14);
  switch(randomNumber){

    case 1:{
    //this taps the left foot 5 times
      for(int k=0;k<=5;k+=1){
        left_foot_tap();  
        }
      break;
    }
     case 2:{
      //this taps the left and right foot 5 times
      for(int k=0;k<=5;k+=1){
        left_foot_tap();
        right_foot_tap();
        delay(50);  
        }
      break;     
    }
     case 3:{
      for(int k=0;k<=4;k+=1){
       left_hiproll();
      }
      break;
    }
     case 4:{
      stand_leg_left();
      delay(2000);
      break;
    }
     case 5:{
      stand_leg_right();
      delay(500);
      break;
    }
     case 6:{
       for(int k=0;k<=3;k+=1){
        full_hiproll();
       }
       break;
    }
     case 7:{
       for(int k=0;k<=2;k+=1){
         right_foot_wave();
         left_foot_wave();
         delay(50);
       }
      break;
    }
     case 8:{
      right_foot_wave();
      break;
    
    }
     case 9:{
       left_foot_wave();
       break;
    }
     case 10:{
      for(int k=0;k<=2;k+=1){
        toe_stand();
        heal_stand();
      }
      break;
    }
     case 11:{
      toe_stand();
      break;
    }
     case 12:{
      heal_stand();
      break;
    } 
      case 13:{
      for(int k=0;k<=5;k+=1){
      right_foot_tap();  
      }
      break;        
    }
    case 14:{
      for(int k=0;k<=4;k+=1){
       right_hiproll();
      }
      break;
    }         
  }
  randomNumber = random(1,14);
  delay(randomNumber*1000);
  
}

//fidget function=========================
void fidget(){
  
  increment = 3;
  delay(10000);
  //this taps the left foot 5 times
  for(int k=0;k<=5;k+=1){
    left_foot_tap();  
    }
  //wait in the initial position
  initialpos();
  delay(10000);
  //this taps the left and right foot 5 times
  for(int k=0;k<=5;k+=1){
    left_foot_tap();
    right_foot_tap();
    delay(50);  
    }
  //wait in the initial positon
  initialpos();
  delay(7000);
  for(int k=0;k<=4;k+=1){
     left_hiproll();
    }
 //wait in the initial positon
  initialpos();
  delay(5000);
  stand_leg_left();
  delay(500);
  stand_leg_right();
  delay(500);
  for(int k=0;k<=3;k+=1){
    full_hiproll();
    }
  initialpos();
  delay(15000);
  for(int k=0;k<=2;k+=1){
     right_foot_wave();
     left_foot_wave();
     delay(50);
    }
 initialpos();
 delay(8000);
 for(int k=0;k<=2;k+=1){
    toe_stand();
    heal_stand();
    }
    
 initialpos();
 delay(5000);
 
  }

 
//walking function========================================
 
void walk_back(int steps){
  Serial.println("start the walk...");   
  //this is the variable
  int dir = 1;
  int inc = 5;
  int x = 1;
  int mult = 0;  
  int sub = 0;
  
  for (int k = 0;k<=steps;k+=1){        

     if(dir ==1){        
        for (int i = 0; i <= 4; i += 1){
          dir = 2;
          mult = inc*i;
          left_leg = 90+mult;
          right_leg = 90+ mult*4;
          
          NewArray[0] = left_leg;
          NewArray[1] = right_leg;
          NewArray[2] = -1;
          NewArray[3] = -1;
          Serial.println("enter the position");
          sweep_write(NewArray);        
      }   
     }
    else{      
      for (int i = 0; i <= 4; i += 1){
         dir = 1;
         mult = inc *i;
         left_leg = 90-mult*4;
         right_leg = 90- mult;
         
         NewArray[0] = left_leg;
         NewArray[1] = right_leg;
         NewArray[2] = -1;
         NewArray[3] = -1;
         Serial.println("enter the position again");
         sweep_write(NewArray);        
      } 
    }

  //this is the hip rotation
  //*************************************
  x = -1*x;
  sub = 0;
  for (int i = 1; i <= 3; i += 1){
    
        
     sub = i*10*x;
     left_hip = 90+sub;
     right_hip = 90+sub;
     NewArray[0] = -1;
     NewArray[1] = -1;
     NewArray[2] = left_hip;
     NewArray[3] = right_hip;
      
     sweep_write(NewArray);       
  }
  
//this is the end of the step
//**************************************
  left_leg = 90;
  right_leg = 90;
  
  NewArray[0] = left_leg;
  NewArray[1] = right_leg;
  NewArray[2] = -1;
  NewArray[3] = -1;  
  sweep_write(NewArray);
  }
}

//walk back==============================
  
void walk_forward(int steps){
  Serial.println("start the walk...");   
  //this is the variable
  int dir = 1;
  int inc = 5;
  int x = 1;
  int mult = 0;  
  int sub = 0;
  
  for (int k = 0;k<=steps;k+=1){        

     if(dir ==1){        
        for (int i = 0; i <= 4; i += 1){
          dir = 2;
          mult = inc*i;
          left_leg = 90+mult;
          right_leg = 90+ mult*4;
          
          NewArray[0] = left_leg;
          NewArray[1] = right_leg;
          NewArray[2] = -1;
          NewArray[3] = -1;
          Serial.println("enter the position");
          sweep_write(NewArray);         
      }   
     }
    else{      
      for (int i = 0; i <= 4; i += 1){
         dir = 1;
         mult = inc *i;
         left_leg = 90-mult*4;
         right_leg = 90- mult;
         
         NewArray[0] = left_leg;
         NewArray[1] = right_leg;
         NewArray[2] = -1;
         NewArray[3] = -1;
         Serial.println("enter the position again");
         sweep_write(NewArray);       
      } 
    }

  //this is the hip rotation
  //*************************************
  x = -1*x;
  sub = 0;
  for (int i = 1; i <= 3; i += 1){
    
        
     sub = i*10*x;
     left_hip = 90-sub;
     right_hip = 90-sub;
     NewArray[0] = -1;
     NewArray[1] = -1;
     NewArray[2] = left_hip;
     NewArray[3] = right_hip;
      
     sweep_write(NewArray);      
  }
  
//this is the end of the step
//**************************************
  left_leg = 90;
  right_leg = 90;
  
  NewArray[0] = left_leg;
  NewArray[1] = right_leg;
  NewArray[2] = -1;
  NewArray[3] = -1;  
  sweep_write(NewArray);
  }
}  

void turn_right(int angle){

  //initial position
  initialpos();
  //stand left leg
  stand_leg_right();

  //lift foot
  NewArray[0] = 90;
  NewArray[1] = -1;
  NewArray[2] = -1;
  NewArray[3] = -1;  
  //write to the motors
  sweep_write(NewArray);
  
  //do hip rotation
  NewArray[0] = -1;
  NewArray[1] = -1;
  NewArray[2] = -1;
  NewArray[3] = 90-angle;  
  //write to the motors
  sweep_write(NewArray);

  //put foot down
  NewArray[0] = -1;
  NewArray[1] = 90;
  NewArray[2] = -1;
  NewArray[3] = -1;  
  //write to the motors
  sweep_write(NewArray);

  //initial position - known state
  initialpos();
  }

//==============================================
//turn right backwards, this is if the robot is walking backwards first
void turn_right_back(int angle){

 //initial position
  initialpos();
  //stand left leg
  stand_leg_right();

  //lift foot
  NewArray[0] = 90;
  NewArray[1] = -1;
  NewArray[2] = -1;
  NewArray[3] = -1;  
  //write to the motors
  sweep_write(NewArray);
  
  //do hip rotation
  NewArray[0] = -1;
  NewArray[1] = -1;
  NewArray[2] = -1;
  NewArray[3] = 90+angle;;  
  //write to the motors
  sweep_write(NewArray);

  //put foot down
  NewArray[0] = -1;
  NewArray[1] = 90;
  NewArray[2] = -1;
  NewArray[3] = -1;  
  //write to the motors
  sweep_write(NewArray);

  //initial position - known state
  initialpos();     
  }

//=================================================
//turn_left
void turn_left(int angle){

  //initial position
  initialpos();
  //stand left leg
  stand_leg_left();

  //lift foot
  NewArray[0] = -1;
  NewArray[1] = 90;
  NewArray[2] = -1;
  NewArray[3] = -1;  
  //write to the motors
  sweep_write(NewArray);
  
  //do hip rotation
  NewArray[0] = -1;
  NewArray[1] = -1;
  NewArray[2] = 90+angle;
  NewArray[3] = -1;  
  //write to the motors
  sweep_write(NewArray);

  //put foot down
  NewArray[0] = 90;
  NewArray[1] = -1;
  NewArray[2] = -1;
  NewArray[3] = -1;  
  //write to the motors
  sweep_write(NewArray);

  //initial position - known state
  initialpos(); 
  }

//==========================================
//turn left back
void turn_left_back(int angle){

  //initial position
  initialpos();
  //stand left leg
  stand_leg_left();

  //lift foot
  NewArray[0] = -1;
  NewArray[1] = 90;
  NewArray[2] = -1;
  NewArray[3] = -1;  
  //write to the motors
  sweep_write(NewArray);
  
  //do hip rotation
  NewArray[0] = -1;
  NewArray[1] = -1;
  NewArray[2] = 90-angle;
  NewArray[3] = -1;  
  //write to the motors
  sweep_write(NewArray);

  //put foot down
  NewArray[0] = 90;
  NewArray[1] = -1;
  NewArray[2] = -1;
  NewArray[3] = -1;  
  //write to the motors
  sweep_write(NewArray);

  //initial position - known state
  initialpos();    
  }
