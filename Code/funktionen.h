
#ifndef funktionen_H
#define funktionen_H

#define TRUE		1
#define FALSE		0

#define BLACK           0x0     //0
#define DEEPBLUE        0x1     //1
#define DARKGREEN       0x2     //2
#define TURKY           0x3     //3
#define DARKRED         0x4     //4
#define DARKMAGENTA     0x5     //5
#define BROWN           0x6     //6
#define GRAY1           0x7     //7
#define GRAY2           0x8     //8
#define DARKBLUE        0x9     //9
#define GREEN           0xA     //10
#define BLUE            0xB     //11
#define RED             0xC     //12
#define MAGENTA         0xD     //13
#define YELLOW          0xE     //14
#define WHITE           0xF     //15


typedef unsigned int   size_t;
typedef unsigned int   UINT;
typedef unsigned char  UCHAR;
typedef unsigned short USHORT;
typedef unsigned long  ULONG;
typedef signed int     INT;
typedef signed char    CHAR;
typedef signed short   SHORT;
typedef signed long    LONG;



/*Definiert das Operating system Data Areal*/
#define KQSIZE    20 // grösste des Keybuffers

typedef struct oda
{
    // Hardware Data
    ULONG COM1, COM2, COM3, COM4; // address
    ULONG LPT1, LPT2, LPT3, LPT4; // address
    ULONG Memory_Size;            // Memory size in Byte

    // Key Queue
    UCHAR  KEYQUEUE[KQSIZE];   // circular queue buffer
    UCHAR* pHeadKQ;            // pointer to the head of valid data
    UCHAR* pTailKQ;            // pointer to the tail of valid data
    ULONG  KQ_count_read;      // number of data read from queue buffer
    ULONG  KQ_count_write;     // number of data put into queue buffer
}oda_t;

// operatings system common data area
oda_t ODA;
extern oda_t* pODA;
extern char ODA_install();


/*
Diese Struktur definiert(speicher/laden) den stack, der nach einem ISR ausgelösst wurde.
*/
struct regs
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;
};




//video.c
extern void k_clear_screen();
extern void settextcolor(UCHAR forecolor, UCHAR backcolor);
extern void putch(UCHAR c);
extern void puts(UCHAR* text);
extern void scroll();
extern void k_printf(UCHAR* message, UINT line, UCHAR attribute);
extern void set_cursor(UCHAR x, UCHAR y);
extern void update_cursor();
extern void move_cursor_right();
extern void move_cursor_left();
extern void move_cursor_home();
extern void move_cursor_end();
extern void save_cursor();
extern void restore_cursor();
extern void printformat (char *args, ...);

//timer.c
extern void timer_handler(struct regs* r);
extern void timer_wait (ULONG ticks);
extern void sleepSeconds (ULONG seconds);
extern void sleepMilliSeconds (ULONG seconds);
extern char timer_install();
extern void timer_uninstall();

//keyboard.c
extern char keyboard_install();
extern void keyboard_init();
extern UCHAR FetchAndAnalyzeScancode();
extern UCHAR ScanToASCII();
extern void keyboard_handler(struct regs* r);
extern int k_checkKQ_and_print_char();

//util.c
extern void outportb(UINT port, UINT val);
extern void outportw(const unsigned int port, const unsigned int value);
inline UINT inportb(UINT port);
extern void* k_memset(void* dest, char val, size_t count);
extern USHORT* k_memsetw(USHORT* dest, USHORT val, size_t count);
extern void* k_memcpy(void* dest, const void* src, size_t count);
extern size_t k_strlen(const char* str);
extern void reboot();
extern void clear_keyboard_buffer();
extern void cli();
extern void sti();
extern void k_itoa(int value, char* valuestring);
extern void k_i2hex(UINT val, UCHAR* dest, int len);
extern void float2string(float value, int decimal, char* valuestring);
extern char farpeekl(char sel, void* off);


//gdt.c
extern void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
extern char gdt_install();

//idt.c
extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
extern char idt_install();

//irq.c and isrs.c
extern char isrs_install();
extern char irq_install();
extern void fault_handler(struct regs* r);
extern void irq_install_handler(int irq, void (*handler)(struct regs* r));
extern void irq_uninstall_handler(int irq);
extern void irq_remap(void);
extern void irq_handler(struct regs* r);

//int32.c
// definiert struktur um alle register abzuspeichern vor dem vga modus wechsel
typedef struct __attribute__ ((packed)) {
    unsigned short di, si, bp, sp, bx, dx, cx, ax;
    unsigned short gs, fs, es, ds, eflags;
} regs16_t;
extern void int32(unsigned char intnum, regs16_t *regs);
extern void int32_enalbe_gm_0x12();
extern void int32_enalbe_gm_0x13();
extern void int32_disable_gm();
extern void int32_clear_screen_0x12(char farbe);
extern void int32_clear_screen_0x13(char farbe);
extern void int32_setpixel_0x12(int x, int y, char farbe);//geht noch nicht
extern void int32_setpixel_0x13(int x, int y, char farbe);
extern void int32_line_0x13(int xstart,int ystart,int xend,int yend, char farbe);
extern void int32_rechteck_0x13(int xstart, int ystart, int xend, int yend, char farbe);
extern void int32_rasterCircle_0x13(int x0, int y0, int radius, char farbe);
extern void int32_ellipse_0x13(int xm, int ym, int a, int b, char farbe);
extern void int32_whaitforkey();

extern void int32_test();
extern int int32_apfel_checkC(double reC, double imC);
extern void int32_apfel_paint_0x13();



#endif
