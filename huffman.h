#ifndef _HUFFMAN_H
#define _HUFFMAN_H

#include <vector>
#include<map>
#include<string>
using namespace std;
// Define the tree node struct here ...
struct Node {
	Node(){
		left=NULL;
		right = NULL;
	};
	Node* left;
	Node* right;
	int value;
	float probability;
};
// Define a symbol struct here to hold the symbol (grayscale value)
// and its probability/frequency
struct Symbol {
	// Grayscale value of the symbol
	unsigned char val;
	float probability;
	int frequency;
};

class Huffman {
public:
	Huffman(){};
	// Constructor and destructor

	// A function to compute the entropy of the input message and
	// stores the probabilities of the different symbols in
	// the input array.	s
	float compute_entropy(const vector<unsigned char>& msg,
		vector<Symbol>* prob);

	// A function to build the Huffman tree given the computed
	// symbol probabilities.
	void build_tree(const vector<Symbol>& prob);

	// A function to print the code table computed from the build_tree above.
	void print_code_table();

	// A function to encode the input message using the computed tree
	// and store the output in the output array, where each entry
	// corresponds to the codeword for an input symbol in the message.
	//
	// The function should return the number of bits in the encoded
	// message.
	int encode(const vector<unsigned char>& msg,
		vector<unsigned int>* encoded_msg);
	vector<Symbol>* getSymbols();
	void clear();
	void setCodewords(Node* root , string path);

private:
	// Data members here ... for example to store the tree and the codeword
	// hash table
	vector<Symbol> symbols;
	Node* tree;
	map<int,string> codewords;
};

#endif
