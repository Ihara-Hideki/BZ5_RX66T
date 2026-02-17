
#include    "custom.h"
/***
**  ID     = SBI_Handler
**  name   = ÇrÇaÇhäÑÇËçûÇ›
**  func   = ÇrÇaÇhäÑÇËçûÇ›ÉÇÉWÉÖÅ[Éã
**  called = void SBI_Handler(void)
**  io     = none
**  return = none
**  using  =                                   :     /          : 
**  common =                                   :        :   :
**  note   = 
**  date   = 2005/02/03 by íJêÏÇ‹Ç≥Ç‚
***/
void SBI_Handler(void)
{
#if false
	static long		j = 0;

	++j;
	if(j>2000){
		j=0;
	}
	else if(j>1500){
		P9DATA	= 0x01;
	}
	else if(j>1000){
		P9DATA	= 0x02;
	}
	else if(j>500){
		P9DATA	= 0x04;
	}
	else{
		P9DATA	= 0x07;
	}

SBICR = 0x01;
SBICR = 0x00;
#else
	long	i = 0;
	ubool	flg = false;
	while(true){
		if(++i > 1000000){
			if(flg){
				P9DATA	= 0x07;
				flg		= false;
			}
			else{
				P9DATA	= 0x00;
				flg		= true;
			}
			i=0;
		}
	}

#endif
}

/***
**  ID     = DummyHandler
**  name   = É_É~Å[äÑÇËçûÇ›
**  func   = É_É~Å[äÑÇËçûÇ›ÉÇÉWÉÖÅ[Éã
**  called = void DummyHandler(void)
**  io     = none
**  return = none
**  using  =                                   :     /          : 
**  common =                                   :        :   :
**  note   = 
**  date   = 2005/02/03 by íJêÏÇ‹Ç≥Ç‚
***/
void DummyHandler(void)
{
}
//------------------------
//  End of Interrupt.c
//------------------------
