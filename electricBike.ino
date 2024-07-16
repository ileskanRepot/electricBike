int const potPin = A0;
const int motorLeft = 6;
const int motorRight = 5;

const int cutVal = 20;

const int LIST_SIZE = 10;
unsigned char avgList[LIST_SIZE];
int listPos = 0;

int cut(int val, char minVal){
  if (val < minVal){
    return 0;
  }
  return val;  
}

int avg(unsigned char*list, int listSize){
  int sum = 0;
  for (int ii = 0; ii < listSize; ii++){
    sum += avgList[ii];
    Serial.print(avgList[ii], DEC);
    Serial.print(" ");
  }
  Serial.println();
  return sum / listSize;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(motorLeft, OUTPUT);
  pinMode(motorRight, OUTPUT);

  for (int ii = 0; ii < LIST_SIZE; ii++){
    avgList[ii] = 0;  
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  const int potVal = analogRead(potPin);
  const int mappedVal = map(potVal, 0, 1024, 0, 256);
  // Serial.println(potVal);

  avgList[listPos] = mappedVal;
  listPos = (listPos + 1) % LIST_SIZE;

  int writeMotor = cut(avg(avgList, LIST_SIZE), cutVal);
  if (mappedVal < cutVal) {
    writeMotor = 0;  
  }
  analogWrite(motorLeft, writeMotor);
  analogWrite(motorRight, 0);
  
  delay(100);
}
