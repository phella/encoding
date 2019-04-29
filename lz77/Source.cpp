#include"Lz77.h"
#include<iostream>
void readPgm(string& version,int& width ,int& height , int& range ,vector<unsigned char>* img );
void readEncoded(vector<Triplet>* encodedMsg);
void decorrelation(int width,int height,vector<unsigned char>*symbols);
int main(int argc, char* argv[]) {
	// read parameters here
	LZ77 lz77 ;
	string command;
	vector<Triplet> encodedMsg;
	vector<unsigned char> message;
	string version;
	int width,height,range;
	if(strncmp(argv[1], "-encode",7) == 0 &&strncmp(argv[2],"-diff",5)!=0)
	{
		int searchBuff,lookAhead,symbols;
		searchBuff=stoi(argv[2]);
		lookAhead = stoi(argv[3]);
		symbols = stoi(argv[4]);
		readPgm(version,width,height,range,&message);
		cout<<lz77.encode(message ,searchBuff,lookAhead,symbols,&encodedMsg)<<endl;
		cout<<encodedMsg.size()<<endl;
		for(int i=0;i<encodedMsg.size();i++)
		{
			cout<<encodedMsg[i].j<<" "<<encodedMsg[i].k<<" "<<(int)encodedMsg[i].c<<endl;
		}
	}
	else if(strncmp(argv[1],"-decode",7)==0)
	{
		int dummy;
		cin>>dummy;
		int xres=stoi(argv[2]);
		int yres=stoi(argv[3]);
		int max = stoi(argv[4]);
		vector<unsigned char> decodedMsg;
		readEncoded(&encodedMsg);
		lz77.decode(encodedMsg,&decodedMsg);
		cout<<"P2"<<endl<<xres<<" "<<yres<<endl<<max<<endl;
		for(int i=0;i<xres;i++)
		{
			for(int j=0;j<yres;j++)
			{
				cout<<(int)decodedMsg[i*yres+j]<<" ";
			}
		}
	}
	else
	{
		int searchBuff,lookAhead,symbols;
		searchBuff=stoi(argv[3]);
		lookAhead = stoi(argv[4]);
		symbols = stoi(argv[5]);
		readPgm(version,width,height,range,&message);
		decorrelation(width,height,&message);
		cout<<lz77.encode(message ,searchBuff,lookAhead,symbols,&encodedMsg)<<endl;
		cout<<encodedMsg.size()<<endl;
		for(int i=0;i<encodedMsg.size();i++)
		{
			cout<<encodedMsg[i].j<<" "<<encodedMsg[i].k<<" "<<(int)encodedMsg[i].c<<endl;
		}
	}
	return 0;
}



void readPgm(string& version,int& width ,int& height , int& range ,vector<unsigned char>* img )
{
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

void readEncoded(vector<Triplet>* encodedMsg)
{
	long long size;
	cin>>size;
	int j,k,c;
	for(int i=0;i<size;i++)
	{
		cin>>j>>k>>c;
		Triplet add(j,k,(char)c);
		encodedMsg->push_back(add);
	}
}

void decorrelation(int width,int height,vector<unsigned char>*symbols)
{
	for(int i=0;i<height;i++)
	{
		for(int j=width-1;j>0;j--)
		{
			symbols->at(i*width+j) -= symbols->at(i*width+j-1) ;
		}
	}
}
