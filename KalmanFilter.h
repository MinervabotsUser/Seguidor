#ifndef KALMAN_H
#define KALMAN_H
#include <MatrixMath.h>

class KalmanFilter
{
  public:
  KalmanFilter
  {
    H[0][0] = 1;
    H[0][1] = 0;
    H[0][2] = 0;
    H[0][3] = 0;
    H[0][4] = 0;
    H[1][0] = 0;
    H[1][1] = 0;
    H[1][2] = 0;
    H[1][3] = 1;
    H[1][4] = 0;
    q[0] = 0;
    q[1] = 0;
    q[2] = 0;
    q[3] = 0;
    q[4] = 0;
    F[0][0] = 1;
    F[0][1] = 0;
    F[0][2] = 0;
    F[0][3] = 0;
    F[0][4] = 0;
    F[1][1] = 1;
    F[1][2] = 0;
    F[1][3] = 0;
    F[1][4] = 0;
    F[2][3] = 0;
    F[2][4] = 0;
    F[2][3] = 0;
    F[3][0] = 0;
    F[3][1] = 0;
    F[3][2] = 0;
    F[3][3] = 1;
    F[3][4] = 0;
    F[4][0] = 0;
    F[4][1] = 0;
    F[4][2] = 0;
    F[4][4] = 1;
    P[0][0] = 10000;
    P[1][1] = 10000;
    P[2][2] = 10000;
    P[3][3] = 10000;
    P[4][4] = 10000;
    lastRun = micros();
  }
  void Predict()
  {
    double dt = (micros()-lastRun)*10^(-6);
    F[1][0] = dt;
    F[2][0] = (dt*dt)/2.0;
    F[2][1] = dt;
    F[4][3] = dt;
    float qt[5][1];
    Matrix.Multiply((float *)F,(float *)q,5,5,1,(float*)qt);
    Matix.Copy((float *)qt,5,1,(float*)q);
    float pt[5][5];
    Matrix.Multiply((float*)F,(float*)P,5,5,5,(float*)pt);
    float ft[5][5];
    Matrix.Transpose((float*)F,5,5,(float*)ft);
    Matrix.Multiply((float*)pt,(float*)ft,5,5,5,(float*)P);
  };
  void Predict(int accel, int gyro)
  {
    float y[2] = { accel - q[0],gyro-q[4]};
    
  };
  private:
  float P[5][5];
  float Q[5][5];
  float F[5][5];
  float H[2][5];
  float x[5];
  unsigned long lastRun;
}
#endif
