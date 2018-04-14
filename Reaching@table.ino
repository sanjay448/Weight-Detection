#define mlf 22
#define mlb 24
#define mlp 9
#define mrf 28
#define mrb 26
#define mrp 11
#define pin 2
#define pin1 3
#define pin2 4
int count = 0;
int flag = 0 ;
int mlpwm=0,mrpwm=0,mls=70,mrs=70;
int reading[6];
int dread[6];
int perr=0, derr=0, corr=0, kp=18, kd=20, sen_thr=200,sum=0,err=0,wsum=0;

void setup()
{
  Serial.begin(9600);
  pinMode(mlf, OUTPUT);
  pinMode(mlb, OUTPUT);
  pinMode(mlp, OUTPUT);
  pinMode(mrp, OUTPUT);
  pinMode(mrf, OUTPUT);
  pinMode(mrb, OUTPUT);
 pinMode(pin, INPUT);
  pinMode(pin1, INPUT);
   pinMode(pin2, INPUT);

}
void turn_360(){
 
       digitalWrite(mlf,LOW);
      digitalWrite(mrf,HIGH);
      digitalWrite(mlb,HIGH);
      digitalWrite(mrb,LOW);
      
      analogWrite(mlp,70);
      analogWrite(mrp,70);
      sensor_read();
      while((dread[2]==0)&&(dread[3]==0)){
sensor_read();


}
}
void lil_move(){
 int t = millis();
  while (millis() - t < 1000) {
    digitalWrite(mlf, HIGH);
    digitalWrite(mrf, HIGH);
    digitalWrite(mlb, LOW);
    digitalWrite(mrb, LOW);
    analogWrite(mlp, 80);
    analogWrite(mrp, 80);
  }
  no_move();
  delay(100);
}
void turn_left() {
 
  
    digitalWrite(mlf, HIGH);
    digitalWrite(mrf, LOW);
    digitalWrite(mlb, LOW);
    digitalWrite(mrb, HIGH);
    analogWrite(mlp, 90);
    analogWrite(mrp, 90);
    delay(500);
    sensor_read();
    while((dread[2]==0)&&(dread[3]==0)){
    sensor_read();
    }
  no_move();
  delay(100);
}
void turn_right(){

     digitalWrite(mlf,LOW);
      digitalWrite(mrf,HIGH);
      digitalWrite(mlb,HIGH);
      digitalWrite(mrb,LOW);
       analogWrite(mlp,90);
      analogWrite(mrp,90);
      delay(500); 
      sensor_read();
      while((dread[2]==0)&&(dread[3]==0)){
sensor_read();
      }
no_move();
delay(100);
   
}
 void no_move(){
    digitalWrite(mlf,LOW);
      digitalWrite(mrf,LOW);
      digitalWrite(mlb,LOW);
      digitalWrite(mrb,LOW);
       analogWrite(mlp,0);
      analogWrite(mrp,0);
 }
    void sensor_read(){
      reading[0]=analogRead(A0);
      reading[1]=analogRead(A1);
      reading[2]=analogRead(A2);
      reading[3]=analogRead(A3);
      reading[4]=analogRead(A4);
      reading[5]=analogRead(A5);
     
      for(int l=0; l<6; l++)
    {
      if(reading[l]<sen_thr) dread[l]=0;
      else dread[l]=1;
      }
    
    }
    void return_table1(){
      digitalWrite(mlf,LOW);
      digitalWrite(mrf,HIGH);
      digitalWrite(mlb,HIGH);
      digitalWrite(mrb,LOW);
       analogWrite(mlp,90);
      analogWrite(mrp,90);
      delay(1500);
      turn_right();
      line_follow_2();
    }
     void return_table2(){
      digitalWrite(mlf,LOW);
      digitalWrite(mrf,HIGH);
      digitalWrite(mlb,HIGH);
      digitalWrite(mrb,LOW);
       analogWrite(mlp,90);
      analogWrite(mrp,90);
      delay(1500);
      turn_right();
      line_follow_1();
    }
    void calc_error(){
      sum=0;
    for(int l=0; l<6;l++)
      sum=sum+dread[l];
     int wsum=5*dread[0]+3*dread[1]+1*dread[2]-1*dread[3]-3*dread[4]-5*dread[5];
    err=wsum/sum;
      }
        
    void motor_1(){ 
      int c1 = 0;
      int f1 =0 ;
       sensor_read();
        if((c1==0)&& ((dread[0]==1)&&(dread[1]==1)&&(dread[2]==1)&&(dread[3]==1)&&(dread[4]==1)&&(dread[5]==1))){
   
   lil_move();
   turn_left();
        }
         sensor_read();
    if((f1==0)&& ((dread[0]==0)&&(dread[1]==0)&&(dread[2]==0)&&(dread[3]==0)&&(dread[4]==0)&&(dread[5]==0))){
     digitalWrite(mlf,LOW);
      digitalWrite(mrf,LOW);
      digitalWrite(mlb,HIGH);
      digitalWrite(mrb,HIGH);
       analogWrite(mlp,50);
      analogWrite(mrp,50);
      delay(300);
 no_move();
        }
      derr=err-perr;
    corr=kp*err+kd*derr;
    perr=err;
       
    
        mrpwm=mrs+corr;
         mlpwm=mls-corr;
      if(mlpwm>254) mlpwm=254;
      if(mrpwm>254) mrpwm=254;
      if(mlpwm<0) {
        mlpwm=(-1)*mlpwm;
        digitalWrite(mlf,LOW);
      digitalWrite(mrf,HIGH);
      digitalWrite(mlb,HIGH);
      digitalWrite(mrb,LOW);
      
      analogWrite(mlp,mlpwm);
      analogWrite(mrp,mrpwm);
      }
      if(mrpwm<0) {
        mrpwm=(-1)*mrpwm;
        if(mrpwm>254) mrpwm=254;
        digitalWrite(mrf,LOW);
      digitalWrite(mlf,HIGH);
      digitalWrite(mrb,HIGH);
      digitalWrite(mlb,LOW);
      
      analogWrite(mlp,mlpwm);
      analogWrite(mrp,mrpwm);
        }
      if(mlpwm>0 && mrpwm>0){
      digitalWrite(mlf,HIGH);
      digitalWrite(mrf,HIGH);
      digitalWrite(mlb,LOW);
      digitalWrite(mrb,LOW);
      
      analogWrite(mlp,mlpwm);
      analogWrite(mrp,mrpwm);
      }
      }
    

