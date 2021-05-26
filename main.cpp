
#include <bits/stdc++.h>
#include <chrono>
using namespace std;
// Structure for nodes in fibonaci and binomial
struct node{
    int data;
    int orders;
    int index;
    struct node *child;
    struct node *right;
    struct node *left;
    struct node *parent;
};
// Main structure of binomial
struct binomial {
    vector <node *> n_add;
    vector < node *> order;
    
    struct node * min;

};
// Main structure of fibonaci
struct fibonaci {
    vector <node *> n_add;
    vector <node *> order;
    vector <bool> marker;
    struct node *min;
    struct node *header;
};
// Initialisation function for fibonaci
void create_fibonaci(struct fibonaci **head,int n){
    for(int i=0; i <= ceil(log2(n))+1; i++){
        (*head)->order.push_back(NULL);
        
    }

    for(int i=0; i <n ; i++){
        (*head)->n_add.push_back(NULL);
        (*head)->marker.push_back(false);
    }
    
    (*head)->min=NULL;
    (*head)->min=NULL;


}
// Function to add elements in fibonaci heap
void add_fibonacci(struct fibonaci **head,int n,int indexe){
    struct node *temp;
    temp=(node *)malloc(sizeof(node));
    temp->data=n;
    temp->parent=NULL;
    temp->child=NULL;
    temp->left=NULL;
    temp->index=indexe;
    temp->orders=0;
    if((*head)->min==NULL){
        (*head)->min=temp;
    }
    else{
    if(temp->data<(*head)->min->data){
        (*head)->min=temp;
    }
    else if(temp->data==(*head)->min->data){
        if(temp->index < (*head)->min->index){
            (*head)->min=temp;
        }
    }
    }
    (*head)->n_add[indexe]=temp;
    if((*head)->header==NULL){
        temp->left=NULL;
        temp->right=NULL;
        (*head)->header=temp;
    }
    else{
    temp->right=(*head)->header;
    (*head)->header->left=temp;
    (*head)->header=temp;
    }
}

// Functions to extract min from fibonaci heap

 pair <int,int> extract_fibonaci(struct fibonaci **head){
    struct node *temp,*temp1,*temp2;
    int hehe;
    hehe=(*head)->min->data;
    (*head)->min->data=999999;
    temp1=(*head)->min;
    if((*head)->header==temp1){
        (*head)->header=temp1->right;
        if(temp1->right!=NULL){
            temp1->right->left==NULL;
            temp1->right=NULL;
        }
    }
    else{
        if(temp1->left!=NULL)
        temp1->left->right=temp1->right;
        if(temp1->right!=NULL){
            temp1->right->left==temp1->left;
            temp1->right=NULL;
        }
        temp1->left=NULL;
    }
    int flag=0;
    temp=(*head)->header;

    // Removing subtrees of min.. and consolidating them in their respective places

    while(temp!=NULL){
        temp->parent=NULL;
        temp->left=NULL;
        temp2=temp->right;
        temp->right=NULL;
        if(temp2==NULL){
            if(flag==0){
                temp2=temp->child;
                flag=1;
            }
        }
        
        while(1){
            if(((*head)->order[temp->orders])!=NULL){
                if((*head)->order[temp->orders]->data<temp->data){
                    temp->parent=(*head)->order[temp->orders];
                    temp->right=(*head)->order[temp->orders]->child;
                    (*head)->order[temp->orders]->child=temp;
                    if(temp->right!=NULL){
                        temp->right->left=temp;
                    }
                    temp->parent->orders++;
                    (*head)->order[temp->orders]=NULL;
                    temp=temp->parent;
                }
                else if((*head)->order[temp->orders]->data>temp->data){
                    
                    (*head)->order[temp->orders]->parent=temp;
                    (*head)->order[temp->orders]->right=temp->child;
                    temp->child=(*head)->order[temp->orders];
                    if(temp->child->right!=NULL){
                    temp->child->right->left=temp->child;
                    temp->child->right->parent=temp;}
                    temp->orders++;
                    (*head)->order[temp->orders-1]=NULL;
                }
                else{
                    if((*head)->order[temp->orders]->index>temp->index){
                    (*head)->order[temp->orders]->parent=temp;
                    (*head)->order[temp->orders]->right=temp->child;
                    temp->child=(*head)->order[temp->orders];
                    if(temp->child->right!=NULL){
                    temp->child->right->left=temp->child;
                    temp->child->right->parent=temp;}
                    temp->orders++;
                    (*head)->order[temp->orders-1]=NULL;
                    }
                    else {
                    temp->parent=(*head)->order[temp->orders];
                    temp->right=(*head)->order[temp->orders]->child;
                    (*head)->order[temp->orders]->child=temp;
                    if(temp->right!=NULL){
                        temp->right->left=temp;
                    }
                    temp->parent->orders++;
                    (*head)->order[temp->orders]=NULL;
                    temp=temp->parent;
                    }
                }
            }
            else{
                (*head)->order[temp->orders]=temp;
                temp=temp2;
                break;
            }
        }
    }
    temp=NULL;
    (*head)->header=NULL;

    // Merging subtrees of same ranks.

    for(int i=0;i<(*head)->order.size();i++){
        if((*head)->order[i]!=NULL){
            if((*head)->header==NULL){
                (*head)->min=(*head)->order[i];
                (*head)->header=(*head)->order[i];
                (*head)->header->left=NULL;
                (*head)->header->parent=NULL;
            }
            else{
                temp=(*head)->order[i];
                temp->left=NULL;
                temp->right=(*head)->header;
                (*head)->header=temp;
                temp->right->left=NULL;
                temp->parent=NULL;
                if((*head)->min->data>temp->data){
                    (*head)->min=temp;
                }
                else if((*head)->min->data==temp->data){
                    if((*head)->min->index>temp->index){
                        (*head)->min=temp;
                    }
                }
            }
            (*head)->order[i]=NULL;
        }
    }

    return make_pair(hehe,temp1->index); 
}

