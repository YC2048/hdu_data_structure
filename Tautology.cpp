/*



 运算符号构建次序
 优先级最低
 1.括号
 2.无括号或（逻辑加）
 3.无括号且（逻辑乘）
 4.无括号非
 5.有括号依次序

 构建过程：
 1.寻找无括号最低
 2.无括号则为非最后加一数字
 3.有括号则为括号内容
 4.括号内容在非后面则为单目运算
 5.括号内容在非外则为双目计算

 测试数据：
 (1)(A|~A)&(B|~B)              T
 (2)(A&~A)&C                     F
 (3) A|B|C|D|E|~A          T
 (4) A&B&C&~B                 F
 (5)(A|B)&(A|~B)                F
 (6)A&~B|~A&B                 S=

 */


#include <iostream>
#include <string>
#include <cctype>
using namespace std;


//定义节点
struct ExpNode{
    char item;
    int  weight;
    ExpNode(){}//无参数初始化
    ExpNode(char d, int w){item=d;weight=w;cout<<d<<w;}//带参数初始化
};
int trueCount=0;//语句为真计数
int falseCount=0;//语句为假计数
int wlength = 0; //字符串长度
int klength=0;//字符表达式种类
string input="(A|~A)&(B|~B)";//输入字符串
ExpNode KeyedArray[26];//赋值数组(代表26字母）
ExpNode WeightedArray[1000];//带权数组
void convertToWArray();//将字符串转化为带权数组
int root_of(int start,int end);//求根节点
int initKeyedArray();//初始化赋值数组
int value_of(char);//求某一字母表达式值
int virtualCreateTree(int start,int end);//由带权数组start位至end位构建二叉树
void assignValues(ExpNode *KeyedArray, int i);//赋值语句
void getResult();//获得答案










//将表达式写为数组
void convertToWArray(){
        int weight=0;
    cout<<"please enter the expression:"<<endl;
   cin>>input;
    wlength=(int) input.length();
    for (int i=0; input[i]!='\0'; i++) {
        //因为赋值数组只有26个字母，小写改大写
        if(input[i]>=97&&input[i]<=122) input[i]-=32;
        //输入数组
        switch(input[i]){
                //括号不会输入数组
            case '(':
                weight+=4;     //遇见左括号
                WeightedArray[i].item=input[i];
                WeightedArray[i].weight=0;
                break;
            case ')':
                weight-=4;      //遇见右括号
                WeightedArray[i].item=input[i];
                WeightedArray[i].weight=0;
                break;
            case '|':
                WeightedArray[i].item=input[i];
                WeightedArray[i].weight=weight+1;
                break;
            case '&':
               WeightedArray[i].item=input[i];
                WeightedArray[i].weight=weight+2;
                break;
            case '~':
              WeightedArray[i].item=input[i];
                WeightedArray[i].weight=weight+3;
                break;
            default:
                //只输入字母
                if (isalpha(input[i])) {
                    WeightedArray[i].item=input[i];
                    WeightedArray[i].weight=0;//imply the data is char
                }else{
                    cout<<"ERRCHAR"<<endl;
                    exit(1);
                }
                break;
        }
    }
    //括号不对称问题
    if (weight!=0) {
        cout<<"ERRBRKTS"<<endl;
        exit(1);
    }
        return;
}



//查找表达式中权值最小节点作为子树的根节点
int root_of(int start,int end){
    //错误抛出
    if (start>end) {
        cout<<"ERRMIN"<<endl;
        exit(1);
    }
        int key=0;
        int current=start;
        int position=0;
        while(!WeightedArray[current].weight){
            key=WeightedArray[current].weight;current++;
        }
        key= current>end?key:WeightedArray[current].weight;
        position=current>end?0:current;
    //若current大于end则key不变，否则为权值数组权值
    //若current大于end则取起始位置为0，否则由current起始
        while(current<=end){
               if(WeightedArray[current].weight&&WeightedArray[current].weight<key){
                      position=current;
                      key=WeightedArray[current].weight;
                       }
               current++;
                }
        return position;
}





