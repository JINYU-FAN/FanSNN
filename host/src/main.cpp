#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "neuron.h"
#include "synapse.h"
#include "AOCLUtils/aocl_utils.h"
#include <fstream>
using namespace std;
using namespace fansnn;
using namespace aocl_utils;



int main(){
    ofstream outFile;
    outFile.open("./host/src/neuron_data.csv", ios::out);
    for (int i = 0; i < 100; i++){  
        outFile << i << ',';
    }    
    outFile << endl;
    const double start_time = getCurrentTimestamp();
    Neuron layer1(1); 
    layer1.randomize_Iinject(0.00000005,0.00000005);
    int n = 1;
    for (int i = 0; i < 100; i++){  
        layer1.update();
        //cout << layer1.u[0] << endl;
        outFile << layer1.u[0] << ',';
    }
    outFile << endl;
    outFile.close();
    const double end_time = getCurrentTimestamp();
    printf("Time: %f\n", end_time - start_time);
}





void cleanup(){
    
}