#include "keyboard.h"
#include "funktionen.h"
/*
Variablen für:
ShiftKeyDown = 0 = shift nicht gedrückt, 1 = shift gedrückt
KeyPressed   = 0 = taste nicht gedrückt, 1 = Taste gedrückt
Scan         = 0 = keien Scancode, 0< = scancode von der Tastatur
*/
UCHAR ShiftKeyDown = 0; 
UCHAR KeyPressed   = 0; 
UCHAR scan         = 0; 


/* warte bis der Buffer lehr ist */
void keyboard_init()
  {
      while( inportb(0x64)&1 )
          inportb(0x60);
  };

/*
scannt die tastatur und setzt die oben genannten variablen.
*/
UCHAR FetchAndAnalyzeScancode()
{
	if( inportb(0x64)&1 )
	    scan = inportb(0x60);   // 0x60: nim den scancode der Tastatur

    // ACK: toggle bit 7 an port 0x61
    UCHAR port_value = inportb(0x61);
    outportb(0x61,port_value |  0x80); // 0->1
    outportb(0x61,port_value &~ 0x80); // 1->0

	if( scan & 0x80 ) // Taste losgelassen? Checke bit 7 (10000000b = 0x80) vom scancode für das
	{
        KeyPressed = 0;
        scan &= 0x7F; // taste wurde losgelassen, verANDe nur die 7 tieferen bits: 01111111b = 0x7F
        if( scan == KRLEFT_SHIFT || scan == KRRIGHT_SHIFT ) // taste wurde losgelassen, shift auch?
        {
            ShiftKeyDown = 0;	// ja, benutzte nonshift
        }
	}
	else // taste wurde gedrückt
	{
	    KeyPressed = 1;
		if( scan == KRLEFT_SHIFT || scan == KRRIGHT_SHIFT ) // wurde shift gedrükt?
		{
		    ShiftKeyDown = 1; // ja, benutte shiftscode
		}
	}
	return scan;
}

/*
nimm den scancode und gib den ascii code als rückgabewert
zurück. Tastenbelegung ist in keyboard.h
*/
UCHAR ScanToASCII() // Scancode --> ASCII
{
	UCHAR retchar;	                   // speichert das Zeichen aus der Ascii tabelle
	scan = FetchAndAnalyzeScancode();  // scannt den scancode und schauft auf die shifttaste

	if( ShiftKeyDown )                  // ist shift gdrückt?
	    retchar = asciiShift[scan];	   // Shift Codes
	else
		retchar = asciiNonShift[scan]; //  Non-Shift Codes

	if( ( !(scan == KRLEFT_SHIFT || scan == KRRIGHT_SHIFT) ) && ( KeyPressed == 1 ) ) //filtert Shift Key und Key Release
	    return retchar; // gibt ASCII version zurück
	else
	    return 0;
}

/*
wenn ein Interrupt ausgelösst wird vom keyboard, wird diese funktion aufgerüfen, egal was das OS macht!
*/
void keyboard_handler(struct regs* r)
{
   UCHAR KEY = ScanToASCII();//hollle info aus der tastatur
   if(KEY)//wenn key != 0,
   {
       *(pODA->pTailKQ) = KEY;//dan wird er in den KQ geladen(Key Queue)hinterste stelle
       ++(pODA->KQ_count_write);//schreibzähler wird erhöht

       if(pODA->pTailKQ > pODA->KEYQUEUE)//Solange der Wert des Tail-Zeigers größer ist als der Anfang der KQ (pODA->KEYQUEUE),
       {
           --pODA->pTailKQ;// wird der Tail-Zeiger erniedrigt.
       }
       if(pODA->pTailKQ == pODA->KEYQUEUE)//Sobald allerdings der Anfang erreicht ist, setzt der Zirkularmechanismus ein.
       {
           pODA->pTailKQ = (pODA->KEYQUEUE)+KQSIZE-1;//Der Tail-Zeiger wird auf das hintere Ende der KQ gesetzt. Damit ist der Kreis geschlossen.
       }
   }
}

int k_checkKQ_and_print_char()
{
   if(pODA->KQ_count_write > pODA->KQ_count_read)//Solange mehr in die KQ hinein geschrieben als heraus gelesen wurde
   {
       UCHAR KEY = *(pODA->pHeadKQ);// lesen wir weiter.
       ++(pODA->KQ_count_read);//Der Lesezeiger zählt mit, damit wir keine "ungültigen" Zeichen heraus holen. 

       if(pODA->pHeadKQ > pODA->KEYQUEUE)//Solange der Kopf-Zeiger oberhalb des Anfangs der KQ liegt, 
       {
           --pODA->pHeadKQ;//bewegen wir uns auf diesen zu
       }
       if(pODA->pHeadKQ == pODA->KEYQUEUE)//Sobald wir ihn erreichen,
       {
           pODA->pHeadKQ = (pODA->KEYQUEUE)+ KQSIZE-1;//erfolgt ein Sprung ans andere Ende, genau wie beim Schreiben.
       }

       restore_cursor();
       switch(KEY)
       {
           case KINS:
               break;
           case KDEL:
               move_cursor_right();
               putch('\b'); //BACKSPACE
               break;
           case KHOME:
               move_cursor_home();
               break;
           case KEND:
               move_cursor_end();
               break;
           case KPGUP:
               break;
           case KPGDN:
               break;
           case KLEFT:
               move_cursor_left();
               break;
           case KUP:
               break;
           case KDOWN:
               break;
           case KRIGHT:
               move_cursor_right();
               break;
           default:
               printformat("%c",KEY); // the ASCII character
               break;
       }
       save_cursor();
       return 1;
   }
   return 0;
}

/*
"installiert" den keyboard handler auf IRQ 1
*/
char keyboard_install()
{
    irq_install_handler(1, keyboard_handler);
    keyboard_init();
    return(1);
}




