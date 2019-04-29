#include "huffman.h"
#include<iostream>
#include<string>

using namespace std;
void decorrelation(int width,int height,vector<unsigned char>*symbols);
void readPgm(string& version,int& width ,int& height , int& range ,vector<unsigned char>* img);
int main(int argc, char* argv[])
{
	string version;
	string commands[2];
	int width,height,range;
	vector<unsigned char> img;
	vector<unsigned int> encodedMsg;
	readPgm(version,width,height,range,&img);
	Huffman huffman;
	if( strncmp( argv[1], "-entropy",8)==0)
	{
		float entropy =huffman.compute_entropy(img,huffman.getSymbols());
		cout<<entropy<<endl;
	}
	else if (strncmp( argv[1], "-tree",5)==0)
	{
		float entropy =huffman.compute_entropy(img,huffman.getSymbols());
		huffman.build_tree(*huffman.getSymbols());
	}
	else if (strncmp( argv[1],"-encode",7)==0 && argc<3)
	{
		float entropy =huffman.compute_entropy(img,huffman.getSymbols());
		huffman.build_tree(*huffman.getSymbols());
		int length = huffman.encode(img,&encodedMsg);
		cout<<length<<endl;
	}
	else if(strncmp( argv[1],"-encode",7)==0 && argc ==3 )
	{
		decorrelation(width,height,&img);
		float entropy =huffman.compute_entropy(img,huffman.getSymbols());
		huffman.build_tree(*huffman.getSymbols());
		float length = huffman.encode(img,&encodedMsg);
		cout<<length;
	}
	return 0;
}

void readPgm(string& version,int& width ,int& height , int& range ,vector<unsigned char>* img ){
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
