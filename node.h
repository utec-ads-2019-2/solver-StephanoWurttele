#include <iostream>
#include <string>
#include <cmath>
using namespace std;

struct Node{
	string value;
	Node* right;
	Node* left;
	int rank;
	Node(string valuee):value(valuee){
		right = nullptr;
		left = nullptr;
		if (valuee=="+" || value=="-")
			rank=1;
		else{
			if (value=="*" || value=="/")
				rank=2;
			else{
				if(value=="^")
					rank=3;
				else
					rank=0;
			}
		}
	};
	Node(){
		right = nullptr;
		left =nullptr;
		value="";
		rank=0;
	};
	float operate(){
		if (value=="+")
			return(this->left->operate()+this->right->operate());
		else {
			if(value=="-")
				return(this->left->operate()-this->right->operate());
			else { 
				if(value=="*")
					return(this->left->operate()*this->right->operate());
				else {
					if(value=="/")
						return(this->left->operate()/this->right->operate());
					else{
						if(value=="^")
							return(pow(this->left->operate(),this->right->operate()));
						else
							return (stoi(this->value));
					}
				}
			}
		}
	}
};


