#include <iostream>
#include <string>

using namespace std;

int main()
{
	string infilename;
	string outfilename;
	int howmany;
	int width;
	int height;
	int i,j,k;

	cout << "Input Filename? ";
	cin >> infilename;

	FILE* infile;
	if((infile = fopen(infilename.c_str(), "rb")) == NULL) {
		printf("Error : Input file could not be opened\n");
		return 1;
	}

	cout << "Output Filename? ";
	cin >> outfilename;

	FILE* outfile;
	if((outfile = fopen(outfilename.c_str(), "w")) == NULL) {
		printf("Error : Input file could not be opened\n");
		return 1;
	}

	cout << "How many frames to convert? ";
	cin >> howmany;
	cout << "Frame width? ";
	cin >> width;
	cout << "Frame height? ";
	cin >> height;

	unsigned char* data = new unsigned char[height*width];

	for (i=0; i<howmany; i++)
	{
		fread(&data[0], sizeof(unsigned char), width*height, infile);
		for (j = 0; j< height; j++)
		{
			for (k=0; k< width; k++)
			{
				fprintf(outfile,"%02X ",data[j*width+k]);
			}
			fprintf(outfile,"\n");
		}
		fprintf(outfile,"\n");

		
	}


	return 0;
}