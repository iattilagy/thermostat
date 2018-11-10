#ifndef __OledDisplay_H
#define __OledDisplay_H

#include <Adafruit_GFX.h>
#include <WEMOS_Matrix_GFX.h>
#include <Data.h>

static const uint8_t PROGMEM
  one_2_5_bmp[] =
  { B01,
    B11,
    B01,
    B01,
    B01 },
  two_2_5_bmp[] =
  { B11,
    B01,
    B01,
    B10,
    B11 };


class MatrixDisplay
{
  public:
    MatrixDisplay();
    void update(Data data);

  private:
    void prepareDisplay(void);
};

#endif
