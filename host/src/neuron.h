#ifndef NEURON_H
#define NEURON_H
#include <vector>
using namespace std;
namespace fansnn{
    class Neuron{
        /*
        This class defines a population of neurons.
        */
        public:
            Neuron(unsigned __int128 N);
            void update(void); // It update the membrane potential for one step.
            void randomize_Iinject(const float MIN, const float MAX); // Randomize the current.
            void inject(void);
            void randomize_u(const float MIN, const float MAX); // Randomize the membrane potential.
            void randomize_spike(float p); // Randomize the spikes with probability p.
            unsigned __int128 size(void); // Get the size of the population

        //private:
            unsigned __int128 N;
            vector<float> u; // The membrane potential of the neurons.
            vector<bool> spike; // The spike of the neurons.
            vector<float> Iinject; // The injection current.
            vector<float> I; // The overall input current, it is the summation of synaptic, inject and noisy current
    };
}

#endif