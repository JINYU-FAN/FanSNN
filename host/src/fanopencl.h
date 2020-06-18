#ifndef FANOPENCL_H
#define FANOPENCL_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "CL/opencl.h"
#include "AOCLUtils/aocl_utils.h"
using namespace aocl_utils;
using namespace std;

struct Context{
    cl_context _context;
    cl_device_id _device;
    cl_platform_id _platform;
};

struct CommandQueue{
    // Need refinement
    cl_command_queue _queue;
};


struct Program{
    cl_program _program;
};





class CL{
    public:
        CL();
        ~CL();
        void create_context();
        void create_command_queue();
        cl_mem create_buffer(cl_mem_flags mem_flags, int size);
        Program create_program(const char* program_name);
        void enqueue_write(cl_mem* buf_ptr, void* host_buf_ptr, int size);
        void enqueue_read(void* host_buf_ptr, cl_mem* buf_ptr, int size);
        cl_kernel create_kernel(const char* kernel_name);
        void execute_kernel(cl_kernel kernel, cl_mem* args[], unsigned size);
    //private:
        cl_int status;
        unsigned int num_devices;
        Context ctx;
        CommandQueue queue;
        vector<cl_mem> buffers;
        vector<cl_kernel> kernels;
        Program program;

        
};

#endif