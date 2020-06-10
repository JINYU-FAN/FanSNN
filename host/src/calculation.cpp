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
        cout << "u:"<< u[i] << endl;
        cout << "I:"<< I[i] << endl;
        u[i] += I[i];

        cout << "u:"<< u[i] << endl;
        if(u[i] >= 10){ // 10 is the firing threshold
            spike[i] = 1;
            printf("SPIKE!\n");
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





namespace fpga{

extern const __int128 N_NEURON;
extern const __int128 N_SYNAPSE;

void neuron_update(vector<float>& u, vector<float>& I, vector<float>& Iinject, vector<bool>& spike){
    __int128 N = u.size(); // The problem size
    int REPEAT = N / N_NEURON;
    if (N % N_NEURON != 0){
        REPEAT += 1;
    }
    for (int i=0; i < REPEAT; i++){
        //fpga_easy_neuron_update();
    }
}



void synapse_update(Neuron& layer_pre, Neuron& layer_post, vector<unsigned __int128>& pre_ID, vector<unsigned __int128>& post_ID, vector<float>& weights){



}


}