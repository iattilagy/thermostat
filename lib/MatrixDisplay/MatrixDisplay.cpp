#include "MatrixDisplay.h"
#include <EEPROM.h>

MLED matrix(7);

MatrixDisplay::MatrixDisplay()
{
    
}

/* Draw one in 2x5 pixels */
void drawOne25(uint16_t x, uint16_t y){
    matrix.drawPixel(x, y + 1, LED_ON);
    matrix.drawLine(x + 1, y, x + 1, y + 4, LED_ON);
}

/* Draw two in 2x5 pixels */
void drawTwo25(uint16_t x, uint16_t y){
    matrix.drawPixel(x, y, LED_ON);
    matrix.drawLine(x + 1, y, x + 1, y + 2, LED_ON);
    matrix.drawLine(x, y + 2, x, y + 4, LED_ON);
    matrix.drawPixel(x + 1, y + 4, LED_ON);
}

/* Draw three in 2x5 pixels */
void drawThree35(uint16_t x, uint16_t y){
    matrix.drawLine(x, y, x +2, y, LED_ON);
    matrix.drawLine(x, y + 2, x + 2, y + 2, LED_ON);    
    matrix.drawLine(x, y + 4, x + 2, y + 4, LED_ON);
    matrix.drawLine(x + 2, y, x + 2, y + 4, LED_ON);
}

/* Draw four in 2x5 pixels */
void drawFour35(uint16_t x, uint16_t y){
    matrix.drawLine(x + 2, y, x + 2, y + 4, LED_ON);
    matrix.drawLine(x + 2, y, x, y + 2, LED_ON);
    matrix.drawLine(x, y + 3, x + 2, y + 3, LED_ON);
    matrix.drawPixel(x + 2, y + 4, LED_ON);
}

/* Draw five in 2x5 pixels */
void drawFive35(uint16_t x, uint16_t y){
    matrix.drawLine(x, y, x +2, y, LED_ON);
    matrix.drawLine(x, y + 2, x + 2, y + 2, LED_ON);    
    matrix.drawLine(x, y + 4, x + 2, y + 4, LED_ON);
    matrix.drawLine(x, y, x, y + 2, LED_ON);
    matrix.drawLine(x + 2, y + 2, x + 2, y + 4, LED_ON);
}

/* Draw six in 2x5 pixels */
void drawSix35(uint16_t x, uint16_t y){
    matrix.drawLine(x, y, x +2, y, LED_ON);
    matrix.drawLine(x, y + 2, x + 2, y + 2, LED_ON);    
    matrix.drawLine(x, y + 4, x + 2, y + 4, LED_ON);
    matrix.drawLine(x, y, x, y + 4, LED_ON);
    matrix.drawLine(x + 2, y + 2, x + 2, y + 4, LED_ON);
}

/* Draw seven in 2x5 pixels */
void drawSeven35(uint16_t x, uint16_t y){
    matrix.drawLine(x, y, x +2, y, LED_ON);
    matrix.drawLine(x + 2, y, x + 2, y + 2, LED_ON);    
    matrix.drawLine(x + 1, y + 2, x + 1, y + 4, LED_ON);
}

/* Draw eight in 2x5 pixels */
void drawEight35(uint16_t x, uint16_t y){
    matrix.drawLine(x, y, x +2, y, LED_ON);
    matrix.drawLine(x, y + 2, x + 2, y + 2, LED_ON);    
    matrix.drawLine(x, y + 4, x + 2, y + 4, LED_ON);
    matrix.drawLine(x, y, x, y + 4, LED_ON);
    matrix.drawLine(x + 2, y, x + 2, y + 4, LED_ON);
}

/* Draw eight in 2x5 pixels */
void drawNine35(uint16_t x, uint16_t y){
    matrix.drawLine(x, y, x +2, y, LED_ON);
    matrix.drawLine(x, y + 2, x + 2, y + 2, LED_ON);    
    matrix.drawLine(x, y + 4, x + 2, y + 4, LED_ON);
    matrix.drawLine(x, y, x, y + 2, LED_ON);
    matrix.drawLine(x + 2, y, x + 2, y + 4, LED_ON);
}

/* Draw eight in 2x5 pixels */
void drawZero35(uint16_t x, uint16_t y){
    matrix.drawLine(x, y, x +2, y, LED_ON);
    matrix.drawLine(x, y + 4, x + 2, y + 4, LED_ON);
    matrix.drawLine(x, y, x, y + 4, LED_ON);
    matrix.drawLine(x + 2, y, x + 2, y + 4, LED_ON);
}

void drawM(uint16_t x, uint16_t y){
    matrix.drawPixel(x, y, LED_ON);
    matrix.drawPixel(x + 2, y, LED_ON);
    
    matrix.drawLine(x, y + 1, x + 2, y + 1, LED_ON);
}

void drawT(uint16_t x, uint16_t y){
    matrix.drawLine(x, y, x + 2, y, LED_ON);

    matrix.drawPixel(x+1, y+1, LED_ON);
}

void MatrixDisplay::update(Data data)
{
    matrix.clear();

    float temp;
    if(data.anim == 0 || !data.heating){
        temp = data.temperature;
        drawM(0, 6);
    } else {
        temp = EEPROM.read(2);
        drawT(0, 6);
    }

    int t = temp;
    if(t/10 == 2){
        drawTwo25(0, 0);
    } else if(t/10 == 1){
        drawOne25(0, 0);
    }

    switch (t % 10){
        case 0:
            drawZero35(3, 0);
            break;
        case 1:
            drawOne25(4, 0);
            break;
        case 2:
            drawTwo25(4, 0);
            break;
        case 3:
            drawThree35(3, 0);
            break;
        case 4:
            drawFour35(3, 0);
            break;
        case 5:
            drawFive35(3, 0);
            break;
        case 6:
            drawSix35(3, 0);
            break;
        case 7:
            drawSeven35(3, 0);
            break;
        case 8:
            drawEight35(3, 0);
            break;
        case 9:
            drawNine35(3, 0);
            break;
    }

    int a = (temp * 10);
    a %= 10;
    switch (a){
        case 9:
        case 8:
            matrix.drawPixel(7, 0, LED_ON);
        case 7:
        case 6:           
            matrix.drawPixel(7, 1, LED_ON);        
        case 5:
        case 4:     
            matrix.drawPixel(7, 2, LED_ON);
        case 3:
        case 2:
            matrix.drawPixel(7, 3, LED_ON);
        case 1:
        case 0:
            matrix.drawPixel(7, 4, LED_ON);
    }

    if(data.heating){
        for(int i = 4; i < 8; i +=2){
            if(data.anim == 0){
                matrix.drawPixel(i + 1, 6, LED_ON);
                matrix.drawPixel(i, 7, LED_ON);
            } else {
                matrix.drawPixel(i + 1, 7, LED_ON);
                matrix.drawPixel(i, 6, LED_ON);
            }
        }
    }
    matrix.writeDisplay();
}

// clear display, set size and cursor
void MatrixDisplay::prepareDisplay(void)
{
    
}