// Funtion to initialize binomial heap

void create_binomial(struct binomial **head, int n){
    for(int i=0; i <= ceil(log2(n)); i++){
        (*head)->order.push_back(NULL);
        
    }
    for(int i=0; i <n ; i++){
        (*head)->n_add.push_back(NULL);
    }
    (*head)->min=NULL;

}

// funtion to add elements in binomial heap

void add_binomial(struct binomial **head, int n,int indexe){
    node *temp;
    temp=(node*)malloc(sizeof(node));
    temp->data=n;
    temp->parent=NULL;
    temp->child=NULL;
    temp->right=NULL;
    temp->left=NULL;
    temp->index=indexe;
    (*head)->n_add[indexe]=temp;
    temp->orders=0;
    if((*head)->min==NULL){
        (*head)->min=temp;
    }

    // consolidating the elements in binomial heap

    while(1){
        if(((*head)->order[temp->orders])!=NULL){
            if((*head)->order[temp->orders]->data<temp->data){
                temp->parent=(*head)->order[temp->orders];
                temp->right=(*head)->order[temp->orders]->child;
                (*head)->order[temp->orders]->child=temp;
                if(temp->right!=NULL){
                    temp->right->left=temp;
                }
                temp->parent->orders++;
                (*head)->order[temp->orders]=NULL;
                temp=temp->parent;
            }
            else if((*head)->order[temp->orders]->data>temp->data){
                if(((*head)->min)==(*head)->order[temp->orders]){
                    (*head)->min=temp;
                }
                (*head)->order[temp->orders]->parent=temp;
                (*head)->order[temp->orders]->right=temp->child;
                temp->child=(*head)->order[temp->orders];
                if(temp->child->right!=NULL){
                temp->child->right->left=temp->child;
                temp->child->right->parent=temp;}
                temp->orders++;
                (*head)->order[temp->orders-1]=NULL;
                
            }

            else{
                if((*head)->order[temp->orders]->index>temp->index){
                if(((*head)->min)==(*head)->order[temp->orders]){
                    (*head)->min=temp;
                }
                (*head)->order[temp->orders]->parent=temp;
                (*head)->order[temp->orders]->right=temp->child;
                temp->child=(*head)->order[temp->orders];
                if(temp->child->right!=NULL){
                temp->child->right->left=temp->child;
                temp->child->right->parent=temp;}
                temp->orders++;
                (*head)->order[temp->orders-1]=NULL;  
                }
                else {
                temp->parent=(*head)->order[temp->orders];
                temp->right=(*head)->order[temp->orders]->child;
                (*head)->order[temp->orders]->child=temp;
                if(temp->right!=NULL){
                    temp->right->left=temp;
                }
                temp->parent->orders++;
                (*head)->order[temp->orders]=NULL;
                temp=temp->parent;

                }
            }
        }
        else{
            (*head)->order[temp->orders]=temp;
            if((*head)->min->data>temp->data){
                (*head)->min=temp;
            }
            else if((*head)->min->data==temp->data){
                if((*head)->min->index>temp->index){
                    (*head)->min=temp;
                }
            }
            break;
        }

    }
    

}

