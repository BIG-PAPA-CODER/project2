#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <iostream>                            
#include <windows.h>            
#include <time.h>
#include <ctime>

using namespace std;
typedef int Key;
typedef float Elem;                              //definition of one node 
typedef string Line;
class DNode{
    public:
        DNode(){}; 
        ~DNode(){};
    private:
        Key key;
        Line line;
        Elem elem;
        DNode* prev;
        DNode* next;
    friend class DLinkedList;
};

//////////////////

class DLinkedList{                                           //definition of doubly linked list
    public:
        DLinkedList();                                       //constructor
        ~DLinkedList();                                      //distructor

        bool isEmpty();                                      //checks if list is empty
        void addFront(const Elem& e);                        // add to front of list
        void addBack(const Elem& e);                         // add to back of list
        void addBackLineElemKey(const Line& e, const Elem& k, const Key& p);  // add string and float at the same moment
        void addBackLine(const Line& e);                     // add string to back of list
        void removeFront();                                  // remove from front
        void removeBack();                                   // remove from back
        void printDLL_Line();                                // print function for string saved in nodes
        void printDLL();
        int sizeofDLL();                                     // returns size of elements (number of elements)
        void check_DLL();                                    // checks if DLL is sorted in a right way
        void newDLL(DLinkedList* DLL);                       // creates new DLL
        void quick_sort(DLinkedList* DLL); 
        void merge_sort(DLinkedList* S);
        void insertion_sort(DLinkedList* DLL);
        void intro_sort(DLinkedList* DLL);
        void binary_search_F(DLinkedList* DLL1, string** arr, int rows);
        void averege_median(DLinkedList* DLL);


    private:
        DNode* header;
        DNode* trailer;
        DNode* pointer;
    protected:
        void add(DNode* v, const Elem& e);
        void addLineElemKey(DNode* v, const Line& e, const Elem& k, const Key& p);
        void addLine(DNode* v, const Line& e);
        void remove(DNode* v);
};

DLinkedList::DLinkedList(){
    pointer = new DNode();
    header = new DNode();
    trailer = new DNode();
    pointer->next = header;
    header->next = trailer;
    trailer->prev = header;
};

DLinkedList::~DLinkedList(){
    while (!isEmpty()) removeFront();
    delete header;
    delete trailer;
    delete pointer;
};

bool DLinkedList::isEmpty(){
    return header->next == trailer;
};

void DLinkedList::add(DNode* v, const Elem& e){
    DNode* u = new DNode();
    u->elem = e;
    u->next = v;
    u->prev = v->prev;
    v->prev->next = v->prev = u;
};

void DLinkedList::addLine(DNode* v, const Line& e){
    DNode* u = new DNode();
    u->line = e;
    u->next = v;
    u->prev = v->prev;
    v->prev->next = v->prev = u;
};

void DLinkedList::addLineElemKey(DNode* v, const Line& e, const Elem& k, const Key& p){
    DNode* u = new DNode();
    u->elem = k;
    u->line = e;
    u->key = p;
    u->next = v;
    u->prev = v->prev;
    v->prev->next = v->prev = u;
};

void DLinkedList::remove(DNode* v){
    DNode* u = v->prev;
    DNode* w = v->next;
    u = w->prev;
    w = u->next;
    delete v; 
};

void DLinkedList::addFront(const Elem& e){
    add(header->next, e);
    //header = header->next;
};

void DLinkedList::addBack(const Elem& e){
    add(trailer, e);
};

void DLinkedList::addBackLine(const Line& e){
    addLine(trailer, e);
};

void DLinkedList::addBackLineElemKey(const Line& e, const Elem& k, const Key& p){
    addLineElemKey(trailer, e, k, p);
};



void DLinkedList::removeFront(){
    header = header->next;
    remove(header->prev);
    
};

void DLinkedList::removeBack(){
    remove(trailer->prev);
    //trailer = trailer->prev;
};

