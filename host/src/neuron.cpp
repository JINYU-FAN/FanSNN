#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "neuron.h"
#include "calculation.h"

using namespace std;
namespace fansnn{

Neuron::Neuron(unsigned __int128 N){
    this->N = N;
    this->u.resize(N);
    this->spike.resize(N);
    this->Iinject.resize(N);
    this->I.resize(N);
}

void Neuron::update(void){
    cpu::neuron_update(this->u, this->I, this->Iinject, this->spike);
}

void Neuron::randomize_Iinject(const float MIN, const float MAX){
    // Not an optimal function
    for(unsigned __int128 i=0;i < this->N; i++){
        this->Iinject[i] = float(rand()) / float(RAND_MAX) * (MAX - MIN) + MIN;
        this->I[i] = this->Iinject[i];
    }
}

void Neuron::inject(void){

}

void Neuron::randomize_u(const float MIN, const float MAX){
    for(unsigned __int128 i=0;i < this->N; i++){
        this->u[i] = float(rand()) / float(RAND_MAX) * (MAX - MIN) + MIN;
    }
}

void Neuron::randomize_spike(float p){
    for(unsigned __int128 i=0;i < this->N; i++){
        this->spike[i] = rand() % 2;
    }
}

unsigned __int128 Neuron::size(void){
    return this->N;
}


}