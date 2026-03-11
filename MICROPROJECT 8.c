#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
    int id;
    char name[50];
    char block[50];
    int value;
    struct Node *left,*right;
};

struct Node* create(int id,char name[],char block[],int value){
    struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
    newNode->id=id;
    strcpy(newNode->name,name);
    strcpy(newNode->block,block);
    newNode->value=value;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}

struct Node* insert(struct Node* root,int id,char name[],char block[],int value){
    if(root==NULL)
        return create(id,name,block,value);

    if(id<root->id)
        root->left=insert(root->left,id,name,block,value);
    else if(id>root->id)
        root->right=insert(root->right,id,name,block,value);

    return root;
}

struct Node* search(struct Node* root,int id){
    if(root==NULL || root->id==id)
        return root;

    if(id<root->id)
        return search(root->left,id);
    else
        return search(root->right,id);
}

struct Node* findMin(struct Node* root){
    while(root->left!=NULL)
        root=root->left;
    return root;
}

struct Node* deleteNode(struct Node* root,int id){

    if(root==NULL)
        return root;

    if(id<root->id)
        root->left=deleteNode(root->left,id);

    else if(id>root->id)
        root->right=deleteNode(root->right,id);

    else{

        if(root->left==NULL && root->right==NULL){
            free(root);
            return NULL;
        }

        else if(root->left==NULL){
            struct Node* temp=root->right;
            free(root);
            return temp;
        }

        else if(root->right==NULL){
            struct Node* temp=root->left;
            free(root);
            return temp;
        }

        struct Node* temp=findMin(root->right);

        root->id=temp->id;
        strcpy(root->name,temp->name);
        strcpy(root->block,temp->block);
        root->value=temp->value;

        root->right=deleteNode(root->right,temp->id);
    }

    return root;
}

void inorder(struct Node* root){
    if(root!=NULL){
        inorder(root->left);
        printf("ID:%d Name:%s Block:%s Value:%d\n",
        root->id,root->name,root->block,root->value);
        inorder(root->right);
    }
}

void preorder(struct Node* root){
    if(root!=NULL){
        printf("ID:%d Name:%s Block:%s Value:%d\n",
        root->id,root->name,root->block,root->value);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct Node* root){
    if(root!=NULL){
        postorder(root->left);
        postorder(root->right);
        printf("ID:%d Name:%s Block:%s Value:%d\n",
        root->id,root->name,root->block,root->value);
    }
}

struct Node* predecessor(struct Node* root){
    root=root->left;
    while(root->right!=NULL)
        root=root->right;
    return root;
}

struct Node* successor(struct Node* root){
    root=root->right;
    while(root->left!=NULL)
        root=root->left;
    return root;
}

void rangeQuery(struct Node* root,int low,int high){

    if(root==NULL)
        return;

    if(root->value>low)
        rangeQuery(root->left,low,high);

    if(root->value>=low && root->value<=high)
        printf("ID:%d Name:%s Value:%d\n",
        root->id,root->name,root->value);

    if(root->value<high)
        rangeQuery(root->right,low,high);
}

int main(){

    struct Node* root=NULL;
    int choice,id,value,low,high;
    char name[50],block[50];

    while(1){

        printf("\n1 Insert Asset");
        printf("\n2 Search Asset");
        printf("\n3 Delete Asset");
        printf("\n4 Inorder Display");
        printf("\n5 Preorder Display");
        printf("\n6 Postorder Display");
        printf("\n7 Range Query");
        printf("\n8 Exit\n");

        printf("\nEnter Choice: ");
        scanf("%d",&choice);

        switch(choice){

            case 1:
            printf("Enter ID Name Block Value: ");
            scanf("%d %s %s %d",&id,name,block,&value);
            root=insert(root,id,name,block,value);
            break;

            case 2:{
            printf("Enter ID: ");
            scanf("%d",&id);

            struct Node* s=search(root,id);

            if(s)
            printf("Found: %s %s %d\n",s->name,s->block,s->value);
            else
            printf("Not Found\n");
            break;
            }

            case 3:
            printf("Enter ID to delete: ");
            scanf("%d",&id);
            root=deleteNode(root,id);
            break;

            case 4:
            inorder(root);
            break;

            case 5:
            preorder(root);
            break;

            case 6:
            postorder(root);
            break;

            case 7:
            printf("Enter value range: ");
            scanf("%d %d",&low,&high);
            rangeQuery(root,low,high);
            break;

            case 8:
            exit(0);

            default:
            printf("Invalid choice\n");
        }
    }
}

