#include "huffman.h"
#include <iostream>
#include <cmath>
#include <queue>
#include <math.h>
#include <string>
using namespace std;

class compare{
public:
	int operator()(const Node* A, const Node* B){
		return (A->probability> B->probability);
	}
};

// Using preorder traverse
void Huffman::setCodewords(Node* root , string path)
{
	// Print codewords
	if(root->value>-1)
	{
		cout<<"Symbol: "<<root->value<<",codeword equal "<<path<<endl;
		pair<int,string>x ;
		x.first=root->value;
		x.second=path;
		codewords.insert(x);
	}
	if(root->left)
		setCodewords(root->left,path +'0');
	if(root->right)
		setCodewords(root->right,path + '1');
}


float Huffman::compute_entropy(const vector<unsigned char>& msg,vector<Symbol>* prob)
{
	float entropy=0;
	int size = msg.size();
	for(int i=0;i<msg.size();i++)
	{
		bool flag = true;
		for(int j=0;j<prob->size();j++)
		{
			if(prob->at(j).val==msg[i])
			{
				flag= false;
				prob->at(j).frequency++;
				break;
			}
		}
		if(flag)
		{
			Symbol symbol;
			symbol.val = msg[i];
			symbol.frequency=1;
			prob->push_back(symbol);
		}
	}

	for(int i=0;i<prob->size();i++)
	{
		prob->at(i).probability=(float)prob->at(i).frequency/size;
		entropy-=prob->at(i).probability*log((prob->at(i).probability)) / log(2.0);
	}
	return entropy;
}

void Huffman::build_tree(const vector<Symbol>& prob){
	priority_queue<Node* ,vector<Node*>,compare> nodes;
	for(int i=0;i<prob.size();i++)
	{
		Node* newNode = new Node();
		newNode->value = prob[i].val;
		newNode->probability = prob[i].probability;
		nodes.push(newNode);
	}
	while(nodes.size()>1)
	{
		Node* min1 = nodes.top();
		nodes.pop();
		Node* min2 = nodes.top();
		nodes.pop();
		Node* newNode = new Node();
		newNode->left = min1;
		newNode->right = min2;
		newNode->probability = min1->probability + min2->probability;
		nodes.push(newNode);
	}
	this->tree = nodes.top();
	setCodewords(this->tree,"");
}

int Huffman::encode(const vector<unsigned char>& msg,vector<unsigned int>* encoded_msg){
	int bits = 0;
	for(int i=0;i<msg.size();i++)
	{
		int path=0;
		for(int j=0;j<codewords[msg[i]].size();j++)
		{
			if(codewords[msg[i]][j] =='1')
			{
				path+=pow(2,0);
			}
		}
		bits+= codewords[msg[i]].size();
		encoded_msg->push_back(path);
	}
	return bits;
}

vector<Symbol>* Huffman::getSymbols() {
	return &symbols;
}

void Huffman::clear(){
	symbols.clear();
	tree = NULL;
}
