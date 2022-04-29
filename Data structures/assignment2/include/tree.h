#pragma once
using namespace std;
#define ARRAY_SIZE 20

class City{
    public:
        string name; // To store city's name
        int travel_cost = 0;
};

class Node{
    public:
        Node(string);
        Node();
        City city;  // To store token
        Node *left;   // To use in binary tree
        Node *right;  // To use in binary tree
        int dist_left=0; //distance to the left child
        int dist_right=0; //distance to the right child
};

class Tree{
    public:
        Tree();
        Node* root;
        City city_array[ARRAY_SIZE];
        int city_count=0;
        void read_file(int ,char*[]);
        void preorder_traverse_print(Node*);
        void preorder_prune(Node*);
        void print_preorder(int);
        void return_parent_inorder(Node* ,string);
        int contains(string);
        void pruning_traverse(Node*,string,int);
        Node* returner;
};
/* @Author
Student Name: Eren Yaşa
Student ID: 150200022
E-mail: yasa20@itu.edu.tr
Date: 28.12.2021
*/