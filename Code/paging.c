#include "kmalloc.h"
#include "paging.h"
#include <limits.h> // ULONG_MAX

#define PHYSICAL_MEMORY  0x40000000     // 1 GB
#define PAGESIZE         0x00001000     // 0x1000 = 4096 = 4K

page_directory_t* kernel_directory  = 0;
extern ULONG placement_address;

/************* bitset variables and functions **************/

// A bitset of frames - used or free
ULONG   NFRAMES = (PHYSICAL_MEMORY/PAGESIZE);
ULONG*  frames; // pointer to the bitset (functions: set/clear/test)
ULONG   ind, offs;

static void get_Index_and_Offset(ULONG frame_addr)
{
    ULONG frame = frame_addr/PAGESIZE;
    ind         = frame/32;
    offs        = frame%32;
}

static void set_frame(ULONG frame_addr)
{
    get_Index_and_Offset(frame_addr);
    frames[ind] |= (1<<offs);
}

static void clear_frame(ULONG frame_addr)
{
    get_Index_and_Offset(frame_addr);
    frames[ind] &= ~(1<<offs);
}

/*
static ULONG test_frame(ULONG frame_addr)
{
    get_Index_and_Offset(frame_addr);
    return( frames[ind] & (1<<offs) );
}
*/

static ULONG first_frame() // find the first free frame in frames bitset
{
    ULONG index, offset;
    for(index=0; index<(NFRAMES/32); ++index)
    {
        if(frames[index] != ULONG_MAX)
        {
            for(offset=0; offset<32; ++offset)
            {
                if( !(frames[index] & 1<<offset) ) // bit set to zero?
                    return (index*32 + offset);
            }
        }
    }
    return ULONG_MAX; // no free page frames
}

static void bitset_install()
{
    printformat("setup bitset:\n");
    frames = (ULONG*) k_malloc( NFRAMES/32, 0, 0 );
    k_memset( frames, 0, NFRAMES/32 );
}
/***********************************************************/


/********************* paging functions ********************/
void paging_install()
{
    bitset_install();

    printformat("make a page directory:\n");
    ULONG phys;
    kernel_directory = (page_directory_t*) k_malloc( sizeof(page_directory_t), 1, &phys );
    k_memset(kernel_directory, 0, sizeof(page_directory_t));
    kernel_directory->physicalAddr = phys;

    printformat("map phys addr to virt addr from 0x0 to the end of used memory:\n");
    ULONG counter=0, i=0, index=0;
    while( i < (placement_address) )
    {
        page_t* page = set_page(i, kernel_directory);
        index = alloc_frame( page, 0, 0 );
        printformat("index: %x\n", index);
        i+=PAGESIZE; ++counter;
    }

    printformat("\nINFO from paging_install():\n");
    printformat("frames: %x\n", frames);
    printformat("kernel_directory->phys: %x\n", kernel_directory->physicalAddr);
    printformat("placement_address: %x allocated frames: %x\n\n", placement_address, counter);

    // cr3: PDBR (Page Directory Base Register)
    asm volatile( "mov %0, %%cr3" : : "r"(kernel_directory->physicalAddr) );

    // read cr0, set paging bit, write cr0 back
    ULONG cr0;
    asm volatile("mov %%cr0, %0": "=r"(cr0)); // read cr0
    cr0 |= 0x80000000; // set the paging bit in CR0 to enable paging
    asm volatile("mov %0, %%cr0":: "r"(cr0)); // write cr0
}


void paging_cli()
    {
        ULONG cr0;
        asm volatile("mov %%cr0, %0": "=r"(cr0)); // read cr0
        cr0 &= 0x7FFFFFFF; // set the paging bit in CR0 to 0
        asm volatile("mov %0, %%cr0":: "r"(cr0)); // write cr0
    }


void paging_sti()
    {
        ULONG cr0;
        asm volatile("mov %%cr0, %0": "=r"(cr0)); // read cr0
        cr0 |= 0x80000000; // set the paging bit in CR0 to 1
        asm volatile("mov %0, %%cr0":: "r"(cr0)); // write cr0
    }

