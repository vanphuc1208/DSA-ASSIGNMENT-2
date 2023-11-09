#include "main.h"
//handle truong hop lam sao cap nhat order trong avl
//lam sao de chon xoa dung khach khi cac khach co cung result trong avl
struct HuffmanNode {
	char data;
	int freq;
	int order;
	HuffmanNode *left,*right;
	HuffmanNode(char data, int freq, int order) {
		left=right=NULL;
		this->data=data;
		this->freq=freq;
		this->order=order;
	}
};

class compareHuffman {
	public:
	bool operator() (HuffmanNode *below, HuffmanNode* above) {// the order is the from the bottom to top
		if(below->freq==above->freq) return below->order>above->order;
		return below->freq>above->freq;
	} 
};

void storeCodes( HuffmanNode* node, string str,map<char,string>& codes)
{
    if (node == NULL) return;
    if (node->data!='0') codes[node->data]=str;
    storeCodes(node->left, str + "0",codes);
    storeCodes(node->right, str + "1",codes);
}
void deleteHuff(HuffmanNode* root) {
    if (root == nullptr) {
        return;
    }
    deleteHuff(root->left); // Recursively delete left subtree
    deleteHuff(root->right); // Recursively delete right subtree
    delete root; // Delete current node
}


void buildHuff(map<char,int>& frequency, map<char,string>&codes) {
	int order=0;
	priority_queue<HuffmanNode*,vector<HuffmanNode*>,compareHuffman> forest;
	for(auto it: frequency) {
       forest.push(new HuffmanNode(it.first,it.second,order));
	   order++;
	}
HuffmanNode *temp1, *temp2, *temp3;
while (forest.size() > 1) {
temp1 = forest.top(); // Pull first two trees
forest.pop();
temp2 = forest.top(); // off the list
forest.pop();
temp3 = new HuffmanNode('0', temp1->freq + temp2->freq,order);
temp3->left=temp1;
temp3->right=temp2;
forest.push(temp3); // Put the new tree back on list
order++;
}
storeCodes(forest.top(),"",codes);
deleteHuff(forest.top());
}


int getResult(string name) {
if(name.length()==1) return 1;
map <char,int>frequency;
map <char,string> codes;
for(unsigned int i=0;i<name.length();i++) {
	frequency[name[i]]++;
}
buildHuff(frequency,codes);
string encode="";
for(unsigned int i=0;i<name.length();i++) {
 encode+=codes[name[i]];
}
if (encode.length()>15) encode=encode.substr(encode.length()-15,15);
int res=0;
int k=0;
for(int i=encode.length()-1;i>=0;i--) {
	if(encode[i]=='1') res+=pow(2,k);
	k++;
}
return res;
}




struct customerInfo{
	int ID,result,order,area,appear;
    string name;
	customerInfo(string name="",int area=0,int ID=0, int result=0, int order=0,int appear=0) {
		this->name=name;
        this->area=area;
        this->ID=ID;
		this->result=result;
		this->order=order;// time orders
        this->appear=appear;
	}
};
class Heap
{
    private:
    vector<customerInfo> arr;
    protected:
	void swap(int a, int b) {
		customerInfo tmp=arr[a];
		arr[a]=arr[b];
		arr[b]=tmp;
	}
    void reheapUp(int index) {
    if (index<=0) return;
    int parent=(index-1)/2;
	if(arr[parent].order==arr[index].order) {
       if(arr[parent].appear>arr[index].appear) {
		swap(index,parent);
		reheapUp(parent);
	   } 
	}
    else if (arr[parent].order>arr[index].order) {
    swap(index,parent);
    reheapUp(parent);
    }
	}
    void reheapDown(int index) {
   int lastPos=arr.size()-1;
   int leftChild=2*index+1;
   int rightChild=2*index+2;
   if(leftChild<=lastPos) {
    int Child=leftChild;
    if(rightChild <=lastPos) {
		if (arr[rightChild].order==arr[leftChild].order) {
			if(arr[rightChild].appear<arr[leftChild].appear) Child=rightChild;
		} 
        else if(arr[rightChild].order<arr[leftChild].order) Child=rightChild;
    }
	if(arr[index].order==arr[Child].order) {
       if(arr[index].appear>arr[Child].appear) {
		swap(index,Child);
		reheapDown(Child);
	   } 
	}
   else if(arr[index].order>arr[Child].order) {
    swap(index,Child);
    reheapDown(Child);
   }
   }
	}
    void printPreOrder(int index) {
        int n=arr.size();
        if(index>=n) return;
        cout<<arr[index].ID<<"-"<<arr[index].order<<endl;
        printPreOrder(2*index+1);
        printPreOrder(2*index+2);
    }
    public:
    void insert(customerInfo newCustomer){
        arr.push_back(newCustomer);
        reheapUp(arr.size()-1);
    }
    void remove(customerInfo deleteCustomer) {
        int index=-1;
    for(unsigned int i=0;i<arr.size();i++) {
        if(arr[i].name==deleteCustomer.name) {
            index=i;
            break;
        }
    }
     if (index==-1) return;
    swap(arr.size()-1,index);
    arr.pop_back();
    reheapDown(index);
    reheapUp(index);
    }
    void updateOrder(customerInfo updateCustomer) {
        int index=-1;
        for(unsigned int i=0;i<arr.size();i++) {
        if(arr[i].name==updateCustomer.name) {
            index=i;
            break;
        }
    }
     if (index==-1) return;
     customerInfo tmp=arr[index];
     tmp.order++;
    swap(arr.size()-1,index);
    arr.pop_back();
    reheapDown(index);
    reheapUp(index);
    this->insert(tmp);
    }
    customerInfo getfirst() {
        return arr[0];
    }

