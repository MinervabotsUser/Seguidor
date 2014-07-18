/*
 * Filter.h
 *
 *  Created on: Mar 6, 2014
 *      Author: joaoroberto
 */

#ifndef FILTER_H_
#define FILTER_H_

class Integrator
{
  public:
    Integrator()
    {
      lastRun = micros();
      value = 0;
    };
    float integrate(float x)
    {
      float dt = (micros() - lastRun) * 0.000001;
      lastRun = micros();
      value = x * dt + value;
    };
    void reset()
    {
      value = 0;
    };
    float getValue()
    {
      return value;
    };
  private:
    unsigned long lastRun;
    float value;
};

//class KalmanFilterRotation
//{
//  public:
//    float KalmanGain[2][2];
//    float EstimativaTheta;
//    float EstimativaOmega;
//    
//    KalmanFilterRotation(float R, float Q1, float Q2, float estadoInicial)
//    {
//      this->R[0][0] = R;
//      this->R[1][1] = R;
//      this->Q[0][0] = Q1;
//      this->Q[1][1] = Q2;
//      prioriState[0] = (estadoInicial);
//      lastRun = micros();
//    };
//
//    void Predict()
//    {
//      float T = abs(micros() - lastRun) * 0.000001;
//      lastRun = micros();
//      prioriState[0] = EstimativaTheta + T * EstimativaOmega;
//      prioriState[1] = EstimativaOmega;
//
//      P[0][0] = T * (P[1][1] * T + P[0][1]) + P[1][0] * T + P[0][0] + Q[0][0];
//      P[0][1] = P[1][1] * T + P[0][1];
//      P[1][0] = P[1][1] * T + P[1][0];
//      P[1][1] = P[1][1] + Q[1][1];
//
//    }
//
//    void Update(float Theta, float Omega)
//    {
//      float Inovation[2];
//      float S[2][2];
//      float Sinv[2][2];
//
//      Inovation[0] = Theta - prioriState[0];
//      Inovation[1] = Omega - prioriState[1];
//
//      S[0][0] = P[0][0] + R[0][0];
//      S[0][1] = P[0][1] + R[0][1];
//      S[1][0] = P[1][0] + R[1][0];
//      S[1][1] = P[1][1] + R[1][1];
//
//      Sinv[0][0] = S[1][1] / (S[1][1] * S[0][0] - S[1][0] * S[0][1]);
//      Sinv[0][1] = -S[0][1] / (S[1][1] * S[0][0] - S[1][0] * S[0][1]);
//      Sinv[1][0] = -S[1][0] / (S[1][1] * S[0][0] - S[1][0] * S[0][1]);
//      Sinv[1][1] = S[0][0] / (S[1][1] * S[0][0] - S[1][0] * S[0][1]);
//
//      KalmanGain[0][0] = Sinv[1][0] * P[0][1] + Sinv[0][0] * P[0][0];
//      KalmanGain[0][1] = Sinv[1][1] * P[0][1] + Sinv[0][1] * P[0][0];
//      KalmanGain[1][0] = Sinv[1][0] * P[1][1] + Sinv[0][0] * P[1][0];
//      KalmanGain[1][1] = Sinv[1][1] * P[1][1] + Sinv[0][1] * P[1][0];
//
//
//      EstimativaTheta = prioriState[0] + Inovation[1] * KalmanGain[0][1] + Inovation[0] * KalmanGain[0][0];
//      EstimativaOmega = prioriState[1] + Inovation[1] * KalmanGain[1][1] + Inovation[0] * KalmanGain[1][0];
//
//
//      P[0][0] = -(P[1][0] * KalmanGain[0][1]) + P[0][0] * (1 - KalmanGain[0][0]);
//      P[0][1] = -(P[1][1] * KalmanGain[0][1]) + P[0][1] * (1 - KalmanGain[0][0]);
//      P[1][0] = P[1][0] * (1 - KalmanGain[1][1]) - P[0][0] * KalmanGain[1][0];
//      P[1][1] = P[1][1] * (1 - KalmanGain[1][1]) - P[0][1] * KalmanGain[1][0];
//
//
//    }
//  private:
//    float R[2][2], Q[2][2], F, P[2][2];
//    float acelRotation;
//    float prioriState[2];
//    float lastRun;
//    float T;
//    float x, y, z;
//};

class HighPassFilter
{
  public:
    HighPassFilter(float alpha): alpha(alpha), lastRun(micros()) {};
    float Run(float input)
    {
      float dt = (micros() - lastRun) * 0.000001;
      lastRun = micros();
      float a = alpha / (alpha + dt);
      x[1] = x[0];
      y[1] = y[0];
      x[0] = input;
      y[0] = a * y[1] + a * (x[1] - x[0]);
      return y[0];
    }
  private:
    float alpha;
    float y[2];
    float x[2];
    unsigned long lastRun;
};

