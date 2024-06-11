#include <mega328p.h>
#include <delay.h>
#include "UARST.h"
int countA = 0;
int countB = 0;
int countHand = 1;
int ZO = 1;
void setup() {
  TCCR1A = 0;
  TCCR1B = 0;
  // RESET l?i 2 thanh ghi
  DDRB |= (1 << DDB1) | (1 << DDB2) | (1 << DDB3);
  // Ð?u ra PB1 và PB2 là OUTPUT ( pin ~9, ~10)
  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << WGM12) | (1 << WGM13);
  // ch?n Fast PWM, ch? d? ch?n TOP_value t? do ICR1
  ICR1H = 0xFF;
  ICR1L = 0xFF;
  // xung rang cua tràn sau 10001 P_clock
  TCCR1B |= (1 << CS10) | (0 << CS11) | (0 << CS12);
  TCCR1A |= (1 << COM1A1);
  // So sánh thu?ng cho PB1 ( none-inverting)
  TCCR1A |= (1 << COM1B1);
  // So sánh thu?ng cho PB2 ( none-inverting)
  OCR1AH = 8480 / 256;  //(PB1) Value=8480
  OCR1AL = 8480;        //(PB1) Value=8480
  OCR1BH = 0b00100001;  //(PB2) Value=8480
  OCR1BL = 0b00100000;  //(PB2) Value=8480
  UARTinit();
  //BUTTONS
  DDRD = (0 << DDD3) | (0 << DDD4) | (0 << DDD5) | (0 << DDD6) | (0 << DDD7);
  //TIMER 2
  TCCR2A = 0;
  TCCR2B = 0;
  //reset
  TCCR2A |= (1 << COM2A1);
  // so sánh thu?ng ( none-inverting)
  TCCR2A |= (1 << WGM21) | (1 << WGM20);
  // PWM Mode (rang cua)

  28

    TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);
  // prescaler= 32, P_clock=16mhz/1024=15625 hz
  // TOP = 15624*530us=
  OCR2A = 9;
}
void updateA(int goc) {
  int tim = (int)(1880 / 180 * goc + 530);
  int x = (int)(16 * tim);
  OCR1AH = x / 256;  //(PB0) Value=8480
  OCR1AL = x;        //(PB0) Value=8480
}
void updateB(int goc) {
  int tim = (int)(1880 / 180 * goc + 530);
  int x = (int)(16 * tim);
  OCR1BH = x / 256;  //(PB1) Value=8480
  OCR1BL = x;        //(PB1) Value=8480
}
void updateHand(int TF) {
  if (TF == 1) {
    OCR2A = 38;
  } else {
    OCR2A = 8.5;
  }
}
void main() {
  UARTinit();
  setup();
  while (1) {
    if (PIND .5 == 1) {
      putchar('R');
      if (countA < 180)
        countA += 1;
      delay_ms(100);
    } else if (PIND .4 == 1) {
      putchar('L');
      if (countA > 0)
        countA -= 1;
      delay_ms(100);
    }
    if (PIND .6 == 1) {

      29

        putchar('R');
      if (countB < 180)
        countB += 1;
      delay_ms(100);
    } else if (PIND .7 == 1) {
      putchar('L');
      if (countB > 0)
        countB -= 1;
      delay_ms(100);
    }
    if (PIND .3 == 1) {
      countHand = !countHand;
      delay_ms(500);
    }
    updateA(countA);
    updateB(countB);
    updateHand(countHand);
  }
}