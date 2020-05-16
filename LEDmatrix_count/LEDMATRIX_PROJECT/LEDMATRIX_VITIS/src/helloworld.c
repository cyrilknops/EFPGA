/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "MATRIX_IPBLOK_DEF.h"
#include "sleep.h"
#include "xscugic.h"
#include "xscutimer.h"

static void timer1_interrupt_handler(void *CallBackRef);

int InterruptCounter= 0;
	/**
	 * The XScuTimer driver instance data. The user is required to allocate a
	 * variable of this type for every timer device in the system.
	 * A pointer to a variable of this type is then passed to the driver API
	 * functions.
	 */
XScuTimer Timer1;
int StateCounter = 0;

int main()
{
	int Status;
		int Timer1_Value;

		/**
		 * This typedef contains configuration information for the device.
		 */

		XScuTimer_Config * Timer1_config;

		XScuGic Gic1;
		XScuGic_Config *Gic1_Config;

		/**
		* Lookup the device configuration based on the unique device ID. The table
		* contains the configuration info for each device in the system.
		**/

		Timer1_config = XScuTimer_LookupConfig(XPAR_PS7_SCUTIMER_0_DEVICE_ID);

		/**
		* CfgInitialize a specific interrupt controller instance/driver
		**/
		Status = XScuTimer_CfgInitialize(&Timer1, Timer1_config, Timer1_config->BaseAddr);
		/** Write to the timer load register. This will also update the
		* timer counter register with the new value. This macro can be used to
		* change the time-out value.
		**/

		//XScuTimer_LoadTimer(&Timer1,1000000000);

		Gic1_Config = XScuGic_LookupConfig(XPAR_PS7_SCUGIC_0_DEVICE_ID);
		Status = XScuGic_CfgInitialize(&Gic1, Gic1_Config, Gic1_Config->CpuBaseAddress);

		Xil_ExceptionInit();

		Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_IRQ_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, &Gic1);

		Status = XScuGic_Connect(&Gic1, XPAR_SCUTIMER_INTR, (Xil_ExceptionHandler)timer1_interrupt_handler, (void *) &Timer1);

		XScuGic_Enable(&Gic1, XPAR_SCUTIMER_INTR);

		XScuTimer_EnableInterrupt(&Timer1);

		Xil_ExceptionEnable();

		// Load the timer with a value that represents one second of real time
		// HINT: The SCU Timer is clocked at half the frequency of the CPU.
		XScuTimer_LoadTimer(&Timer1, XPAR_PS7_CORTEXA9_0_CPU_CLK_FREQ_HZ/2);

		XScuTimer_EnableAutoReload(&Timer1);

		// Start The Timer
		XScuTimer_Start(&Timer1);

	    init_platform();

    while(1){
    	Timer1_Value = XScuTimer_GetCounterValue(&Timer1);
    	if(Timer1_Value <= XPAR_PS7_CORTEXA9_0_CPU_CLK_FREQ_HZ/4)
    	{
    		printf("Timervalue: %d\n\r",Timer1_Value);
    		printf("Timer1 value reached...\n\r");
    		Timer1_Value =-1;

    	}
    	else
    	{
    		// For debugging you can uncomment the following line ;-)
    		//printf("Timervalue: %d\n\r",Timer1_Value);
    	}


		if (StateCounter == 0){ //0
    		MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0000001000001001);
    		usleep_A9(17);
    		MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
    		usleep_A9(7);
    		MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0010100001111001);
    		usleep_A9(17);
    		MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
    		usleep_A9(7);
    		MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0010100101101001);
    		usleep_A9(17);
    		MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
    		usleep_A9(7);
    		MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0000010000001001);
    		usleep_A9(17);
    		MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
    		usleep_A9(7);
		}/*KRRKRKKKKRRKRKRR
                                                                                                                        --7768463515348221*/
		else if (StateCounter==1){ //1
	       	MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0000000100001001);
	        	usleep_A9(17);
	        	MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
	        	usleep_A9(7);
	        	MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001011011);
	        	usleep_A9(17);
	        	MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
	        	usleep_A9(7);
	            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110001001101011);
	            usleep_A9(17);
	        	MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
	        	usleep_A9(7);



    	}

    	else if (StateCounter==2){ //2
    		                                                                                                            /*KRRKRKKKKRRKRKRR
                                                                                                                        --7768463515348221*/
    	MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0000101001001011);
    	usleep_A9(17);
    	MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
    	usleep_A9(7);
    	MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0010100000111001);
    	usleep_A9(17);
    	MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
    	usleep_A9(7);
    	MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0010000101101001);
    	usleep_A9(17);
    	MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
    	usleep_A9(7);
    	MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0010110001001011);
    	usleep_A9(17);
    	MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
    	usleep_A9(7);
        }

        else if (StateCounter==3){ //3
        	                                                                                                            /*KRRKRKKKKRRKRKRR
        	                                                                                                            --7768463515348221*/
        MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0100001001101001);
        usleep_A9(17);
        MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
        usleep_A9(7);
        MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0100000001111001);
        usleep_A9(17);
        MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
        usleep_A9(7);
        MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0100000101101001);
        usleep_A9(17);
        MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
        usleep_A9(7);
        MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0100010000001001);
        usleep_A9(17);
        MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
        usleep_A9(7);

    	}
        else if (StateCounter==4){ //4
        	                                                                                                            /*KRRKRKKKKRRKRKRR
        	                                                                                                            --7768463515348221*/
        MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110001000101011);
        usleep_A9(17);
        MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
        usleep_A9(7);
        MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100000011011);
        usleep_A9(17);
        MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
        usleep_A9(7);
        MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0000000100001001);
        usleep_A9(17);
        MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
        usleep_A9(7);
        MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110110000101011);
        usleep_A9(17);
        MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
        usleep_A9(7);

    	}
        else if (StateCounter==5){ //5
        	                                                                                                                /*KRRKRKKKKRRKRKRR
        	                                                                                                                --7768463515348221*/
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0100001001001001);
            usleep_A9(17);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
            usleep_A9(7);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0010000001111001);
            usleep_A9(17);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
            usleep_A9(7);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0010000101101001);
            usleep_A9(17);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
            usleep_A9(7);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0100110000101001);
            usleep_A9(17);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
            usleep_A9(7);

    	}
        else if (StateCounter==6){ //6
        	                                                                                                                /*KRRKRKKKKRRKRKRR
        	                                                                                                                --7768463515348221*/
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0100001000001011);
            usleep_A9(17);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
            usleep_A9(7);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0010000001111001);
            usleep_A9(17);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
            usleep_A9(7);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0010000101101001);
            usleep_A9(17);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
            usleep_A9(7);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0100110000101001);
            usleep_A9(17);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
            usleep_A9(7);

    	}
        else if (StateCounter==7){ //7
        	                                                                                                                /*KRRKRKKKKRRKRKRR
        	                                                                                                           -     -7768463515348221*/
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110101001101001);
            usleep_A9(17);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
            usleep_A9(7);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0000100000111001);
            usleep_A9(17);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
            usleep_A9(7);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110000101101001);
            usleep_A9(17);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
            usleep_A9(7);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110110001001001);
            usleep_A9(17);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
            usleep_A9(7);


    	}
        else if (StateCounter==8){ //8
        	                                                                                                                /*KRRKRKKKKRRKRKRR
        	                                                                                                                --7768463515348221*/
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0000001000001000);
            usleep_A9(17);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
            usleep_A9(7);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0010000001111010);
            usleep_A9(17);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
            usleep_A9(7);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0010000101101010);
            usleep_A9(17);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
            usleep_A9(7);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0000010000001000);
            usleep_A9(17);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
            usleep_A9(7);

    	}
        else if (StateCounter==9){ //9
        	                                                                                                                /*KRRKRKKKKRRKRKRR
        	                                                                                                                --7768463515348221*/
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0010001001001001);
            usleep_A9(17);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
            usleep_A9(7);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0010000001111001);
            usleep_A9(17);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
            usleep_A9(7);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0010000101101001);
            usleep_A9(17);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110100001101011);
            usleep_A9(7);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0000010000001001);
            usleep_A9(17);
            MATRIX_IPBLOK_DEF_mWriteReg(XPAR_MATRIX_IPBLOK_DEF_0_S00_AXI_BASEADDR,MATRIX_IPBLOK_DEF_S00_AXI_SLV_REG0_OFFSET,0b0110110001101011);
            usleep_A9(7);


    }
    }
    cleanup_platform();
    return 0;
}

static void timer1_interrupt_handler(void *CallBackRef)
{
	XScuTimer *my_Timer_LOCAL = (XScuTimer *) CallBackRef;

	if (XScuTimer_IsExpired(&Timer1))
		{
          if (StateCounter <9){
        	  StateCounter++;
          }
          else{
        	  StateCounter = 0;
          }
			// Clear the interrupt flag in the timer, so we don't service
			// the same interrupt twice.
			XScuTimer_ClearInterruptStatus(my_Timer_LOCAL);
			// Print something to the UART to show that we're in the interrupt handler
			printf("** Interrupt Handler by Timer1!\n\r");
		}
}
