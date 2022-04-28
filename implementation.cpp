#include<iostream>
#include<unordered_map>
using namespace std;

class node{
    public:
    char data;
    unordered_map<char, node*> children;
    bool terminal;

    node(char data){
        this -> data = data; 
        terminal = false;
    }
};

class trie{
    node* root;
    int cnt;

    public:
    trie(){
        root = new node('\0'); //initially
        cnt = 0; //initially
    }

    void insert(char* w){
        node* temp = root;

        for(int i=0; w[i]!='\0'; i++){

            char ch = w[i];
            if(temp -> children.count(ch) == true){ //checking if the w[i] exists in the trie
                temp = temp->children[ch];          //if it exists, then we will jump to the next node
            }
            else{
                node* n = new node(ch);     //if it doesn't exist, then we will make a new node
                temp -> children[ch] = n;   //we will store this node in trie
                temp = n;                   //temp will jump to the new node
            }
        }
        temp-> terminal = true; //marking the last char of the string as the terminal point
    }

    bool find(char* w){
        node* temp = root;
        for(int i=0; w[i]!='\0'; i++){
            char ch = w[i];
            if(temp -> children.count(ch) == 0){
                return false;
            }
            else{
                temp = temp-> children[ch]; //jump to the next char
            }
        }
        return temp->terminal; //will return true if the not is terminal, it means the word is present
    }
};
int main(){
    trie t;
    char words[][10] = {"a" ,"hello", "not", "news", "apple"};
    char input[8];
    cin>>input;

    for(int i=0; i<5; i++){
        t.insert(words[i]);
    }

    if(t.find(input)){
        cout<<"present";
    }
    else{
        cout<<"absent";
    }

    return 0;
}