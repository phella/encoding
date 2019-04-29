#include"Lz77.h"
#include<iostream>
int LZ77::encode(const vector<unsigned char>& msg,int S, int T, int A,vector<Triplet>* encoded_msg)
{
	string message ="" ;
	int maxSize =S+T;
	string subs1,subs2;
	for(int i =0;i<msg.size();i++)
	{
		message+=msg[i];
	}

	for(int i=0;i<msg.size();i++)
	{
		int added=0;
		Triplet codeword2(0,0,msg[i]);
		int start =  ((i-S > 0) ? i-S : 0);
		int end =  ((i+T < msg.size()) ? i+T : msg.size());
		bool flag=false;
		for(int  j=start;j<end;j++)
		{
			if(flag)
				break;
			Triplet codeword(0,0,msg[i]) ;
			bool found =false;
			for(int k=0;k<maxSize && i+k+1 <msg.size();k++)
			{
				subs1 = message.substr(i,k+1);
				subs2= message.substr(j,k+1);
				if( i==j && codeword.k == 0)
				{
					flag= true;
					break;
				}
				if(subs1==subs2)
				{
					found = true;
					codeword.k = k+1;
					codeword.j = i-j;
					codeword.c =(int) message[i+k+1];
					if(codeword.k > codeword2.k)
					{
						codeword2 = codeword;
						if(codeword.k>0)
							added = codeword.k;
					}
				}
				else
				{
					break;
				}
			}
		}
		encoded_msg->push_back(codeword2);
		i+=added;
	}
	return encoded_msg->size()*(ceil( log(S)/log(2))+ ceil( log(S+T)/log(2)) +ceil( log(A)/log(2)));
}

void LZ77::decode(const vector<Triplet>& encoded_msg,vector<unsigned char>* decoded_msg)
{
	int decodedCounter=0;
	for (int i =0;i<encoded_msg.size();i++)
	{
		if(encoded_msg[i].k==0)
		{
			decoded_msg->push_back((int)encoded_msg[i].c);
			decodedCounter++;
		}
		else
		{
			int offset = encoded_msg[i].j;
			for(int j=0;j<encoded_msg[i].k;j++)
			{
				decoded_msg->push_back((int)decoded_msg->at(decodedCounter-offset));
				decodedCounter++;
			}
			decoded_msg->push_back((int)encoded_msg[i].c);
			decodedCounter++;
		}
	}
}