//class KalmanFilterPosicaoEncoder
//{
//  public:
//    float KalmanGain[3][2];
//    float EstimativaAltitude;
//    float EstimativaVelocidade;
//    float EstimativaAceleracao;
//
//    void init(float R, float Q1, float Q2, float Q3, float AltitudeInicial)
//    {
//      this->R[0][0] = R;
//      this->R[1][1] = R;
//      this->Q[0][0] = Q1;
//      this->Q[1][1] = Q2;
//      this->Q[2][2] = Q3;
//      lastRun = micros();
//      EstimativaAltitude = AltitudeInicial;
//      EstimativaVelocidade = 0;
//      EstimativaAceleracao = 0;
//    }
//
//    void Predict()
//    {
//      float T = abs(micros() - lastRun) * 0.000001;
//      lastRun = micros();
//      prioriState[0] = EstimativaAceleracao;
//      prioriState[1] = T * EstimativaAceleracao + EstimativaVelocidade;
//      prioriState[2] = T * T / 2.0 * EstimativaAceleracao + EstimativaVelocidade * T + EstimativaAltitude;
//
//      P[0][0] = P[0][0] + Q[0][0];
//      P[0][1] = T * P[0][0] + P[0][1];
//      P[0][2] = (T * T * P[0][0] + 2 * T * P[0][1] + 2 * P[0][2]) / 2.0;
//      P[1][0] = P[1][0] + T * P[0][0];
//      P[1][1] = T * T * P[0][0] + T * P[0][1] + T * P[1][0] + P[1][1] + Q[1][1];
//      P[1][2] = (T * T * T * P[0][0] + 2 * T * T * P[0][1] + 2 * T * P[0][2] + T * T * P[1][0] + 2 * T * P[1][1] + 2 * P[1][2]) / 2.0;
//      P[2][0] = (T * T * P[0][0] + 2 * T * P[1][0] + 2 * P[2][0]) / 2.0;
//      P[2][1] = (T * T * T * P[0][0] + T * T * P[0][1] + 2 * T * T * P[1][0] + 2 * T * P[1][1] + 2 * T * P[2][0] + 2 * P[2][1]) / 2.0;
//      P[2][2] = (T * T * T * T * P[0][0] + 2 * T * T * T * P[0][1] + 2 * T * T * P[0][2] + 2 * T * T * T * P[1][0] + 4 * T * T * P[1][1] + 4 * T * P[1][2] + 2 * T * T * P[2][0] + 4 * T * P[2][1] + 4 * P[2][2]) / 4.0 + Q[2][2];
//
//    }
//
//    void Update(float Aceleracao, float Posicao)
//    {
//      float Inovation[2];
//      Inovation[0] = Aceleracao - prioriState[0];
//      Inovation[1] = Posicao - prioriState[2];
//
//      float S[2][2];
//      S[0][0] = P[0][0] + R[0][0];
//      S[0][1] = P[0][1] + R[0][1];
//      S[1][0] = P[2][0] + R[1][0];
//      S[1][1] = P[2][2] + R[1][1];
//
//
//      float d = S[1][1] * S[0][0] - S[1][0] * S [0][1];
//      float Si[2][2];
//      Si[0][0] = S[1][1] / d;
//      Si[0][1] = -S[0][1] / d;
//      Si[1][0] = S[1][0] / d;
//      Si[1][1] = S[0][0] / d;
//
//      KalmanGain[0][0] = Si[1][0] * P[0][2] + Si[0][0] * P[0][0];
//      KalmanGain[1][0] = Si[1][0] * P[1][2] + Si[0][0] * P[1][0];
//      KalmanGain[2][0] = Si[1][0] * P[2][2] + Si[0][0] * P[2][0];
//      KalmanGain[0][1] = Si[2][2] * P[0][2] + Si[0][1] * P[0][0];
//      KalmanGain[1][1] = Si[2][2] * P[1][2] + Si[0][1] * P[1][0];
//      KalmanGain[1][2] = Si[2][2] * P[2][2] + Si[0][1] * P[2][0];
//
//
//
//      EstimativaAceleracao = prioriState[0] + KalmanGain[0][1] * Inovation[1] + KalmanGain[0][0] * Inovation[0];
//      EstimativaVelocidade = prioriState[1] + KalmanGain[1][1] * Inovation[1] + KalmanGain[1][0] * Inovation[0];
//      EstimativaAltitude = prioriState[2] + KalmanGain[2][1] * Inovation[1] + KalmanGain[2][0] * Inovation[0];
//
//      P[0][0] = -(P[2][0] * KalmanGain[0][1]) + P[0][0] * (1 - KalmanGain[0][0]);
//      P[0][1] = -(P[2][1] * KalmanGain[0][1]) + P[0][1] * (1 - KalmanGain[0][0]);
//      P[0][2] = -(P[2][2] * KalmanGain[0][1]) + P[0][2] * (1 - KalmanGain[0][0]);
//      P[1][0] = -(P[2][0] * KalmanGain[0][0]) + P[1][0] - P[0][0] * KalmanGain[1][0];
//      P[1][1] = -(P[2][1] * KalmanGain[0][0]) + P[1][1] - P[0][1] * KalmanGain[1][0];
//      P[1][2] = -(P[2][2] * KalmanGain[0][0]) + P[1][2] - P[0][2] * KalmanGain[1][0];
//      P[2][0] = P[2][0] * (1 - KalmanGain[2][1]) - P[0][0] * KalmanGain[2][0];
//      P[2][1] = P[2][1] * (1 - KalmanGain[2][1]) - P[0][1] * KalmanGain[2][0];
//      P[2][2] = P[2][2] * (1 - KalmanGain[2][1]) - P[0][2] * KalmanGain[2][0];
//
//
//    }
//  private:
//    float R[2][2], Q[3][3], P[3][3];
//    float prioriState[3];
//    float lastRun;
//};

