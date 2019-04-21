#include "arithmetic.h"
#include<string>
#include <fstream>

void readPgm(string& version,int& width ,int& height , int& range ,vector<unsigned char>* img);

int main(int argc, char* argv[]) {
	string command;
	Arithmetic arithmetic;
	cin>>command;
	if(command == "-bin_to_dec")
	{
		long long bin ;
		cin >> hex >> bin;
		std::bitset<32> b1;
		for(int i=31;i>-1;i--)
		{
			b1[i]=(bin%2);
			bin /= 2;
		}
		double ans=arithmetic.binary_to_decimal(b1);
		cout<<ans<<endl;
	}
	else if(command == "-dec_to_bin")
	{
		double dec;
		cin>>dec;
		std::bitset<32> bitString;
		cout<< arithmetic.decimal_to_binary(dec)<<endl;
	}
	else if(command=="-encode")
	{
		int blockSize;
		vector<bitset<32> > encoded_msg;
		vector<unsigned char>message;
		string version;
		int width,height,range;
		cin>>blockSize;
		readPgm(version,width,height,range,&message);
		int numberOfBits=arithmetic.encode( message , blockSize ,&encoded_msg);
		cout<<numberOfBits<<endl;
		double comprassionRatio= width*height*8/numberOfBits;
		cout <<comprassionRatio<<endl;
		for(int z =0;z<encoded_msg.size();z++)
		{
			cout<<encoded_msg[z]<<endl;
		}
	}
	else if(command=="-decode")
	{
		int blockSize,coloumns,rows,max;
		vector<unsigned char> decodedMsg;
		cin>>blockSize>>coloumns>>rows>>max;
		vector<bitset<32>> encodedMsg;
		arithmetic.decode(encodedMsg,blockSize,&decodedMsg);
	}
	return 0;
}

void readPgm(string& version,int& width ,int& height , int& range ,vector<unsigned char>* img ){
	ifstream infile;
	infile.open ("sena.pgm");
	char x;
	string test;
	int val;
	cin>>x;
	version+=x;
	cin>>x;
	version+=x;
	while(true)
	{
		cin>>test;
		if(test[0]!='#')
		{
			break;
		}
		else
		{
			getline(cin,test);
		}
	}
	width = stoi(test);
	cin>>height;
	cin>>range;
	for(int i=0;i<width*height;i++)
	{
		cin>>val;
		img->push_back(val);
	}
}
