#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "fanopencl.h"

void cleanup(){}
int main(){
    CL cl;
    cl.create_context();
    cl.create_command_queue();
    Program program = cl.create_program("neuron");
    cl_kernel kernel = cl.create_kernel("easy_neuron_update");

    vector<float> u(10);
    vector<float> I(10);
    vector<float> Iinject(10);
    vector<float> spike(10);
    for (int i=0; i<10;i++){
        u[i] = 5;
        Iinject[i] = 3;
        spike[i] = 0;
    }







    cl_int status;
    cl_mem u_buf = clCreateBuffer(cl.ctx._context, CL_MEM_READ_WRITE, 
        10 * sizeof(float), NULL, &status);
    checkError(status, "Failed to create buffer for input u");
    cl_mem I_buf = clCreateBuffer(cl.ctx._context, CL_MEM_READ_WRITE, 
        10 * sizeof(float), NULL, &status);
    checkError(status, "Failed to create buffer for input I");
    cl_mem Iinject_buf = clCreateBuffer(cl.ctx._context, CL_MEM_READ_ONLY, 
        10 * sizeof(float), NULL, &status);
    checkError(status, "Failed to create buffer for input Iinject");
    cl_mem spike_buf = clCreateBuffer(cl.ctx._context, CL_MEM_READ_WRITE, 
        10 * sizeof(float), NULL, &status);
    checkError(status, "Failed to create buffer for input spike");
    
    
    cl_event write_event[4];
    status = clEnqueueWriteBuffer(cl.queue._queue, u_buf, CL_FALSE,
        0, 10 * sizeof(float), &u, 0, NULL, &write_event[0]);
    checkError(status, "Failed to transfer input u");
    status = clEnqueueWriteBuffer(cl.queue._queue, I_buf, CL_FALSE,
        0, 10 * sizeof(float), &I, 0, NULL, &write_event[1]);
    checkError(status, "Failed to transfer input u");
    status = clEnqueueWriteBuffer(cl.queue._queue, Iinject_buf, CL_FALSE,
        0, 10 * sizeof(float), &Iinject, 0, NULL, &write_event[2]);
    checkError(status, "Failed to transfer input u");
    status = clEnqueueWriteBuffer(cl.queue._queue, spike_buf, CL_FALSE,
        0, 10 * sizeof(float), &spike, 0, NULL, &write_event[3]);
    checkError(status, "Failed to transfer input u");  
    clWaitForEvents(4, write_event);
    

    unsigned argi = 0;
    status = clSetKernelArg(kernel, argi++, sizeof(cl_mem), &u_buf);
    checkError(status, "Failed to set argument %d", argi - 1);
    status = clSetKernelArg(kernel, argi++, sizeof(cl_mem), &I_buf);
    checkError(status, "Failed to set argument %d", argi - 1);
    status = clSetKernelArg(kernel, argi++, sizeof(cl_mem), &Iinject_buf);
    checkError(status, "Failed to set argument %d", argi - 1);
    status = clSetKernelArg(kernel, argi++, sizeof(cl_mem), &spike_buf);
    checkError(status, "Failed to set argument %d", argi - 1);


    const size_t global_work_size = 10;
    printf("Launching for device %d (%zd elements)\n", 1, global_work_size);

    cl_event kernel_event;
    status = clEnqueueNDRangeKernel(cl.queue._queue, kernel, 1, NULL,
        &global_work_size, NULL, 0, NULL, &kernel_event);
    clWaitForEvents(1, &kernel_event);
}
