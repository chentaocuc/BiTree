// 建立二叉树
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define OK 			 1 
#define ERROR		 0
#define TRUE		 1
#define FALSE		 0
#define INFEASIBLE	-1
// #define OVERFLOW	-2
// 系统对 OVERFLOW 宏定义为 3

typedef int Status;			// 函数返回状态
typedef char TElemType;		// 树节点数据类型

// 二叉树的二叉链表存储表示
typedef struct BiTNode{
	TElemType data;
	int iflag, depth;
	struct BiTNode *LeftChild, *RightChild, *parent;
}BiTNode, *BiTree;

Status PreOrderTraverse(BiTree T, Status (* Visit)(TElemType e, int depth)){
	// 先序遍历树
	// 调用格式: PreOrderTraverse(T, PrintElement);
	if(T){
		if(Visit(T->data, T->depth))
			if(PreOrderTraverse(T->LeftChild, Visit))
				if(PreOrderTraverse(T->RightChild, Visit)) return OK;
		return ERROR;
	}else return OK;
} // PreOrderTraverse

Status PreOrderTraverse2(BiTree T, Status (* Visit)(TElemType e, int depth)){
	// 先序遍历树, 到达叶子, 打印完叶子后, 换行, 并回到根节点重新遍历
	// 并且不再遍历已经遍历过的路径.
	// 调用格式: PreOrderTraverse(T, PrintElement);
	int i;
	if(T){
		if(T->LeftChild || T->RightChild){
			if(!(T->iflag)){
				if(Visit(T->data, T->depth)){
					if(PreOrderTraverse2(T->LeftChild, Visit))
						if(PreOrderTraverse2(T->RightChild, Visit)) return OK;
					return ERROR;
				}else return OK;
			}
			else{	// 已经被打印过
				return OK;
			}
		}
		else{	// 已经到达叶子
			T->iflag = 1;
			if(Visit(T->data, T->depth)){
				for(i=T->depth; i>0; i--){
					T = T->parent;
				}
				if(PreOrderTraverse2(T->LeftChild, Visit))
					if(PreOrderTraverse2(T->RightChild, Visit)) return OK;
				return ERROR;
			}
			else return OK;
		}
	}else return OK;
} // PreOrderTraverse

Status PrintElement(TElemType e, int depth){
	printf("%*s", depth*4, "");
	printf("%c\n", e);
	return OK;
}

Status CreateTree(BiTree T){
	// 建树
	char ch;
	printf("\n Input: ");
	scanf("%c", &ch);
	if(ch == ' '){
		T = NULL;
		return OK;
	}
	else{
		if(!(T = (BiTNode *) malloc(sizeof(BiTNode)))){
			printf("OVERFLOW!\n");
			exit(OVERFLOW);
		}
		T->data = ch;	// 生成根节点
		printf("\n Input LeftChild: ");
		CreateTree(T->LeftChild);	// 创建孩子
		printf("\n Input RightChild: ");
		CreateTree(T->RightChild);	// 创建孩子的兄弟
	}
	return OK;
}

BiTree NewNode(){
	BiTree Node;
	Node = (BiTNode *) malloc(sizeof(BiTNode));
	return Node;
}

void main(){
	BiTNode T;
	BiTree PT = &T;
	int depth = 0;
	int i, j, k, m, n;
	
	// 根节点 D
	PT->data = 'D';
	PT->depth = depth;
	PT->iflag = 0;
	PT->LeftChild = NewNode();
	PT->RightChild = NewNode();
	PT->LeftChild->parent = PT;
	PT->RightChild->parent = PT;
	PT->parent = NULL;
	
	PT = PT->LeftChild;		// 进入子节点
	depth++;
	PT->data = 'B';
	PT->depth = depth;
	PT->iflag = 0;
	PT->LeftChild = NULL;
	PT->RightChild = NewNode();
	PT->RightChild->parent = PT;
	PT = PT->parent;		// 退回父节点
	depth--;
	
	PT = PT->RightChild;
	depth++;
	PT->data = 'A';
	PT->depth = depth;
	PT->iflag = 0;
	PT->LeftChild = PT->parent->LeftChild->RightChild;
	PT->RightChild = NULL;
	PT = PT->parent;		// 退回父节点
	depth--;
	
	PT = PT->LeftChild;		// 进入第1层
	depth++;
	PT = PT->RightChild;	// 进入第2层
	depth++;
	PT->data = 'C';
	PT->depth = depth;
	PT->iflag = 0;
	PT->LeftChild = NewNode();
	PT->RightChild = NewNode();
	PT->LeftChild->parent = PT;
	PT->RightChild->parent = PT;
	
	PT = PT->LeftChild;
	depth++;
	PT->data = '2';
	PT->depth = depth;
	PT->iflag = 0;
	PT->LeftChild = NULL;
	PT->RightChild = NewNode();
	PT->RightChild->parent = PT;
	PT = PT->parent;
	depth--;
	
	PT = PT->RightChild;
	depth++;
	PT->data = '1';
	PT->depth = depth;
	PT->iflag = 0;
	PT->LeftChild = PT->parent->LeftChild->RightChild;
	PT->RightChild = NULL;
	PT = PT->parent;
	depth--;
	
	// 叶子节点
	PT = PT->LeftChild;
	depth++;
	PT = PT->RightChild;
	depth++;
	PT->data = '3';
	PT->depth = depth;
	PT->iflag = 0;
	PT->LeftChild = NULL;
	PT->RightChild = NULL;
	
	for(i=0; i<depth; i++)
		PT = PT->parent;	
	
	PreOrderTraverse(PT, PrintElement);
	
	
	
	return;
}

