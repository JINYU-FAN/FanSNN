#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "CL/opencl.h"
#include "AOCLUtils/aocl_utils.h"
#include "fpga.h"
using namespace aocl_utils;

cl_platform_id platform = NULL;
unsigned num_devices = 0;
scoped_array<cl_device_id> device;
cl_context context = NULL;
scoped_array<cl_command_queue> queue;
scoped_array<cl_kernel> kernel;
//scoped_array<unsigned> n_per_device;
cl_program program = NULL;
cl_int status;



bool init_opencl(){
    

    printf("Initializing OpenCL\n");

    if(!setCwdToExeDir()) {
        return false;
    }

    // Get the OpenCL platform.
    platform = findPlatform("Intel(R) FPGA SDK for OpenCL(TM)");
    if(platform == NULL) {
        printf("ERROR: Unable to find Intel(R) FPGA OpenCL platform.\n");
        return false;
    }

    // Query the available OpenCL device.
    device.reset(getDevices(platform, CL_DEVICE_TYPE_ALL, &num_devices));
    printf("Platform: %s\n", getPlatformName(platform).c_str());
    printf("Using %d device(s)\n", num_devices);
    for(unsigned i = 0; i < num_devices; ++i) {
        printf("  %s\n", getDeviceName(device[i]).c_str());
    }

    // Create the context.
    context = clCreateContext(NULL, num_devices, device, &oclContextCallback, NULL, &status);
    checkError(status, "Failed to create context");

}


void cleanup(){

    for(unsigned i = 0; i < num_devices; ++i) {
        if(kernel && kernel[i]) {
        clReleaseKernel(kernel[i]);
        }
    }
    printf("The kernels are released.\n");
    for(unsigned i = 0; i < num_devices; ++i) {
        if(queue && queue[i]) {
            clReleaseCommandQueue(queue[i]);
        }
    }
    printf("The command queues are released.\n");


    if(program) {
        clReleaseProgram(program);
        printf("The program is released.\n");
    }

    if(context) {
        clReleaseContext(context);
        printf("The context is released.\n");
    }    
}


void create_program(const char* program_name){
    // Create the program for all device. Use the first device as the
    // representative device (assuming all device are of the same type).
    std::string binary_file = getBoardBinaryFile(program_name, device[0]);
    printf("Using AOCX: %s\n", binary_file.c_str());
    program = createProgramFromBinary(context, binary_file.c_str(), device, num_devices);

    // Build the program that was just created.
    status = clBuildProgram(program, 0, NULL, "", NULL, NULL);
    checkError(status, "Failed to build program");
}


void create_command_queue(){
    queue.reset(num_devices);
    for(unsigned i = 0; i < num_devices; ++i) {
        // Command queue.
        queue[i] = clCreateCommandQueue(context, device[i], CL_QUEUE_PROFILING_ENABLE, &status);
        checkError(status, "Failed to create command queue");
    }
}


void create_kernel(const char* kernel_name){
    kernel.reset(num_devices);
    
    for(unsigned i = 0; i < num_devices; ++i) {
        // Kernel.
        kernel[i] = clCreateKernel(program, kernel_name, &status);
        checkError(status, "Failed to create kernel");
    }
}








