#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
// Check that what needs to be an int is an int, color does not need to be checked
// Check valgrind for memory leaks
// Document in README that if input file has a blank spae output file will return error
int main(int argc, char* argv[])
{
  if(argc < 3)
  {
    cerr << "Please provide an input and output file." << endl;
    return 1;
  }
  ifstream input(argv[1]);
  ofstream output(argv[2]);

  int constructionspots;
  int *buildingheights;
  string **skyline;
  string curr;

  input >> constructionspots; 
  getline(input, curr); //consume the newline character for the first line.
  skyline = new string*[constructionspots];

  //you will need to keep track of the height of each building
  buildingheights = new int[constructionspots];

  for (int i = 0; i < constructionspots; i++) 
  {
	  buildingheights[i] = 0;
	  skyline[i] = NULL;
  }
  while(getline(input, curr)) 
  {
	 	stringstream ss;
	 	ss << curr;
	 	ss >> curr;
	 	if (curr == "BUILD") 
	 	{
			int x,y;
			string c, t;
			ss >> x;
			ss >> y;
		 	ss >> c;
			if (ss.fail() || skyline[x] != NULL || x > constructionspots-1 || x<0 || y<0) 
			{
				output << "Error - incorrect command" << endl;
			}
			else if (ss >> t)
				output << "Error - incorrect command";
			else 
			{
		  		buildingheights[x] = y;
		  		skyline[x] = new string[y];
		  		for (int i=0; i<y; i++)
		  		{
		  			skyline[x][i] = c;
		  		}
			}
	  	}
	  else if (curr == "EXTEND") 
	  {
	  	int x, y;
	  	string c ,t;
	  	ss >> x;
	  	ss >> y;
	  	ss >> c;
	  	if (ss.fail() || skyline[x] == NULL || x<0 || x>constructionspots-1 || y<0) 
	  	{
	  		output << "Error - incorrect command" << endl;
	  	}
	  	else if (ss >> t)
			output << "Error - incorrect command";
	  	else 
	  	{
	  		//arrays have fixed lengths

	  		string* temp = new string[buildingheights[x]];
	  		for (int i=0; i<buildingheights[x]; i++)
	  		{
	  			temp[i] = skyline[x][i];
	  		}
  			delete [] skyline[x];
  			skyline[x] = new string[buildingheights[x]+y];

  			for (int i=0; i<buildingheights[x]; i++)
  			{
  				skyline[x][i] = temp[i];
  			}
	  		for (int i=buildingheights[x]; i<buildingheights[x]+y; i++)
	  		{
	  			skyline[x][i] = c;
	  		}
	  		delete [] temp;
	  		buildingheights[x] += y;
	  	}
	  }
	  else if (curr == "DEMOLISH") 
	  {
	  	// delete allocated building at spot x
	  	int x;
	  	string t;
	  	ss >> x;
	  	if (ss.fail() || skyline[x] == NULL || x> constructionspots-1 || x< 0)
	  	{
	  		output << "Error - incorrect command";
	  	}
	  	else if (ss >> t)
			output << "Error - incorrect command";
	  	else 
	  	{
	  		buildingheights[x] = 0;
	  		delete [] skyline[x];
	  		skyline[x] = NULL;
	  	}
	  }

	  else if (curr == "SKYLINE") 
	  {
	  	int y;
	  	string t;
	  	ss >> y;
	  	if (ss.fail() || y<1) 
	  	{
	  		output << "Error - incorrect command";
	  	}
	  	else if (ss >> t)
			output << "Error - incorrect command";
	  	else
	  	{
	  		for (int i =0; i<constructionspots; i++)
	  		{
	  			if (buildingheights[i] < y)
	  				output << "SKY ";
	  			else
	  				output << skyline[i][y-1] << " ";
	  		}
	  	}
	  	output << endl;
	  }
	  else 
	  {
	  	output << "Error - incorrect command" << endl;
	  }
	}
	
	//deallocate skyline
	for (int i=0; i<constructionspots; i++){
		if (buildingheights[i] > 0)
			delete [] skyline[i];
	}
	delete [] skyline;
	//deallocate buildingheights
	delete [] buildingheights;
  return 0;
}