//分析原表达式，提取所有变量 就是把所有变量罗列在一个数组内
int initKeyedArray(){
        int assign[26]={0};//26个字母
    for(int i=0;WeightedArray[i].item!='\0';i++){
        if(WeightedArray[i].item>=65&&WeightedArray[i].item<=90){
                   if(!assign[(int)(WeightedArray[i].item-65)]){
                       assign[(int)(WeightedArray[i].item-65)]=1;
                       KeyedArray[klength].item=WeightedArray[i].item;
                                  klength++;
                              }
                       }
                }
        return 0;
}

//查找每个变量所代表值 0或1
int value_of(char Exp){
        int position=0;
        while(KeyedArray[position].item!=Exp){
               position++;
                }
        return KeyedArray[position].weight;
}

//虚拟构建一个二叉树 注意并没有真正构建 不过可理解为建立一个树了 算法核心是一个类似中序遍历二叉树
 //在以start和end的范围内建子树
//返回为左右子树表达式计算结果
int virtualCreateTree(int start,int end){
        int key=0;
    if(start==end)  {           //start==end 表明这个是叶子节点 那么里面是个变量
        int value = value_of(WeightedArray[start].item);
        return value;
    }else if(start>end){
            return 1;
            //start>end  处理~的特殊情况
        }else{
             //寻找最小权值  作为子树根节点
               key=root_of(start,end);
            bool lchild;
            bool rchild ;
               switch(WeightedArray[key].item){
                   case '|':
                       //递归左右子树并运算
                       //|符号
                       lchild = virtualCreateTree(start,key-1);
                       rchild = virtualCreateTree(key+1,end);
                       return (lchild||rchild);
                      break;
                   case '&':
                       //&符号
                       lchild = virtualCreateTree(start,key-1);
                       rchild = virtualCreateTree(key+1,end);
                       return (lchild&&rchild);
                      break;
                       //~符号
                       case '~':
                       rchild = virtualCreateTree(key+1,end);
                       return (!rchild);
                       break;
                   }
                }
    return 0;
}



//递归给所有变量赋值
//从i开始
void assignValues(ExpNode *KeyedArray, int i){
    //cout<<i;
    //只有一个变量的时候赋1就可以（因为默认为0）
    if (klength==1) {
        i++;
        switch (virtualCreateTree(0, wlength-1)){
            case 1:
                trueCount++;
                break;
            case 0:
                falseCount++;
                break;
            default :
                break;
        }
        //赋值为1
        KeyedArray->weight=1;
        switch (virtualCreateTree(0, wlength-1)){
            case 1:
                trueCount++;
                break;
            case 0:
                falseCount++;
                break;
            default :
                break;
        }
    }else if(i<klength){
            //在多个变量的时候，赋值所有可能分支，在最后都会清算结果
        KeyedArray[i].weight=0;    //当前变量取0
               assignValues(KeyedArray,i+1);    //递归调用下一个变量直至i=klength
        KeyedArray[i].weight=1;    //当前变量取1
               assignValues(KeyedArray,i+1);    //递归调用下一个变量
    //递归结束i=klength时
          }else{
              //但仅有真值或假值时程序运行
               if(!trueCount||!falseCount){
                   int extractedExpr = virtualCreateTree(0,(int)wlength-1);
                   switch(extractedExpr){
                              case 1:
                                  trueCount++;
                                  break;
                              case 0:
                                  falseCount++;
                                  break;
                              default :
                                  break;
                          }
                       }
               else
                  return ;
                }
}



//结果处理
void getResult(){
        int i=0;
    //真假都存在
        if(trueCount&&falseCount){
            cout<<"Variables listed as below::"<<endl;;
               while(i<klength){
                   cout<<KeyedArray[i].item<<":"<<"satisfactible"<<endl;
                   i++;
               }
    //仅有真式
        }else if((!trueCount)&&falseCount)
            cout<<"false forever"<<endl;
    //仅有假式
        else if(trueCount&&(!falseCount)){
            cout<<"true forever"<<endl;
        }else cout<<"ERRFIN"<<endl;
    return;
}



int main(){
    convertToWArray();
    initKeyedArray();
    assignValues(KeyedArray,0);
    getResult();
    return 0;
}
