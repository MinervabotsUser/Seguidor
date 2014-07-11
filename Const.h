#ifndef CONST_H
#define CONST_H

/***********  Bluetooth ************/
#define BLUETOOTH_TX 2
#define BLUETOOTH_RX 3
/***********************************/

/***********  Sensores  ************/
#define SENSOR_MAIS_ESQUERDO        0
#define SENSOR_ESQUERDO             1
#define SENSOR_MENOS_ESQUERDO       2
#define SENSOR_MENOS_DIREITO        3
#define SENSOR_DIREITO              4
#define SENSOR_MAIS_DIREITO         5
/***********************************/

/***********  Limiar dos Sensores ****/
#define LIMIAR_MAIS_ESQUERDO        800
#define LIMIAR_ESQUERDO             800
#define LIMIAR_MENOS_ESQUERDO       600
#define LIMIAR_MENOS_DIREITO        750
#define LIMIAR_DIREITO              900
#define LIMIAR_MAIS_DIREITO         850
/***********************************/

/***********  Motores  *************/
#define MOTOR_DIREITO 11
#define TERRA_DIREITO 10
#define MOTOR_ESQUERDO 5
#define TERRA_ESQUERDO 6
/***********************************/

#define MAX_SPEED 255
/***********  Constantes PID  ******/
#define kp MAX_SPEED/2
#define ki 0
#define kd 0
/***********************************/

#define NUMBER_OF_SENSORS  6

#endif
