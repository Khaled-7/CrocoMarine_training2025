#define F_CPU 16000000UL
#define BAUD 9600
#define UBRR_VALUE ((F_CPU / (16UL * BAUD)) - 1)

void UART_init() {
  UBRR0H = (unsigned char)(UBRR_VALUE >> 8);
  UBRR0L = (unsigned char)UBRR_VALUE;

  UCSR0B = (1 << RXEN0) | (1 << TXEN0);           
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);        
}

void UART_send(unsigned char data) {
  while (!(UCSR0A & (1 << UDRE0)));
  UDR0 = data;
}

unsigned char UART_receive() {
  while (!(UCSR0A & (1 << RXC0)));
  return UDR0;
}

void UART_send_string(const char* str) {
  while (*str) {
    UART_send(*str++);
  }
}

void setup() {
  UART_init();
}

void loop() {
  unsigned char x = UART_receive();
  unsigned char y = x + 1;

  UART_send_string("Received: ");
  UART_send(x);
  UART_send_string("    Sent: ");
  UART_send(y);
  UART_send('\n');  
}