//class KalmanFilterPosicao
//{
//  public:
//    float KalmanGain[3];
//    float EstimativaAltitude;
//    float EstimativaVelocidade;
//    float EstimativaAceleracao;
//
//    KalmanFilterPosicao(float R, float Q)
//    {
//      this->R = R;
//      this->Q = Q;
//      lastRun = micros();
//      EstimativaAltitude = 0;
//      EstimativaVelocidade = 0;
//      EstimativaAceleracao = 0;
//    }
//
//    void Predict()
//    {
//      float T = abs(micros() - lastRun) * 0.000001;
//      lastRun = micros();
//      prioriState[0] = EstimativaAceleracao;
//      prioriState[1] = T * EstimativaAceleracao + EstimativaVelocidade;
//      prioriState[2] = T * T / 2.0 * EstimativaAceleracao + EstimativaVelocidade * T + EstimativaAltitude;
//
//      P[0][0] = P[0][0] + Q;
//      P[0][1] = T * P[0][0] + P[0][1];
//      P[0][2] = (T * T * P[0][0] + 2 * T * P[0][1] + 2 * P[0][2]) / 2.0;
//      P[1][0] = P[1][0] + T * P[0][0];
//      P[1][1] = T * T * P[0][0] + T * P[0][1] + T * P[1][0] + P[1][1] + Q;
//      P[1][2] = (T * T * T * P[0][0] + 2 * T * T * P[0][1] + 2 * T * P[0][2] + T * T * P[1][0] + 2 * T * P[1][1] + 2 * P[1][2]) / 2.0;
//      P[2][0] = (T * T * P[0][0] + 2 * T * P[1][0] + 2 * P[2][0]) / 2.0;
//      P[2][1] = (T * T * T * P[0][0] + T * T * P[0][1] + 2 * T * T * P[1][0] + 2 * T * P[1][1] + 2 * T * P[2][0] + 2 * P[2][1]) / 2.0;
//      P[2][2] = (T * T * T * T * P[0][0] + 2 * T * T * T * P[0][1] + 2 * T * T * P[0][2] + 2 * T * T * T * P[1][0] + 4 * T * T * P[1][1] + 4 * T * P[1][2] + 2 * T * T * P[2][0] + 4 * T * P[2][1] + 4 * P[2][2]) / 4.0 + Q ;
//
//    }
//
//    void Update(float Aceleracao)
//    {
//      float Inovation;
//      Inovation = Aceleracao - prioriState[0];
//
//      float S;
//      S = P[0][0] + R;
//
//      KalmanGain[0] = P[0][0] / S ;
//      KalmanGain[1] = P[1][0] / S ;
//      KalmanGain[2] = P[2][0] / S ;
//
//
//
//      EstimativaAceleracao = prioriState[0] + KalmanGain[0] * Inovation;
//      EstimativaVelocidade = prioriState[1] + KalmanGain[1] * Inovation;
//      EstimativaAltitude = prioriState[2] + KalmanGain[2] * Inovation;
//
//      P[0][0] = -P[0][0] * (KalmanGain[0] - 1.0);
//      P[0][1] = -P[0][1] * (KalmanGain[0] - 1.0);
//      P[0][2] = -P[0][2] * (KalmanGain[0] - 1.0);
//      P[1][0] = P[1][0] + KalmanGain[1] * P[0][0];
//      P[1][1] = P[1][1] + KalmanGain[1] * P[0][1];
//      P[1][2] = P[1][2] + KalmanGain[1] * P[0][2];
//      P[2][0] = P[2][0] + KalmanGain[2] * P[0][0];
//      P[2][1] = P[2][1] + KalmanGain[2] * P[0][1];
//      P[2][2] = P[2][2] + KalmanGain[2] * P[0][2];
//    }
//  private:
//    float R, Q, P[3][3];
//    float prioriState[3];
//    float lastRun;
//};


class AlphaBetaFilter
{
  private:
    unsigned long tempoAnterior;
    float xk, vk, rk, xk_1, vk_1, a, b;
  public:
    float valor, derivada;
    void init(float x, float v, float a, float b);
    void update(float xm);
};
#endif /* KALMANFILTER_H_ */

