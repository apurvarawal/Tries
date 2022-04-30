//find a pair with maximum XOR.

//Input[] = {3,10,5,25,2,8}

//Output[] = 5^25 = 28

// 3 - 0 0 0 1 1
//10 - 0 1 0 1 0
// 5 - 0 0 1 0 1
//25 - 1 1 0 0 1
// 2 - 0 0 0 1 0
// 8 - 0 1 0 0 0

//Time complexity :
//brute force = O(n^2)
//trie        = O(logn)

//We will try to get more no. of '1' towards the RHS, to get the max XOR.
//
//                     |---> 1 ---> 0 ---> 1 ---> 0
//          |---> 0 ---|
//          |          |---> 0 ---> 0 ---> 1 ---> 1
//   '\0'---|                |      |
//          |                |      |---> 1 ---> 0
//          |                |
//          |                |---> 1 ---> 0 ---> 1
//          |
//          |---> 1 ---> 1 ---> 0 ---> 0 ---> 1

// XOR table :
// 0^0 = 0
// 1^1 = 0
// 0^1 = 1
// 1^0 = 1

//CONVERSIONS FROM BINARY TO DECIMAL AND VICE VERSA

//decimal to binary :
//(value>>position of digit) & 1 

//binary to decimal :
//(binary digit<<position of digit)

#include<iostream>
#include<unordered_map>
using namespace std;

class node{
    public:
    node* left;  //for 0
    node* right; //for 1
};

class trie{
    node* root;

    public:
    trie(){
        root = new node();
    }

    //function to insert the number in trie, after converting it to binary

    void insert(int val){

        node* temp = root; //temp will iterate over the nodes

        for(int i=31; i>=0; i--){
            int bit = (val>>i)&1; //it will give us the value in bits of the integer
            if(bit==0){
                if(temp->left==NULL){ //if the trie of left side is null, then we will build the left side, starting from '0'.
                    temp->left=new node();
                }
                temp=temp->left;//else we will jump on the next node on the left
            }
            else{
                if(temp->right==NULL){
                    temp->right=new node();
                }
                temp=temp->right;
            }
        }
    }

    //function to find xor of each number with the previous numbers

    int xor_helper(int val){
        int current_ans = 0;
        node* temp = root;
        for(int i=31; i>=0; i--){
            int bit = (val>>i)&1;

            if(bit==0){ //then we will check the right side to find the complementary of '0', i.e. '1'
                if(temp->right!=NULL){
                    temp = temp->right;
                    current_ans += (1<<i); //to convert '1' into decimal number, depending upon it's position in the binary number (for e.g. 2^0,2^1,etc)
                }
                else{
                    temp = temp -> left; //if right side is null, then we will shift the temp to the left
                }
            }
            else{
                if(temp->left!=NULL){
                    temp=temp->left;
                    current_ans += (1<<i);
                }
                else{
                    temp = temp -> right;
                }
            }
        }
        return current_ans;
    }

    //function to find the max xor from all xor we calculated in the above function

    int max_xor(int* input, int n){
        int max_xor = 0;
        
        for(int i=0; i<n; i++){
            int val = input[i];
            insert(val);
            int current_xor = xor_helper(val);
            cout<<current_xor<<" ";
            max_xor = max(current_xor,max_xor);
        }
        cout<<endl<<"Max XOR is : ";
        return max_xor;
    }
};

int main(){
    int input[] = {3,10,5,25,2,8};
    int n = sizeof(input)/sizeof(int);
    trie t;
    cout<<t.max_xor(input,n)<<endl;
    return 0;
}