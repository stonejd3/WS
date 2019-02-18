#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <inttypes.h>

using namespace std;

vector<string> explode( const string &del, const string &str){
  
  vector<string> arr; 

  uint8_t str_len = str.length();
 
  uint8_t l_index = 0;
  uint8_t h_index = 0;
  
  for(uint8_t i = 0; i < str_len; i++){
    if(str[i] == del[0]){
      h_index = i - l_index;
      arr.push_back(str.substr(l_index, h_index));
      l_index = i+1;
    }
  }
  arr.push_back(str.substr(l_index, str_len));
  return arr;

}

int main(){

	// Create a variable for storing lines in.
	string line = "";

	// Create instance of the stream:
	ifstream file;

	// Open the file:
	file.open("downstreamData.txt");

	// Check to see if file is really open:
	if(file.is_open()){

		// Read file line-by-line:
		while(getline(file, line)){
	
      vector<string> stringData = explode(",", line);
			for(uint8_t i = 0; i < stringData.size(); i++){
        printf("%s\t", stringData[i].c_str());
      }
      printf("\n");
		}

		file.close();		

	} else {
	
		cout<<"Unable to open file"<<endl;
	
	}
	// End the program:
	return 0;
}