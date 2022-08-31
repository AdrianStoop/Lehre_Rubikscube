#include "funktionen.h"

ULONG const FREQ  = 100; // 100 "ticks" pro sekunde
ULONG timer_ticks =   0;
ULONG eticks;


void timer_handler(struct regs* r)
  {
    /*Diese Funktion wird durch einen Interrupt aufgeruffen(ca 55mal in der sekunde)*/
    ++timer_ticks;
    if (eticks)
        --eticks;
  }
void timer_wait (ULONG ticks)
  {
    /*Diese Funktion warten eine gewisse anzahl an "ticks"*/
    timer_uninstall();
    eticks = ticks;
    timer_install();
    while (eticks)// warte bis eticks = 0 ist, updatet cursor immer
    {update_cursor();}
  }
void sleepSeconds (ULONG seconds)
  {
    /*Diese Funktion wartet(delay) gewisse Sekunden*/
    timer_wait(FREQ * seconds);
  }
void sleepMilliSeconds (ULONG ms)
  {
    /*Diese Funktion wartet(delay) gewisse Millisekunden*/
    timer_wait(FREQ * ms/1000UL);
  }
static void systemTimer_setFrequency( ULONG freq )
  {
    /*Diese Funktion setzt die Interne Frequenz um*/
   ULONG divisor = 1193180 / freq; //divisor mus 2Byte lang sein

   // Sende das Befehls Byte
   outportb(0x43, 0x36);

   // Sende den Divisor
   outportb(0x40, (UCHAR)(  divisor     & 0xFF )); // low  byte
   outportb(0x40, (UCHAR)( (divisor>>8) & 0xFF )); // high byte
  }
char timer_install()
  {
    /*setzt timer_handler auf IRQ0*/
    irq_install_handler(0, timer_handler);
    systemTimer_setFrequency( FREQ ); // FREQ in Hz
    return(1);
  }
void timer_uninstall()
  {
    /* lösche timer_handler auf IRQ0 */
    irq_uninstall_handler(0);
  }
