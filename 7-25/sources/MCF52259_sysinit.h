/*
 * File:		m52259evb_sysinit.h
 * Purpose:		Power-on Reset configuration of the MCF52259.
 *
 * Notes:
 *
 */

#ifndef __MCF52259_SYSINIT_H__
#define __MCF52259_SYSINIT_H__

#ifdef __cplusplus
extern "C" {
#endif

#if ENABLE_UART_SUPPORT==1 
/*** 
 * System Bus Clock Info 
 */
#define SYSTEM_CLOCK_KHZ  80000    /* system bus frequency */

/*** 
 * Serial Port Info
 * The baud rate to be : 19200
 * Data bits : 8
 * Parity : None
 * Stop Bits : 1
 * Flow Control : None 
 */
#define TERMINAL_PORT       (0)
#define TERMINAL_BAUD       kBaud19200
#endif  //ENABLE_UART_SUPPORT==1 

/*
 * Ethernet Port Info
 */
#define FEC_PHY0            (0x00)


/********************************************************************/
/* __initialize_hardware Startup code routine
 * 
 * __initialize_hardware is called by the startup code right after reset, 
 * with interrupt disabled and SP pre-set to a valid memory area.
 * Here you should initialize memory and some peripherics;
 * at this point global variables are not initialized yet.
 * The startup code will initialize SP on return of this function.
 */
void __initialize_hardware(void);

/********************************************************************/
/* __initialize_system Startup code routine
 * 
 * __initialize_system is called by the startup code when all languages 
 * specific initialization are done to allow additional hardware setup.
 */ 
void __initialize_system(void);

/********************************************************************/

void pll_init(void);
void scm_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __MCF52259_SYSINIT_H__ */


