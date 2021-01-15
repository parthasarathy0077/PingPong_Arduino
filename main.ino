#include <LiquidCrystal.h>
float x=24;//initialising balls horizontal position-x
int sl=1,a=0,dly=100,speed,b=1,c=0;
//slope,menu selection,dealy,speed variables,
int i=1,j=5,y=3,m=0,n=1,pause=1,drift=1,rise=0,fd=1;
//racket position(i&j),
//ball's vertical position-y,
//cursor variables(m,n),
//vertical motion of ball(rise or drift),
//horizontal motion of ball-fd
int p1=0,p2=0; // player 1, player 2 score variables
byte left[8]={0};byte ball[8]={0};byte leftl[8]={0};//racket and ball character arrays
byte right[8]={0};byte rightl[8]={0};byte blank[8]={0};//racket and ball character arrays

//menu button arrays
byte uparrow[8]={0,4,14,21,4,4,4,0};byte downarrow[8]={0,4,4,4,21,14,4,0};//the array values are decimal equivalent of binary byte
byte back[8]={0,1,5,9,31,9,4,0};byte ok[8]={0,31,17,21,21,17,31,0};
//analog read initialisation 
float raw=0; float vin=5,vout=0; float r1=100000,r2=0,buffer;

LiquidCrystal lcd(7, 6, 4, 3, 2, 1);
//menu interface method
void menu()
{
  while(b){
lcd.createChar(byte(0),uparrow);lcd.setCursor(0,0);lcd.write(byte(0)); //displaying menu button
lcd.createChar(byte(1),downarrow);lcd.setCursor(0,1);lcd.write(byte(1)); //displaying menu button
lcd.createChar(byte(2),ok);lcd.setCursor(15,0);lcd.write(byte(2)); //displaying menu button
lcd.createChar(byte(3),back);lcd.setCursor(15,1);lcd.write(byte(3));//displaying menu button 
lcd.setCursor(3,0);lcd.print(" New game");//displaying menu option
  lcd.setCursor(4,1);lcd.print("settings");//displaying menu option 
  lcd.setCursor(2,a);lcd.print(">");//displaying menu cursor 
if(read()==41&&a>0)//reads for button press
{lcd.setCursor(2,a);lcd.print(" ");a--;lcd.setCursor(2,a);lcd.print(">");}//increments cursor position on button press }
if(read()==60&&a<1)
{lcd.setCursor(2,a);lcd.print(" ");a++;lcd.setCursor(2,a);lcd.print(">");}//decrements cursor position on button press}
if(read()==2){//defining 'ok' and 'back' buttons
  switch(a){
  case 0:lcd.clear();initi();b=0;break;//this line executes when ok is pressed on new game option, game initiates
  case 1:lcd.setCursor(3,0);//this line executes when ok is pressed on settings option, enters setting
   lcd.print("speed =  ");lcd.setCursor(2,1);lcd.print("          ");//on entering settings, displays the option 'speed'
   while(1)
  {
   speed=(1000-dly)/100;//default speed is at 9
   lcd.setCursor(10,0);lcd.print(speed);//displaying speed
   if(read()==41&&dly>0)//increments speed on pressing up-arrow button
   {dly-=50;speed=(1000-dly)/100;
    lcd.setCursor(10,0);lcd.print(speed);delay(30);}//printing incremented speed }
    if(read()==60&&dly<900)
    {dly+=50;speed=(1000-dly)/100;//decrements speed on pressing down-arrow button
     lcd.setCursor(10,0);lcd.print(speed); delay(30);//printing decremented speed
     lcd.setCursor(11,0);lcd.print(" ");}//printing blank character to erase redunduant data on display
     if(read()==4){break;}}break;// on pressing 'back' button takes user to Mainmenu
    if(read()==4){menu();}
          }}}
 //continue menu
 if(c){lcd.setCursor(0,0);lcd.print("player1:");lcd.print(p1);//displays player 1 score
 lcd.setCursor(0,1);lcd.print("player2:");lcd.print(p2);// displays player 2 score
 lcd.setCursor(10,0);lcd.print("Cont.>");//displays continue button, on pressing this gameplay continues
 lcd.setCursor(11,1);lcd.print("Menu>");//displays menu button, on pressing this takes user to Mainmenu
       while(c){
 if(read()==2){reset();c=0;}//reads input, whether to continue or to go to Mainmenu
   if(read()==4){c=0;b=1;lcd.clear();menu();}}}}

