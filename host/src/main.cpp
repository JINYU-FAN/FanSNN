#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "fanopencl.h"

void cleanup(){}
int main(){
    CL cl;
    cl.create_context();
    cl.create_command_queue();
    vector<float> u(10);
    vector<float> v(10);
    for (int i=0; i < u.size(); i++){
        u[i] = i;
    }
    cout << u[5] << endl;
    cl_mem u_buf = cl.create_buffer(CL_MEM_READ_WRITE|CL_MEM_COPY_HOST_PTR, 10*sizeof(float), &u);
    cl.enqueue_write(&u_buf, &u);
    u[5] = 20.0;
    cout << u[5] << endl;
    cl.enqueue_read(&u, &u_buf);
    cout << u[5] << endl;
    
    


}
