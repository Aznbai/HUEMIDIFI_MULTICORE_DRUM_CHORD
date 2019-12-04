#define LED 2
// WIFI
// const char *ssid = "Buero";
// const char *password = "Katzenkot666";
const char *ssid = "L3 2,4";
const char *password = "24217969664271750506";
// const char *ssid = "midihub666";
// const char *password = "midihub666";
// ROTARY ENCODER
#define ROTARY_ENCODER_A_PIN 22      // CLK (A pin) any GPIO pin with interrupt
#define ROTARY_ENCODER_B_PIN 21      // DT (B pin) any GPIO pin with interrupt
#define ROTARY_ENCODER_BUTTON_PIN 19 // SW (button pin)  any GPIO pin
#define ROTARY_ENCODER_VCC_PIN -1    //
int encoderDelta;
int encoderLimits = 2;
bool encoderDirection = 0;
// TFT
int pageNumber;
unsigned int colour = 0;
// MIDI
#define MIDI_CLOCK_BYTE 0xF8
#define MIDI_START_BYTE 0xFA
#define MIDI_CONTINUE_BYTE 0xFB
#define MIDI_STOP_BYTE 0xFC
#define MIDI_RESET_BYTE 0xFF
#define MIDI_TUNEREQUEST_BYTE 0xF6
int drumCh = 1;
int chordCh = 2;
int arpCh = 3;
int drumTickCurr = 0;
int chordTickCurr = 0;
int drumTick[7] = {5, 11, 23, 47, 95, 191, 383};
int chordTick[9] = {5, 11, 23, 47, 95, 191, 383,767,1535};
int drumTickIndex = 0;
int chordTickIndex = 4;
//DRUMS
char *drumMask[6] = {
    "0000000000000000",
    "0000000000000000",
    "0000000000000000",
    "0000000000000000",
    "0000000000000000",
    "0000000000000000"};

String drumMask0 = "0000000000000000";
String drumMask1 = "0000000000000000";
String drumMask2 = "0000000000000000";
String drumMask3 = "0000000000000000";
String drumMask4 = "0000000000000000";
String drumMask5 = "0000000000000000";
int partPosition[6] = {0, 0, 0, 0, 0, 0};
int drumNotes[6] = {60, 62, 64, 65, 67, 69};
// volca notes 60, 62, 64, 65, 67, 69
//NOTES
int rootCurr = 60;
int notePrev = 60;
int noteCurr = 60;
int velMin = 100;
int velMax = 127;
int velCurr = 110;
int octShift = 0;
int fifthShift = 0;
// bool play16 = false;
bool tick16 = false;

// int scaleMajorStep[8] = {0, 2, 2, 1, 2, 2, 2, 1};
int scaleMajorStep[8] = {0, 2, 4, 5, 7, 9, 11, 12};
// int scaleMajorStep[8] = {0, 2, 5, 6, 8, 10, 12, 13};

int scaleProbStep[8] = {100, 0, 0, 0, 0, 0, 0, 0};
// CHORD
int chordRoot = 64;
bool chordPulseOn = false;
int chordScaleInterval[3][7] = { // [1=Major 0=Minor] [progression index]
    {0, 2, 4, 5, 7, 9, 11},
    {4, 5, 7, 9, 11, 12, 14},
    {7, 9, 11, 12, 14, 16, 17}};
int chordScaleStepIndex[16] = {0, 1, 3, 4, 0, 1, 3, 4, 0, 1, 3, 4, 0, 1, 3, 4};
int chordScaleStepCurr = 0;
int chordStepNumber = 4;
int prevChord[3] = {40, 44, 47};
int currChord[3] = {52, 56, 59};
int currChordVel[3] = {52, 56, 59};
// PROGRESSION
int shiftCurr = 0;
int progCurr = 1;
int progStep = 1;
int progStepMax = 1;
int progShift[11] = {2, 6, 8, 4, 5, 7, 2, 11, 6, 8, 5};
int progChord[2][11] = { // [1=Major 0=Minor] [progression index]
    {1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0}};
bool progStart = true;
unsigned long bpmMin = 20.0;
unsigned long bpmMax = 380.0;
unsigned long bpmCurr = 120.0;
int bpmIn = 1;
int bpmInPrev = 1;
unsigned long ppqnDurr = 20833.0;   //micros per pulse @120 bpm
unsigned long note16Durr = 20833.0; //micros per pulse @120 bpm
unsigned long currPPQNMicros = 0.0;
unsigned long prevPPQNMicros = 0.0;
unsigned long curr16Micros = 0.0;
unsigned long prev16Micros = 0.0;
bool pulseOn = false;

// SERVER
bool playOn = false;
bool newStart = true;
bool newStartPrev = false;

//ERROR STATE VARIABLES
bool spiffsErr = true;
bool dnsErr = true;
bool wifiErr = true;
byte omm = 99;
