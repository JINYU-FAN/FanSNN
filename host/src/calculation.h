#ifndef CALCULATION_H
#define CALCULATION_H
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "neuron.h"
using namespace fansnn;
using namespace std;
namespace easy{
    void neuron_update(vector<float>& u, vector<float>& I, vector<float>& Iinject, vector<bool>& spike);
    void synapse_update(Neuron& layer_pre, Neuron& layer_post, vector<unsigned __int128>& pre_ID, vector<unsigned __int128>& post_ID, vector<float>& weights);
}

namespace cpu{
    void neuron_update(vector<float>& u, vector<float>& I, vector<float>& Iinject, vector<bool>& spike);
    void synapse_update(Neuron& layer_pre, Neuron& layer_post, vector<unsigned __int128>& pre_ID, vector<unsigned __int128>& post_ID, vector<float>& weights);
    void Izhikevich_neuron_update(vector<float>& u, vector<float>& I, vector<float>& Iinject, vector<bool>& spike);
}

namespace fpga{
    void neuron_update(vector<float>& u, vector<float>& I, vector<float>& Iinject, vector<bool>& spike);
    void synapse_update(Neuron& layer_pre, Neuron& layer_post, vector<unsigned __int128>& pre_ID, vector<unsigned __int128>& post_ID, vector<float>& weights);
}
#endif