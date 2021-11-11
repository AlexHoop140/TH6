#include <iostream> 
#define size 11
#define DELETED -10000
#define EMPTY -11000

using namespace std;

typedef int elementType;
typedef elementType HashTable[size];

void init_Table(HashTable &table){
    for(int i = 0; i < size; i++){
        table[i] = EMPTY;
    }
}

int hashFunction(elementType x){
    return x % size;
}

int locate(HashTable table, elementType x){
    int initialIndex = hashFunction(x);
    int i = 0;
    while((i < size) && (table[(initialIndex + i*i) % size] != x) && (table[(initialIndex + i*i) % size] != EMPTY))
        i++;
    return (initialIndex + i*i) % size;
}

int locate1(HashTable table, elementType x){
    int initialIndex = hashFunction(x);
    int i = 0;
    while((i < size) && (table[(initialIndex + i*i) % size] != x) && (table[(initialIndex + i*i) % size] != EMPTY)
    && (table[(initialIndex + i*i) % size] != DELETED))
        i++;
    return (initialIndex + i*i) % size;
}

bool isMember(HashTable table, elementType x){
    return table[locate(table, x)] == x;
}

void insert_Table(HashTable &table, elementType data){
    if(table[locate(table, data)] != data){
        int bucket = locate1(table, data);
        if(table[bucket] == EMPTY || table[bucket] == DELETED){
            table[bucket] = data;
        }
    }else{
        cout << "[ERROR] TABLE IS FULL!" << endl;
    }
}

void delete_Table(HashTable &table, elementType data){
    int bucket = locate(table, data);
    if(table[bucket] == data){
        table[bucket] = DELETED;
    }
}

void print_Table(HashTable table){
    cout << "\n --- Print Table --- " << endl;
    for(int i = 0; i < size; i++){
        if(table[i] == DELETED)
            cout << "Bucket "<< i << ": " << "DELETED" << endl;
        else if(table[i] == EMPTY)
        	cout << "Bucket "<< i << ": " << "EMPTY" << endl;
        else
            cout << "Bucket "<< i << ": " << table[i] << endl;
    }
}

int main(){
    HashTable HT;
    init_Table(HT);
    insert_Table(HT, 1);
    insert_Table(HT, 8);
    insert_Table(HT, 27);
    insert_Table(HT, 64);
    insert_Table(HT, 125);
    insert_Table(HT, 216);
    insert_Table(HT, 343);

    print_Table(HT);

    delete_Table(HT, 125);
    delete_Table(HT, 343);

    print_Table(HT);

    insert_Table(HT, 12);
    insert_Table(HT, 432);
    print_Table(HT);
}

