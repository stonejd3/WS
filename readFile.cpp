#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){

	// Create a variable for storing lines in.
	string line;

	// Create instance of the stream:
	ifstream hashFile;

	// Open the file:
	hashFile.open("hash.txt");

	// Check to see if file is really open:
	if(hashFile.is_open()){

		// Read file line-by-line:
		while(getline(hashFile, line)){
	
			cout<<line<<'\n';
	
		}

		hashFile.close();		

	} else {
	
		cout<<"Unable to open file";
	
	}

	// End the program:
	return 0;
}

getNumLines(string filename);