void DLinkedList::printDLL_Line(){
    int res = 0;
    while(header != trailer->prev){                          
        cout << header->next->line << endl;
        cout << header->next->key << endl;
        //cout << header->next->elem << endl;
        header = header->next;              //here is the problem, header is moved
        ++res;
    };
    int j = 0;                              //and here is the solution, returning head to its place
    while(j < res){
        header = header->prev;
        ++j;
    };
    cout << endl;
    //cout << header->next->key << " is key" << endl;
};

void DLinkedList::printDLL(){
    int res = 0;
    while(header != trailer->prev){                          
        cout << header->next->elem << " ";
        header = header->next;              //here is the problem, header is moved
        ++res;
    };
    int j = 0;                              //and here is the solution, returning head to its place
    while(j < res){
        header = header->prev;
        ++j;
    };
    cout << endl;
};

int DLinkedList::sizeofDLL(){

    int res = 0;
    int sizeDLL = 0;
    while(header != trailer->prev){                          
        sizeDLL += 1;//sizeof(header);
        header = header->next;              
        ++res;
    };
    int j = 0;                              //returning head to its place
    while(j < res){
        header = header->prev;
        ++j;
    };
    return sizeDLL;
};

void DLinkedList::newDLL(DLinkedList* DLL){
    
    int size;
    int range_max;
    int range_min;

    srand(time(0));

    cout << "Enter size of list, max value and min: " << endl;
    cin >> size;
    cin >> range_max;
    cin >> range_min;

    for(int i = 0; i < size; ++i){
        int r = rand() % range_max + range_min;
        DLL->addBack(r);
    };
};

void DLinkedList::quick_sort(DLinkedList* DLL){
    
    float p;                                     //the pivotal

    if(DLL->sizeofDLL() <= 1){
        p = DLL->trailer->prev->elem;
        //cout << p << endl;
    }
    
    else{

        DLinkedList* L = new DLinkedList();      //if number is less then the pivot
        DLinkedList* E = new DLinkedList();      //if number is equal to the pivot
        DLinkedList* G = new DLinkedList();      //if number is greater then the pivot
        
        p = DLL->trailer->prev->elem;

        while(!(DLL->isEmpty())){
            
            if(header->next->elem < p){
                L->addBackLineElemKey(DLL->header->next->line, DLL->header->next->elem, DLL->header->next->key);
                //L->addBackLine(DLL->header->next->line);
                DLL->removeFront();
            }
            else if(header->next->elem == p){
                //E->addBack(DLL->header->next->elem);
                E->addBackLineElemKey(DLL->header->next->line, DLL->header->next->elem, DLL->header->next->key);
                //E->addBackLine(DLL->header->next->line);
                DLL->removeFront();
            }
            else{
                //G->addBack(DLL->header->next->elem);
                G->addBackLineElemKey(DLL->header->next->line, DLL->header->next->elem, DLL->header->next->key);
                //G->addBackLine(DLL->header->next->line);
                DLL->removeFront();
            }
        }

        L->quick_sort(L);         //recursion for elements less then p
        G->quick_sort(G);         //recursion for elements greater then p

        while(!(L->isEmpty())){
            //DLL->addBack(L->header->next->elem);
            DLL->addBackLineElemKey(L->header->next->line, L->header->next->elem, L->header->next->key);
            //DLL->addBackLine(L->header->next->line);
            L->removeFront();
        }

        while(!(E->isEmpty())){
            //DLL->addBack(E->header->next->elem);
            DLL->addBackLineElemKey(E->header->next->line, E->header->next->elem, E->header->next->key);
            //DLL->addBackLine(E->header->next->line);
            E->removeFront();
        }

        while(!(G->isEmpty())){
            //DLL->addBack(G->header->next->elem);
            DLL->addBackLineElemKey(G->header->next->line, G->header->next->elem, G->header->next->key);
            //DLL->addBackLine(G->header->next->line);
            G->removeFront();
        }

        delete L;
        delete E;
        delete G;

    }
};