ULONG alloc_frame(page_t* page, int is_kernel, int is_writeable) // allocate a frame
{
    if( !(page->frame_addr) )
    {
        ULONG index = first_frame(); // search first free page frame
        if( index == ULONG_MAX )
            printformat("message from alloc_frame: no free frames!!!");

        set_frame(index*PAGESIZE);

        page->present    = 1;
        page->rw         = ( is_writeable == 1 ) ? 1 : 0;
        page->user       = ( is_kernel    == 1 ) ? 0 : 1;
        page->frame_addr = index;
        return index;
    }
    return 0;
}

void free_frame(page_t* page) // deallocate a frame
{
    if( page->frame_addr )
    {
        clear_frame(page->frame_addr);
        page->frame_addr = 0;
    }
}

page_t* get_page(ULONG address, page_directory_t* dir)
{
    //ULONG tmp = address;
    address>>=12; // /= PAGESIZE        // index <== address
    ULONG table_index = (address>>10);  // ==> page table containing this address

    if( dir->tables[table_index] )      // table already assigned
        return &dir->tables[table_index]->pages[address%1024];
    else
        return 0;
}

page_t* set_page(ULONG address, page_directory_t* dir)
{
    //ULONG tmp = address;
    address>>=12; // /= PAGESIZE        // index <== address
    ULONG table_index = (address>>10);  // ==> page table containing this address

    //TODO: check it against Intel Manual 3A !!!
    if(
        ( ( (ULONG)(  dir->tablesPhysical[table_index] ) ) & 0x1 )
                  && (dir->tables[table_index])
      )
        putch('!');
    else
    {
        putch('?'); /*printformat(" address: %x\n",tmp)*/;
        ULONG phys;
        dir->tables[table_index] = (page_table_t*) k_malloc( sizeof(page_table_t), 1, &phys );
        k_memset(dir->tables[table_index], 0, PAGESIZE);
        dir->tablesPhysical[table_index] = phys | 0x7; // 111b meaning: PRESENT=1, RW=1, USER=1
    }
    return &dir->tables[table_index]->pages[address%1024];
}

/******************** analysis tools *************************/

void analyze_frames_bitset(ULONG sec)
{
    ULONG index, offset, counter1=0, counter2=0;
    for(index=0; index<(NFRAMES/32); ++index)
    {
        settextcolor(15,0);
        printformat("\n%x  ",index*32*0x1000);
        ++counter1;
        for(offset=0; offset<32; ++offset)
        {
            if( !(frames[index] & 1<<offset) )
            {
                settextcolor(4,0);
                putch('0');
            }
            else
            {
                settextcolor(2,0);
                putch('1');
                ++counter2;
            }
        }
        if(counter1==24)
        {
            counter1=0;
            if(counter2)
                sleepSeconds(sec);
            counter2=0;
        }
    }
}

static ULONG show_physical_address(ULONG virtual_address)
{
    page_t* page = get_page(virtual_address, kernel_directory);
    return( (page->frame_addr)*PAGESIZE + (virtual_address&0xFFF) );
}

void analyze_physical_addresses()
{
   int i,j,k, k_old;
   k = 0;//wegen warning meldung bei compilen
    for(i=0;i<(PHYSICAL_MEMORY/0x18000+1);++i)
    {
        for(j=i*0x18000; j<i*0x18000+0x18000; j+=PAGESIZE)
        {
            if(show_physical_address(j)==0)
            {
                settextcolor(4,0);
                k_old=k; k=1;
            }
            else
            {
                if(show_physical_address(j)-j)
                {
                    settextcolor(3,0);
                    k_old=k; k=2;
                }
                else
                {
                    settextcolor(2,0);
                    k_old=k; k=3;
                }
            }
            if(k!=k_old)
                printformat("%x %x\n", j, show_physical_address(j));
        }
    }
}