// Function to extract elements from binomial heap

pair <int,int> extract_binomial(struct binomial **head){
    struct node *temp,*temp1,*temp2;
    temp1=(*head)->min;
    (*head)->order[temp1->orders]=NULL;
    int nice=999999;
    if(temp1->child==NULL){
        for(int i=0;i<(*head)->order.size();i++){
            if((*head)->order[i]==NULL){
                continue;
            }
            else{
                if((*head)->order[i]->data<nice){
                    (*head)->min=(*head)->order[i];
                    nice=(*head)->min->data;;                }
            }
        }
        return make_pair(temp1->data,temp1->index);
    }

    // If there are children then those have to be ciosolidated in the heap according to their ranks
    else{
        
        temp=temp1->child;
        temp1->child=NULL;
        while(temp!=NULL){
            temp->parent=NULL;
            temp->left=NULL;
            temp2=temp->right;
            temp->right=NULL;
            while(1){
                if(((*head)->order[temp->orders])!=NULL){
                    if((*head)->order[temp->orders]->data<temp->data){
                        temp->parent=(*head)->order[temp->orders];
                        temp->right=(*head)->order[temp->orders]->child;
                        (*head)->order[temp->orders]->child=temp;
                        if(temp->right!=NULL){
                            temp->right->left=temp;
                        }
                        temp->parent->orders++;
                        
                        (*head)->order[temp->orders]=NULL;
                        temp=temp->parent;
                    }
                    else if((*head)->order[temp->orders]->data>temp->data){
                        
                        (*head)->order[temp->orders]->parent=temp;
                        (*head)->order[temp->orders]->right=temp->child;
                        temp->child=(*head)->order[temp->orders];
                        if(temp->child->right!=NULL){
                        temp->child->right->left=temp->child;
                        temp->child->right->parent=temp;}
                        temp->orders++;
                        (*head)->order[temp->orders-1]=NULL;
                    }
                    else{
                        if((*head)->order[temp->orders]->index>temp->index){
                        (*head)->order[temp->orders]->parent=temp;
                        (*head)->order[temp->orders]->right=temp->child;
                        temp->child=(*head)->order[temp->orders];
                        if(temp->child->right!=NULL){
                        temp->child->right->left=temp->child;
                        temp->child->right->parent=temp;}
                        temp->orders++;
                        (*head)->order[temp->orders-1]=NULL;
                        }
                        else {
                        temp->parent=(*head)->order[temp->orders];
                        temp->right=(*head)->order[temp->orders]->child;
                        (*head)->order[temp->orders]->child=temp;
                        if(temp->right!=NULL){
                            temp->right->left=temp;
                        }
                        temp->parent->orders++;
                        (*head)->order[temp->orders]=NULL;
                        temp=temp->parent;

                        }
                    }
                }
                else{
                    (*head)->order[temp->orders]=temp;
                    temp=temp2;
                    break;
                }
            }

        }
            
    }
    for(int i=0;i<(*head)->order.size();i++){
            if((*head)->order[i]==NULL){
                continue;
            }
            else{
                if((*head)->order[i]->data<nice){
                    (*head)->min=(*head)->order[i];
                    nice=(*head)->min->data;;                }
            }
        }
    return make_pair(temp1->data,temp1->index);
}

// Funtion to add elements in binary heap

void add_heap(vector <pair <int,int>> &heaps,pair <int,int> test){
    heaps.push_back(test);
    int key=heaps.size()-1;
    pair <int,int> temp;
    while(key!=0){
        if(heaps[(key-1)/2].first>heaps[key].first){
            temp=heaps[key];
            heaps[key]=heaps[(key-1)/2];
            heaps[(key-1)/2]=temp;
            key=(key-1)/2;
        }
        else if(heaps[(key-1)/2].first==heaps[key].first){
            if(heaps[(key-1)/2].second>heaps[key].second){
                temp=heaps[key];
                heaps[key]=heaps[(key-1)/2];
                heaps[(key-1)/2]=temp;
                key=(key-1)/2;
            }
            else{
                break;
            }
        }
        else{
            break;
        }
    }


}

