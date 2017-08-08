#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define BACKLIGHT_PIN     13

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// classRoster is a list of all students in a class
char* classRoster[]={
  "Colton",
  "Sophie",
  "Jimmy",
  "Phil", 
  "Skittlez"
};

// determins the length of the classRoster array
int classRosterLength = sizeof(classRoster) / sizeof(classRoster[0]);

// alreadyChosen is a list of students (their index in the roster) who have
// already been chosen for snack. We fill this list with numbers as the students are
// selected. We verify newly selected students aren't already in this list.
// Resetting the Snackerator is wiping out this list of already chosen kids.
// set each element to -1, so we can scan and find which index is "next".
int alreadyChosen[50] = {};
int alreadyChosenLength = sizeof(alreadyChosen) / sizeof(alreadyChosen[0]);

// pins for buttons
int NEXT_STUDENT_BTN = 2;
int AT_LESSON_BTN = 3;
int RESET_BTN = 4;  // TODO: change me from a button to fob

// selectedStudentIndex is the student currently snacking.
// the number represents the index of the student in the classRoster list
int selectedStudentIndex = -1;

// lastClickTime is the timestamp for the last button click.
// this is reset for each successful button push (outside the minimum wait window)
// and we compare the current time against lastClickTime to determine whether or not
// the minimum wait window is satisfied.
long lastClickTime = 0;

// minimumWait is the minimum number of milliseconds in between each "click"
// so that someone can't spam the button.
int minimumWait = 1000;

// depth is stack depth to avoid infinite recursion
int depth = 0;

void setup()
{
  pinMode(NEXT_STUDENT_BTN, INPUT);
  pinMode(AT_LESSON_BTN, INPUT);
  pinMode(RESET_BTN, INPUT);
    
  lcd.begin(16,2);
  lcd.backlight();
  
  randomSeed(analogRead(0));

  lcd.home ();                   // go home
  lcd.print("Setup ... ");
  lcd.setCursor ( 0, 1 );        // go to the next line
  delay(500);
  lcd.print ("Snackerator 9000");
  delay(500);
  lcd.clear();
  
  reset();
}

boolean hasMinimumTimeElapsed(){
  // lastClickTime should be 0 when the Snackerator first starts
  if (lastClickTime == 0){
    return true;
  }
  long currentTime = millis();
  long elapsed = currentTime - lastClickTime;
  return elapsed > minimumWait;
}

boolean isAlreadyChosen(int index) {
  for(int i = 0; i < alreadyChosenLength; i++){
     if (index == alreadyChosen[i]){
        return true;
     } 
  }
  return false;
}

int getNextStudent(){
  for(int x = 0; x < 1000; x++){
    int randomStudent = random(classRosterLength - 1);
    if (!isAlreadyChosen(randomStudent)){
       return randomStudent;    
    } 
  }
  return -1;
}

void reset(){
  int length = (sizeof(alreadyChosen) / sizeof(alreadyChosen[0]));
 for(int i = 0; i < length ; i++){
   alreadyChosen[i] = -1; 
 }
 selectedStudentIndex = -1;
 lcd.clear();
}

void addStudent(int index){
  int length = (sizeof(alreadyChosen) / sizeof(alreadyChosen[0]));
  for(int i = 0; i < length ; i++){
      if (alreadyChosen[i] == -1) {
        alreadyChosen[i] = index;
        return; 
      }
    }
}


void loop()
{ 
  int nextStudentButton = digitalRead(NEXT_STUDENT_BTN);
  int lesson = digitalRead(AT_LESSON_BTN);
  int resetStudents = digitalRead(RESET_BTN);
  
  if (nextStudentButton == HIGH && hasMinimumTimeElapsed()){
    lcd.clear();
    int randomInt = getNextStudent();
    lastClickTime = millis();
    selectedStudentIndex = randomInt;  
    lcd.print(classRoster[selectedStudentIndex]);
    addStudent(selectedStudentIndex);
  }
  
  if (resetStudents == HIGH) {
    lcd.print("Reset...");
    delay(100);
    reset(); 
  }
  
}





void fadeLeft(String msg1){
  fadeLeft(msg1, "");
}

void fadeLeft(String msg1, String msg2){
  lcd.clear();
  lcd.home ();
  lcd.print (msg1);
  lcd.setCursor ( 0, 1 );
  lcd.print (msg2);
  delay(700);

  for(int i = 0; i < 16; i++){
    lcd.scrollDisplayLeft();  
    delay(100);
  }  
}

void fadeRight(String msg1){
  fadeRight(msg1, "");
}

void fadeRight(String msg1, String msg2){
  lcd.clear();
  lcd.home ();
  lcd.print (msg1);
  lcd.setCursor ( 0, 1 );
  lcd.print (msg2);
  delay(700);

  for(int i = 0; i < 16; i++){
    lcd.scrollDisplayRight();  
    delay(100);
  }  
}
