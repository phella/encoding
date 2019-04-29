#include "arithmetic.h"
#include<string>
#include <fstream>
#include <sstream>
using namespace std;
void readPgm(string& version,int& width ,int& height , int& range ,vector<unsigned char>* img);

int main(int argc, char* argv[]) {
	Arithmetic arithmetic;
	bitset<32>b1;
	if(strncmp("-bin_to_dec",argv[1],11)==0)
	{
		string hex = argv[2];
		for(int i=0;i<8;i++)
		{
			if((int)(hex[i+2])-'0'>=8)
			{
				b1[i*4]=1;
				hex[i+2]=(int)hex[i+2]-8;
			}
			else
				b1[i*4]=0;
			if((int)hex[i+2]-'0'>=4)
			{
				b1[i*4+1]=1;
				hex[i+2]=(int)hex[i+2]-4;
			}
			else
				b1[i*4+1]=0;
			if((int)hex[i+2]-'0'>=2)
			{
				b1[i*4+2]=1;
				hex[i+2]=(int)hex[i+2]-2;
			}
			else
				b1[i*4+2]=0;
			if((int)hex[i+2]-'0'>=1)
			{
				b1[i*4+3]=1;
			}
			else
				b1[i*4+3]=0;
		}
		double ans=arithmetic.binary_to_decimal(b1);
		cout<<ans<<endl;
	}
	else if(strncmp("-dec_to_bin",argv[1],11)==0)
	{
		double dec;
		stringstream(argv[2])>>dec;
		std::bitset<32> bitString;
		cout<< arithmetic.decimal_to_binary(dec)<<endl;
	}
	else if(strncmp("-encode",argv[1],7)==0)
	{

		int blockSize = stoi(argv[2]);
		vector<bitset<32> > encoded_msg;
		vector<unsigned char>message;
		string version;
		int width,height,range;
		readPgm(version,width,height,range,&message);
		double numberOfBits=arithmetic.encode( message , blockSize ,&encoded_msg);
		double comprassionRatio= width*height*8/numberOfBits;
		for(int z =0;z<encoded_msg.size();z++)
		{
			cout<<encoded_msg[z]<<endl;
		}
		//cout <<comprassionRatio<<endl;
		//cout<<numberOfBits/8<<endl;
	}
	else if(strncmp("-decode",argv[1],7)==0)
	{
		long long size;
		vector<pair<int,double>> prob;
		cin>>size;
		for(int i=0;i<size;i++)
		{
			pair<int,double> symbolProb;
			cin>>symbolProb.first;
			cin>>symbolProb.second;
			prob.push_back(symbolProb);
		}
		arithmetic.setProb(prob);
		int blockSize,coloumns,rows,max;
		vector<unsigned char> decodedMsg;
		blockSize=stoi(argv[2]);
		coloumns= stoi(argv[3]);
		rows = stoi(argv[4]);
		max = stoi(argv[5]);
		vector<bitset<32>> encodedMsg;
		for(int i=0;i<rows*coloumns/blockSize;i++)
		{
			bitset<32> newVal;
			cin>>newVal;
			encodedMsg.push_back(newVal);
		}
		arithmetic.decode(encodedMsg,blockSize,&decodedMsg);
		cout<<"P2"<<endl;
		cout<<coloumns<<" "<<rows<<endl;
		cout<<max<<endl;
		for(int i=0;i<decodedMsg.size();i++)
		{
			cout<<(int)decodedMsg[i]<<" ";
		}
		return 0;
	}
}
void readPgm(string& version,int& width ,int& height , int& range ,vector<unsigned char>* img ) {
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
