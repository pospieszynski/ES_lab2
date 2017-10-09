dbgu_print_ascii(const char *a) {}

#define PIT_ENABLED (1<<24)
#define PIT_DISABLED ~(1<<24)
#define SET_DS_1 (1<<8)

volatile unsigned int* 	PIT_MR = (volatile unsigned int*)(0xFFFFFD30);
volatile unsigned int* 	PIT_SR = (volatile unsigned int*)(0xFFFFFD34);

volatile unsigned int* PIOB_PER = (volatile unsigned int*)0xFFFFF400;
volatile unsigned int* PIOB_OER = (volatile unsigned int*)0xFFFFF410;
volatile unsigned int* PIOB_ODSR = (volatile unsigned int*)0xFFFFF438;

volatile unsigned int* PIOB_SODR = (volatile unsigned int*)0xFFFFF430;
volatile unsigned int* PIOB_CODR = (volatile unsigned int*)0xFFFFF434;

void startTimer();
void enablePIT();
void disablePIT();
void turnOffDS1();
unsigned int checkIfStoppped();
unsigned int checkIfTurnedOn();
void turnOnDS1();
void configureDS1();

int main() {
  configureDS1();
  
  enablePIT();
  while(1) {
    startTimer();
    if(checkIfStoppped()) {
      if(checkIfTurnedOn()) {
	turnOffDS1();
      }else {
	turnOnDS1();
      }
      disablePIT();
      enablePIT();
    }
  }
}

void turnOnDS1() {
  *PIOB_CODR = SET_DS_1;
}

void turnOffDS1() {
  *PIOB_SODR = SET_DS_1;
}

unsigned int checkIfTurnedOn() {
  if(*PIOB_ODSR & SET_DS_1) {
    return 1;
  } else {
    return 0;
  }
}

void configureDS1() {
  // Peripherial enable register must be configured to set IO port in IO mode and enable further configuration
  *PIOB_PER = SET_DS_1;
  // By defult, IO mode is set to input but we want diods to be used as an output(blinking)
  *PIOB_OER = SET_DS_1;
  // Switch off DS1 by default
  turnOffDS1();
}

unsigned int checkIfStoppped() {
  if(*PIT_SR) {
    return 1;
  } else {
    return 0;
  }
}

void startTimer() {
  *PIT_MR = *PIT_MR | 6279 * 1000;
}

void enablePIT() {
  *PIT_MR = *PIT_MR | PIT_ENABLED;
}

void disablePIT() {
  *PIT_MR = *PIT_MR & PIT_DISABLED;
}