#ifndef METRONOME_WAVE_GENERATOR_PCIE_H
#define METRONOME_WAVE_GENERATOR_PCIE_H

void GenerateSineWave(double amplitude, double frequency);

void GenerateRectangleWave();

void GenerateSawtoothWave();

void GenerateTriangleWave();

void GenerateWave(struct Wave *wave);

#endif