//method to cahnge racket position on button press
void cre(unsigned char c[],unsigned char c1[],int v,int ad,int m,int n,int &j,int dr,int l)
{ if(dr){j--;}else{j++;}                //depending on the button press(whether up or down),its position variable is changed 
     memcpy(c,blank,sizeof(blank));     //copies a blank array to racket character, to erase previous racket character 
     c[j]=v;c[j+1]=v;c[j+2]=v;c[j+3]=v; //values of four members of racket array is changed. v is the decimal value, equivalent to bianry character dots
     lcd.createChar(ad,c);//creating character in CGRAM
     lcd.setCursor(m,n);//setting cursor position to write racket
 lcd.write(ad);if(l){ memcpy(left,c,sizeof(c));}else{memcpy(right,c,sizeof(c));}//updating the changes made to a global variable 
 if((j+3)>=7)//when racket leaves from one row to another, the following code is executed
    {memcpy(c1,blank,sizeof(blank));
      c1[j-5]=v;c1[j-6]=v;c1[j-7]=v;c1[j-8]=v;//four members of array are changed, because the length of the racket is four pixels
      lcd.createChar(ad+1,c1);//creating character in CGRAM
      lcd.setCursor(m,n+1);//setting cursor position to write racket
   lcd.write(ad+1);//printing racket
     if(l){memcpy(leftl,c1,sizeof(c1));}//updating the changes made to a global variable
     else{memcpy(rightl,c1,sizeof(c1));}}}

//method to reset and clear diaplay
void reset()
{while(read()==22)
 {}lcd.clear();pause=1;initi();}