void DLinkedList::merge_sort(DLinkedList* S){

    if (S->sizeofDLL() <= 1){
        S->header->next->elem;
    }

    else {
        DLinkedList* S1 = new DLinkedList();
        DLinkedList* S2 = new DLinkedList();

        int size1 = 1;
        int size2 = 1;       
        int sizeH = S->sizeofDLL()/2;

/////////////////////////////////////////////////////////////////////////////////////
        while(size1 <= sizeH){                                                     //
            S1->addBackLineElemKey(S->header->next->line, S->header->next->elem, S->header->next->key);     //
            S->removeFront();                                                      //
            ++size1;                                                               //
        };                                                                         //
                                                                                   //
        int sizeF = S->sizeofDLL();                                                //
                                                                                   //
        while(size2 <= sizeF){                                                     //
            S2->addBackLineElemKey(S->header->next->line, S->header->next->elem, S->header->next->key);     //  <- this part of code is dividing DLL into 2 enothers.
            S->removeFront();                                                      //
            ++size2;                                                               //
        };                                                                         //
                                                                                   //
        if (!(S->isEmpty())){                                                      //
            S2->addBackLineElemKey(S->header->next->line, S->header->next->elem, S->header->next->key);     //
            S->removeFront();                                                      //
        }                                                                          //
                                                                                   //
        //S1->printDLL();                                                          //
        //S2->printDLL();                                                          //
/////////////////////////////////////////////////////////////////////////////////////

        S1->merge_sort(S1);                         // recursion for S1
        S2->merge_sort(S2);                         // recursion for S2

        while(!(S1->isEmpty()) && !(S2->isEmpty())){
            
            if (S1->header->next->elem < S2->header->next->elem){
                S->addBackLineElemKey(S1->header->next->line, S1->header->next->elem, S1->header->next->key);
                S1->removeFront();
            }

            else if (S1->header->next->elem > S2->header->next->elem){
                S->addBackLineElemKey(S2->header->next->line, S2->header->next->elem, S2->header->next->key);
                S2->removeFront();
            }
            
            else{
                S->addBackLineElemKey(S1->header->next->line, S1->header->next->elem, S1->header->next->key);
                S->addBackLineElemKey(S2->header->next->line, S2->header->next->elem, S2->header->next->key);
                S1->removeFront();
                S2->removeFront();
            }
        }

        

        while(!(S1->isEmpty())){
            S->addBackLineElemKey(S1->header->next->line, S1->header->next->elem, S1->header->next->key);
            S1->removeFront();
        }

        while(!(S2->isEmpty())){
            S->addBackLineElemKey(S2->header->next->line, S2->header->next->elem, S2->header->next->key);
            S2->removeFront();
        }

        

    /*  cout << sizeH << endl;
        cout << sizeF << endl;
        cout << endl;*/

        delete S1;
        delete S2;
    }
};

void DLinkedList::insertion_sort(DLinkedList* DLL){
    
    float el;
    string elSTR;
    float el1;
    string el1STR;
    float elKEY;
    float el1KEY;

    int res = 0;
    int res1 = 0;
    int i = 0;
    //DLL->addFront(0);
    //DLL->addFront(0);
    DLL->addFront(0);
    if (DLL->sizeofDLL() <= 1){
        DLL->header->next->elem;
    }

    else{
        while(header != trailer->prev->prev->prev){
////////////////////////////////////////////////////////////////////////////////////
            if (header->next->next->elem > header->next->next->next->elem){       //
                el = header->next->next->elem;                                    //
                header->next->next->elem = header->next->next->next->elem;        //  <- this part of code do "SWAP"
                header->next->next->next->elem = el;                              //
                                                                                  //
                elSTR = header->next->next->line;                                 //
                header->next->next->line = header->next->next->next->line;        //  <- this part of code do "SWAP"
                header->next->next->next->line = elSTR;                           //
                                                                                  //
                elKEY = header->next->next->key;                                  //
                header->next->next->key = header->next->next->next->key;          //  <- this part of code do "SWAP"
                header->next->next->next->key = elKEY;                            //                                          
////////////////////////////////////////////////////////////////////////////////////    
                while(header->next->elem > header->next->next->elem){       
                    el1 = header->next->elem;                          
                    header->next->elem = header->next->next->elem;        
                    header->next->next->elem = el1;

                    el1STR = header->next->line;                          
                    header->next->line = header->next->next->line;        
                    header->next->next->line = el1STR;
                        
                    el1KEY = header->next->key;                          
                    header->next->key = header->next->next->key;        
                    header->next->next->key = el1KEY;

                    if(header->prev != NULL){
                        header = header->prev;
                        ++res1;
                    }       
                } 
                while(i < res1){
                    header = header->next;
                    ++i;
                }
            }            
            header = header->next;
            ++res;
        }
        int j = 0;                              //returning head to its place
        while(j < res){
            header = header->prev;
            ++j;
        }          
    }
    //DLL->removeFront();
    //DLL->removeFront();
    DLL->removeFront();
}

