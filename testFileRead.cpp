#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){

	// Create a variable for storing lines in.
	string line;

	// Create instance of the stream:
	ifstream file;

	// Open the file:
	file.open("output.txt");

	// Check to see if file is really open:
	if(file.is_open()){

		// Read file line-by-line:
		while(getline(file, line)){
	
			cout<<line<<'\n';
	
		}

		file.close();		

	} else {
	
		cout<<"Unable to open file";
	
	}

	// End the program:
	return 0;
}