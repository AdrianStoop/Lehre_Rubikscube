#include "funktionen.h"
/*
das sind funktionsprototypen für alle ausnahme handler. Die ersten 32 Einträge
in der IDT sind reserviert für Service ausnahmen!
*/
extern void isr0();  extern void isr1();  extern void isr2();  extern void isr3();
extern void isr4();  extern void isr5();  extern void isr6();  extern void isr7();
extern void isr8();  extern void isr9();  extern void isr10(); extern void isr11();
extern void isr12(); extern void isr13(); extern void isr14(); extern void isr15();
extern void isr16(); extern void isr17(); extern void isr18(); extern void isr19();
extern void isr20(); extern void isr21(); extern void isr22(); extern void isr23();
extern void isr24(); extern void isr25(); extern void isr26(); extern void isr27();
extern void isr28(); extern void isr29(); extern void isr30(); extern void isr31();

/*
setze die ersten 32 Einträge in der IDT zu den ersten 32 ISRs
Zugriffsrechtbit ist 0x8E:
1000 1110
|    |> 5 bit's für erfodlerliche für das : 80386 Interrupt Gate
|>present bit's = ring 0
*/
char isrs_install()
    {
        idt_set_gate( 0, (unsigned) isr0, 0x08, 0x8E);    idt_set_gate( 1, (unsigned) isr1, 0x08, 0x8E);
        idt_set_gate( 2, (unsigned) isr2, 0x08, 0x8E);    idt_set_gate( 3, (unsigned) isr3, 0x08, 0x8E);
        idt_set_gate( 4, (unsigned) isr4, 0x08, 0x8E);    idt_set_gate( 5, (unsigned) isr5, 0x08, 0x8E);
        idt_set_gate( 6, (unsigned) isr6, 0x08, 0x8E);    idt_set_gate( 7, (unsigned) isr7, 0x08, 0x8E);
        idt_set_gate( 8, (unsigned) isr8, 0x08, 0x8E);    idt_set_gate( 9, (unsigned) isr9, 0x08, 0x8E);
        idt_set_gate(10, (unsigned)isr10, 0x08, 0x8E);    idt_set_gate(11, (unsigned)isr11, 0x08, 0x8E);
        idt_set_gate(12, (unsigned)isr12, 0x08, 0x8E);    idt_set_gate(13, (unsigned)isr13, 0x08, 0x8E);
        idt_set_gate(14, (unsigned)isr14, 0x08, 0x8E);    idt_set_gate(15, (unsigned)isr15, 0x08, 0x8E);
        idt_set_gate(16, (unsigned)isr16, 0x08, 0x8E);    idt_set_gate(17, (unsigned)isr17, 0x08, 0x8E);
        idt_set_gate(18, (unsigned)isr18, 0x08, 0x8E);    idt_set_gate(19, (unsigned)isr19, 0x08, 0x8E);
        idt_set_gate(20, (unsigned)isr20, 0x08, 0x8E);    idt_set_gate(21, (unsigned)isr21, 0x08, 0x8E);
        idt_set_gate(22, (unsigned)isr22, 0x08, 0x8E);    idt_set_gate(23, (unsigned)isr23, 0x08, 0x8E);
        idt_set_gate(24, (unsigned)isr24, 0x08, 0x8E);    idt_set_gate(25, (unsigned)isr25, 0x08, 0x8E);
        idt_set_gate(26, (unsigned)isr26, 0x08, 0x8E);    idt_set_gate(27, (unsigned)isr27, 0x08, 0x8E);
        idt_set_gate(28, (unsigned)isr28, 0x08, 0x8E);    idt_set_gate(29, (unsigned)isr29, 0x08, 0x8E);
        idt_set_gate(30, (unsigned)isr30, 0x08, 0x8E);    idt_set_gate(31, (unsigned)isr31, 0x08, 0x8E);

        return(1);
    }


/*
nachrichten string für die Ausnahmezustzände 0-31: exception_messages[interrupt_nummer]
*/
unsigned char* exception_messages[] =
    {
        "Division By Zero",        "Debug",                         "Non Maskable Interrupt",    "Breakpoint",
        "Into Detected Overflow",  "Out of Bounds",                 "Invalid Opcode",            "No Coprocessor",
        "Double Fault",            "Coprocessor Segment Overrun",   "Bad TSS",                   "Segment Not Present",
        "Stack Fault",             "General Protection Fault",      "Page Fault",                "Unknown Interrupt",
        "Coprocessor Fault",       "Alignment Check",               "Machine Check",             "Reserved",
        "Reserved",                "Reserved",                      "Reserved",                  "Reserved",
        "Reserved",                "Reserved",                      "Reserved",                  "Reserved",
        "Reserved",                "Reserved",                      "Reserved",                  "Reserved"
    };


/*
die Ausnahme behandlung der ISR zeigt auf diese Funktion. Diese sagt wechle ausnahme
benutzt wurde. OSRs deaktivieren Interrups wärend sie gewartet werden.
*/
void fault_handler(struct regs* r)
{
    if (r->int_no < 32)
    {
        if (r->int_no == 14) //Page Fault
        {
            ULONG faulting_address;
            asm volatile("mov %%cr2, %0" : "=r" (faulting_address)); // faulting address => CR2 register

            // The error code gives us details of what happened.
            int present   = !(r->err_code & 0x1); // Page not present
            int rw        =   r->err_code & 0x2;  // Write operation?
            int us        =   r->err_code & 0x4;  // Processor was in user-mode?
            int reserved  =   r->err_code & 0x8;  // Overwritten CPU-reserved bits of page entry?
            int id        =   r->err_code & 0x10; // Caused by an instruction fetch?

            // Output an error message.
                          printformat("Page Fault (");
            if (present)  printformat("page not present");
            if (rw)       printformat("read-only - write operation");
            if (us)       printformat("user-mode");
            if (reserved) printformat("overwritten CPU-reserved bits of page entry");
            if (id)       printformat("caused by an instruction fetch");
                          printformat(") at %x - EIP: %x\n", faulting_address, r->eip);
        }
        printformat("%s >>> Exception. System Halted! <<<", exception_messages[r->int_no]);
        for (;;);
    }
}
