#include "node.h"
#include <string>
#include <stack>
#include <vector>
#include <map>
using namespace std;


void signspush(Node* &slab, stack<Node*> &signs, stack<Node*> &build){
	while(!signs.empty()){
		if(signs.top()->rank >= slab->rank && slab->rank!=0){
			build.push(signs.top());
			signs.pop();
		}
		else
			break;
	}
	signs.push(slab);
};

Node* constructTree(stack<Node*> &build){
	Node* root=build.top();
	Node* temp=root;
	build.pop();
	if(!build.empty()){
		root->right=build.top();
		temp=temp->right;
	}
	if(temp->rank!=0)
		constructTree(build);
	build.pop();
	root->left=build.top();
	temp=root->left;
	if(temp->rank!=0)
		constructTree(build);
return root;
}

void traverseInOrder(Node* newroot) {
	Node* temp=newroot;
	if (temp->left)
		traverseInOrder(temp->left);
	cout<<temp->value<<" ";
	if (temp->right)
		traverseInOrder(temp->right);
	return;
}

bool inmap(char &x,map<char,string> &variables){
	for(auto it=variables.begin();it!=variables.end();it++){
		if(it->first==x)
			return true;
	}
	return false;
};



int main(){
	stack<Node*> build;
	stack<Node*> signs;
	string input="";
	cout<<"Write \"quit\" to exit and variables in caps"<<endl;
	while(true){
	map<char,string> variables;
	cin>>input;
	if(input=="quit")
		break;
	for(int i=0;i<input.length();i++){
		if(!isdigit(input[i])){
			if(input[i]>='A' && input[i]<='Z'){
				if(inmap(input[i],variables)){
					input.replace(i,1,variables[input[i]]);
				}
				else{
					cout<<"Insert number for "<<input[i]<<endl;
					string number;
					cin>>number;
					variables[input[i]]=number;
					input.replace(i,1,number);
				}
			}
		}
	}
	for(int i=0;i<input.length();i++){
		string temp="";
		while(isdigit(input[i]) && isdigit(input[i+1])){
			temp=temp+input[i];
			i++;
		}
		temp=temp+input[i];
		Node* slab = new Node(temp);
		if(isdigit(temp[0]) ){
			build.push(slab);
		}
		else{
			if(temp!=")")
				signspush(slab, signs, build);
			else{
				while(signs.top()->value!="("){
					build.push(signs.top());
					signs.pop();
				}
				signs.pop();
			}
		}
	}

	while(!signs.empty()){
		build.push(signs.top());
		signs.pop();
	}

	Node* root=constructTree(build);
	traverseInOrder(root);
	float answer=root->operate();
	cout<<endl<<endl;
	cout<<"Answer is "<<answer<<endl;
	}
	return 0;
	
}
