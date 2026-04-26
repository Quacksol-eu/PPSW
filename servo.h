void DetectorInit();
enum DetectorState {ACTIVE, INACTIVE};
enum DetectorState eReadDetector();
enum ServoState {CALLIB, IDLE, IN_PROGRESS};
void ServoInit(unsigned int uiServoFrequency);
void ServoCalib(void);
void ServoGoTo(unsigned int uiPosition);