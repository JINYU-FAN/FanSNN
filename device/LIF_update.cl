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




__kernel void LIF_update(__global double *u)
{
    // get index of the work item
    int index = get_global_id(0);
    // The code below is a very intimate version and required refinement.
    __local double du;
    // Synaptic current is not considered

    //printf("%f\n", u[index]);
    du = ((Vrest - u[index])/Rm + Iinject)*dt/Cm;
    u[index] += du;
    if (u[index] > Vthresh){
        //printf("SPIKE\n");
        u[index] = Vreset;
    }

}

