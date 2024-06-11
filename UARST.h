#include <mega328p.h>
#include <delay.h>
//BAUD = 115200
#define BAUDRATE 9600
#define fosc 16000000
unsigned int n;
unsigned char str[];
//n = fOSC/(16*BAUD) – 1
void putchar(unsigned char data) {
  while (!(UCSR0A & 0b00100000))
    ;  //Ch? thanh ghi d? li?u Empty
  UDR0 = data;
}

void putString(char *str) {
  while (*str) {
    putchar(*str);  //Gia tri
    if (*str == '\n')
      ;
    str++;  //Dia chi
  }
  putchar('\r');
}
void put_int(unsigned int value) {
  unsigned char buf[8];

  30

    int index = 0,
        i, j;
  j = value;
  do {
    buf[index] = j % 10 + 48;
    j = j / 10;
    index += 1;
  } while (j);
  for (i = index; i > 0; i--) {
    putchar(buf[i - 1]);
  }
}
interrupt[USART_RXC] void usart_rx_isr(void) {
  *str = UDR0;
}
void UARTinit() {
  n = fosc / (16 * BAUDRATE) - 1;
  UBRR0H = n >> 8;
  UBRR0L = n;
  UCSR0C = 0b00000110;
  UCSR0B = 0b10011000;
#asm("sei");
}