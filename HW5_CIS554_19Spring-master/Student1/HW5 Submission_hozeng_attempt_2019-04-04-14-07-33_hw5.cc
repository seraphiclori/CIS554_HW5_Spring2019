//HW5 Due: April 7 (Sunday) at 11:59PM
//Author: Honghao Zeng <hozeng@syr.edu>
//SUID: 757737642
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
    ring(){}
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

};

ring::ring(int i, int j) {
    num_rows = i;
    num_cols = j;
    int val = 0;
    head = shared_ptr<node> (new node (val++));
    shared_ptr<node> cur = head;
    for (int i = 2; i <= num_rows * num_cols; i++) {
        cur->east = shared_ptr<node> (new node(val++));
        cur = cur->east;
    }
    cur->east = head;
    cur = head;
    shared_ptr<node> next_row = head;
    for (int j = 1; j <= num_cols; j++) next_row = next_row->east;
    for (int i = 1; i <= num_rows - 1; i++) {
        for (int j = 1; j <= num_cols; j++) {
            cur->south = next_row;
            cur = cur->east;
            next_row = next_row->east;
        }
    }
    next_row = next_row->east;
    for (int j = 1; j <= num_cols - 1; j++) {
        cur->south = next_row;
        next_row = next_row->east;
        cur = cur->east;
    }
    cur->south = head;
}

ring::~ring() {
    if (!head) return;
    shared_ptr<node> p_row = head->south;
    shared_ptr<node> p_col = head->east;
    head->east.reset();
    head->south.reset();

    for (int i = 0; i < num_rows - 1; i++) {
        shared_ptr<node> p_row_next = p_row->south;
        p_row->east.reset();
        p_row->south.reset();
        p_row = p_row_next;
    }

    for (int i = 0; i < num_cols - 1; i++) {
        shared_ptr<node> p_col_next = p_col->east;
        p_col->east.reset();
        p_col->south.reset();
        p_col = p_col_next;
    } 
}

ring::ring(const ring &r) {
    num_cols = r.num_cols;
    num_rows = r.num_rows;
    int n = r.num_rows * r.num_cols;
    shared_ptr<node> ptr_other = r.head;
    head = shared_ptr<node> (new node (ptr_other->value));
    shared_ptr<node> ptr_this = head;
    for (int i = 2; i <= n; i++) {
        ptr_this->east = shared_ptr<node> (new node (ptr_other->east->value));
        ptr_this = ptr_this->east;
        ptr_other = ptr_other->east;
    }
    ptr_this->east = head;
    ptr_this = head;
    shared_ptr<node> next_row = head;
    for (int j = 1; j <= num_cols; j++) next_row = next_row->east;
    for (int i = 1; i <= num_rows - 1; i++) {
        for (int j = 1; j <= num_cols; j++) {
            ptr_this->south = next_row;
            ptr_this = ptr_this->east;
            next_row = next_row->east;
        }
    }
    next_row = next_row->east;
    for (int j = 1; j <= num_cols - 1; j++) {
        ptr_this->south = next_row;
        next_row = next_row->east;
        ptr_this = ptr_this->east;
    }
    ptr_this->south = head;
}

ring::ring(ring &&r) {
    num_cols = r.num_cols;
    num_rows = r.num_rows;
    head = r.head;
    r.head.reset();
}

void ring::operator=(ring &&r) {
    if (head) {
        shared_ptr<node> p_row = head->south;
        shared_ptr<node> p_col = head->east;
        head->east.reset();
        head->south.reset();

        for (int i = 0; i < num_rows - 1; i++) {
            shared_ptr<node> p_row_next = p_row->south;
            p_row->east.reset();
            p_row->south.reset();
            p_row = p_row_next;
        }

        for (int i = 0; i < num_cols - 1; i++) {
            shared_ptr<node> p_col_next = p_col->east;
            p_col->east.reset();
            p_col->south.reset();
            p_col = p_col_next;
        } 
    }

    num_cols = r.num_cols;
    num_rows = r.num_rows;
    head = r.head;
    r.head.reset();
}

void ring::operator=(const ring &r) {
    if (head) {
        shared_ptr<node> p_row = head->south;
        shared_ptr<node> p_col = head->east;
        head->east.reset();
        head->south.reset();

        for (int i = 0; i < num_rows - 1; i++) {
            shared_ptr<node> p_row_next = p_row->south;
            p_row->east.reset();
            p_row->south.reset();
            p_row = p_row_next;
        }

        for (int i = 0; i < num_cols - 1; i++) {
            shared_ptr<node> p_col_next = p_col->east;
            p_col->east.reset();
            p_col->south.reset();
            p_col = p_col_next;
        } 
    }
    
    num_cols = r.num_cols;
    num_rows = r.num_rows;
    int n = r.num_rows * r.num_cols;
    shared_ptr<node> ptr_other = r.head;
    head = shared_ptr<node> (new node (ptr_other->value));
    shared_ptr<node> ptr_this = head;
    for (int i = 2; i <= n; i++) {
        ptr_this->east = shared_ptr<node> (new node (ptr_other->east->value));
        ptr_this = ptr_this->east;
        ptr_other = ptr_other->east;
    }
    ptr_this->east = head;
    ptr_this = head;
    shared_ptr<node> next_row = head;
    for (int j = 1; j <= num_cols; j++) next_row = next_row->east;
    for (int i = 1; i <= num_rows - 1; i++) {
        for (int j = 1; j <= num_cols; j++) {
            ptr_this->south = next_row;
            ptr_this = ptr_this->east;
            next_row = next_row->east;
        }
    }
    next_row = next_row->east;
    for (int j = 1; j <= num_cols - 1; j++) {
        ptr_this->south = next_row;
        next_row = next_row->east;
        ptr_this = ptr_this->east;
    }
    ptr_this->south = head;
}

