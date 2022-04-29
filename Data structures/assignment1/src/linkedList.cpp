#include <iostream>
#include <stdio.h>
#include <string.h>

#include "linkedList.h"

using namespace std;

void Train::create(){
    head = NULL;
    tail = NULL; //added tail node
}; 

wagonNode::wagonNode(int num){
    this->wagonId = num;
};

materialNode::materialNode(char material, int weight){
    this->id = material;
    this->weight=weight;
};

materialNode* Train::search(char letter,wagonNode* wagon,int c){
    if(wagon==NULL){ //A search function is added to decide where to put the material in a wagon.
        return NULL;
    }
    materialNode* x = wagon->material;
    if (x==NULL)
        return NULL;
    if (letter - x->id < 0 && c==1)
        return NULL;  //If wagon has no material or the materials in the wagon are alphabetically of less priority, it returns NULL.
    else if(c==1){ //and c variable holds a value that indicates the function is being used to add or delete a material.1 for adding 2 for deleting.
        while(x->next != NULL){ // the only difference is "=" symbol though.
            if (x->next->id - letter >0)
                return x;
            x=x->next;
        }
        return x;
    }
    if (letter - x->id <= 0 && c==2)
        return NULL;
    else{
        while(x->next != NULL){
            if (x->next->id - letter >=0)
                return x;
            x=x->next;
        }
        return x;
    }
};


void Train::addMaterial(char material, int weight){
    //FILL THIS FUNCTION ACCORDINGLY
    materialNode* new_material= new materialNode(material,weight);
    int temp_weight= new_material->weight; //the function's loop works by this variable. Continues adding while temp_weight != 0.
    if (head==NULL) {
        head = new wagonNode(++wagon_num);
        tail=head;
    }
    wagonNode* new_wagon=head;
    materialNode* for_loop = new_wagon->material; //for_loop variable holds materials in a wagon all the time.
    while(temp_weight){
        
        while (new_wagon!=NULL){  // To increase the weight of an alrady existing material in a wagon.
            for_loop = new_wagon->material;
            while(for_loop !=NULL){  
                if(for_loop->id == new_material->id){
                    int c = 2000 - for_loop->weight; //This c holds how much of the same material current wagon can take.
                    if(c!=0 && temp_weight > c){  //adds if the current wagon can't take the whole new material.
                        for_loop->weight += c;
                        if(c>0){  //c can be bigger than 0 in some cases so this fixes everything.
                            temp_weight-=c;
                            new_material->weight -= c;
                        }
                    }
                    else if(c!=0 && c>=temp_weight){ //adds if the current wagon can take whole new material.
                        for_loop->weight +=c;
                        temp_weight =0;
                    }
                }
                for_loop = for_loop->next;
            }
            new_wagon=new_wagon->next;
        }
        new_wagon=head;
        for_loop = new_wagon->material;
        int count=0;
        if(temp_weight != 0){  // adds if the current wagon doesn't have any of the new kind of material.
            while(new_wagon!=NULL){
                for_loop = new_wagon->material;
                while(for_loop!=NULL){
                    if(for_loop->id == material){ //if the current wagon has that material, count increases and the final value of count shows
                        count++;                  //the first wagon that doesn't have that element.
                    }
                    for_loop=for_loop->next;
                }
                new_wagon=new_wagon->next;
            }
            new_wagon=head;
            if(count == 0 && wagon_num==1){ //in the first adding, this protects from a segfault.
                ;
            }
            else if(count == wagon_num){ // if whole the wagons have that material, a new wagon is added
                wagonNode* control = new wagonNode(++wagon_num);
                tail=control;
                while(new_wagon!=NULL){
                    if(new_wagon->next==NULL){
                        new_wagon->next=tail;
                        break;
                    }
                    new_wagon =new_wagon->next;
                }
            }
            else{
                while(count){ //this takes the new_wagon variable to the wagon which the new_material variable is to be added.
                    new_wagon=new_wagon->next;
                    count--;
                }
            }
            for_loop = new_wagon->material;
            materialNode* prev = this->search(material,new_wagon,1);
            materialNode* material2= new materialNode(material,temp_weight); //temp_weight helps to adjust kg's in different wagons.
            if(prev==NULL){                                                  //i faced some mistakes at all other solutions.
                material2->next = for_loop; //add to the beginning.
                new_wagon->material= material2;
                if(temp_weight<=2000)
                    temp_weight=0;
                else if(temp_weight>2000)
                    temp_weight-=2000;
            }
            else{
                if(prev->id != material2->id){ // add anywhere else. 
                    material2->next=prev->next;
                    prev->next = material2;
                    if(temp_weight<=2000)
                        temp_weight=0;
                    else if(temp_weight>2000)
                        temp_weight-=2000;
                }
            }
        }
    }
};


