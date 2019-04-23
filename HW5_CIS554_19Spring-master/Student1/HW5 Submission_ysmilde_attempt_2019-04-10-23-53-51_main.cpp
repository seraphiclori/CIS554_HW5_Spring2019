//HW5 Due: April 7 (Sunday) at 11:59PM
//Yara Smilde
#include <iostream>
#include <memory>

using namespace std;

class node {
public:
    shared_ptr<node> east;
    shared_ptr<node> south;
    int value;
    node() {}
    node(int i) { value = i; }
};

class ring {
public:
    //Implement all functions described below
    //funciton operator[] can be invoked by other functions
    
    shared_ptr<node> head;
    int num_rows;
    int num_cols;
    ring() {}
    ring(int i, int j);//constructor
    //i rows and j cols
    //values from 0 to i*j-1
    //See the photo for ring structures.
    
    ~ring();//destructor; do as little work as possible
    ring(const ring &r); //copy constructor
    ring(ring &&r); //move constructor
    void operator=(ring &&r);//R-value operator=
    void operator=(const ring &r); //L-value operator=
    ring(const initializer_list<int> &V);//see the explanation in main function
    int & operator[](int a);
    int & operator[](pair<int, int> p); //first is row number and second is col number
    
    void DelCol(int i);//delete col i of *this
    ring Threetimes();
    //return a ring with the same dimenstion as *this, and the value of every node is three times of that of *this.
    
    friend ostream & operator<<(ostream &s, const ring &L);
};

ring::ring(int i, int j) { //i rows j columns
    head = make_shared<node>(0);
    //head = make_shared<node>(new node(0));
    shared_ptr<node> p1 = head;
    
    num_rows = i;
    num_cols = j;
    
    for (int k = 1; k < i*j; k++) {
        //shared_ptr<node> temp(new node(k));
        shared_ptr<node> temp = make_shared<node>(k);
        p1->east = temp;
        p1 = p1->east;
    }
    
    p1->east = head; //loop it back to start to make circle
    p1->south = head; //make south node of the last node to circle back also
    p1 = head;
    
    for (int k = 0; k < i*j - 1; k++) {
        shared_ptr<node> p2 = p1;
        for (int a = 0; a < i; a++) {
            p2 = p2->east; //to get the node its going to point down
            if (p2 == head)
                p2 = p2->east; //for the last nodes that have an extra node (?)
        }
        p1->south = p2;
        p1 = p2;
    }
}

//overload operator<<
ostream & operator<<(ostream &s, const ring &L) {
    int row = 0;
    shared_ptr<node> p1 = L.head;
    //	s << p1->value << " ";
    //	p1 = p1->east;
    
    while (p1->east != L.head) {
        s << p1->value << " ";
        p1 = p1->east;
        row++;
        if (row == L.num_rows) {
            s << "\n";
            row = 0;
        }
    }
    
    // p1 = p1->east;
    s << p1->value << " ";
    
    return s;
}

ring::~ring() { //destructor
    shared_ptr<node> p1 = head;
    shared_ptr<node> p2;
    
    for(int i = 0; i < num_rows; i++){
        p2 = p1->east;
        p1.reset();
        p1 = p2;
    }
    
    p1 = head;
    
    for(int i = 0; i < num_cols; i++){
        p2 = p1->south;
        p1.reset();
        p1 = p2;
    }
}

ring::ring(const ring &r){ //copy constructor
    head = r.head;
    
    shared_ptr<node> temp = this->head;
    
    for(int i = 0; i < num_cols; i++){
        
    }
    
}

ring::ring(ring &&r){ //move constructor
    head = r.head;
    r.head.reset();
    
    num_cols = r.num_cols;
    num_rows = r.num_rows;
    
    num_cols = 0;
    num_rows = 0;
}

//ring::void operator=(ring &&r){ //R-value operator=
//    
//}
//
//ring::void operator=(const ring &r){ //L-value operator=
//    
//}