ring::ring (const initializer_list<int> &l) {
    auto lit = l.begin();
    num_rows = *lit;
    lit++;
    num_cols = *lit;
    int n = num_rows * num_cols;
    lit++;
    head = shared_ptr<node> (new node (*lit));
    shared_ptr<node> cur = head;
    for (int i = 2; i <= num_rows * num_cols; i++) {
        if (lit == l.end()) return;
        lit++;
        cur->east = shared_ptr<node> (new node(*lit));
        cur = cur->east;
    }
    cur->east = head;
    cur = head;
    shared_ptr<node> next_row = head;
    for (int j = 1; j <= num_cols; j++) next_row = next_row->east;
    for (int i = 1; i <= num_rows - 1; i++) {
        for (int j = 1; j <= num_cols; j++) {
            cur->south = next_row;
            cur = cur->east;
            next_row = next_row->east;
        }
    }
    next_row = next_row->east;
    for (int j = 1; j <= num_cols - 1; j++) {
        cur->south = next_row;
        next_row = next_row->east;
        cur = cur->east;
    }
    cur->south = head;
}

int& ring::operator[](int a) {
    shared_ptr<node> cur = head;
    //if (a <= num_cols * num_rows) {
    for (int i = 0; i < a; i++) cur = cur->east;
    return cur->value;
    //}
}

int& ring::operator[](pair<int, int> p) {
    int r = p.first;
    int c = p.second;
    shared_ptr<node> cur = head;
    //if (r <= num_rows && c <= num_cols) {
    for (int i = 0; i < r; i++) cur = cur->south;
    for (int i = 0; i < c; i++) cur = cur->east;
    return cur->value;
    //}
}

void ring::DelCol(int n) {
    shared_ptr<node> cur = head;
    shared_ptr<node> prev_row = head;
    bool is_first = false;
    for (int i = 0; i < n; i++) {
        prev_row = cur;
        cur = cur->east;
    }
    // cur points to start of col now.
    if (cur == head) {
        head = head->east;
        is_first = true;
        prev_row = head;
        for (int i = 0; i < num_cols; i++)
            prev_row = prev_row->east;
    }

    for (int i = 0; i < num_rows - 1; i++) {
        prev_row->east = cur->east;
        prev_row = prev_row->south;
        cur = cur->south;
    }
    
    prev_row->east = cur->east;
    prev_row->south = is_first ? head : cur->south;
    num_cols--;
}

ring ring::Threetimes () {
    ring r(*this);
    shared_ptr<node> cur = r.head;
    do {
        cur->value = 3 * cur->value;
        cur = cur->east;
    } while (cur != r.head);

    return move(r);
}

//overload operator<<

ostream& operator<< (ostream &os, const ring &r) {
    int n = r.num_rows * r.num_cols;
    shared_ptr<node> ptr = r.head;
    for (int i = 1; i <= n; i++) {
        os << ptr->value << " ";
        if (i % r.num_cols == 0) os << endl;
        ptr = ptr->east;
    }

    return os;
}

int main() {

    ring R1(4, 6);//24 numbers from 0 to 23 will be initialized to nodes.
    cout << R1 << endl;
    R1[14] = 1000;  
    R1[{2, 4}] = 2000;
    cout << R1[14] << " " << R1[{2, 4}] << endl;
    R1.DelCol(3);
    cout << R1 << endl;
    R1.DelCol(4);
    cout << R1 << endl;
    R1.DelCol(0);
    cout << R1 << endl;
    shared_ptr<ring> p1 = make_shared<ring>(3, 5);
    cout << *p1 << endl;
    p1.reset();
    ring R2 = { 3, 5, 10,20,30,40,50, 100, 200, 300, 400, 500, 1000, 2000, 3000, 4000, 5000 };//
     //first two numbers are num_rows and num_cols; followed by values of nodes of ring
    cout << R2 << endl;
    ring R3(R2);
    cout << R3 << endl;
    ring R4;
    R4 = R3;
    cout << R4 << endl;
    ring R5;
    R5 = R4.Threetimes();
    cout << R5 << endl;
    
    getchar();
    getchar();
    return 0;
}