    void print() {
        printPreOrder(0);
    }
   
};

class AVLTree
{
public:
    class Node;
private:
    Node *root;
	int count;
protected:
    int getHeightRec(Node *node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }
    Node* rotateLeft1(Node* root) {
    Node *newRoot=root->pRight;
    root->pRight=newRoot->pLeft;
    newRoot->pLeft=root;
    return newRoot;
}
Node* rotateRight1(Node* root) {
    Node *newRoot=root->pLeft;
    root->pLeft=newRoot->pRight;
    newRoot->pRight=root;
    return newRoot;
}
int getBalance(Node* root) {
    return getHeightRec(root->pLeft)-getHeightRec(root->pRight);
}
Node* rebalance(Node* root) {
    if(root==NULL) return NULL;
    Node* newRoot=root;
    if(getBalance(root)>1) {//LH
        Node *left=root->pLeft;
        if(getBalance(left)<0) {//RH of LH
            root->pLeft=rotateLeft1(root->pLeft);
            newRoot=rotateRight1(root);
        }
        else newRoot=rotateRight1(root); //LH of LH or EH of LH
    }
    else if(getBalance(root)<-1){//RH
         Node *right=root->pRight;
         if(getBalance(right)>0) {//LH of RH
             root->pRight=rotateRight1(root->pRight);
             newRoot=rotateLeft1(root);
         }
         else newRoot=rotateLeft1(root);//RH of RH or EH of RH
    }
    return newRoot;
    
}
void updateOrderHelp(Node *root,customerInfo updateCustomer ) {
    if (root==NULL) return;
    if(root->data.result==updateCustomer.result) {
         if(root->data.name==updateCustomer.name) root->data.order++;
         else if(root->pLeft&&root->pLeft->data.name==updateCustomer.name) root->pLeft->data.order++;
         else root->pRight->data.order++;
    }
    else if(updateCustomer.result<root->data.result) updateOrderHelp(root->pLeft,updateCustomer);
    else  updateOrderHelp(root->pRight,updateCustomer);
}
Node* AVLRemove(Node*root, customerInfo deleteCustomer) {
    if(root==NULL) return NULL;
    else if(deleteCustomer.result<root->data.result) root->pLeft=AVLRemove(root->pLeft,deleteCustomer);
    else if(deleteCustomer.result>root->data.result) root->pRight=AVLRemove(root->pRight,deleteCustomer);
    else{
        //no child
        if(root->data.name==deleteCustomer.name) {
        if(root->pLeft==NULL && root->pRight==NULL) {
            delete root;
            return NULL;
        }
        else if(root->pLeft==NULL) {
            Node *tmp=root;
            root=root->pRight;
            delete tmp;
            return root;
        } //just has right child
        else if(root->pRight==NULL) {
            Node *tmp=root;
            root=root->pLeft;
            delete tmp;
            return root;
        }//just has left child
        else {
            Node*smallestOnRight=root->pRight;
            while(smallestOnRight->pLeft!=NULL) smallestOnRight=smallestOnRight->pLeft;
            root->data=smallestOnRight->data;
            root->pRight=AVLRemove(root->pRight,smallestOnRight->data);
        }
    }
    else {
        root->pLeft=AVLRemove(root->pLeft,deleteCustomer);
        root->pRight=AVLRemove(root->pRight,deleteCustomer);
    }
    }
   return rebalance(root);
}
Node *AVLInsert(Node* root, customerInfo newCustomer) {
    if(root==NULL) return new Node(newCustomer);
    if(newCustomer.result<root->data.result) root->pLeft=AVLInsert(root->pLeft,newCustomer);
    else root->pRight=AVLInsert(root->pRight,newCustomer);
    return rebalance(root);
}
void clearBST(Node* node) {
   if (node != nullptr) {
            clearBST(node->pLeft);
            clearBST(node->pRight);
            delete node;
        }
        this->root = nullptr;
    }
public:
    AVLTree() : root(nullptr), count(0) {}
    ~AVLTree() {
		this->clear();
	}
	void insert(customerInfo newCustomer){//
    root=AVLInsert(root,newCustomer);
	count++;    
}
    void remove(customerInfo deleteCustomer)
    {
         root=AVLRemove(root,deleteCustomer);
		 count--;
    }
    void updateOrder(customerInfo updateCustomer) {
        this->updateOrderHelp(root,updateCustomer);

    }
	bool checkFull() {
		return count==MAXSIZE/2;
	}
	void print() {
        if(root==NULL) return;
		queue<Node*> container;
		container.push(root);
		while(!container.empty()) {
			Node *tmp=container.front();
			container.pop();
			if(tmp->pLeft) container.push(tmp->pLeft);
			if(tmp->pRight) container.push(tmp->pRight);
			cout<<tmp->data.ID<<"-"<<tmp->data.result<<"-"<<tmp->data.order<<endl;
		}
	}
	void clear() {
		clearBST(this->root);
        count=0;
	}
    int getCount() {
        return count;
    }
	 class Node
    {
    private:
        customerInfo data;
        Node *pLeft, *pRight;
        friend class AVLTree;