ring::ring(const initializer_list<int> &V){ //first two numbers are num_rows and num_cols; followed by values of nodes of ring
    
    auto it1 = V.begin();
    num_rows = *it1;
    it1++;
    num_cols = *it1;
    it1++;
    
    head = make_shared<node>(*it1);
    //	head = make_shared<node>(new node(0));
    shared_ptr<node> p1 = head;
    
    it1++;
    
    for (int k = 1; k < num_rows*num_cols; k++) {
        //shared_ptr<node> temp(new node(k));
        shared_ptr<node> temp = make_shared<node>(*it1);
        p1->east = temp;
        p1 = p1->east;
        it1++;
    }
    
    p1->east = head; //loop it back to start to make circle
    p1->south = head; //make south node of the last node to circle back also
    p1 = head;
    
    for (int k = 0; k < num_rows*num_cols - 1; k++) {
        shared_ptr<node> p2 = p1;
        for (int a = 0; a < num_rows; a++) {
            p2 = p2->east; //to get the node its going to point down
            if (p2 == head)
                p2 = p2->east; //for the last nodes that have an extra node (?)
        }
        p1->south = p2;
        p1 = p2;
    }

}

int & ring::operator[](int a){
    shared_ptr<node> p = head;
    
    for(int i=0; i<a; i++){
        p = p->east;
    }
    
    return p->value;
}

int & ring::operator[](pair<int, int> p){
    shared_ptr<node> a = head;
    
    for(int e=0; e<p.second; e++){
        a = a->east;
    }
    
    for(int s=0; s<p.first; s++){
        a = a->south;
    }
    
    return a->value;
}

void ring::operator=(const ring &r) {
    head = r.head;
    num_rows = r.num_rows;
    num_cols = r.num_cols;
}

void ring::operator=(ring &&r) {
    head = r.head;
    r.head.reset();
    
    num_cols = r.num_cols;
    num_rows = r.num_rows;
    
    num_cols = 0;
    num_rows = 0;
}

void ring::DelCol(int i){
    shared_ptr<node> p = head;
    shared_ptr<node> q;
    
    //first get to col # -1
    for(int a=0; a<i-1; a++){
        p = p->east;
    }
    
    //connect south back to next node
    shared_ptr<node> s = p;
    for(int a=0; a<num_rows-1; a++){
        s = s->south;
    }
    s->south = p->east->east;
    
    //then, go through each node of the column and delete
    for(int a=0; a<num_rows; a++){
        shared_ptr<node> p1 = p->east;
        p->east = p1->east;
        p1.reset();
        //get to next row
        for(int b=0; b<num_cols; b++){
            p=p->east;
        }
        
    }
    
}

ring ring::Threetimes(){ //return a ring with the same dimenstion as *this, and the value of every node is three times of that of *this.
    
    shared_ptr<node> p = head;
    
    p->value = p->value * 3; //multiply value times 3 and replace value
    p = p->east;
    
    while (p != head) { //repeat for all values
        p->value = p->value * 3;
        p = p->east;
    }
    
    return *this;
    
}

int main() {
    
    ring R1(4, 6);//24 numbers from 0 to 23 will be initialized to nodes.
    cout << R1 << endl;
//    R1[14] = 1000;
//    R1[{2, 4}] = 2000;
//    cout << R1[14] << " " << R1[{2, 4}] << endl;
    R1.DelCol(2);
    cout << R1 << endl;
    //    cout << R1 << endl;
    //    R1.DelCol(4);
    //    cout << R1 << endl;
    //    R1.DelCol(0);
    //    cout << R1 << endl;
    //    shared_ptr<ring> p1 = make_shared<ring>(3, 5);
    //    cout << *p1 << endl;
//        p1.reset();
//    ring R2 = { 3, 5, 10,20,30,40,50, 100, 200, 300, 400, 500, 1000, 2000, 3000, 4000, 5000 };//
    //first two numbers are num_rows and num_cols; followed by values of nodes of ring
//    cout << R2 << endl;
    //    ring R3(R2);
    //    cout << R3 << endl;
    //    ring R4;
    //    R4 = R3;
    //    cout << R4 << endl;
    //    ring R5;
    //    R5 = R4.Threetimes();
    //    cout << R5 << endl;
    
//    ring R1(4, 6);
//    cout << R1 << endl;
    
    getchar();
    getchar();
    return 0;
}
