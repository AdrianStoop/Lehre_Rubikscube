#include "funktionen.h"

oda_t* pODA = &ODA;

char ODA_install()
	{
    	int i;
    	for(i=0;i<KQSIZE;++i)

    		{pODA->KEYQUEUE[i]=0;} // queue buffer ausrichten (20)
    		
                
	    pODA->pHeadKQ = pODA->KEYQUEUE;  // pointer to the head of valid data
	    pODA->pTailKQ = pODA->KEYQUEUE;  // pointer to the tail of valid data
	    pODA->KQ_count_read  = 0;        // number of data read from queue buffer
	    pODA->KQ_count_write = 0;        // number of data put into queue buffer

	    return(1);
	}