    public:
        Node(customerInfo newCustomer) : data(newCustomer), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
};

// ID =0 la o do trong
class hashtable {
public:
customerInfo* table;
int count;
int capacity;
hashtable() {
	this->count=0;
	this->capacity=MAXSIZE/2;
	this->table=new customerInfo[capacity];
	for(int i=0;i<this->capacity;i++) {
		customerInfo blank;
        table[i]=blank;//khoi tao nhung o trong
	}
}
~hashtable() {
	delete[] table;
}
void insert(customerInfo newCustomer) {
	// k can handle truong hop full vi minh da chac con ms goi ham
	int index=newCustomer.result %(MAXSIZE/2);
	 while (table[index].ID != 0) { // linear probing
            index = (index + 1) % capacity;
        }
        table[index] = newCustomer;
        count++;
}
void remove(customerInfo deleteCustomer) {
	int index=deleteCustomer.result%(MAXSIZE/2);
	while(table[index].ID!=deleteCustomer.ID) {
		index=(index+1) %capacity;
	}
	customerInfo blank;
	table[index]=blank;
	count--;
}

void updateOrder(customerInfo updateCustomer) {
    int index=updateCustomer.result%(MAXSIZE/2);
	while(table[index].ID!=updateCustomer.ID) {
		index=(index+1) %capacity;
	}
    table[index].order++;
}
bool checkFull() {
	return count==capacity;
}
void clear() {
	this->count=0;
	for(int i=0;i<this->capacity;i++) {
		customerInfo blank;
        table[i]=blank;//khoi tao nhung o trong
	}
}

void print() {
	for(int i=0;i<this->capacity;i++) {
		if(table[i].ID!=0) cout<<table[i].ID<<"-"<<table[i].result<<"-"<<table[i].order<<endl;
}
}
};

class DLinkedList {
public:
    class Node; // Forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    DLinkedList(){
        head=NULL;
        tail=NULL;
        count=0;
    }
    ~DLinkedList(){
        this->clear();
    }
    void  add(customerInfo newCustomer){
         Node *newNode= new Node(newCustomer);
    if (head==NULL) {
        head=newNode;
        tail=newNode;
        count++;
        return;
    }
    tail->next=newNode;
    newNode->previous=tail;
    tail=newNode;
    count++;
    }
    void    addfirst(customerInfo newCustomer) {
        Node* newNode = new Node(newCustomer);
        newNode->previous = nullptr;
        newNode->next = head;
        if (head != nullptr) {
            head->previous = newNode;
        }
        head = newNode;
        count++;
    }
    void       removeAt(int index){
/* Remove element at index and return removed value */
    if (index < 0 || index > count) return ;

    Node* temp = head;
    for (int i = 0; i < index; i++) temp = temp->next;

    if (temp->previous!=NULL) temp->previous->next = temp->next;
    if (temp->next!=NULL) temp->next->previous = temp->previous;

    if (index == 0) head = temp->next;
    if (index == count - 1) tail = temp->previous;
    delete temp;
    count--;
    }
    void    removeItem(customerInfo deleteCustomer) {
    Node*tmp=head;
    int idx=0;
    while(tmp!=NULL) {
        if(tmp->data.name==deleteCustomer.name) {
            removeAt(idx);
            return;
        }
        idx++;
        tmp=tmp->next;
    }
    }
    void updateOrder(customerInfo updateCustomer) {
        this->removeItem(updateCustomer);
        this->addfirst(updateCustomer);
    }
void deleteArea(int data) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data.area == data) {
            if (current == head) {
                head = current->next;
                if (head != nullptr) {
                    head->previous = nullptr;
                } else {
                    // list is now empty, update tail
                    tail = nullptr;
                }
            } else {
                current->previous->next = current->next;
                if (current->next != nullptr) {
                    current->next->previous = current->previous;
                } else {
                    // current is the tail node, update tail
                    tail = current->previous;
                }
            }
            Node* temp = current;
            current = current->next;
            delete temp;
            count--;
        } else {
            current = current->next;
        }
    }
}
    void    clear(){
         while(head!=NULL) {
        Node* next=head->next;
        delete head;
        head=next;
    }
    tail=NULL;
    count=0;
    }
    customerInfo getHead() {
        return head->data;
    }
    customerInfo getTail() {
        Node* tmp=head;
        while(tmp->next!=NULL) {
            tmp=tmp->next;
        }
        return tmp->data;
    }
    void print() {
        Node*tmp=head;
        while(tmp!=NULL) {
            cout<<tmp->data.ID<<"-"<<tmp->data.area<<"-"<<tmp->data.name<<"-"<<tmp->data.result<<endl;
            tmp=tmp->next;
        }
    }
