#include <iostream>
#include <cstdlib>
#include <inttypes.h>

using namespace std;

const uint8_t numOutputs = 2;
const uint8_t numInputs = 2;

uint16_t outputs[numOutputs][2*numInputs+1];

int main(){
	
	outputs[0][0] = 13;		// pin
	outputs[0][1] = 0;		// sens1_low
	outputs[0][2] = 0;		// sens1_high
	outputs[0][3] = 0;		// sens2_low
	outputs[0][4] = 0;		// sens2_high
	
}