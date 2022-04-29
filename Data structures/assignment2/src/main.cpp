#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include "tree.h"

using namespace std;

Tree::Tree() {
    this->root=NULL;
}

Node::Node(){
    this->left=NULL;
    this->right=NULL;
}

Node::Node(string s){
    this->city.name =s;
    this->left=NULL;
    this->right=NULL;
}
int Tree::contains(string s){
    for(int i=0;i<city_count;i++){ //if a city is already exists, returns 1 otherwise 0
        if (city_array[i].name==s)
            return 1;
    }
    return 0;
}
void Tree::read_file(int a, char* argv[]){
    ifstream travel;
    travel.open(argv[a],ifstream::in);
    string from;
    string to;
    int dist;
    while(travel >> from >> to >> dist){
        if(this->root ==NULL){
            Node* first = new Node(from);
            this->root = first;
            city_array[city_count++].name=from;
        }
        int a =contains(to); // if the destination is already reachable from another city, a is 1 otherwise 0
        return_inorder(this->root,from);
        if(a == 0){ //if there is no way to destination, create a new node for it
            Node* new_node = new Node(to);
            city_array[city_count++].name=to;
            if(returner->left==NULL){ //if left child is empty, adds first
                returner->left = new_node;
                returner->dist_left=dist;
            }
            else if(returner->right==NULL){
                returner->right = new_node;
                returner->dist_right=dist;
            }
        }
        else{ //if destination is already reachable
            Node* tmp = returner;
            return_inorder(this->root,to);
            if(tmp->left==NULL){//just connects two existing nodes
                tmp->left = returner;
                tmp->dist_left=dist;
            }
            else if(tmp->right==NULL){
                tmp->right = returner;
                tmp->dist_right=dist;
            }
        }
    }
    travel.close();
}

void Tree::preorder_prune(Node* traversal){
    if(traversal!=NULL){ //this functions traverses in preorder way, calculates costs and cuts the unnecessary links
        if(traversal->left!=NULL){
            int x = traversal->left->city.travel_cost;
            if(x !=0 && x > traversal->city.travel_cost+traversal->dist_left){ //if the left node is already visited, then one of the links must be pruned
                string removal = traversal->left->city.name; //if the cost from current node to the target is smaller
                pruning_traverse(this->root , removal,x);
                traversal->left->city.travel_cost=traversal->city.travel_cost+traversal->dist_left;
            }
            else if(x!=0 && x < traversal->city.travel_cost+traversal->dist_left){ //if the cost from current node to the target is larger than the other node
                traversal->left=NULL;
                traversal->dist_left=0;
            }
            else //if the node isn't already visited, calculates its cost
                traversal->left->city.travel_cost = traversal->city.travel_cost + traversal->dist_left;
        }
        this->preorder_prune(traversal->left);
        if(traversal->right!=NULL){ //same goes here if the right child has more than 1 parent
            int x = traversal->right->city.travel_cost;
            if(x !=0 && x > traversal->city.travel_cost+traversal->dist_right){
                string removal = traversal->right->city.name;
                pruning_traverse(this->root , removal,x);
                traversal->right->city.travel_cost=traversal->city.travel_cost+traversal->dist_right;
            }
            else if(x!=0 && x < traversal->city.travel_cost+traversal->dist_right){
                traversal->right=NULL;
                traversal->dist_right=0;
            }
            else
                traversal->right->city.travel_cost = traversal->city.travel_cost + traversal->dist_right;
        }
        this->preorder_prune(traversal->right);
        for(int i=0;i<city_count;i++){ //appends the cost values to array members
            if(city_array[i].name==traversal->city.name){
                city_array[i].travel_cost=traversal->city.travel_cost;
                break;
            }
        }
    }
}

void Tree::pruning_traverse(Node* traversal, string a, int x){
    if(traversal!=NULL){
        if(traversal->left!=NULL && traversal->left->city.name == a && traversal->city.travel_cost+traversal->dist_left == x){
            traversal->left=NULL; //if the node which we need to prune its link to child is on the left
            traversal->dist_left=0;
        }
        pruning_traverse(traversal->left,a,x);
        if(traversal->right!=NULL && traversal->right->city.name == a && traversal->city.travel_cost+traversal->dist_right == x){
            traversal->right=NULL;//if the node which we need to prune its link to child is on the right
            traversal->dist_right=0;
        }
        pruning_traverse(traversal->right,a,x);
    }
}

void Tree::return_inorder(Node* traversal,string s){ //returns any node if you give the city name as a parameter
    if(traversal->left!=NULL)
        return_inorder(traversal->left,s);
    if(traversal->city.name == s){
        returner= traversal;
    }
    if(traversal->right!=NULL)
        return_inorder(traversal->right,s);
    if(traversal->city.name == s){
        returner= traversal;
    }
}

void Tree::preorder_traverse_print(Node* traversal){
    if(traversal!=NULL){ //traverses and prints the city name
        cout << traversal->city.name << " ";
        this->preorder_traverse_print(traversal->left);
        this->preorder_traverse_print(traversal->right);
    }
}
void Tree::print_preorder(int b){
    cout << "FRIEND-" <<b<<": "; //organizes output correctly
    this->preorder_traverse_print(this->root);
    cout<<endl;
}

int main(int argc, char*argv[]){
    Tree* t = new Tree(); //friend1's map
    t->read_file(1,argv);
    t->preorder_prune(t->root);
    t->print_preorder(1);
    Tree* t2= new Tree(); //friend2's map
    t2->read_file(2,argv);
    t2->preorder_prune(t2->root);
    t2->print_preorder(2);
    City final_array[ARRAY_SIZE]; //to collect the cities in a place which are reachable by both of the friends
    int c=0;
    for(int i=0;i<t->city_count;i++){
        for (int j=0;j<t2->city_count;j++){ 
            if (t->city_array[i].name == t2->city_array[j].name){//if the names match, gets it to the array with total cost
                final_array[c].name=t->city_array[i].name;
                final_array[c++].travel_cost = t->city_array[i].travel_cost + t2->city_array[j].travel_cost;
                break;
            }
        }
    }
    int min = final_array[0].travel_cost;
    int index=0;
    for(int i=1;i<c;i++){ //finds minimum cost city and returns its index
        if(final_array[i].travel_cost<min){
            min = final_array[i].travel_cost;
            index=i;
        }
    }
    cout <<"MEETING POINT: "<< final_array[index].name << endl;
    cout <<"TOTAL DURATION COST: "<<final_array[index].travel_cost<<endl;
    return 0;
}
/* @Author
Student Name: Eren Yaşa
Student ID: 150200022
E-mail: yasa20@itu.edu.tr
Date: 28.12.2021
*/