void line_follow_1(){
     sensor_read();
     calc_error();
     motor_1(); 
      }
      
            void motor_2(){ 
              int c2 = 0;
              int f2 = 0;
       sensor_read();
        if((c2==0)&& ((dread[0]==1)&&(dread[1]==1)&&(dread[2]==1)&&(dread[3]==1)&&(dread[4]==1)&&(dread[5]==1))){
   lil_move();
   
   
   turn_right();
      
        }
              sensor_read();
    if((f2==0)&& ((dread[0]==0)&&(dread[1]==0)&&(dread[2]==0)&&(dread[3]==0)&&(dread[4]==0)&&(dread[5]==0))){
     digitalWrite(mlf,LOW);
      digitalWrite(mrf,LOW);
      digitalWrite(mlb,HIGH);
      digitalWrite(mrb,HIGH);
       analogWrite(mlp,50);
      analogWrite(mrp,50);
      delay(300);
 no_move();
        }
        
   
      derr=err-perr;
    corr=kp*err+kd*derr;
    perr=err;
       
    
        mrpwm=mrs+corr;
         mlpwm=mls-corr;
      if(mlpwm>254) mlpwm=254;
      if(mrpwm>254) mrpwm=254;
      if(mlpwm<0) {
        mlpwm=(-1)*mlpwm;
        digitalWrite(mlf,LOW);
      digitalWrite(mrf,HIGH);
      digitalWrite(mlb,HIGH);
      digitalWrite(mrb,LOW);
      
      analogWrite(mlp,mlpwm);
      analogWrite(mrp,mrpwm);
      }
      if(mrpwm<0) {
        mrpwm=(-1)*mrpwm;
        if(mrpwm>254) mrpwm=254;
        digitalWrite(mrf,LOW);
      digitalWrite(mlf,HIGH);
      digitalWrite(mrb,HIGH);
      digitalWrite(mlb,LOW);
      
      analogWrite(mlp,mlpwm);
      analogWrite(mrp,mrpwm);
        }
      if(mlpwm>0 && mrpwm>0){
      digitalWrite(mlf,HIGH);
      digitalWrite(mrf,HIGH);
      digitalWrite(mlb,LOW);
      digitalWrite(mrb,LOW);
      
      analogWrite(mlp,mlpwm);
      analogWrite(mrp,mrpwm);
      }
      }
   void line_follow_2(){
     sensor_read();
     calc_error();
     motor_2(); 
      } 
      /* void motor_3(){ 
       sensor_read();
         if((count==0)&& ((dread[0]==1)&&(dread[1]==1)&&(dread[2]==1)&&(dread[3]==1)&&(dread[4]==1)&&(dread[5]==1))){
  count++ ;
  lil_move();
      line_follow_3();
  }
        if((count!=0)&& ((dread[0]==1)&&(dread[1]==1)&&(dread[2]==1)&&(dread[3]==1)&&(dread[4]==1)&&(dread[5]==1))){
   no_move();
   delay(1450);
   turn_left();
  
      
        }
        
  
      derr=err-perr;
    corr=kp*err+kd*derr;
    perr=err;
       
    
        mrpwm=mrs+corr;
         mlpwm=mls-corr;
      if(mlpwm>254) mlpwm=254;
      if(mrpwm>254) mrpwm=254;
      if(mlpwm<0) {
        mlpwm=(-1)*mlpwm;
        digitalWrite(mlf,LOW);
      digitalWrite(mrf,HIGH);
      digitalWrite(mlb,HIGH);
      digitalWrite(mrb,LOW);
      
      analogWrite(mlp,mlpwm);
      analogWrite(mrp,mrpwm);
      }
      if(mrpwm<0) {
        mrpwm=(-1)*mrpwm;
        if(mrpwm>254) mrpwm=254;
        digitalWrite(mrf,LOW);
      digitalWrite(mlf,HIGH);
      digitalWrite(mrb,HIGH);
      digitalWrite(mlb,LOW);
      
      analogWrite(mlp,mlpwm);
      analogWrite(mrp,mrpwm);
        }
      if(mlpwm>0 && mrpwm>0){
      digitalWrite(mlf,HIGH);
      digitalWrite(mrf,HIGH);
      digitalWrite(mlb,LOW);
      digitalWrite(mrb,LOW);
      
      analogWrite(mlp,mlpwm);
      analogWrite(mrp,mrpwm);
      }
      }
    

void line_follow_3(){
     sensor_read();
     calc_error();
     motor_3(); 
      }
     void motor_4(){ 
       sensor_read();
                 if((count==0)&& ((dread[0]==1)&&(dread[1]==1)&&(dread[2]==1)&&(dread[3]==1)&&(dread[4]==1)&&(dread[5]==1))){
  count++ ;
  lil_move();
  line_follow_4();
  }
        if((count!=0)&& ((dread[0]==1)&&(dread[1]==1)&&(dread[2]==1)&&(dread[3]==1)&&(dread[4]==1)&&(dread[5]==1))){
   no_move();
   delay(1450);
   turn_right();
  
      
        }
        
   
      derr=err-perr;
    corr=kp*err+kd*derr;
    perr=err;
       
    
        mrpwm=mrs+corr;
         mlpwm=mls-corr;
      if(mlpwm>254) mlpwm=254;
      if(mrpwm>254) mrpwm=254;
      if(mlpwm<0) {
        mlpwm=(-1)*mlpwm;
        digitalWrite(mlf,LOW);
      digitalWrite(mrf,HIGH);
      digitalWrite(mlb,HIGH);
      digitalWrite(mrb,LOW);
      
      analogWrite(mlp,mlpwm);
      analogWrite(mrp,mrpwm);
      }
      if(mrpwm<0) {
        mrpwm=(-1)*mrpwm;
        if(mrpwm>254) mrpwm=254;
        digitalWrite(mrf,LOW);
      digitalWrite(mlf,HIGH);
      digitalWrite(mrb,HIGH);
      digitalWrite(mlb,LOW);
      
      analogWrite(mlp,mlpwm);
      analogWrite(mrp,mrpwm);
        }
      if(mlpwm>0 && mrpwm>0){
      digitalWrite(mlf,HIGH);
      digitalWrite(mrf,HIGH);
      digitalWrite(mlb,LOW);
      digitalWrite(mrb,LOW);
      
      analogWrite(mlp,mlpwm);
      analogWrite(mrp,mrpwm);
      }
      }
    

void line_follow_4(){
     sensor_read();
     calc_error();
     motor_4(); 
      }
    
      
  */      
 
void loop(){
if((digitalRead(pin)==HIGH)&&(digitalRead(pin1)==LOW)&&(digitalRead(pin2)==HIGH)){
  line_follow_1();
} 
if((digitalRead(pin)==LOW)&&(digitalRead(pin1)==HIGH)&&(digitalRead(pin2)==HIGH)){     
line_follow_2();
}
if((digitalRead(pin)==HIGH)&&(digitalRead(pin1)==HIGH)&&(digitalRead(pin2)==HIGH)){     
return_table1();
}
if((digitalRead(pin)==LOW)&&(digitalRead(pin1)==LOW)&&(digitalRead(pin2)==LOW)){     
no_move();
}
if((digitalRead(pin)==LOW)&&(digitalRead(pin1)==LOW)&&(digitalRead(pin2)==HIGH)){     
return_table2();
}
}
