/*
This file defines multiple current sources which could be applied on neurons.
*/
#ifndef SOURCE_H
#define SOURCE_H
#include <math.h>

namespace fansnn{
    class DC{
        public:
            DC(float I); // The value of the constant current;
            float update(void); // It return the value of the source;
        private:
            float I;
    };

    class AC{
        public:
            AC(float A, int f, int phi); // A: The amplification; f: The frequency; phi: The phase.
            float update(void); // It return the value of the source;
        private:
            float A;
            float dphi; // The change of phase for each step
            int phi;
    };
}

#endif