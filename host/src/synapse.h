#ifndef SYNAPSE_H
#define SYNAPSE_H
#include "neuron.h"
namespace fansnn{
    class Synapse{
        public:
            Synapse(Neuron& layer_pre, Neuron& layer_post, float p); // p represents the probability of connecting two neurons.
            void update(void); // Update the postsynaptic current.
            void randomize_weights(const float MIN, const float MAX);
        private:
            unsigned __int128 N;
            Neuron* layer_pre;
            Neuron* layer_post;
            vector<unsigned __int128> pre_ID;
            vector<unsigned __int128> post_ID;
            vector<float> weights;


    };
}


#endif