public:
    class Node
    {
    private:
        customerInfo data;
        Node *next;
        Node *previous;
        friend class DLinkedList;

    public:
        Node()
        {
            this->previous = NULL;
            this->next = NULL;
        }

        Node(const customerInfo &data)
        {
            this->data = data;
            this->previous = NULL;
            this->next = NULL;
        }
    };

};
hashtable area1;
int appear=0;
AVLTree area2;
DLinkedList Fifo;
DLinkedList LRCO;
Heap LFCO;
customerInfo handleID[MAXSIZE];// mangage that ID is empty or not(the index will save the ID-1) if the table is not empty indicate the area of that table
bool cmp(customerInfo a, customerInfo b) {
    return a.appear<b.appear;
}
void deleteAreaHeap(int data) {
    customerInfo tmp[MAXSIZE]; 
    for(int i=0;i<MAXSIZE;i++) {
        tmp[i]=handleID[i];
    }
    sort(tmp,tmp+MAXSIZE,cmp);
    for(int i=0;i<MAXSIZE;i++) {
        if(tmp[i].ID!=0&&tmp[i].area==data) LFCO.remove(tmp[i]);
}
}


void clearCustomer(int num) {
 if(num<1) {
area1.clear();
Fifo.deleteArea(1);
LRCO.deleteArea(1);
deleteAreaHeap(1);
	for(int i=0;i<MAXSIZE;i++) {
        if (handleID[i].area==1) {
        customerInfo empty;
         handleID[i]= empty;
        }
}
 }
 else if (num>MAXSIZE) {
    area2.clear();
Fifo.deleteArea(2);
LRCO.deleteArea(2);
deleteAreaHeap(2);
	for(int i=0;i<MAXSIZE;i++) {
        if (handleID[i].area==2) {
        customerInfo empty;
         handleID[i]= empty;
        }
}
 }
 else {
    if(handleID[num-1].ID!=0) {
        customerInfo deleteCustomer=handleID[num-1];
        if(deleteCustomer.area==1) area1.remove(deleteCustomer);
        else area2.remove(deleteCustomer);
        Fifo.removeItem(deleteCustomer);
        LRCO.removeItem(deleteCustomer);
        LFCO.remove(deleteCustomer);
        customerInfo blank;
        handleID[num-1]=blank;
    }
 }
}



