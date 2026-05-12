void DetectorInit();
enum DetectorState {ACTIVE, INACTIVE};
enum DetectorState eReadDetector();
enum ServoState {CALLIB, IDLE, IN_PROGRESS};
void ServoInit(unsigned int uiServoFrequency);
void ServoCalib(void);
void ServoGoTo(unsigned int uiPosition);
struct Servo
{
	
	enum ServoState eState; 
	unsigned int uiCurrentPosition; 
	unsigned int uiDesiredPosition;
	
};
extern volatile struct Servo sServo;

