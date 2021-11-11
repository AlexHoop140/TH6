#include <iostream> 
#define size 7
#define DELETED "== DEAD =="
#define EMPTY "== AVAILABLE =="

using namespace std;

typedef string elementType;
typedef elementType HashTable[size];

void init_Table(HashTable &table){
    for(int i = 0; i < size; i++){
        table[i] = EMPTY;
    }
}

int hashFunction(elementType x){
    int sum;
    for(int i = 0; i < x.length(); i++){
        sum = sum + (int)x[i];
    }
    return sum % size;
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
    cout << "--- Print Table --- " << endl;
    for(int i = 0; i < size; i++){
        if(table[i] == DELETED)
            cout << "Bucket "<< i << ": " << DELETED << endl;
        else
            cout << "Bucket "<< i << ": " << table[i] << endl;
    }
}

int main(){
    HashTable HT;
    init_Table(HT);
    insert_Table(HT, "Phuong");
    insert_Table(HT, "Trung");
    insert_Table(HT, "Le");
    insert_Table(HT, "HIHI");
    insert_Table(HT, "ANHONHASEO");
    insert_Table(HT, "facebook");
    insert_Table(HT, "gooogle");
	print_Table(HT);

    delete_Table(HT, "gooogle");
    delete_Table(HT, "HIHI");
	print_Table(HT);

    insert_Table(HT, "unneeee");
    // insert_Table(HT, "satoshi");
    insert_Table(HT, "moas");
    print_Table(HT);
}

