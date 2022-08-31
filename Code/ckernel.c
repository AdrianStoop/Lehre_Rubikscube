/*-------------------------------------------------------------;
;   Name:               Eigenes OS in Asm/C/C++     >WinBex<   ; 
;   Autor:              Adrian Stoop                           ;
;   Datei:              ckernel.c                              ;
;   OS_Version:         V.0.01.20                              ;
;   Datum:              11.02.2016                             ;
;-------------------------------------------------------------*/
#include "funktionen.h"
#include "paging.h"

#define F(a,b)  for(a=0;a<b;++a)
#define W(a)    while(a)
#define S(a)    switch(a)
#define C(a)    case(a)
#define D()     default
#define B()     break

int main()
{
    /*
    Da man aus dem asm-Kernel kommt und der Bildschirm noch benutzt war, 
    muss man zuerst den Bildschirm löschen
    */
    k_clear_screen();

    /*
    Lade Titelbild auf den Bildschirm
    */

    settextcolor(RED,       BLACK);         printformat("    #**********************************************************************#   \n");
    settextcolor(GREEN,     BLACK);         printformat("    #  __             __   __              __         ______   __      __  #   \n");
    settextcolor(BLUE,      BLACK);         printformat("    # |  |           |  | |__|            |  |      .'  ____' |  |    |  | #   \n");
    settextcolor(TURKY,     BLACK);         printformat("    # |  |           |  |  __   __        |  |      |  |____   |  |  |  |  #   \n");
    settextcolor(YELLOW,    BLACK);         printformat("    # |  |           |  | |  | |  |_____  |  |___   |   ___.'   |  ''  |   #   \n");
    settextcolor(MAGENTA,   BLACK);         printformat("    #  |  |    .    |  |  |  | |   __   ) |   __ '. |  |        |  --  |   #   \n");
    settextcolor(BROWN,     BLACK);         printformat("    #   |  |_.-^-._|  |   |  | |  |  |  | |  |__| | |  |____   |  |  |  |  #   \n");
    settextcolor(GRAY1,     BLACK);         printformat("    #    |____---____|    |__| |__|  |__| |______.' '._____.' |__|    |__| #   \n");
    settextcolor(DARKRED,   BLACK);         printformat("    #**********************************************************************#   \n");
    settextcolor(GRAY2,     BLACK);         printformat("    # V.0.01.20 # Kernel in Asm und C #  stand: 19.02.2016  # adrian stoop #   \n");
    settextcolor(RED,       BLACK);         printformat("    #**********************************************************************#   \n\n");
    settextcolor(WHITE,     BLACK);

    /*
    Initialisiere GDT, IDT, ISRS, IRQ, ODA, timer und keyboard.
    Genauere Bschreibung in den einzelnen Funktionen
    */

    set_cursor(0,12);
    settextcolor(BROWN,BLACK);printformat("Init status:\n\nGDT----------------\nIDT----------------\nISRS---------------\nIRQ----------------\nODA----------------\nTimer--------------\nKeyboard-----------");
    set_cursor(0,14);

    
    //Global Desktriptor Tabelle
    if(gdt_install() == 1)      {settextcolor(GREEN,    BLACK);printformat("\t\t OK\n");    settextcolor(WHITE, BLACK);}
    else                        {settextcolor(RED,      BLACK);printformat("\t\t ERROR\n"); settextcolor(WHITE, BLACK);}

    //Interrupt descriptor table 
    if(idt_install() == 1)      {settextcolor(GREEN,    BLACK);printformat("\t\t OK\n");    settextcolor(WHITE, BLACK);}
    else                        {settextcolor(RED,      BLACK);printformat("\t\t ERROR\n"); settextcolor(WHITE, BLACK);}

    //Interrupt Service Routine
    if(isrs_install() == 1)     {settextcolor(GREEN,    BLACK);printformat("\t\t OK\n");    settextcolor(WHITE, BLACK);}
    else                        {settextcolor(RED,      BLACK);printformat("\t\t ERROR\n"); settextcolor(WHITE, BLACK);}

    //Interrupt Requests 
    if(irq_install() == 1)      {settextcolor(GREEN,    BLACK);printformat("\t\t OK\n");    settextcolor(WHITE, BLACK);}
    else                        {settextcolor(RED,      BLACK);printformat("\t\t ERROR\n"); settextcolor(WHITE, BLACK);}

    //Operating System Data Area
    if(ODA_install() == 1)      {settextcolor(GREEN,    BLACK);printformat("\t\t OK\n");    settextcolor(WHITE, BLACK);}
    else                        {settextcolor(RED,      BLACK);printformat("\t\t ERROR\n"); settextcolor(WHITE, BLACK);}

    //zeit
    if(timer_install() == 1)    {settextcolor(GREEN,    BLACK);printformat("\t\t OK\n");    settextcolor(WHITE, BLACK);}
    else                        {settextcolor(RED,      BLACK);printformat("\t\t ERROR\n"); settextcolor(WHITE, BLACK);}


    //Keyboard
    if(keyboard_install() == 1) {settextcolor(GREEN,    BLACK);printformat("\t\t OK\n");    settextcolor(WHITE, BLACK);}
    else                        {settextcolor(RED,      BLACK);printformat("\t\t ERROR\n"); settextcolor(WHITE, BLACK);}
    
    

    /*
    Das OS ist jetzt Initialisiert und kann ab jetzt auf Interrupt reagieren:
    sti = SeT Interrupts,  (Interrupt erlauben/zulassen)
    cli = CLear Interrupts (Interrupt nicht erlauben/zulassen)
    */
    sti();

    /*
    Ende Vorbereitung
    */


    /*
    setzte startposizion des Cursor (stadartwerte sind 0,0 und alte position auch 0,0)
    */

    //paging_install();// paging aktivieren
    k_clear_screen();
    set_cursor(0,0);
    save_cursor();




#define F(a,b)  for(a=0;a<b;++a)
#define W(a)    while(a)
#define S(a)    switch(a)
#define C(a)    case(a)
#define D()     default

    int a = 8;

    S(a)
        {
            C(1):{printformat("\t\t 1\n");B();}

            C(2):{printformat("\t\t 2\n");B();}

            C(3):{printformat("\t\t 3\n");B();}

            C(4):{printformat("\t\t 4\n");B();}

            C(5):{printformat("\t\t 5\n");B();}

            D():{printformat("\t\t D\n");B();}
        }
    W(1);














    Rubiks();
    reboot();


    while(1);
    return 0;
};







