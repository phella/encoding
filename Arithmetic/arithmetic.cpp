#include "arithmetic.h"

double Arithmetic::binary_to_decimal(const bitset<32>& fraction)
{
	double x =0;
	for(int i=0;i<32;i++)
	{
		x+= fraction[i]/pow(2,i+1);
	}
	return x;
}


bitset<32> Arithmetic::decimal_to_binary(double fraction)
{
	bitset<32> bitString;
	for(int i=0;i<32;i++)
	{
		if(fraction*2>=1)
		{
			bitString[i]=1;
			fraction=fraction*2-1;
		}
		else
		{
			bitString[i]=0;
			fraction = fraction*2;
		}
	}
	return bitString;
}

int Arithmetic::encode(const vector<unsigned char>& msg,int num_symbols_per_block,vector<bitset<32> >* encoded_msg)
{
	int length=0;
	vector<pair<int,double>> prob;
	for(int i=0;i<msg.size();i++)
	{
		bool flag = true;
		for(int j=0;j<prob.size();j++)
		{
			if(prob[j].first==msg[i])
			{
				flag= false;
				prob[j].second++;
				break;
			}
		}
		if(flag)
		{
			pair<int,double> add;
			add.first = msg[i];
			add.second=1;
			prob.push_back(add);
		}
	}
	cout<<prob.size()<<endl;
	for(int i=0;i<prob.size();i++)
	{
		prob[i].second=prob[i].second/msg.size();
		cout<<prob[i].first<<" "<<prob[i].second<<endl;
	}
	for(int j=0;j < 256*256/num_symbols_per_block;j++)
	{
		double l =0;
		double u =1;
		double f,p;
		for(int i=0;i<num_symbols_per_block;i++)
		{
			f=0;
			p=0;
			bool found = false;
			int h=0;
			while(!found)
			{
				if(prob[h].first != msg[j*num_symbols_per_block+i])
					p += prob[h].second;
				else
					found = true;
				f+= prob[h].second;
				h++;
			}
			double temp =l;
			l = l + (u-l)*p;
			u = temp + (u-temp)*f;
		}
		encoded_msg->push_back( decimal_to_binary( (u+l)/2 ) );
		if(u-l<1 && u-l>0)
			length+=ceil( log(1/(u-l))/log(2))+1;
	}
	return length;
}

void Arithmetic::decode(const vector<bitset<32> >& encoded_msg,int num_symbols_per_block,vector<unsigned char>* decoded_msg)
{

	for(int j=0;j<encoded_msg.size();j++)
	{
		double l=0;
		double u=1;
		double t;
		for(int i=0;i<num_symbols_per_block;i++)
		{
			t = (binary_to_decimal( encoded_msg[j]) - l)/(u-l);
			double sum =0;
			for(int k=0;k<prob.size();k++)
			{
				sum+=prob[k].second;
				if(t < sum)
				{
					double temp =l;
					l = l+(u-l)*(sum-prob[k].second);
					u = temp+(u-temp)*sum;
					decoded_msg->push_back(prob[k].first);
					break;
				}
			}
		}
	}
}

void Arithmetic::setProb(vector<pair<int,double>> prob)
{
	this->prob = prob;
}
