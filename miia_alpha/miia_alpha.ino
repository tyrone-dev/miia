#include <Servo.h>

Servo myservo_0; // left ankle
Servo myservo_1; //right ankle
Servo myservo_2; //left hip
Servo myservo_3; //right hip

//Global variables 
//==================================
//variables
int Init = 0;
int left_leg,right_leg,left_hip,right_hip;
int increment = 1;
int angle;

//array variables
int initial[4] = {90,90,90,90};
int Range[4] = {0,0,0,0};
int NewArray[4] = {0,0,0,0};


//function declarations
//==================================
void sweep_write(int NewArray);//pass
void walk_forward(int steps);//pass - walk is skew because shaft slips
void walk_back(int steps);//pass - walk is skew because shaft slips
void turn_right(int angle);
void turn_right_back(int angle);
void turn_left(int angle);
void turn_left_back(int angle);

//to be tested- new functions
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
//this is the setup for the code
void setup() {
  
  Serial.begin(9600); 
  
  myservo_0.attach(9);  // attaches the servo on pin 9 to the left leg
  myservo_1.attach(5); //attacges the servo on pin 10 to the right leg  
  myservo_2.attach(10);  // attaches the servo on pin 11 to the left hip
  myservo_3.attach(6); //attacges the servo on pin 10 to the right hip 

  myservo_0.write(initial[0]);
  myservo_1.write(initial[1]);
  myservo_2.write(initial[2]);
  myservo_3.write(initial[3]); 

  delay(10000);
  Serial.println("This is the start of the program");  
}
//========================================================
//this is the main code
void loop() {
  /*
  int steps = 3;
  increment = 3;  
  angle = 50;*/
  
  increment = 3;
  int steps = 3;
  //left_hiproll();
  //right_hiproll();
  walk_forward(steps);
  /*
  left_foot_tap();
  right_foot_tap();
  */
  /*
  initialpos();
  toe_stand();
  heal_stand();
  stand_leg_left();
  stand_leg_right();
  right_foot_wave();
  left_foot_wave();
  */
  //half_fwd_hiproll();
  //half_bck_hiproll();
  //full_hiproll();
  delay(1000);
 /* NewArray[0] = 90; //left ankle
  NewArray[1] = -1; //right ankle
  NewArray[2] = -1; //left hip
  NewArray[3] = -1; //right hip
  Serial.println("enter the position");
  sweep_write(NewArray);
  */
  //walk_forward(steps);  
  //walk_back(steps);  
  //turn_right(angle);
  // to test still
  //turn_right_back(angle);
  //turn_left(angle);
  //turn_left_back(angle);
}
//========================================================
//========================================================
//function declarations 
//========================================================
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

  //initial leg position

  left_leg = 90+30;//angle that otto will tilt to stand, the smaller the better
  right_leg = 90+ 80;

  NewArray[0] = left_leg;
  NewArray[1] = right_leg;
  NewArray[2] = -1;
  NewArray[3] = -1;

  //write to the motors
  sweep_write(NewArray);

  //this is the angle that the robot turns
   
  NewArray[0] = 90+20; 
  NewArray[1] = 90+50;
  NewArray[2] = 90-angle;
  NewArray[3] = -1;
  //write to the motors
  sweep_write(NewArray);

  //this makes thing right

  //stage 1
  NewArray[0] = 90;
  NewArray[1] = 90;
  NewArray[2] = -1;
  NewArray[3] = -1;
  //write to the motors
  sweep_write(NewArray);

  //this is the end of the step
  NewArray[0] = 90;
  NewArray[1] = 90;
  NewArray[2] = 90;
  NewArray[3] = 90;
  //write to the motors
  sweep_write(NewArray);   
  }

