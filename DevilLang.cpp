#include <iostream>
#include <string>
using namespace std;

string Sentence="((ab)(cd))";

//Node
struct Node {
    char word;
    Node *next;
};




//Stack
class Stack{
private:
    Node *top,*base;
public:
    Stack();
    ~Stack();
    bool push(char e);
    bool pop();
    bool empty();
    char getTop();
    };



Stack::Stack(){
    top=base=NULL;
}


Stack::~Stack(){
    while (!empty()) {
        this->pop();
    }
}



bool Stack::push(char e){
    Node *p=new Node;
    if (!p) {
        cout<<"Overflow"<<endl;
        return false;
    }
p->word=e;
    if (empty()) {
        top=base=p;
    }else{
        p->next=top;
        top=p;
    }
    return true;
}



bool Stack::pop(){
    if(empty())
    {
        cout<<"Empty Stack"<<endl;
        return false;
    }else{

        Node *p;
        p=top;
        if (top==base) {
            top=base=NULL;
        }

        if (top!=base) {
            top=top->next;
        }

        if(p)delete p;
        //length--;
        return true;
    }

}

bool Stack::empty(){
    return base==NULL;
}

char Stack::getTop(){
    return top->word;
}


    class Queue{
    private:
        Node *front,*back;
    public:
        Queue();
        ~Queue();
        bool push(char e) ;
        bool pop();
        bool empty() ;
        char getFront();
        char getBack();
        bool Equal();
    };


Queue::Queue(){
    front=back=NULL;
}



Queue::~Queue(){
    while (!empty()) {
        this->pop();
    }
}


bool Queue::push(char e) {
    Node *p=new Node;
    if (p==NULL) {
        cout<<"Overflow"<<endl;
        return false;
    }
    p->word=e;
    if (empty()) {
        front=back=p;
    }else{
    back->next=p;//确保指针是从front指向back
    back=p;
    }

    return true;
}


bool Queue::pop(){

    if (empty()) {
        cout<<"Empty Queue"<<endl;
        return false;
    }
    Node *p=front;
    if (front==back) {
        front=back=NULL;
    }
    if (front!=back) {
        front=front->next;
        }
    if (p) {delete p;}

    return true;
}

bool Queue::empty() {
    return back==NULL;
}

char Queue::getFront(){
    if(!front){cout<<"Error!"<<endl; exit(1);}
    return front->word;
}

char Queue::getBack(){
    return back->word;
}


bool Queue::Equal(){
    return front==back;
}











//using recurrence func
class translation{
private:
    Stack S;
    Queue Q;
public:
    translation();
    ~translation();
    void readLanguge();
    void deBrackets(int&, Queue&);
    void deCapital(int&, Queue&);
    void deCapital(int&);
    void print();
};







translation::translation(){
 }



//Output
void translation::print(){
    Stack outra;
    while (!S.empty()) {
        outra.push(S.getTop());
        S.pop();
    }
    cout<<"Output (with recurrence)     :";
    while (!outra.empty()) {
        cout<<outra.getTop();
        outra.pop();
    }
    cout<<endl;
}





translation::~translation(){
}




void translation::readLanguge(){
    for (int i=0; i<Sentence.length(); i++) {

        if (Sentence[i]>='a'&&Sentence[i]<='z') {
            S.push(Sentence[i]);
        }else if(Sentence[i]==')'){
        }else if(Sentence[i]=='('){
            deBrackets(i, Q);
            while (!Q.empty()) {
                S.push(Q.getFront());
                Q.pop();
            }
        }else{
            deCapital(i);
        }




    }

    return;

}





