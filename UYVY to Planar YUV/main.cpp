#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

int main(int argc,char* argv[])
{
	string basefilename;
	string extension;
	string outputfilename;
	int sequence_start;
	int sequence_end;
	string answer;
	bool Y_only;

	cout << "Base Filename?: ";
	cin >> basefilename;
	cout << "Base File Extension?: ";
	cin >> extension;
	cout << "Output Filename?: ";
	cin >> outputfilename;

	cout << "Export Only Y Values?(y/n): ";
	cin >> answer;
	if (answer == "y")
	{
		Y_only = true;
	} 
	else
	{
		Y_only = false;
	}

	cout << "Sequence Start?: ";
	cin >> sequence_start;
	cout << "Sequence End?: ";
	cin >> sequence_end;
	if(sequence_end<sequence_start)
	{
		cout << "End cannot be smaller than start.\nTerminating...\n";
		return 1;
	}

	FILE* InputFile;
	FILE* OutputFile;

	string filename;
	string temp;
	stringstream stringout;
	ifstream::pos_type size;
	char * memblock;
	char* Y_array;
	char* U_array;
	char* V_array;

	
	ofstream outstream (outputfilename.c_str(),ios::out|ios::binary);
	
	int i;
	int j;
	for (i = sequence_start;i<=sequence_end;i++)
	{
		stringout.width(5);
		stringout.fill('0');
		stringout << i;
		
		filename = basefilename + stringout.str() +"." + extension;
		cout << filename<<endl;
		stringout.str("");
		ifstream file (filename.c_str(), ios::in|ios::binary|ios::ate);
		if (file.is_open())
		{
			size = file.tellg();
			memblock = new char [size];
			
			file.seekg (0, ios::beg);
			file.read (memblock, size);
			file.close();

			Y_array = new char [size/2];
			U_array = new char [size/4];
			V_array = new char [size/4];

			for(j= 0; j<size;j++)
			{
				if(j%4 == 0)
					U_array[j/4] = memblock[j];
				else if(j%4 == 1)
				{
					Y_array[2*(j/4)] = memblock[j];
				}
				else if (j%4 == 2)
					V_array[j/4] = memblock[j];
				else
					Y_array[2*(j/4) +1] =memblock[j];
			
			}

			outstream.write(Y_array,size/2);
			if (!Y_only)
			{
				outstream.write(U_array,size/4);
				outstream.write(V_array,size/4);
			} 

			
			
			
			
			
			
			delete[] memblock;
			delete[] Y_array;
			delete[] U_array;
			delete[] V_array;

		}
		else cout << "Unable to open file";

	}
	outstream.close();

	

	







	
	
	
	
	
	
	return 0;
}