void DLinkedList::intro_sort(DLinkedList* DLL){
    
    int p;                                       //the pivotal

    DLinkedList* L = new DLinkedList();      //if number is less then the pivot
    DLinkedList* E = new DLinkedList();      //if number is equal to the pivot
    DLinkedList* G = new DLinkedList();      //if number is greater then the pivot
        
    p = DLL->trailer->prev->elem;

    if(DLL->sizeofDLL() <= 16){
        DLL->insertion_sort(DLL);            
    }

    else{
        while(!(DLL->isEmpty())){

            if(header->next->elem < p){
                //L->addBack(DLL->header->next->elem);
                L->addBackLineElemKey(DLL->header->next->line, DLL->header->next->elem, DLL->header->next->key);
                DLL->removeFront();
            }
            else if(header->next->elem == p){
                //E->addBack(DLL->header->next->elem);
                E->addBackLineElemKey(DLL->header->next->line, DLL->header->next->elem, DLL->header->next->key);
                DLL->removeFront();
            }
            else{
                //G->addBack(DLL->header->next->elem);
                G->addBackLineElemKey(DLL->header->next->line, DLL->header->next->elem, DLL->header->next->key);
                DLL->removeFront();
            }
        }
    }

    L->quick_sort(L);         //recursion for elements less then p
    G->quick_sort(G);         //recursion for elements greater then p

    while(!(L->isEmpty())){
        //DLL->addBack(L->header->next->elem);
        DLL->addBackLineElemKey(L->header->next->line, L->header->next->elem, L->header->next->key);
        L->removeFront();
    }

    while(!(E->isEmpty())){
        //DLL->addBack(E->header->next->elem);
        DLL->addBackLineElemKey(E->header->next->line, E->header->next->elem, E->header->next->key);
        E->removeFront();
    }

    while(!(G->isEmpty())){
        //DLL->addBack(G->header->next->elem);
        DLL->addBackLineElemKey(G->header->next->line, G->header->next->elem, G->header->next->key);
        G->removeFront();
    }

    delete L;
    delete E;
    delete G;

}

