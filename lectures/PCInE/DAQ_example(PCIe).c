// 21June2021 : PCIe Version
//******************************************************************************************************
// Performs basic I/O for the Omega PCIe-DAS1602 
//
// Demonstration routine to demonstrate pci hardware programming
// Demonstrated the most basic DIO and ADC and DAC functions
// - excludes FIFO and strobed operations 
// 
// This board is port mapped: info.VendorId=0x1307; info.DeviceId = 0x01;
//
// G.Seet - 20 June 2021
//******************************************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <hw/pci.h>
#include <hw/inout.h>
#include <sys/neutrino.h>
#include <sys/mman.h>
	

#define 	INTERRUPT	iobase[1] + 4		// Badr1 + 4 - PCIe 32-bi 
#define 	ADC_Data		iobase[2] + 0		// Badr2 + 0 - PCIe 16-bit write NULL to start EOC
#define 	DAC0_Data	iobase[2] + 2		// Badr2 + 2 - PCIe 12-bit
#define	DAC1_Data	iobase[2] + 4		// Badr2 + 4 - PCIe 12-bit

#define	MUXCHAN		iobase[3] + 0		// Badr3 + 0 - Mux scan/upper lower
#define 	DIO_Data		iobase[3] + 1		// Badr3 + 1 - PCIe 8-bit xxxx DI3 DI2 DI1 DI0
#define 	ADC_Stat1		iobase[3] + 2 		// Badr3 + 2 - 1 : MSB
#define 	ADC_Stat2		iobase[3] + 3		// Badr3 + 3 - Alt EOC
#define 	CLK_Pace		iobase[3] + 5		// Badr3 + 5 - Set S/W pacer 0x00:XXXX XX0X
#define	ADC_Enable	iobase[3] + 6		// Badr3 + 6 - Burst mode off/Conv Enable:0x01
#define	ADC_Gain		iobase[3] + 7		// Badr3 + 7 - unipolar 5V : 0x01


#define	DEBUG			1
 	
int badr[5];			// PCI 2.2 assigns 6 IO base addresses

int main() {
struct pci_dev_info info;
void *hdl;

uintptr_t iobase[6];
uintptr_t dio_in;
uint16_t adc_in[2];
	
unsigned int i,j, count, read_data;
unsigned short chan;
unsigned int stat,stat1,stat2, stat3;

printf("\fDemonstration Routine for PCI-DAS 1602\n\n");

memset(&info,0,sizeof(info));
if(pci_attach(0)<0) {
  perror("pci_attach");
  exit(EXIT_FAILURE);
  }
			
info.VendorId=0x1307;		// Vendor and Device ID : Same manufacturer
info.DeviceId=0x115;		// info.DeviceId=0x01 (PCI); 0x115 PCIe

if ((hdl=pci_attach_device(0, PCI_SHARE|PCI_INIT_ALL, 0, &info))==0) {
  perror("pci_attach_device");
  exit(EXIT_FAILURE);
  }
  
for(i=0;i<6;i++) {		// Another printf BUG ? - Break printf to two statements
    if(info.BaseAddressSize[i]>0) {
      printf("Aperture %d  Base 0x%x Length %d Type %s\n", i, 
        PCI_IS_MEM(info.CpuBaseAddress[i]) ?  (int)PCI_MEM_ADDR(info.CpuBaseAddress[i]) : 
        (int)PCI_IO_ADDR(info.CpuBaseAddress[i]),info.BaseAddressSize[i], 
        PCI_IS_MEM(info.CpuBaseAddress[i]) ? "MEM" : "IO");
      }
  }  
    														
printf("IRQ %d\n",info.Irq); 		
				// Assign BADRn IO addresses for PCIe-DAS1602			
if(DEBUG) {
printf("\nDAS 1602 Base addresses:\n\n");
for(i=0;i<5;i++) {
  badr[i]=PCI_IO_ADDR(info.CpuBaseAddress[i]);
  if(DEBUG) printf("Badr[%d] : %x\n", i, badr[i]);
  }
 
printf("\nReconfirm Iobase:\n");  		// map I/O base address to user space						

for(i=0;i<5;i++) {									// expect CpuBaseAddress to be the same as iobase for PC
  iobase[i]=mmap_device_io(0x0f,badr[i]);	
  printf("Index %d : Address : %x ", i,badr[i]);
  printf("IOBASE  : %x \n",iobase[i]);
  }										
}
															// Modify thread control privity
if(ThreadCtl(_NTO_TCTL_IO,0)==-1) {
  perror("Thread Control");
  exit(1);
  }																											

printf("\nWaiting for DIO start\n");
getchar();

//********************************************************************************
// Digital Port Functions - There are primary & secondary ports 
//			    A/B/C and 4 bits of primary port
// 
// out8(DIO_CTLREG,0x90);   Port A:In; Port B:Out, Port C(upper|lower):Out|Out	
//
//********************************************************************************																																	

printf("\nDIO Functions\n");													  											

for (i=0;i<16;i++) {					// write out 
	out8(DIO_Data,(i & 0x0f));		// Light up LED lowe 4 bits
	printf("Light up LED %2x\n", (i & 0x0f));
	delay(500);							// Pause 500 ms
	}
	
printf("\nRead Toggle Swtich\n");	
	
for (i=0;i<16;i++) {					// write out 
	read_data= in8(DIO_Data);	// read switch
	printf("Data Read : %2x\n", read_data);
	out8(DIO_Data, read_data);	// Light up LED lower 4 bits
	delay(500);							// Pause 2 seconds
	}
		
printf("\nWaiting for DAC start\n");
getchar();

//******************************************************************************
// D/A Port Functions
// Set to 5V, Unipolar 16 bit offset map. 0V -> 0x0000 mid -> 0x7fff 5V -> 0xffff
//******************************************************************************
	
printf("\nWrite Multiple DAC to Scope\n");
printf("Connect Your Scope\n");
																																					
for (j = 0; j < 0x02ff; j++) {
	for (i = 0x000; i < 0xfff; i++) {
		out16(DAC0_Data, (i & 0x0fff));
		out16(DAC1_Data, ((i >0x800)? 0 : 0x0fff));					
	}
}
printf("Output to Scope Ended\n");

printf("\nWaiting for ADC start\n");
getchar();

//********************************************************************************
// ADC Port Functions
//********************************************************************************
												
												// Initialise Board	
printf("\nReading status of key registers\n");

out8(CLK_Pace,0x00);				// set to SW pacing & verify										
stat1=in32(INTERRUPT); 
stat2=in8(CLK_Pace);
printf("Interrupt Regs : %08x ADC Regs %02x\n",	stat1,stat2);
								
out8(ADC_Enable,0x01);			// set bursting off, conversions on
out8(ADC_Gain,0x01);				// set range : 5V
out8(MUXCHAN,0x10);				// set mux for single channel scan : 1
																
												// Fixed delay OR ULTRA fast conversion ??
for(i=0;i<0x40;i++) {
  out16(ADC_Data,0);					// Initiate Read #0
  delay(1);
  while(in8(ADC_Stat2) >0x80);	   			
  adc_in[0]=in16(ADC_Data);
 
  out16(ADC_Data,0);					// Initiate Read #1
  delay(1);
  while(in8(ADC_Stat2) >0x80);	    			
  adc_in[1]=in16(ADC_Data);
  
  printf("Chan#0 : %04x Chan#1 : %04x\n",adc_in[0],adc_in[1]);
  delay(100);
  }
  
  printf("\nDemo End\n");
}  
