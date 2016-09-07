#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
	if (argc < 2){
		cerr << "Enter file name" << endl;
		return 0; 
	}
	// opening file
	ifstream inFile;
	inFile.open(argv[1]);
	// read amount of words in file
	int numWords;
	inFile >> numWords;
	string * word = new string[numWords];
	// Put words into every element of array
	for(int i=0; i<numWords; i++){
		inFile >> word[i];
	}
	for (int i=numWords-1; i>=0; i--){
		cout << word[i] << endl;
	}
	delete [] word;
	inFile.close();
	return 1;

}