string binary_search(string **arr, int rows, int target) {
    int left = 0;
    int right = rows - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Extract the integer from the first column string using stoi()
        int midValue = stoi(arr[mid][0].substr(2));

        if (midValue == target) {
            return " -----> " + arr[mid][2];
        } else if (midValue < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    // Target not found
    return "not found";
}

void DLinkedList::binary_search_F(DLinkedList* DLL1, string** arr, int rows){
    int res = 0;
    int j = 0;
    cout << "Binary search and saving in process..." << endl;
    ofstream outFile("srtd.txt");
    outFile << "tconst" << "\t" << "Averege Rating" << "\t" << "Num Votes" << "\t" << "Name of Movie" << endl;

    while(DLL1->header != DLL1->trailer->prev){
        int tgt = DLL1->header->next->key;
        DLL1->header->next->line = DLL1->header->next->line + binary_search(arr, rows, tgt);
        outFile << DLL1->header->next->line << endl;
        header = header->next;
        ++res; 
    }
    
    outFile.close();
    cout << "TSV file created successfully!" << endl;
    
    while(j < res){
        header = header->prev;
        ++j;
    }
}

void DLinkedList::check_DLL(){
    while (header != trailer->prev->prev){
        if (header->next->elem <= header->next->next->elem){
            header = header->next;
        }

        else{
            cout << "ERROR: invalid sorting" << endl;
            cout << header->next->elem << " > " << header->next->next->elem << endl;
            break;
        }
    }
    cout << "Sorting completed with success" << endl;
}

void DLinkedList::averege_median(DLinkedList* DLL){
    int sizeH = sizeofDLL()/2;
    float sizeF = sizeofDLL();
    float sum = 0;
    int res = 0;
    int count = 0;

    while(header != trailer->prev){
        float rank1 = header->next->elem;
        sum = sum + rank1;
        header = header->next;
        //cout << sum << endl;
        ++res;
    }
    cout << "averege is: " << sum/sizeF << endl;
    int j = 0;
    while(j < res){
        header = header->prev;
        ++j;
    }

    while(count < sizeH){
        header = header->next;
        ++count;
    }
    float median = (header->next->elem + header->next->next->elem)/2;
    cout << "median is: " << median << endl;
    int i = 0;
    while(i < count){
        header = header->prev;
        ++i;
    }

}

using namespace std;
int main(){

    DLinkedList* DLL = new DLinkedList;
    ifstream file("data.tsv");
    string line;
    int res1 = 0;
    int res = 0;
    int x = 0;

    cout << "Entering info from DATA..." << endl;
    for (int i = 0; i < 1295779/*1295779*/; ++i){
        getline(file, line);
        stringstream ss(line);
        string cell;
        float rank;
        string key;
        int key_f;
        if(i >= 1){
            while (getline(ss, cell, '\t')){
                res++;
                if(res == 2){
                    rank = stof(cell);
                }
                else if(res == 1){
                    key = cell.substr(2);
                    key_f = stoi(key);
                }
            }
            res = 0;
            DLL->addBackLineElemKey(line, rank, key_f);
        }
    }
    cout << endl;
    cout << "Size of list: " << DLL->sizeofDLL() << endl;

    cout << "Sorting..." << endl;
    int start = clock();
    DLL->quick_sort(DLL);
    //DLL->merge_sort(DLL);
    //DLL->intro_sort(DLL);
    int end = clock();
    int t = end - start;

    cout << "Sorting time: " << t << "ms" << endl;
    DLL->averege_median(DLL);

    int rows = 9735227;                               //numbers of rows in BIGDATA
    //cout << "Enter the number of rows: ";
    //cin >> rows;

    // Dynamically allocate memory for a 2D array of size rows x 3.
    string** arr = new string*[rows];
    for (int i = 0; i < rows; i++) {
        arr[i] = new string[4];
    }

    // Open the TSV file for reading.
    ifstream fin("referencyjne.txt");
    if (!fin) {
        cout << "Error opening file!\n";
        return 1;
    }

    // Read data from the file and store it in the 2D array.
    for (int i = 0; i < rows; i++) {
        getline(fin, arr[i][0], '\t'); // Read the first column
        getline(fin, arr[i][1], '\t'); // Skip the second column
        getline(fin, arr[i][2], '\t'); // Read the third column
        getline(fin, arr[i][3], '\n'); 
    }

    // Close the file.
    fin.close();
    cout << "File reading complited" << endl;

    // Display the contents of the 2D array.
    // for (int i = 0; i < rows; i++) {
    //     cout << arr[i][0] << "\t" << arr[i][2] << endl;
    // }

    int start1 = clock();    
    DLL->binary_search_F(DLL, arr, rows);
    int end1 = clock();
    int t1 = end - start;

    cout << "Binary search time: " << t1 << "ms" << endl;


    // Free the dynamically allocated memory.
    for (int i = 0; i < rows; i++) {
        delete[] arr[i];
    }
    delete[] arr;

    //delete BIGDLL;
    delete DLL;

    return 0;
}