#ifndef _H
#define _H

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

class materialNode{
    public:
        materialNode(char,int);  //constructor is added.
        char id;
        int weight;
        materialNode* next;
};

class wagonNode{
    public:
        int wagonId;
        materialNode* material;
        wagonNode* next;
        wagonNode(int);  //constructor is added and int sets its Id.
};

class Train{  

    wagonNode* head;
    wagonNode* tail;
    public:
        int wagon_num=0;
        void create();
        void addMaterial(char,int);
        void deleteFromWagon(char, int); 
        void printWagon(); //Prints wagon info
        materialNode* search(char,wagonNode*,int);  //searching function. char for material Id, wagonNode for which wagon to search,
};                                                  //int to decide either adding or deleting.

#endif

/* @Author 
Student Name: Eren Yaşa
Student ID : 150200022
Date: 10.11.2021 */