//==============================================
//turn right backwards, this is if the robot is walking backwards first
void turn_right_back(int angle){

 //initial leg position
  left_leg = 90+30;//angle that otto will tilt to stand, the smaller the better
  right_leg = 90+ 80;

  NewArray[0] = left_leg;
  NewArray[1] = right_leg;
  NewArray[2] = -1;
  NewArray[3] = -1;

  //write to the motors
  sweep_write(NewArray);

  //this is the angle that the robot turns
   
  NewArray[0] = 90+20; 
  NewArray[1] = 90+50;
  NewArray[2] = 90+angle;
  NewArray[3] = -1;
  //write to the motors
  sweep_write(NewArray);

  //this makes thing right

  //stage 1
  NewArray[0] = 90;
  NewArray[1] = 90;
  NewArray[2] = -1;
  NewArray[3] = -1;
  //write to the motors
  sweep_write(NewArray);

  //this is the end of the step
  NewArray[0] = 90;
  NewArray[1] = 90;
  NewArray[2] = 90;
  NewArray[3] = 90;
  //write to the motors
  sweep_write(NewArray);     
  }

//=================================================
//turn_left
void turn_left(int angle){

  //===============================
  //new image


  //===============================

  //initial leg position  
  left_leg = 90-80;
  right_leg = 90- 30;//angle that otto will tilt to stand, the smaller the better

  NewArray[0] = left_leg;
  NewArray[1] = right_leg;
  NewArray[2] = -1;
  NewArray[3] = -1;
  //write to the motors
  sweep_write(NewArray);
/*
  //mske the foot flat
  NewArray[0] = 60;
  NewArray[1] = -1;
  NewArray[2] = -1;
  NewArray[3] = -1;
  //write to the motors
  sweep_write(NewArray);
  
  //this is the angle that the robot turns
  right_leg = 90;
  left_hip = 90+angle;
  
  NewArray[0] = -1;
  NewArray[1] = right_leg;
  NewArray[2] = -1;
  NewArray[3] = left_hip;
  //write to the motors
  sweep_write(NewArray);

  //this makes thing right

  //stage 1
  NewArray[0] = -1;
  NewArray[1] = 90;
  NewArray[2] = -1;
  NewArray[3] = -1;
  //write to the motors
  sweep_write(NewArray);
/*
  //stage 2
  NewArray[0] = 110;
  NewArray[1] = 45;
  NewArray[2] = -1;
  NewArray[3] = -1;
  //write to the motors
  sweep_write(NewArray);
 
  //this is the end of the step
  NewArray[0] = 90;
  NewArray[1] = 90;
  NewArray[2] = 90;
  NewArray[3] = 90;
  //write to the motors
  sweep_write(NewArray);   */ 
  }

//==========================================
//turn left back
void turn_left_back(int angle){

  //initial leg position

  left_leg = 90+80;//angle that otto will tilt to stand, the smaller the better
  right_leg = 90+ 20;

  NewArray[0] = left_leg;
  NewArray[1] = right_leg;
  NewArray[2] = -1;
  NewArray[3] = -1;

  //write to the motors
  sweep_write(NewArray);

  //this is the angle that the robot turns
  right_leg = 90+angle;
  left_hip = 90;
  
  NewArray[0] = -1;
  NewArray[1] = right_leg;
  NewArray[2] = left_hip;
  NewArray[3] = -1;
  //write to the motors
  sweep_write(NewArray);

  //this makes thing right

  //stage 1
  NewArray[0] = -1;
  NewArray[1] = 90;
  NewArray[2] = -1;
  NewArray[3] = -1;
  //write to the motors
  sweep_write(NewArray);

  //stage 2
  NewArray[0] = 110;
  NewArray[1] = 45;
  NewArray[2] = -1;
  NewArray[3] = -1;
  //write to the motors
  sweep_write(NewArray);
  
  //this is the end of the step
  NewArray[0] = 90;
  NewArray[1] = 90;
  NewArray[2] = 90;
  NewArray[3] = 90;
  //write to the motors
  sweep_write(NewArray);    
  }




