// 필요한 라이브러리를 포함합니다.
#include <DHT.h>    // 강수량 센서 라이브러리
#include <Servo.h>   // 모터 제어 라이브러리

// 강우량 센서와 핀 번호를 정의합니다.
#define RAIN_SENSOR_PIN A0

// 조도 센서와 핀 번호를 정의합니다.
#define LIGHT_SENSOR_PIN A2

// LED 및 모터를 제어할 핀 번호를 정의합니다.
#define LED_PIN 6
#define MOTOR_PIN 5

// 모터의 회전 각도 범위를 정의합니다.
#define MOTOR_OPEN_ANGLE 0   // 그물을 걷는 동작
#define MOTOR_CLOSE_ANGLE 90 // 그물을 뿌리는 동작

// 모터 객체를 생성합니다.
Servo motor;

void setup() {
  // 시리얼 통신을 초기화합니다.
  Serial.begin(9600);

  // LED 및 모터를 제어할 핀을 출력으로 설정합니다.
  pinMode(LED_PIN, OUTPUT);
  pinMode(MOTOR_PIN, OUTPUT);

  // 모터를 초기 위치로 돌립니다.
  motor.attach(MOTOR_PIN);
  motor.write(MOTOR_CLOSE_ANGLE);
}

void loop() {
  Serial.println("시작");
  // 강우량 센서 값 읽기
  int rainSensorValue = analogRead(RAIN_SENSOR_PIN);
  // Serial.println(rainSensorValue);

  // 조도 센서에서 데이터를 읽어옵니다.
  int lightValue = analogRead(LIGHT_SENSOR_PIN);
  Serial.println(lightValue);



  // 강우량이 감지되면 LED와 모터를 작동시킵니다.
  if (rainSensorValue < 600) {
    digitalWrite(LED_PIN, HIGH);
    motor.write(MOTOR_OPEN_ANGLE);
    delay(5000); // 일정 시간 동안 모터 동작 유지
    // motor.write(MOTOR_CLOSE_ANGLE);
    digitalWrite(LED_PIN, LOW);
    Serial.println("rainy");
  }
  // 비가 감지되지 않았지만 조도가 낮으면 그물을 뿌리는 동작을 실행합니다.
  else if (lightValue > 100) {
    motor.write(MOTOR_OPEN_ANGLE);
    delay(5000); // 일정 시간 동안 모터 동작 유지
    // motor.write(MOTOR_CLOSE_ANGLE);
    Serial.println("nosunny");
  }
  // 아무 감지도 되지 않을 때는 그물을 걷는 동작을 실행합니다.
  else {
    motor.write(MOTOR_CLOSE_ANGLE);
    Serial.println("sunny");
  }


  // 일정 시간 간격으로 반복합니다.
  delay(5000);
}
