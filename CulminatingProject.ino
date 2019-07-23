// Variables for the display
int segments[] = {2,3,4,5};
int digits[] = {6,7,8,9};
int hz_delay=5;
int ellie=12;
int button = 11;
int a_knob = 0;
int editStage = 0;
int flash;

// The sounds the clock plays as an alarm
// I included three tunes. They are:
// 1. The Mario theme by Koji Kondo
// 2. Solfeggietto by CPE Bach
// 3. Midna's Lament (from the Legend of Zelda: Twilight Princess) by Koji Kondo
int music[3][25]={{330,330,0,330,0,262,330,0,392,0,0,0,196,0,0,0,131,262,110,220,117,233,0,0,0},
{156,131,156,196,262,311,294,262,247,196,247,294,392,349,311,294,311,262,311,392,523,622,587,494,523},
{147,165,175,220,262,330,147,165,175,220,262,330,147,165,175,220,262,330,392,330,262,220,175,165,0}};
int selectedTune=1; // Solfeggietto is selected by default
int piezo=10;
int lastPlayedNote=990;
int pace=250;

// For storing the time
unsigned long current;
// For avoidance of mutliple minute increments
boolean updated=true;
// For button interaction
bool buttonReady=true;

// Variables for time keeping
int seconds=0;
int minutes=45;
int hours=6;

// Variables for the alarm time
int alarmMinutes=45;
int alarmHours=6;

// Setup pins
void setup() {
  // initialize segments
  for(int i=0;i<4;i++){
    pinMode(segments[i],OUTPUT);
    digitalWrite(segments[i],HIGH);
  }
  // initialize digits
  for(int i=0;i<4;i++){
    pinMode(digits[i],OUTPUT);
  }
  // initalize other components
  pinMode(ellie,OUTPUT);
  pinMode(piezo,OUTPUT);
  pinMode(button,INPUT);
  pinMode(13,OUTPUT);
  digitalWrite(ellie,HIGH);  
}

// Take a digit and output the necessary BCE
void setSegments(int number){
  digitalWrite(ellie,LOW);
  delayMicroseconds(1);
  digitalWrite(segments[0],number%2);
  digitalWrite(segments[1],(number/2)%2);
  digitalWrite(segments[2],(number/4)%2);
  digitalWrite(segments[3],(number/8)%2);
  delayMicroseconds(1);
  digitalWrite(ellie,HIGH);
}

// the loop routine runs over and over again forever:
void loop(){
    
  // Play music tone if necessary
  if(alarmMinutes==minutes&&alarmHours==hours&&editStage==0){
    if(24>=(int)(millis()%60000/pace)){//In range of music
      if(lastPlayedNote!=(int)(millis()%60000/pace)){
        if(music[selectedTune][(int)(millis()%60000/pace)]!=0){
          tone(piezo,music[selectedTune][(int)(millis()%60000/pace)]*2,(int)pace*.5);
        }
        lastPlayedNote=(int)(millis()%60000/pace);
      }
   	}
  }
  
  // When editing, whether the digit should be on or not
  flash=(int)(millis()%1000/500)%2;
  
  // First digit - Set segments, then blink digit on and off if necessary
  if(editStage==5||editStage==6){
    setSegments(alarmMinutes-((int)(alarmMinutes/10))*10);
  }else if(editStage==7){
    setSegments(selectedTune+1);
  }else{
  	setSegments(minutes-((int)(minutes/10))*10);
  }
  // Whether the digit should be on or not
  if(!(editStage==1||editStage>4)||flash==1){
    digitalWrite(digits[0],HIGH); 
  }
  delay(hz_delay); // Keeps digit on for a short period of time, so that it is visible
  digitalWrite(digits[0],LOW); // Turn digit off, regardless if it is turned on or not
  
  // Second digit
  if(editStage==5||editStage==6){
    setSegments((int)alarmMinutes/10);
  }else if(editStage==7){
    setSegments(selectedTune);
  }else{
  	setSegments((int)(minutes/10));
  }
  if(!(editStage==2||editStage>4)||(flash==1&&editStage!=7)){
  	digitalWrite(digits[1],HIGH);
  }
  delay(hz_delay);
  digitalWrite(digits[1],LOW);
  
  // Third digit
  if(editStage==5||editStage==6){
    setSegments(alarmHours-((int)(alarmHours/10))*10);
  }else{
  	setSegments(hours-((int)(hours/10))*10);
  }
  if(!(editStage==3||editStage>4)||(flash==1&&editStage!=7)){
  	digitalWrite(digits[2],HIGH);
  }
  delay(hz_delay);
  digitalWrite(digits[2],LOW);
  
  // Fourth digit
  if(editStage==5||editStage==6){
    setSegments((int)(alarmHours/10));
  }else{
  	setSegments((int)(hours/10));
  }
  if(!(editStage==4||editStage>4)||(flash==1&&editStage!=7)){
  	digitalWrite(digits[3],HIGH);
  }
  delay(hz_delay);
  digitalWrite(digits[3],LOW);
  
  // Get time since program started
  current=millis();
  
  // Update seconds based on the 
  seconds=(int)((current/(unsigned long)1000)%60);
  
  // Update time. If the time for minutes has already been incremented, don't do it again
  if(seconds==0&&updated==false)
  {
    seconds=0;
    minutes ++;
    updated=true;
  }else if(seconds!=0){
    updated=false;
  }
  if(minutes>=60){
    hours++;
    minutes=0;
  }
  if(editStage==0){
    if(hours==0){
      hours=24;
    }else if(hours>24){
      hours=hours%24;
    }
  }
  // Controls the central colon.
  // Not to sure when the colon is supposed to be on and when off, so I guessed.
  if(seconds%2==0){
    digitalWrite(13,LOW);
  }else{
    digitalWrite(13,HIGH);
  }
  
  // Detect a button press, indicating that the next digit should be edited
  if(digitalRead(button)==HIGH&&buttonReady){
  	editStage++;
    buttonReady=false;
    if (editStage>7){
      editStage=0;
    }
  }else if(digitalRead(button)==LOW&&!buttonReady){
    buttonReady=true;	// Used to wait for next button press, avoiding running the above code multiple times with one button press
  }
  
  // Set the digit currently being edited to the position of the potentiometer
  if(editStage==1){
    minutes=(minutes-minutes%10+((int)(analogRead(a_knob)/103)));
  }else if(editStage==2){
    minutes=(minutes%10+((int)(analogRead(a_knob)/171))*10);
  }else if(editStage==3){
    hours=(hours-hours%10+((int)(analogRead(a_knob)/103)));
  }else if(editStage==4){
    hours=(hours%10+((int)(analogRead(a_knob)/342))*10);
  }else if(editStage==5) {
    alarmMinutes=(int)(analogRead(a_knob)/257)*15;
  }else if(editStage==6){
    alarmHours=((int)analogRead(a_knob)/43)+1;
  }else if(editStage==7) {
    selectedTune=(int)(analogRead(a_knob)/342);
  }
  
}

