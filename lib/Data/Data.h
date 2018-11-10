#ifndef __Data_H
#define __Data_H

#include <Arduino.h>

class Data
{
public:
  Data();
  float temperature;
  bool heating;
  int anim;

  void setData(void);
  bool dataAreValid(void);
};

#endif
