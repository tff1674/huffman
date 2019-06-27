#include <iostream>
#include <queue>
 using namespace std;
 #define MAXCODELEN 100
#define MAXHAFF 100
#define MAXCODE 100
#define MAXWEIGHT  10000;
typedef struct Haffman
{
    int weight;
    char ch;
    int parent;
    int leftChild;
    int rightChild;
	int index;
}HaffmaNode;
 
struct cmp 
{
	bool operator() (HaffmaNode haffman1, HaffmaNode haffman2)
	{
		return haffman1.weight > haffman2.weight;
	}	
};
 
typedef struct Code
{
    int code[MAXCODELEN];
    int start;
}HaffmaCode;
 
HaffmaNode haffman[MAXHAFF];
HaffmaCode code[MAXCODE];
priority_queue<HaffmaNode, vector<HaffmaNode>, cmp> que;
void buildHaffman(int all)
{
    for (int i = 0; i < all * 2 - 1; ++i)
    {
        haffman[i].weight = 0;
        haffman[i].parent = -1;
        haffman[i].leftChild = -1;
        haffman[i].rightChild = -1;
		haffman[i].index = -1;
    }
    for (int i = 0; i < all; i++)
    {
        std::cout << "请输入第"<<i+1<<"个"<< "哈夫曼字符和权重" << std::endl;
        std::cin >> haffman[i].ch;
        std::cin >> haffman[i].weight;
		haffman[i].index = i;
		que.push(haffman[i]);
    }
 
	for (int i = 0; i < all - 1; ++i) 
	{
		HaffmaNode node1, node2;
		node1 = que.top();
		que.pop();
		node2 = que.top();
		que.pop();
		haffman[all + i].weight = node1.weight + node2.weight;		
		haffman[all + i].leftChild = node1.index;
		haffman[all + i].rightChild = node2.index;
		haffman[all + i].index = all + i;
		haffman[node1.index].parent = all + i;
		haffman[node2.index].parent = all + i;
		que.push(haffman[all + i]);
	}
	
}
void printCode(int all)
{
    HaffmaCode hCode;
    int curParent;
    int c;
    for (int i = 0; i < all; ++i)
    {
        hCode.start = all - 1;
        c = i;
        curParent = haffman[i].parent;
        while (curParent != -1)
        {
            if (haffman[curParent].leftChild == c)
            {
                hCode.code[hCode.start] = 0;
            }
            else
            {
                hCode.code[hCode.start] = 1;
            }
            hCode.start--;
            c = curParent;
            curParent = haffman[c].parent;
        }
        for (int j = hCode.start + 1; j < all; ++j)
        {
            code[i].code[j] = hCode.code[j];
        }
        code[i].start = hCode.start;
    }
}
int main()
{
    std::cout << "请输入有多少个哈夫曼字符" << std::endl;
    int all = 0;
    std::cin >> all;
    if (all <= 0)
    {
        std::cout << "您输入的个数有误" << std::endl;
        return -1;
    }
    buildHaffman(all);
    printCode(all);
	for (int i = 0; i < all; ++i)
    {
        std::cout << haffman[i].ch << ": Haffman Code is:";
        for (int j = code[i].start + 1; j < all; ++j)
        {
            std::cout << code[i].code[j];
        }
        std::cout << std::endl;
    }
    return 0;
}


