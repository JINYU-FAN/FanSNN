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


cl_mem CL::create_buffer(cl_mem_flags mem_flags, int size, void* host_buf_ptr){
    cl_mem buffer = clCreateBuffer(ctx._context, mem_flags, 
        size, host_buf_ptr, &status);
    checkError(status, "Failed to create buffer for input u");    
    //buffers.push_back(buffer);
    return buffer;
}





void CL::enqueue_write(cl_mem* buf_ptr, void* host_buf_ptr){
    //cl_event write_event;
    printf("Write\n");
    status = clEnqueueWriteBuffer(queue._queue, *buf_ptr, CL_TRUE,
        0, 10*sizeof(float), host_buf_ptr, 0, NULL, NULL);
    checkError(status, "Failed to write buffer");    
    //clReleaseEvent(write_event);    
}

void CL::enqueue_read(void* host_buf_ptr, cl_mem* buf_ptr){
    //cl_event read_event;
    printf("Read\n");
    status = clEnqueueReadBuffer(queue._queue, *buf_ptr, CL_TRUE,
        0, sizeof(float)*10, host_buf_ptr, 0, NULL, NULL);
    checkError(status, "Failed to read buffer");
}



