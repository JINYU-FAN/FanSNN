#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "fpga.h"

int main(){
    init_opencl();
    create_program("neuron");
    create_command_queue();
    create_kernel("easy_neuron_update");
    cleanup();
}
