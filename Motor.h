#ifndef MOTOR_H
#define MOTOR_H

class Motor()
{
  public:
    void Init(float R, float L, float Kt, float J, float B, float Ke);
  private:
  void CalculateCurrent();
    float R, L, Kt, J, B, Ke;
    float Va, Ia, Ea;
}

void Motor::Init(float R, float L, float Kt, float J, float B, float Ke)
{
  this->R = R;
  this->L = L;
  this->Kt = Kt;
  this->J = J;
  this->B = B;
  this->Ke;
  this->Va = 0;
  this->Ia = 0;
  this->Ea = 0;
}

void Motor::CalculateCurrent(float Va)
{
  
}

#endif
