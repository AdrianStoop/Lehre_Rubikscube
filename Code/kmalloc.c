#include "kmalloc.h"

#define PAGESIZE          0x00001000     // 0x1000 = 4096 = 4K 
ULONG placement_address = 0x00200000;

ULONG k_malloc(ULONG size, UCHAR align, ULONG* phys)
{
    if( align == 1 )
    {
        if( !(placement_address == (placement_address & 0xFFFFF000) ) )
        {
            placement_address &= 0xFFFFF000;
            placement_address += PAGESIZE;
        }
    }
    if( phys )
    {
        *phys = placement_address;
    }

    ULONG temp = placement_address;
    placement_address += size;     // new placement_address is increased

    printformat("old: %x sz: %x a: %d new: %x\n", temp, size, align, placement_address);
    sleepSeconds(3);

    return temp;                   // old placement_address is returned
 }



