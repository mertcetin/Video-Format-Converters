#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	FILE* inputfile;
	FILE* outputfile;

	string filename;
	
	cout <<"Input Filename ?:";
	cin >> filename;
	
	inputfile = fopen(filename.c_str(),"rb");
	
	cout <<"Output Filename ?:";
	cin >> filename;
	
	outputfile = fopen(filename.c_str(),"wb");

	int framecount;
	cout <<"Frame Count: ?";
	cin >> framecount;
	int image_width;
	cout <<"Image Width: ?";
	cin >> image_width;
	int image_height;
	cout <<"Image Height: ?";
	cin >> image_height;

	unsigned char* imagedata;
	imagedata = new unsigned char[image_width*image_height];

	int i,j;
	cout <<"Processing Frame: 000"<<endl;
	for (i=0;i<framecount;i++)
	{
		fread(&imagedata[0],sizeof(unsigned char),image_width*image_height,inputfile);
		fwrite(&imagedata[0],sizeof(unsigned char),image_width*image_height,outputfile);
		fseek(inputfile,image_width*image_height*sizeof(unsigned char),SEEK_CUR);
		printf("\b\b\b%03d",i);
	}

	return 0;
}