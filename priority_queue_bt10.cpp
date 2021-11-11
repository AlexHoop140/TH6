#include <iostream>
#include <math.h>

using namespace std;

#define MaxLength 100

struct point{
    float x;
    float y;
};

typedef point elementType;
struct PriorityQueue
{
    elementType data[MaxLength];
    int Last; // so luong phan tu cua cay, vi tri phan tu cuoi cung cua HEAP
};

float p(elementType x){
    return sqrt(x.x*x.x + x.y*x.y);
}

void makeNullPriorityQueue(PriorityQueue &l){
    l.Last = 0;
}

void insertPriorityQueue(elementType x, PriorityQueue &l){
    elementType temp;
    if(l.Last > MaxLength - 1){
        cout << "Queue is full" << endl;
    }
    else {
        l.Last++;
        l.data[l.Last] = x;
        int i = l.Last;
        
        while ((i > 1) && (p(l.data[i]) < p(l.data[i/2]))){
            temp = l.data[i];
            l.data[i] = l.data[i/2];
            l.data[i/2] = temp;
            i = i / 2;
        }
    }
}

elementType deleteMin(PriorityQueue &l){
    int i, j;
    elementType temp;
    // elementType minimum = MaxLength;
    if(l.Last == 0){
        cout << "Empty queue!" << endl;
    }
    else{
        elementType minimum = l.data[1];
        l.data[1] = l.data[l.Last];
        l.Last--;
    

        i = 1;
        while(i <= l.Last / 2){
            if((p(l.data[2*i]) < p(l.data[2*i+1])) || (2*i == l.Last))
                j = 2 * i;
            else
                j = 2 * i + 1;

            if(p(l.data[i]) > p(l.data[j])){
                temp = l.data[i];
                l.data[i] = l.data[j];
                l.data[j] = temp;
                i = j;
            } 
            else 
                break;
        }
        return minimum;
    }

}

int main(){
    PriorityQueue l;
    makeNullPriorityQueue(l);
    int n;
    cout << "How many elements are there in this list? ";
    cin >> n;
    for(int i = 0; i < n; i++){
        cout << "\nPOINT: " << i + 1 << endl;
        elementType point;
        cout << "Type in x: ";
        cin >> point.x;
        cout << "Type in y: ";
        cin >> point.y;
        insertPriorityQueue(point, l);
    }
    

    while(l.Last > 0){
        elementType point2 = deleteMin(l);
        cout << "(" << point2.x << ", " << point2.y << ")   "; 
    }

}
