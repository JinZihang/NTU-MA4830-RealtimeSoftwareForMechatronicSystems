//******************************************************************************
// Wave Generator Functions
// GenerateWave: General generate wave functions
// GenerateSineWave: Generate Sine wave
// GenerateRectangleWave: Generate Rectangle wave
// GenerateTriangleWave: Generate Triangle wave
// GenerateSawtoothWave: Generate Sawtooth wave
//******************************************************************************

#ifndef METRONOME_WAVE_GENERATOR_PCIE_H
#define METRONOME_WAVE_GENERATOR_PCIE_H

// Define registers for PCIe-DAS1602
#define    INTERRUPT    iobase[1] + 4       // Badr1 + 4 - PCIe 32-bit
#define    ADC_Data     iobase[2] + 0       // Badr2 + 0 - PCIe 16-bit w->srt
#define    DAC0_Data    iobase[2] + 2       // Badr2 + 2 - PCIe 12-bit
#define    DAC1_Data    iobase[2] + 4       // Badr2 + 4 - PCIe 12-bit
#define    MUXCHAN      iobase[3] + 0       // Badr3 + 0 - Mux scan/upper lower
#define    DIO_Data     iobase[3] + 1       // Badr3 + 1 - 8bit DI3 DI2 DI1 DI0
#define    ADC_Stat1    iobase[3] + 2       // Badr3 + 2 - 1 : MSB
#define    ADC_Stat2    iobase[3] + 3       // Badr3 + 3 - Alt EOC
#define    CLK_Pace     iobase[3] + 5       // Badr3 + 5 - S/W Pacer : XXXX XX0X
#define    ADC_Enable   iobase[3] + 6       // Badr3 + 6 - Brst_off Conv_EN:0x01
#define    ADC_Gain     iobase[3] + 7       // Badr3 + 7 - unipolar 5V : 0x01

void GenerateSineWave();

void GenerateRectangleWave();

void GenerateTriangleWave();

void GenerateSawtoothWave();

void *GenerateWave();

#endif