void translation::deBrackets(int &i, Queue&Q){
    Queue src;
    i++;
    while (Sentence[i]!=')') {
        if (i==Sentence.length()-1) {
            cout<<"Error"<<endl;
            exit(1);
        }
        if (Sentence[i]=='(') {
            deBrackets(i, src);
        } else if(Sentence[i]<='z'&&Sentence[i]>='a'){
            src.push(Sentence[i]);
        }else{
            deCapital(i, src);
        }
        i++;
    }
    char theta=src.getFront();
    src.pop();
    Q.push(theta);
    
    {
        Stack tem;
    while (!src.empty()) {
        tem.push(theta);
        tem.push(src.getFront());
        src.pop();
    }
        while (!tem.empty()) {
            Q.push(tem.getTop());
            tem.pop();
        }
    }

}







void translation::deCapital(int&i, Queue&upper){
    if (Sentence[i]=='A') {
        upper.push('s');upper.push('a');upper.push('e');
    }else if(Sentence[i]=='B'){
        upper.push('t');upper.push('s');upper.push('a');upper.push('e');
       upper.push('d'); upper.push('s');upper.push('a');upper.push('e');
    }else{
        upper.push('?');
    }
    return;
}


void translation::deCapital(int &i){
    if (Sentence[i]=='A') {
        S.push('s');S.push('a');S.push('e');
    }else if(Sentence[i]=='B'){
        S.push('t');S.push('s');S.push('a');S.push('e');
        S.push('d'); S.push('s');S.push('a');S.push('e');
    }else{
        S.push('?');
    }
}














class newTranslation{

private:
    Stack S;
    Queue Q;
public:
    newTranslation();
    ~newTranslation();
    void readLanguage();
    void deBracket();
    void deCapital();
    void print();
    void pushTheta();
    void pushNn();


};


newTranslation::newTranslation(){
}

newTranslation::~newTranslation(){

}
//核心功能函数
//把解读完的数据存入栈中
void newTranslation::readLanguage(){
  for (int i=0;Sentence[i]!='\0' ; i++) {
        if ((Sentence[i]>='a'&&Sentence[i]<='z')||Sentence[i]=='(') {
            S.push(Sentence[i]);
        }else if(Sentence[i]=='A'){
            S.push('s');S.push('a');S.push('e');
        }else if(Sentence[i]=='B'){
            S.push('t');S.push('s');S.push('a');S.push('e');
            S.push('d');S.push('s');S.push('a');S.push('e');
        }else if(Sentence[i]==')'){
            deBracket();
        }else{
            S.push('?');
        }
    }
    return;
}





//去括号函数
void newTranslation::deBracket(){
    while (S.getTop()!='(') {
        if (S.empty()) {
            cout<<"Unpaired Bracket!"<<endl;
            exit(1);
        }
        Q.push(S.getTop());
        S.pop();
    }
    S.pop();
    pushTheta();
    while (!Q.Equal()) {
        pushNn();
        pushTheta();
        Q.pop();
    }
    Q.pop();
}








void newTranslation::print(){
    Stack outra;
    while (!S.empty()) {
        outra.push(S.getTop());
        S.pop();
    }
    cout<<"Output (without recurrence):";
    while (!outra.empty()) {
        cout<<outra.getTop();
        outra.pop();
    }
    cout<<endl;
}


void newTranslation::pushTheta(){
    char theta=Q.getBack();
    if (theta=='A') {
        S.push('s');S.push('a');S.push('e');
    }else if (theta=='B'){
        S.push('t');S.push('s');S.push('a');S.push('e');
        S.push('d');S.push('s');S.push('a');S.push('e');
    }else {
        S.push(theta);
    }
}



void newTranslation::pushNn(){
    char N=Q.getFront();
    if (N=='A') {
        S.push('s');S.push('a');S.push('e');
    }else if (N=='B'){
        S.push('t');S.push('s');S.push('a');S.push('e');
        S.push('d');S.push('s');S.push('a');S.push('e');
    }else {
        S.push(N);
    }

}





//mian func
int main(int argc, const char * argv[]) {
    cout<<"Enter the codes:"<<endl;
    cin>>Sentence;
  translation a;
    a.readLanguge();
    a.print();
   newTranslation b;
    b.readLanguage();
    b.print();
    cout<<"Original:"<<Sentence<<endl;

}