// Function to extract min from binary heap

pair <int,int> extract_min(vector <pair <int,int>> &heaps){
    pair <int,int> temp,temper;
    
    int temp2;
    temp=heaps[0];
    pair <int,int> temp1=heaps[heaps.size()-1];
    heaps.pop_back();
    heaps[0]=temp1;
    temp2=heaps.size()-1;
    int key=0;
    while(1){

        if((2*key+1)>temp2) break;

        else if((2*key+2)>temp2){


            if(heaps[2*key+1].first<heaps[key].first){
                temper=heaps[2*key+1];
                heaps[2*key+1]=heaps[key];
                heaps[key]=temper;
                key=2*key+1;
            }


            else if(heaps[2*key+1].first==heaps[key].first){

                if(heaps[2*key+1].second<heaps[key].second){
                    temper=heaps[2*key+1];
                    heaps[2*key+1]=heaps[key];
                    heaps[key]=temper;
                    key=2*key+1;
                }


                else{

                    break;
                }

            }


            else{

                break;

            }
        }


        else{


            if(heaps[2*key+1].first<heaps[2*key+2].first){

                if(heaps[2*key+1].first<heaps[key].first){

                    temper=heaps[2*key+1];
                    heaps[2*key+1]=heaps[key];
                    heaps[key]=temper;
                    key=2*key+1;

                }

                else if(heaps[2*key+1].first==heaps[key].first){

                    if(heaps[2*key+1].second < heaps[key].second){

                    temper=heaps[2*key+1];
                    heaps[2*key+1]=heaps[key];
                    heaps[key]=temper;
                    key=2*key+1;

                    }

                    else{

                        break;

                    }

                }
                else{

                    break;

                }
            }
            else if(heaps[2*key+1].first>heaps[2*key+2].first){

                if(heaps[2*key+2].first<heaps[key].first){
                    temper=heaps[2*key+2];
                    heaps[2*key+2]=heaps[key];
                    heaps[key]=temper;
                    key=2*key+2;

                }

                else if(heaps[2*key+2].first==heaps[key].first){

                    if(heaps[2*key+2].second < heaps[key].second){
                    temper=heaps[2*key+2];
                    heaps[2*key+2]=heaps[key];
                    heaps[key]=temper;
                    key=2*key+2;

                    }
                    else{


                        break;

                    }
                }

                else{

                    break;

                }

            }
            else{

                if(heaps[2*key+1].second < heaps[2*key+2].second){

                    if(heaps[2*key+1].first<heaps[key].first){

                        temper=heaps[2*key+1];
                        heaps[2*key+1]=heaps[key];
                        heaps[key]=temper;
                        key=2*key+1;

                    }
                    else if(heaps[2*key+1].first==heaps[key].first){

                        if(heaps[2*key+1].second < heaps[key].second){

                        temper=heaps[2*key+1];
                        heaps[2*key+1]=heaps[key];
                        heaps[key]=temper;
                        key=2*key+1;

                        }
                        else{

                            break;

                        }


                    }
                    else{
                        break;
                    }
                }
                else if(heaps[2*key+1].second > heaps[2*key+2].second){

                    if(heaps[2*key+2].first<heaps[key].first){

                        temper=heaps[2*key+2];
                        heaps[2*key+2]=heaps[key];
                        heaps[key]=temper;
                        key=2*key+2;

                    }

                    else if(heaps[2*key+2].first==heaps[key].first){

                        if(heaps[2*key+2].second < heaps[key].second){

                        temper=heaps[2*key+2];
                        heaps[2*key+2]=heaps[key];
                        heaps[key]=temper;
                        key=2*key+2;

                        }
                        else{
                            break;
                        }
                    }

                    else{
                        break;
                    }
                }

                else{
                    break;
                }

            }
        }
    }
    return temp;
    

}


// Decrease key for fibonaci

