#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include "calculation.h"
#include "neuron.h"
#include "environment.h"
using namespace std;

namespace easy{

void neuron_update(vector<float>& u, vector<float>& I, vector<float>& Iinject, vector<bool>& spike){
    /*
    This model is a linear model.
    u+=I
    if u > threshold:
        spike
        u = 0
    */
    for (unsigned __int128 i = 0; i < u.size(); i++){
        cout << I[i] << endl;
        u[i] += I[i];
        if(u[i] >= 10){ // 10 is the firing threshold
            spike[i] = 1;
            u[i] = 0;
        }
        else{
            spike[i] = 0;
        }
        I[i] = Iinject[i]; // Reset the current to only inject current
        //printf("inject current\n");
    }
}

void synapse_update(Neuron& layer_pre, Neuron& layer_post, vector<unsigned __int128>& pre_ID, vector<unsigned __int128>& post_ID, vector<float>& weights){   
    for(unsigned __int128 s=0; s < weights.size(); s++){
        //printf("syna current\n");
        layer_post.I[pre_ID[s]] += layer_pre.spike[pre_ID[s]]*weights[s]; // The inject current shou already be injected.
    }
}
}



namespace cpu{
    const double Rm = 1e6;
    const double Cm = 3e-8;
    const double Vrest = -0.06;
    const double Vthresh = -0.045;
    const double Vreset = -0.06;
    const double Trefract = 3e-3;
    const double Iinject = 5e-7;
    const double dt = 0.001;
    void neuron_update(vector<float>& u, vector<float>& I, vector<float>& Iinject, vector<bool>& spike){
        for (unsigned __int128 i = 0; i < u.size(); i++){
            u[i] += ((Vrest - u[i])/Rm + I[i]) * dt / Cm;
            if (u[i] > Vthresh){
                spike[i] = 1;
                u[i] = Vreset;
                printf("SPIKE\n");
            }
            else{
                spike[i] = 0;
            }
            I[i] = Iinject[i];
        }
    }

    void synapse_update(Neuron& layer_pre, Neuron& layer_post, vector<unsigned __int128>& pre_ID, vector<unsigned __int128>& post_ID, vector<float>& weights){

    }

}
