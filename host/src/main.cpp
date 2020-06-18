#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "fanopencl.h"

void cleanup(){}
int main() {
    CL cl;
    cl.create_context();
    cl.create_command_queue();
    Program program = cl.create_program("neuron");
    cl_kernel kernel = cl.create_kernel("easy_neuron_update");


    float u[10];
    float I[10];
    float Iinject[10];
    float spike[10];
    for (int i=0; i < 10; i++){
        Iinject[i] = i;
    }

    cl_mem u_buf = cl.create_buffer(CL_MEM_READ_WRITE, 10 * sizeof(float));
    cl_mem I_buf = cl.create_buffer(CL_MEM_READ_WRITE, 10 * sizeof(float));
    cl_mem Iinject_buf = cl.create_buffer(CL_MEM_READ_WRITE, 10 * sizeof(float));
    cl_mem spike_buf = cl.create_buffer(CL_MEM_READ_WRITE, 10 * sizeof(float));

    cl.enqueue_write(&u_buf, &u, 10 * sizeof(float));
    cl.enqueue_write(&I_buf, &I, 10 * sizeof(float));
    cl.enqueue_write(&Iinject_buf, &Iinject, 10 * sizeof(float));
    cl.enqueue_write(&spike_buf, &spike, 10 * sizeof(float));

    cl_mem* a[] = {&u_buf, &I_buf, &Iinject_buf, &spike_buf};
    cl.execute_kernel(kernel, a, 4);


    cl.equeue_read()



  

}
