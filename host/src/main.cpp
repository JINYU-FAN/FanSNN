#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "neuron.h"
#include "synapse.h"
using namespace std;
using namespace fansnn;


int main(){
    Neuron layer1(2);
    Neuron layer2(2);
    
    layer1.randomize_Iinject(10,10.2);
    Synapse s(layer1, layer2, 1.0);
    int n = 1;
    for (int i = 0; i < 100; i++){  
        cout << "\nUpdate:" << n<<endl;  
        n+= 1;
        cout << "layer1 update"<<endl; 
        layer1.update();
        cout << "layer2 update"<<endl;  
        layer2.update(); 
        cout << "synapse update"<<endl;  
        s.update();   
    }
}





void cleanup(){
    
}