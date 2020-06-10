#include <stdlib.h>
#include <stdio.h>
#include <boost/assert.hpp>
#include "synapse.h"
#include "calculation.h"
using namespace easy;
namespace fansnn{

Synapse::Synapse(Neuron& layer_pre, Neuron& layer_post, float p){
    this->layer_pre = &layer_pre;
    this->layer_post = &layer_post;
    for (unsigned __int128 i =0; i < layer_pre.size(); i++){
        for (unsigned __int128 j =0; j < layer_post.size(); j++){
            if (rand() % 1000 / 1000.0 < p){
                this->pre_ID.push_back(i);
                this->post_ID.push_back(j);
                this->weights.push_back(1); // The initial value of all weights is 1.
            }
        }
    }
    this->N = weights.size();
}


void Synapse::update(void){
    synapse_update(*(this->layer_pre), *(this->layer_post), this->pre_ID, this->post_ID, this->weights);
}

void Synapse::randomize_weights(const float MIN, const float MAX){
    for(unsigned __int128 i=0; i < this->N; i++){
        this->weights[i] = float(rand()) / float(RAND_MAX) * (MAX - MIN) + MIN;
    }
}

}