void decrease_fibonaci(struct fibonaci **head,int news,int indexe){
    struct node *temp,*temp1;
    temp=(*head)->n_add[indexe];
    temp->data=news;
    while(temp!=NULL){
        if(temp->parent==NULL){
            if(temp->data<(*head)->min->data){
                (*head)->min=temp;
            }
            else if(temp->data==(*head)->min->data){
                if((*head)->min->index>temp->index){
                    (*head)->min=temp;
                }
            }
            break;
        }
        else if(temp->parent->parent==NULL){

            if(temp->left==NULL){
            temp->parent->child=temp->right;}
            else{
                temp->left->right=temp->right;
            }
            if(temp->right!=NULL)
            temp->right->left=temp->left;
            temp->parent=NULL;
            temp->right=NULL;
            temp->left=NULL;
            temp->right=(*head)->header;
            if(temp->right!=NULL)
            temp->right->left=temp;
            (*head)->header=temp;
            if(temp->data<(*head)->min->data){
                (*head)->min=temp;
            }
            else if(temp->data==(*head)->min->data){
                if((*head)->min->index>temp->index){
                    (*head)->min=temp;
                }
            }
            temp=NULL;
        }
        else{
            temp1=temp->parent;
            if(temp->left==NULL){
            temp->parent->child=temp->right;}
            else{
                temp->left->right=temp->right;
            }
            if(temp->right!=NULL)
            temp->right->left=temp->left;
            temp->parent=NULL;
            temp->right=NULL;
            temp->left=NULL;
            temp->right=(*head)->header;
            if(temp->right!=NULL)
            temp->right->left=temp;
            (*head)->header=temp;
            if(temp->data<(*head)->min->data){
                (*head)->min=temp;
            }
            else if(temp->data==(*head)->min->data){
                if((*head)->min->index>temp->index){
                    (*head)->min=temp;
                }
            }
            if((*head)->marker[temp1->index]){
                temp=temp1;
            }
            else{
                (*head)->marker[temp1->index]=true;
                temp=NULL;
            }
            
        }
    }
}


// Decrease key for binomial

void decrease_binomial(struct binomial **head, int news,int indexe){
    struct node * temp, * temp1;
    temp=(*head)->n_add[indexe];
    temp->data=news;
    int temp3;
    while(temp!=NULL){
        if(temp->parent==NULL){
            (*head)->order[temp->orders]=temp;
            break;
        }
        else if(temp->parent->data<temp->data){
            break;
        }
        else if(temp->parent->data>temp->data){
            (*head)->n_add[temp->index]=temp->parent;
            (*head)->n_add[temp->parent->index]=temp;
            temp3=temp->data;
            temp->data=temp->parent->data;
            temp->parent->data=temp3;
            temp3=temp->index;
            temp->index=temp->parent->index;
            temp->parent->index=temp3;
            temp=temp->parent;
            

            
        }
        else{
            if(temp->parent->index>temp->index){
            (*head)->n_add[temp->index]=temp->parent;
            (*head)->n_add[temp->parent->index]=temp;
            temp3=temp->data;
            temp->data=temp->parent->data;
            temp->parent->data=temp3;
            temp3=temp->index;
            temp->index=temp->parent->index;
            temp->parent->index=temp3;
            temp=temp->parent;
            }
            else{
                break;
            }
        }
    }

    int nice=999999;
    for(int i=0;i<(*head)->order.size();i++){
        if((*head)->order[i]==NULL){
            continue;
        }
        else{
            if((*head)->order[i]->data<nice){
                (*head)->min=(*head)->order[i];
                nice=(*head)->min->data;
            }
        }
    }
}
// Decrease key for binary heap

void decrease_key(vector <pair <int,int>> &heaps,int old,int news,int indexe){
    int key;
    pair<int,int> temp;
    for(int i=0; i<heaps.size(); i++){
        if(heaps[i].first==old && heaps[i].second==indexe){
            key=i;
            break;
        }
    }
    heaps[key].first=news;
    while(key!=0){
        if(heaps[(key-1)/2].first>heaps[key].first){
            temp=heaps[key];
            heaps[key]=heaps[(key-1)/2];
            heaps[(key-1)/2]=temp;
            key=(key-1)/2;
        }
        else if(heaps[(key-1)/2].first==heaps[key].first){
            if(heaps[(key-1)/2].second>heaps[key].second){
                temp=heaps[key];
                heaps[key]=heaps[(key-1)/2];
                heaps[(key-1)/2]=temp;
                key=(key-1)/2;

            }
            else{
                break;
            }
        }
        else{
            break;
        }
    }


}


