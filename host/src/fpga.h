#ifndef FPGA_H
#define FPGA_H


bool init_opencl();
void cleanup();
void create_program(const char* program_name);
void create_command_queue();
void create_kernel(const char* kernel_name);

#endif