void Train::deleteFromWagon(char material, int weight){
    //FILL THIS FUNCTION ACCORDINGLY
    int cur_weight = weight;
    materialNode* loop_material = tail->material;
    wagonNode* loop_wagon = tail;
    wagonNode* new_wagon=head;
    int x;
    while(cur_weight != 0){
        int c=0;
        while(loop_material!=NULL){ //if a wagon has that material, returns its Id, otherwise returns the previous wagon's Id.
            if(loop_material->id == material){
                c++;
            }
            loop_material=loop_material->next;
        }
        if(c==1){
            x = loop_wagon -> wagonId;
        }
        else{
            x = loop_wagon -> wagonId - 1;
        }
        int b=x;
        new_wagon=head;
        while(x-1>0){  //goes to the wagon whose Id has been given.
            new_wagon=new_wagon->next;
            x--;
        }
        loop_material=new_wagon->material;
        while(loop_material!=NULL){
            if(loop_material->id == material && loop_material->weight >= weight){ //for example wagon has 500 kg and 300 kg is to be deleted.
                loop_material->weight -= weight;                                  //then this condition is called.
                cur_weight-=weight;
                break;
            }
            else if(loop_material->id == material && loop_material->weight < weight){ //this works for the other way around.
                weight -= loop_material->weight;
                cur_weight -= loop_material->weight;
                loop_material->weight =0;
                new_wagon=head;
                 while(b-2>0){  //a wagon is clear of that material now but still there is some to be deleted, the previous wagon is called.
                    new_wagon=new_wagon->next;
                    b--;
                }
                loop_material=new_wagon->material;
                loop_wagon=new_wagon;
                break;
            }
            loop_material=loop_material->next;
        }
    }
    new_wagon=head;
    loop_material = new_wagon->material;
    while(new_wagon!=NULL){ // If a material or a wagon is empty, this loop is to delete them.
        loop_material = new_wagon->material;
        while(loop_material!=NULL){
            if(loop_material->weight == 0){
                materialNode* prev_node = search(loop_material->id,new_wagon,2);
                if(prev_node == NULL){
                    new_wagon->material = loop_material->next;//deletes first material in a wagon.
                }
                else{
                    prev_node->next = loop_material->next;    //deletes other materials.

                }
                
            }
            loop_material=loop_material->next;
        }

        if(tail->material==NULL || tail->material->weight==0 ){
            int b= tail->wagonId-1;
            wagonNode* looper= head; //deletes wagons and sets tail again.
            while(b-1>0){
                looper=looper->next;
                b--;
            }
            looper->next=NULL;
            tail=looper;
            wagon_num--;
        }
        new_wagon=new_wagon->next;
    }
};


void Train::printWagon(){
    wagonNode* tempWagon = head;

    if(tempWagon == NULL){
            cout<<"Train is empty!!!"<<endl;
            return;
    }

    while(tempWagon != NULL){
        materialNode* tempMat = tempWagon->material;
        cout<<tempWagon->wagonId<<". Wagon:"<<endl; 
        while (tempMat != NULL){
            cout<<tempMat->id<<": "<<tempMat->weight<<"KG, "; 
            tempMat = tempMat->next;  
        }
        cout<<endl; 
        tempWagon = tempWagon->next;
    }
    cout<<endl;
}; 

/* @Author 
Student Name: Eren Yaşa
Student ID : 150200022
Date: 10.11.2021 */