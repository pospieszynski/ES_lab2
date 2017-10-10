dbgu_print_ascii(const char *a) {}
#define TASK_1 1
#define TASK_2 0
#define TASK_3 0

#define COUNT_FOR_1_MILISEC 6250
#define CLOCK_DISABLED
#define PIT_ENABLED (1<<24)
#define PIT_DISABLED ~(1<<24)
#define PIT_INTERRUPT_ENABLE (1<<25)
#define PIT_INTERRUPT_DISABLE ~(1<<25)
#define SET_DSEGMENT_1 (1<<8)

#define SEGMENT_A (1 << 25)
#define SEGMENT_B (1 << 24)
#define SEGMENT_C (1 << 22)
#define SEGMENT_D (1 << 21)
#define SEGMENT_E (1 << 20)
#define SEGMENT_F (1 << 27)
#define SEGMENT_G (1 << 26)

#define RIGHT_DISPLAY (1 << 30)
#define LEFT_DISPLAY (1 << 28)

#define ZERO  (SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F)
#define ONE   (SEGMENT_B | SEGMENT_C)
#define TWO   (SEGMENT_A | SEGMENT_B | SEGMENT_G | SEGMENT_E | SEGMENT_D)
#define THREE (SEGMENT_A | SEGMENT_B | SEGMENT_G | SEGMENT_C | SEGMENT_D)
#define FOUR  (SEGMENT_F | SEGMENT_G | SEGMENT_B | SEGMENT_C)
#define FIVE  (SEGMENT_A | SEGMENT_F | SEGMENT_G | SEGMENT_C | SEGMENT_D)
#define SIX   (SEGMENT_A | SEGMENT_F | SEGMENT_G | SEGMENT_E | SEGMENT_D | SEGMENT_C)
#define SEVEN (SEGMENT_A | SEGMENT_B | SEGMENT_C)
#define EIGHT (SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G)
#define NINE  (SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_G | SEGMENT_F)

// TIMER REGS
volatile unsigned int* 	PIT_MR = (volatile unsigned int*)(0xFFFFFD30);
volatile unsigned int*  PIT_SR = (volatile unsigned int*)(0xFFFFFD34);
volatile unsigned int* 	PIT_PIVR = (volatile unsigned int*)(0xFFFFFD38);

//IO PORT REGS
volatile unsigned int* PIOB_PER = (volatile unsigned int*)0xFFFFF400;
volatile unsigned int* PIOB_OER = (volatile unsigned int*)0xFFFFF410;
volatile unsigned int* PIOB_ODSR = (volatile unsigned int*)0xFFFFF438;
volatile unsigned int* PIOB_SODR = (volatile unsigned int*)0xFFFFF430;
volatile unsigned int* PIOB_CODR = (volatile unsigned int*)0xFFFFF434;

//DISPLAY
void configureDisplay();
void displayDigit(unsigned int digit)
void enableLeftDisplay();
void disableLeftDisplay();
void enableRightDisplay();
void disableRightDisplay();

//PIT
void configurePIT();
void enablePIT();
void disablePIT();
void clearTimerStatusRegister() 
unsigned int checkIfTimerStoppped();

int main() {
  configurePIT();
  configureDisplay();

  #if TASK_1
    enableLeftDisplay();
    displayDigit(7);
    delay(5000);
    clearAllSegments();
  #endif

  #if TASK_2
    enableRightDisplay();
    unsigned int counter = 0;
    while(1) {
      clearAllSegments();
      displayDigit(counter);
      delay(1000);
      counter++;
      if(counter == 10) counter = 0;
    }
  #endif

  #if TASK_3

  #endif

}

void configurePIT() {
  *PIT_MR |= COUNT_FOR_1_MILISEC;
  *PIT_MR &= PIT_INTERRUPT_DISABLE;
  clearTimerStatusRegister();
  disablePIT();
}

void configureDisplay() {

  *PIOB_PER  = LEFT_DISPLAY;
  *PIOB_OER  = LEFT_DISPLAY;
  disableLeftDisplay();

  *PIOB_PER  = RIGHT_DISPLAY;
  *PIOB_OER  = RIGHT_DISPLAY;
  disableRightDisplay();

  *PIOB_PER  = SEGMENT_A;
  *PIOB_OER  = SEGMENT_A;
  *PIOB_CODR = SEGMENT_A;
  
  *PIOB_PER  = SEGMENT_B;
  *PIOB_OER  = SEGMENT_B;
  *PIOB_CODR = SEGMENT_B;
  
  *PIOB_PER  = SEGMENT_C;
  *PIOB_OER  = SEGMENT_C;
  *PIOB_CODR = SEGMENT_C;
  
  *PIOB_PER  = SEGMENT_D;
  *PIOB_OER  = SEGMENT_D;
  *PIOB_CODR = SEGMENT_D;
  
  *PIOB_PER  = SEGMENT_E;
  *PIOB_OER  = SEGMENT_E;
  *PIOB_CODR = SEGMENT_E;
  
  *PIOB_PER  = SEGMENT_F;
  *PIOB_OER  = SEGMENT_F;
  *PIOB_CODR = SEGMENT_F;
  
  *PIOB_PER  = SEGMENT_G;
  *PIOB_OER  = SEGMENT_G;
  *PIOB_CODR = SEGMENT_G;
}

void enableLeftDisplay() {
  *PIOB_CODR = LEFT_DISPLAY;
}

void disableLeftDisplay() {
  *PIOB_SODR = LEFT_DISPLAY;
}

void enableRightDisplay() {
  *PIOB_CODR = RIGHT_DISPLAY;
}

void disableRightDisplay() {
  *PIOB_SODR = RIGHT_DISPLAY; 
}

void clearAllSegments() {
  *PIOB_CODR = EIGHT;
}

void displayDigit(unsigned int digit) {
  switch(digit) {
    case 0:
      *PIOB_SODR = ZERO;
      break;
    case 1:
      *PIOB_SODR = ONE;
      break;
    case 2:
      *PIOB_SODR = TWO;
      break;
    case 3:
      *PIOB_SODR = THREE;
      break;
    case 4:
      *PIOB_SODR =  FOUR
      break;
    case 5:
      *PIOB_SODR = FIVE;
      break;
    case 6:
      *PIOB_SODR = SIX;
      break;
    case 7:
      *PIOB_SODR = SEVEN;
      break;
    case 8:
      *PIOB_SODR = EIGHT;
      break;
    case 9:
      *PIOB_SODR = NINE;
      break;
  }
}

unsigned int checkIfTimerStoppped() {
  if(*PIT_SR) {
    return 1;
  } else {
    return 0;
  }
}

void enablePIT() {
  *PIT_MR |= PIT_ENABLED;
}

void disablePIT() {
  *PIT_MR &= PIT_DISABLED;
}

void clearTimerStatusRegister() {
  *PIT_PIVR; 
}

void delay(unsigned int miliseconds) {
  unsigned int counter;
  enablePIT();
  for(counter = 0; counter < miliseconds; counter++) {
    while(!checkIfStoppped);
    clearTimerStatusRegister();
  }
  disablePIT();
}