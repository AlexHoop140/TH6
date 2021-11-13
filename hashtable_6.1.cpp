#include <iostream>
#define hashGroup 13

using namespace std;

typedef int dataType;

struct Node{
    dataType data;
    Node* pNext;
};

struct list{
    Node* pHead;
    Node* pTail;
};

// typedef list position;
// typedef position hashTable[hashGroup];

typedef list *hashTable;

void create_List(list &linkedlist){
    linkedlist.pHead = new Node();
    linkedlist.pHead->pNext = linkedlist.pTail = NULL;
}

void addHead(list &l, Node *new_ele){
    if(l.pHead->pNext == NULL){
        l.pHead->pNext = l.pTail = new_ele;
    }
    else{
        new_ele->pNext = l.pHead->pNext;
        l.pHead->pNext = new_ele;
    }
}

void addLast(list &l, Node *new_ele){
    if(l.pTail == NULL){
        l.pHead->pNext = new_ele;
        l.pTail = new_ele;
    }
    else{
        l.pTail->pNext = new_ele;
        new_ele->pNext = NULL;
        l.pTail = new_ele;
    }
}

void init_Table(hashTable &table){
    table = new list[hashGroup];
    for(int i = 0; i < hashGroup; i++){
        create_List(table[i]);
    }

    
}

int hashFunction(dataType x){
    return x % hashGroup;
}

int isMember(dataType x, hashTable &table){
    Node *p = table[hashFunction(x)].pHead;

    while(p->pNext != NULL){
        if(p->pNext->data == x)
            return 1;
        p = p->pNext;
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
    // int bucket;
    // Node *p;

    // if(!isMember(x, table)){
    //     bucket = hashFunction(x);
    //     p = table[bucket];
    //     table[bucket] = new Node();
    //     table[bucket]->data = x;
    //     table[bucket]->pNext = p;
    //     p->pNext = NULL;
    // }
    int bucket = hashFunction(x);
    if(isMember(x, table) == false){
        // cout << "ADD: " << x << endl;
        addLast(table[bucket], getNode(x));
    }
}

void deleteList(Node *position, list &l){
	Node *temp;
	if(position->pNext != NULL){
		temp = position->pNext;
		position->pNext = temp->pNext;
		delete temp;
	}
}

void deleteTable(hashTable &table){
    for(int i = 0; i < hashGroup; i++){
        deleteList(table[i].pHead, table[i]);
    }
}

void removeItem(dataType x, hashTable &table){
    int bucket;
    Node *p, *temp;
    bucket = hashFunction(x);
    if(table[bucket].pHead->pNext != NULL){
        if(table[bucket].pHead->pNext->data == x){
            deleteList(table[bucket].pHead->pNext, table[bucket]);
            cout << "Removed!" << endl;
        } else{
            Node *p = table[bucket].pHead;
		    while(p->pNext != NULL){
			    if(p->pNext->data == x){
				    deleteList(p, table[bucket]);
				    return;
			    }
			    p = p->pNext;
		    }

	        if(p == NULL)
	            cout << endl << "[ERROR] CANNOT FIND ELEMENT: " << x << endl;
	    }
    }else{
        cout << "[ERROR] Empty bucket!" << endl;
    }
}


void traverse(hashTable table){
    for(int i = 0; i < hashGroup; i++){
        cout << "Bucket " << i << ": ";
        Node *p = table[i].pHead->pNext;
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

    int n;
    cout << "How many element in this dictionary? ";
    cin >>  n;
    for(int i = 0; i < n; i++){
        dataType x;
        cout << "Type in element no." << i+1 << ": ";
        cin >> x;
        insertItem(x, HT);
    }
    

    traverse(HT);
    deleteTable(HT);
}

