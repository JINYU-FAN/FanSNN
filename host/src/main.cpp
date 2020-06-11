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
        u[i] = rand()%10;
        Iinject[i] = rand()%3;
        spike[i] = rand()%2;
    }
    cout << u[0] << endl;
    cl_mem u_buf = cl.create_buffer(CL_MEM_READ_WRITE, 10 * sizeof(float));
    cl_mem I_buf = cl.create_buffer(CL_MEM_READ_WRITE, 10 * sizeof(float));
    cl_mem Iinject_buf = cl.create_buffer(CL_MEM_READ_WRITE, 10 * sizeof(float));
    cl_mem spike_buf = cl.create_buffer(CL_MEM_READ_WRITE, 10 * sizeof(float));

    cl.enqueue_write(&u_buf, &u, 10*sizeof(float));
    cl.enqueue_write(&I_buf, &I, 10*sizeof(float));
    cl.enqueue_write(&Iinject_buf, &Iinject, 10*sizeof(float));
    cl.enqueue_write(&spike_buf, &spike, 10*sizeof(float));



    // Set kernel arguments.
    unsigned argi = 0;
    clSetKernelArg(kernel, argi++, sizeof(cl_mem), &u_buf);
    clSetKernelArg(kernel, argi++, sizeof(cl_mem), &I_buf);
    clSetKernelArg(kernel, argi++, sizeof(cl_mem), &Iinject_buf);
    clSetKernelArg(kernel, argi++, sizeof(cl_mem), &spike_buf);


    //const size_t global_work_size = 10;

    //clEnqueueNDRangeKernel(cl.queue._queue, kernel, 1, NULL,
     //   &global_work_size, NULL, 0, NULL, NULL);
    clEnqueueTask(cl.queue._queue, kernel, 0, NULL, NULL);

    cl.enqueue_read(&u, &u_buf, 10*sizeof(float));
    cl.enqueue_read(&I, &I_buf, 10*sizeof(float));
    cl.enqueue_read(&Iinject, &Iinject_buf, 10*sizeof(float));
    cl.enqueue_read(&spike, &spike_buf, 10*sizeof(float));

    cout << u[0] << endl;

}