// Dijkstra for binary heap

int dijkstra_binary(vector <vector<int>> mat, int s, vector <int> &ans){
    vector <pair <int,int>> heap;
    for(int i=0;i<mat[s-1].size();i++){
        if(i!=(s-1)){
        ans[i]=mat[s-1][i];

        add_heap(heap,make_pair(ans[i],i));}
        else{
            ans[i]=0;
        }
        if(ans[i]<0) return -1;
    }
    ans[s-1]=0;
    int min=999999;
    int key=-1;
    pair <int,int> nicer;
    for(int i=0;i<(mat.size()-1);i++){
        nicer=extract_min(heap);
        min=nicer.first;
        key=nicer.second;
        if(min==999999) continue;
        for(int j=0;j<mat[key].size();j++){
            if(mat[key][j]<0) return -1;
            if(ans[j]>(ans[key]+mat[key][j])){
                decrease_key(heap,ans[j],ans[key]+mat[key][j],j);
                ans[j]=ans[key]+mat[key][j];
            }
        }

    }
    return 0;
}


//Dijkstra for binomial heap
int dijkstra_binomial(vector <vector<int>> mat, int s, vector <int> &ans){
    struct binomial *hola;
    hola=new binomial();
    create_binomial(&hola,ans.size());
    for(int i=0;i<mat[s-1].size();i++){
        if(i!=(s-1)){
        ans[i]=mat[s-1][i];

        add_binomial(&hola,ans[i],i);
        }
        else{
            ans[i]=0;
        }
        if(ans[i]<0) return -1;
    }
    ans[s-1]=0;
    int min=999999;
    int key=-1;
    pair <int,int> nicer;
    for(int i=0;i<(mat.size()-1);i++){
        nicer=extract_binomial(&hola);
        min=nicer.first;
        key=nicer.second;
        if(min==999999) continue;
        for(int j=0;j<mat[key].size();j++){
            if(mat[key][j]<0) return -1;
            if(ans[j]>(ans[key]+mat[key][j])){
                decrease_binomial(&hola,ans[key]+mat[key][j],j);
                ans[j]=ans[key]+mat[key][j];
            }
        }

    }
    return 0;
}


// Dijkstra for fibonaci heap 

int dijkstra_fibonaci(vector <vector<int>> mat, int s, vector <int> &ans){
    struct fibonaci *hola;
    hola=new fibonaci();
    create_fibonaci(&hola,ans.size());
    for(int i=0;i<mat[s-1].size();i++){
        if(i!=(s-1)){
        ans[i]=mat[s-1][i];

        add_fibonacci(&hola,ans[i],i);
        }
        else{
            ans[i]=0;
        }
        if(ans[i]<0) return -1;
    }
    ans[s-1]=0;
    int min=999999;
    int key=-1;
    pair <int,int> nicer;
    for(int i=0;i<(mat.size()-1);i++){
        nicer=extract_fibonaci(&hola);
        min=nicer.first;
        key=nicer.second;
        if(min==999999) continue;
        for(int j=0;j<mat[key].size();j++){
            if(mat[key][j]<0) return -1;
            if(ans[j]>(ans[key]+mat[key][j])){
                decrease_fibonaci(&hola,ans[key]+mat[key][j],j);
                ans[j]=ans[key]+mat[key][j];
            }
        }

    }
    return 0;
}

// Dijkstra for array based implementation 
int dijkstra_array(vector <vector<int>> mat, int s, vector <int> &ans){
    for(int i=0;i<mat[s-1].size();i++){
        
        ans[i]=mat[s-1][i];
        if(ans[i]<0) return -1;
    }
    ans[s-1]=0;
    vector <bool> disc(mat.size(),false);
    disc[s-1]=true;
    
    int min=999999;
    int key=-1;
    for(int i=0;i<(mat.size()-1);i++){
        min=999999;
        for(int j=0;j<ans.size();j++){
            if(disc[j]==true) continue;
            else{
                if(ans[j]<=min){
                    min=ans[j];
                    key=j;
                }
            }
        }
        if(min==999999) continue;
        for(int j=0;j<mat[key].size();j++){
            if(mat[key][j]<0) return -1;
            if(ans[j]>(ans[key]+mat[key][j])){
                ans[j]=ans[key]+mat[key][j];
            }
        }
        disc[key]=true;

    }
    return 0;
}
// Bellman ford for johnson algortihm

