#include <iostream>
#define hashGroup 7

using namespace std;

typedef int dataType;

struct Node{
    dataType data;
    Node* pNext;
};

typedef Node* position;
typedef position hashTable[hashGroup];

void init_Table(hashTable &table){
    for(int i = 0; i < hashGroup; i++){
        table[i] = NULL;
    }
}

int hashFunction(dataType x){
    return x % hashGroup;
}

int isMember(dataType x, hashTable &table){
    position p = table[hashFunction(x)];

    while(p != NULL){
        if(p->data == x)
            return 1;
    }
    return 0;
}

Node* getNode(dataType x){
    Node *n = new Node;
    if(n == NULL)
        return NULL;
    n->data = x;
    n->pNext = NULL;
    return n;
}

void insertItem(dataType x, hashTable &table){
    int bucket;
    position p;

    if(!isMember(x, table)){
        bucket = hashFunction(x);
        p = table[bucket];
        table[bucket] = new Node;
        table[bucket]->data = x;
        table[bucket]->pNext = p;
    }
}

void removeItem(dataType x, hashTable &table){
    int bucket;
    position p, temp;
    bucket = hashFunction(x);
    if(table[bucket] != NULL){
        if(table[bucket]->data == x){
            temp = table[bucket];
            table[bucket] = temp->pNext;
            delete temp;
            cout << "Removed!" << endl;
        } else{
            p = table[bucket];
            while(p->pNext->data != x && p->pNext != NULL){
                p = p->pNext;
            }
            if(p->pNext->data == x){
                temp = p->pNext;
                p->pNext = temp->pNext;
                delete temp;
                cout << "Removed!" << endl;
            } else {
                if(p->pNext == NULL)
                    cout << "Not found" << endl;
            }
        }
    }
}

void traverse(hashTable table){
    for(int i = 0; i < hashGroup; i++){
        cout << "Bucket " << i << ": ";
        position p = table[i];
        while(p != NULL){
            cout << p->data << " --> ";
            p = p->pNext;
        }
        cout << endl;
    }
}

int main(){
    hashTable HT;
    init_Table(HT);

    insertItem(1, HT);
    insertItem(8, HT);
    insertItem(27, HT);
    // insertItem(64, HT);
    // insertItem(125, HT);
    // insertItem(216, HT);
    // insertItem(343, HT);

    traverse(HT);
}

