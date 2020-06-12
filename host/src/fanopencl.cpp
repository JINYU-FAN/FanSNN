#include "fanopencl.h"
#include <boost/assert.hpp>
using namespace boost;
CL::CL(){
    printf("Initializing OpenCL\n");
    if(!setCwdToExeDir()) {
        assert(false);
    }
    // Get the OpenCL platform.
    ctx._platform = findPlatform("Intel(R) FPGA SDK for OpenCL(TM)");
    if(ctx._platform == NULL) {
        printf("ERROR: Unable to find Intel(R) FPGA OpenCL platform.\n");
        assert(false);
    }
    // Query the available OpenCL device.
    
    ctx._device = getDevices(ctx._platform, CL_DEVICE_TYPE_ALL, &num_devices)[0];
    printf("Platform: %s\n", getPlatformName(ctx._platform).c_str());
    printf("Using %d device(s)\n", num_devices);
    printf("  %s\n", getDeviceName(ctx._device).c_str());
}


CL::~CL(){
    for(int i=0; i < buffers.size(); i++){
        if(buffers[i]){
            clReleaseMemObject(buffers[i]);
        }
    }
    printf("The buffers are released.\n");

    for(int i=0; i < kernels.size(); i++){
        if(kernels[i]){
            clReleaseKernel(kernels[i]);
        }
    }
    printf("The kernels are released.\n");
    
    if(program._program) {
        clReleaseProgram(program._program);
    }
    printf("The program is released.\n");


    if(queue._queue) {
        clReleaseCommandQueue(queue._queue);
    }
    printf("The command queue is released.\n");

    if(ctx._context) {
        clReleaseContext(ctx._context);
        printf("The context is released.\n");
    }  

}


void CL::create_context(){
    // Create the context.
    ctx._context = clCreateContext(NULL, num_devices, &ctx._device, &oclContextCallback, NULL, &status);
    checkError(status, "Failed to create context");
}


void CL::create_command_queue(){
    queue._queue = clCreateCommandQueue(ctx._context, ctx._device, CL_QUEUE_PROFILING_ENABLE, &status);
    checkError(status, "Failed to create command queue");      

}


cl_mem CL::create_buffer(cl_mem_flags mem_flags, int size){
    cl_mem buffer = clCreateBuffer(ctx._context, mem_flags, 
        size, NULL, &status);
    checkError(status, "Failed to create buffer for input u");    
    buffers.push_back(buffer);
    return buffer;
}





void CL::enqueue_write(cl_mem* buf_ptr, void* host_buf_ptr, int size){
    printf("Write\n");
    cl_event write_event;
    status = clEnqueueWriteBuffer(queue._queue, *buf_ptr, CL_TRUE,
        0, size, host_buf_ptr, 0, NULL, &write_event);
    checkError(status, "Failed to write buffer"); 
    clWaitForEvents(1, &write_event);
    clReleaseEvent(write_event);    
}

void CL::enqueue_read(void* host_buf_ptr, cl_mem* buf_ptr, int size){
    printf("Read\n");
    cl_event read_event;
    status = clEnqueueReadBuffer(queue._queue, *buf_ptr, CL_TRUE,
        0, size, host_buf_ptr, 0, NULL, &read_event);
    checkError(status, "Failed to read buffer");
    clWaitForEvents(1, &read_event);
    clReleaseEvent(read_event);
}



Program CL::create_program(const char* program_name){
      // Create the program for all device. Use the first device as the
  // representative device (assuming all device are of the same type).
  std::string binary_file = getBoardBinaryFile(program_name, ctx._device);
  printf("Using AOCX: %s\n", binary_file.c_str());
  program._program = createProgramFromBinary(ctx._context, binary_file.c_str(), &(ctx._device), 1);

  // Build the program that was just created.
  status = clBuildProgram(program._program, 0, NULL, "", NULL, NULL);
  checkError(status, "Failed to build program");
  return program;
}

cl_kernel CL::create_kernel(const char* kernel_name){
    cl_kernel kernel = clCreateKernel(program._program, kernel_name, &status);
    checkError(status, "Failed to create kernel");
    kernels.push_back(kernel);
    return kernel;
}