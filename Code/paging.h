#ifndef PAGING_H
#define PAGING_H

#include "funktionen.h"

/************************************************************************/
// page_directory ==> page_table ==> page

typedef struct page
{
    ULONG present    :  1;   // Page present in memory
    ULONG rw         :  1;   // 0: read-only,    1: read/write
    ULONG user       :  1;   // 0: kernel level, 1: user level
    ULONG accessed   :  1;   // Has the page been accessed since last refresh?
    ULONG dirty      :  1;   // Has the page been written to since last refresh?
    ULONG unused     :  7;   // Combination of unused and reserved bits
    ULONG frame_addr : 20;   // Frame address (shifted right 12 bits)
} page_t;

typedef struct page_table
{
    page_t pages[1024]; //PTE
} page_table_t;

typedef struct page_directory
{
    ULONG tablesPhysical[1024]; //PDE
    page_table_t* tables[1024];
    ULONG physicalAddr;
} page_directory_t;
/************************************************************************/

void    paging_install();
void    paging_cli();
void    paging_sti();

page_t* get_page(ULONG address, page_directory_t* dir);
page_t* set_page(ULONG address, page_directory_t* dir);

ULONG   alloc_frame(page_t* page, int is_kernel, int is_writeable);
void    free_frame (page_t *page);

void    analyze_frames_bitset(ULONG sec);
void    analyze_physical_addresses();


#endif