int checkAvai(string name) {
    for(int i=0;i<MAXSIZE;i++) {
       if(handleID[i].name==name) return i;
    }
    return -1;
}


int chooseID(int result) {
int res=result%MAXSIZE+1;
while(handleID[res-1].ID!=0) {
    res=(res+1)%MAXSIZE;
    if(res==0) res=MAXSIZE;
}
return res;
}



int chooseArea(int result) {
    if(area1.checkFull()) return 2;
    else if(area2.checkFull()) return 1;
    else {
        if(result%2==1) return 1;
        else return 2;
    }
}


void addCustomer(string name, int ID, int result, int area, int order) {
    customerInfo newCustomer(name,area,ID,result,order,appear);
    Fifo.add(newCustomer);
    LRCO.addfirst(newCustomer);
    LFCO.insert(newCustomer);
    if(area==1) area1.insert(newCustomer);
    else area2.insert(newCustomer);
    handleID[ID-1]=newCustomer;
    appear++;
}

void manageFull(int result,string name) {
     customerInfo deleteCustomer;
if(result%3==0) {
    deleteCustomer=Fifo.getHead();
}
else if(result%3==1) {
     deleteCustomer=LRCO.getTail();
}
else {
    deleteCustomer=LFCO.getfirst();
}
    Fifo.removeItem(deleteCustomer);
    LRCO.removeItem(deleteCustomer);
    LFCO.remove(deleteCustomer);
    if(deleteCustomer.area==1) area1.remove(deleteCustomer);
    else area2.remove(deleteCustomer);
    customerInfo blank;
    handleID[deleteCustomer.ID-1]=blank;
    addCustomer(name,deleteCustomer.ID, result,deleteCustomer.area,1);
}

void reg(string name) {
    int result=getResult(name);
    int index=checkAvai(name);
if(index!=-1) {
customerInfo updateCustomer=handleID[index];
LFCO.updateOrder(updateCustomer);
LRCO.updateOrder(updateCustomer);
if(updateCustomer.area==1) area1.updateOrder(updateCustomer);
else area2.updateOrder(updateCustomer);
}// da co san khach do trong nha hang
else if (area1.checkFull() && area2.checkFull() ) {
manageFull(result,name);
}
else {
int newID=chooseID(result);
int newArea=chooseArea(result);
addCustomer(name,newID,result,newArea,1);
}
}

bool checkREG(string s) {
    if(s.find("REG ")!=0) return 0;
    unsigned int i=4;
    while(i<s.length()) {
        if(s[i]==' ' || s[i] <'A' || (s[i] >'Z' && s[i] <'a') || s[i] >'z') return 0;
        i++;
    }
    return 1;
    }

bool checkCLE(string s) {
if(s.find("CLE ")!=0) return 0;
unsigned int i=5;
if(s[4]!='-'&& !isdigit(s[4])) return 0;
while(i<s.length()) {
    if(s[i]== ' '|| s[i]< '0' || s[i] > '9') return 0;
    i++;
} 
return 1;
}




void simulate(string filename)
{
	for(int i=0;i<MAXSIZE;i++) {
   customerInfo empty;
   handleID[i]= empty;
}
     ifstream filein; // ifstream ofstream 
    filein.open(filename);
    string s;
     while (getline(filein,s))
    {
        if(checkREG(s)) {
            string name=s.substr(4);
            reg(name);
        }
        else if(checkCLE(s)) {
            string Snum=s.substr(4);
            clearCustomer(stoi(Snum));
        }
        else if(s=="PrintHT") area1.print();
        else if(s=="PrintAVL") area2.print();
        else if(s=="PrintMH") LFCO.print();
    }
    filein.close();
	return;
}