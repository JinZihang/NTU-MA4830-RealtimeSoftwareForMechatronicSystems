cc -c functions/helper.c functions/initialization.c functions/input.c functions/logging.c functions/pcie_control.c functions/print.c functions/sound.c functions/timer.c functions/wave_generator_pcie.c
sleep 2
cc -lm helper.o initialization.o input.o logging.o pcie_control.o print.o sound.o timer.o wave_generator_pcie.o -o main main.c -lncurses