int belman(vector <vector <int>> lis,vector <vector <int>> mat, int s, vector <int> &ans){
    vector <int> container;
    int iter=0;
    int r=0,rs=0;
    int temp;
    container.push_back(s);
    vector <int> relax(lis.size(),0);
    vector <bool> disc(lis.size(),0);
    disc[s]=true;
    while(iter!=container.size()){
        temp=container[iter];
        iter++;
        disc[temp]=false;
        for(int i=0; i< lis[temp].size();i++){
            r++;
            if(ans[lis[temp][i]]>mat[temp-1][lis[temp][i]-1]+ans[temp]){
                rs++;
                ans[lis[temp][i]]=mat[temp-1][lis[temp][i]-1]+ans[temp];
                if(disc[lis[temp][i]]==false){
                container.push_back(lis[temp][i]);
                disc[lis[temp][i]]=true;}
                relax[lis[temp][i]]++;
                if(relax[lis[temp][i]]==lis.size()-1) return -1;
            }
            
        }

    }
    
    return 0;
}

int main(int argc,char ** argv){
    int testcases;
    cin >> testcases;
    vector <long double> timer;
    while(testcases--){
        int n,d;
        cin >> n >> d;
        vector < vector <int> > mat;
        for(int i=0;i<n; i++){
            vector <int> row;
            int temp;
            for (int j=0;j<n;j++){
                cin >> temp;
                row.push_back(temp);
            }
            mat.push_back(row);
        }
        vector < vector <int> > lis;
        for(int i=0;i<=n;i++){
            vector <int> sub;
            lis.push_back(sub);
            
        }
                    
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(mat[i][j]!=0 & mat[i][j]!=999999){
                    lis[i+1].push_back(j+1);
                }
            }
        }
        for(int i=0; i<n;i++){
            mat[i].push_back(999999);
        }
        vector <int> temp(n+1,0);
        mat.push_back(temp);
        vector <int> temper;
        for(int i=0;i<  n;i++){
            temper.push_back(i+1);
        }
        lis.push_back(temper);
        for(int i=0; i<=n;i++){
            mat[i][i]=999999;
        }
        chrono::system_clock::time_point start = chrono::high_resolution_clock::now();
        int vers=0;
        int s=0;
        s=n+1;
        vector <int> ans(lis.size(),999999);
        ans[s]=0;
        vers=belman(lis,mat,s,ans);
        if(vers==-1){
            cout << "-1" << endl;
        }
        
        else{
            mat.pop_back();
            lis.pop_back();
            for(int i=0; i < n ; i++){
                mat[i].pop_back();
                for(int j=0; j<n; j++){
                    if(j==i) continue;
                    else{
                        if(mat[i][j]==999999) continue;
                        else{
                            mat[i][j]=mat[i][j]+ans[i+1]-ans[j+1];
                        }
                    }

                }
            }
            for(int i=0; i<n;i++){
                vector<int> ansi(n,999999);
                if(argc>1 && argv[1][0]=='1') vers=dijkstra_array(mat,i+1,ansi);
                else if(argc>1 && argv[1][0]=='2') vers=dijkstra_binary(mat,i+1,ansi);
                else if(argc>1 && argv[1][0]=='3') vers=dijkstra_binomial(mat,i+1,ansi);
                else vers=dijkstra_fibonaci(mat,i+1,ansi);
                if(vers!=0){
                    cout << vers << endl;
                }
                else{
                for(int j=0;j<ansi.size();j++){
                    if(j!=i) {if(ansi[j]==999999) cout << ansi[j] << " ";
                    else cout << ansi[j] - ans[i+1] + ans[j+1] << " ";}
                    else cout << ansi[j] << " ";
                
                }
                cout << endl;
                }
            }


        }
        chrono::system_clock::time_point end = chrono::high_resolution_clock::now();
        timer.push_back(chrono::duration_cast<chrono::nanoseconds>(end - start).count());

    }
    for(int i=0;i < timer.size();i++){
        cout << timer[i]/1e9 << " ";
    }
    cout << endl;
    

}