void initi()
{//initialising all variables to appropriate values on game start and on whenever one of the player loses
  i=1,j=2,y=5,m=7,n=1,pause=1,drift=1,rise=0,fd=1;
memcpy(left,blank,sizeof(blank));memcpy(leftl,blank,sizeof(blank));
memcpy(right,blank,sizeof(blank));memcpy(rightl,blank,sizeof(blank));
i=1,j=2,y=5,m=7,n=0,drift=1,rise=0,fd=1,left[j]=24;left[j+1]=24;left[j+2]=24;left[j+3]=24;
lcd.createChar(3,left);lcd.createChar(4,leftl);lcd.setCursor(0,0);lcd.write(3); 
right[i]=3;right[i+1]=3;right[i+2]=3;right[i+3]=3;
lcd.createChar(1,right);lcd.createChar(2,rightl);lcd.setCursor(15,0);lcd.write(1);
}
//method to read analog pin
int read(){
  raw=analogRead(A1);//on the press of each button, a unique analog value is read
  r2=r1*((1024.0/raw)-1);r2=r2/1000;//this is done by utilising a resistor network
  r2=(int)r2;return r2;//on the press of each button, the resiatance at analog pin varies
//the input is fed into this function above, to get a value to be used in control statements
}
//main method to begin lcd and atmega328p
void setup()
{  lcd.begin(16, 2); 
menu();
}
//loop function, where all motion is defined and displayed
void loop()
{//each case value corrosponds to each button. These buttons change racket position
  switch(read()) {
case 2:if(i>0){cre(right,rightl,3,1,15,0,i,1,0);}break;//this case exeutes on the press of top right button
case 4:if(i<12){cre(right,rightl,3,1,15,0,i,0,0);}break;//this case exeutes on the press of bottom right button
case 41:if(j>0){cre(left,leftl,24,3,0,0,j,1,1);}break;//this case exeutes on the press of top left button
case 60:if(j<12){cre(left,leftl,24,3,0,0,j,0,1);};break;//this case exeutes on the press of bottom left button
case 18:if(i>0){cre(right,rightl,3,1,15,0,i,1,0);}if(j>0){cre(left,leftl,24,3,0,0,j,1,1);}break;//this case exeutes on simultaneous button presses(top right& top left)
case 19:if(i>0){cre(right,rightl,3,1,15,0,i,1,0);}if(j<12){cre(left,leftl,24,3,0,0,j,0,1);}break;//this case exeutes on simultaneous button presses(top right& bottom left)
case 88:if(i<12){cre(right,rightl,3,1,15,0,i,0,0);}if(j>0){cre(left,leftl,24,3,0,0,j,1,1);}break;//this case exeutes on simultaneous button presses(bottom right& top left)
case 96:if(i<12){cre(right,rightl,3,1,15,0,i,0,0);}if(j<12){cre(left,leftl,24,3,0,0,j,0,1);}break;//this case exeutes on simultaneous button presses(bottom right& bottom left)
}//ball motion is defined here
    if(pause){
 if(y<=0&&n==0){sl=1;drift=1;rise=0;delay(50);}//to bounce the ball on hitting the top 
 if(y>=6&&n==1){sl=1;rise=1;drift=0;delay(50);}//to bounce the ball on hitting the bottom 
 byte ball[8]={0};ball[y]=x;ball[y+1]=x;
 if(m==15)//ball transition to the last column from other.i.e to penetrate the ball to racket character
 {if(n==0)
 {  memcpy(ball,right,sizeof(right));//adding ball character with racket character
   ball[y]=right[y]+x;ball[y+1]=right[y+1]+x;
  lcd.createChar(5,ball);lcd.setCursor(15,0);//writing ball an racket as in a single byte in CGRAM
  lcd.write(5);fd=0;if(x==48){m--;x=1.5;lcd.setCursor(15,0);lcd.write(1);delay(dly);//printing the stored character
  }}
 else{memcpy(ball,rightl,sizeof(rightl));//adding ball character with racket character
   ball[y]=rightl[y]+x;ball[y+1]=rightl[y+1]+x;
   lcd.createChar(5,ball);lcd.setCursor(15,1);//writing ball an racket as in a single byte in CGRAM
   lcd.write(5);fd=0;if(x==48){m--;x=1.5;lcd.setCursor(15,1);lcd.write(2);delay(dly);//printing the stored character
   }}}
 else if (m==0)//ball transition to the first column from other .i.e to penetrate the ball to racket character
 {if(n==1)
  { 
    memcpy(ball,leftl,sizeof(leftl));//adding ball character with racket character
    ball[y]=leftl[y]+x;ball[y+1]=leftl[y+1]+x;
    lcd.createChar(5,ball);lcd.setCursor(0,1);//writing ball an racket as in a single byte in CGRAM
   lcd.write(5);if(x==1.5){m++;x=48;lcd.setCursor(0,1);lcd.write(4);delay(dly);}//printing the stored character
    }
 else{
     memcpy(ball,left,sizeof(left));//adding ball character with racket character
     ball[y]=left[y]+x;ball[y+1]=left[y+1]+x;
     lcd.createChar(5,ball);lcd.setCursor(0,0);//writing ball an racket as in a single byte in CGRAM
   lcd.write(5);
   if(x==1.5){m++;x=48;lcd.setCursor(0,0);lcd.write(3);delay(dly);}//printing the stored character
     }}
  else//writing the ball after x and y increments
 {lcd.createChar(5,ball);//writing ball with increments on CGRAM 
  lcd.setCursor(m,n);
  lcd.write(5);delay(dly);}////printing the incremented character
 
  if((m==15&&x==12)||(m==0&&x==6))// defining ball bounces at the rackets (defining newtonian physics)
 {int d=n*8+y+1-i; //vertical distance between the ball and racket to find at which specific location the ball touches the racket 
  if(m==0){d=n*8+y+1-j;}
  
  switch(d)
  {   case -1:sl=2;if(drift){rise=1;drift=0;}else{drift=1;rise=0;}
            if(m==15){fd=0;}else{fd=1;}break;//at the edge, here state and slope of motion of the ball is changed 
      case 0:sl=2;if(m==15){fd=0;}else{fd=1;}break;//at the edge, slope of motion of the ball is changed
      case 1:if(m==15){fd=0;}else{fd=1;}break;//near middle, just bounces 
      case 2:if(m==15){fd=0;}else{fd=1;}break;//at the middle
      case 3:sl=1;if(m==15){fd=0;}else{fd=1;}break;//near middle, just bounces 
      case 4:sl=2;if(m==15){fd=0;}else{fd=1;}break;//at the edge, here slope of motion of the ball is changed
      case 5:sl=2;if(drift){rise=1;drift=0;}else{drift=1;rise=0;}
            if(m==15){fd=0;}else{fd=1;}break;//at the edge, here state and slope of motion of the ball is changed
      default:delay(500);
            if(m==15){p1++;}else{p2++;} lcd.clear();m=7,n=0;c=1;menu(); 
          //if one of the palyer fails to touch the ball, a submenu with player score opens
  }}

 if(y>=7)//if ball leaves first row, vertical position is re-initiated and row variable is incremented 
 {y=0;if(m==0){ left[y]=left[y]-x;left[y+1]=left[y+1]-x;lcd.setCursor(0,0);lcd.write(3);}// at racket columns ball character is added with racket character
  else if(m==15){ right[y]=right[y]-x;right[y+1]=right[y+1]-x;lcd.setCursor(15,0);lcd.write(1);}// at racket columns ball character is added with racket character
   else{byte nul[8]={0}; lcd.createChar(7,nul);lcd.setCursor(m,n);lcd.write(7);}n=1;}
 
 if(y<=0&&n==1&&rise==1)//if ball leaves second row, vertical position is re-initiated and row variable is decremented 
 {lcd.setCursor(m,n);lcd.write(7);n=0;y=7;}
 
 if(drift&&y<=7)//incrementing vertical position on ball's fall
 {y+=sl;}
 
 if(x>=3&&fd){x/=2;}//incrementind or decrementing horizontal position based on direction variable fd
 else{x*=2;}
 if(rise&&y>0){y-=sl;}//decrementing vertical position on ball's rise
 
  if(m<15&&m>0){//defining transition of the ball from one column to another
if(((x==3)&&fd)||((x==24)&&!fd))//checks if the ball reaches the end of a column
{ if(fd){//checks whether the direction of horizontal motion is pointed towars right
   byte bal[8]={0};bal[y]=1;bal[y+1]=1;//writes the ball in half in the last pixel of the current column 
   lcd.createChar(5,bal);lcd.setCursor(m,n);lcd.write(5);
   if(y<6&&y>0) {y=y+drift-rise;} //increments or decrements ball's vertical position   
   byte balli[8]={0};balli[y]=16;balli[y+1]=16;//writes the next ball in half in the first pixel of the next column 
   lcd.createChar(6,balli);lcd.setCursor(m+1,n);lcd.write(6);
   byte nul[8]={0}; lcd.createChar(7,nul);lcd.setCursor(m,n);
   //prints null character to ersase the ball in previous column
   lcd.write(7);delay(dly);}
else
{//this else part gets executed if the horizontal motion is left pointed
  byte bal[8]={0};bal[y]=16;bal[y+1]=16;//writes the ball in half in the last pixel of the current column
  lcd.createChar(5,bal);lcd.setCursor(m,n);lcd.write(5);
  if(y<6&&y>0) {y=y+drift-rise;} 
  byte balli[8]={0};balli[y]=1;balli[y+1]=1;//writes the next ball in half in the first pixel of the next column
  lcd.createChar(6,balli);lcd.setCursor(m-1,n);lcd.write(6);
  byte nul[8]={0}; lcd.createChar(7,nul);//prints null character to ersase the ball in previous column
  lcd.setCursor(m,n);lcd.write(7);delay(dly);}
  if(fd){m++;x=12;}else{m--;x=3;}}}

}
  
}
