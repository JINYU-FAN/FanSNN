/*
 This kernel runs the updates of LIF neuron.
 The equations comes from 
*/

// The constants used in LIF model.
__constant double Rm = 1e6;
__constant double Cm = 3e-8;
__constant double Vrest = -0.06;
__constant double Vthresh = -0.045;
__constant double Vreset = -0.06;
//__constant double Vinit = -0.06;
__constant double Trefract = 3e-3;
//__constant double Inoise = 0.0; //1e-5;
__constant double Iinject = 5e-7;
__constant double dt = 0.001; // dt is not defined in the original version



//(vector<float>& u, vector<float>& I, vector<float>& Iinject, vector<bool>& spike)
//__attribute__((num_compute_units(100)))
//__attribute__((reqd_work_group_size(1,1,1)))
__kernel void easy_neuron_update(__global float *u, __global float *I, __global float *Iinject, __global bool *spike)
{

    // get index of the work item
    int i = get_global_id(0);
    // The code below is a very intimate version and required refinement.
    u[i] += I[i];
    if(u[i] >= 10){ // 10 is the firing threshold
        spike[i] = 1;
        u[i] = 0;
    }
    else{
        spike[i] = 0;
    }
    I[i] = Iinject[i]; // Reset the current to only inject current
}



