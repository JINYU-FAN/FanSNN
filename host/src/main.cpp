#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "neuron.h"
#include "synapse.h"
#include "AOCLUtils/aocl_utils.h"
#include <GL/glut.h>
using namespace std;
using namespace fansnn;
using namespace aocl_utils;


int main(){
    const double start_time = getCurrentTimestamp();
    Neuron layer1(1); 
    layer1.randomize_Iinject(10,10.2);
    int n = 1;
    for (int i = 0; i < 100; i++){  
        layer1.update();
    }
    const double end_time = getCurrentTimestamp();
    printf("Time: %f\n", end_time - start_time);
}





void cleanup(){
    
}