/***********************************************
*name	:red-black tree
*author	:hanshaoteng
*time	:2011-4-7
*des	:���ļ���Ҫ��ʵ���˺�����������������
*		 ��ʽʵ�֡�	
************************************************/
#ifndef RBTREE_H
#define RETREE_H
#include <cstdlib>

//����ڵ����ɫ����Ϊ��ɫ�ͺ�ɫ
enum NodeColor {
    BLACK = 0,
    RED
};

template <class Type>
class TreeNode {
//�������еĽڵ㣬����Ĳ���˵�����£�
//m_data	:�ڵ��е�����ֵ
//m_left	:�ڵ��������
//m_right	:�ڵ��������
//m_parent	:�ڵ�ĸ��׽ڵ�
//m_color	:�ڵ����ɫ
public:
    TreeNode() : m_left(NULL),m_right(NULL),m_parent(NULL),m_color(BLACK) {}
    Type m_data;
    TreeNode<Type>* m_left;
    TreeNode<Type>* m_right;
    TreeNode<Type>* m_parent;
    NodeColor m_color;    
};

template <class Type>
class RbTree {
public:
    typedef TreeNode<Type>* TreeRoot;
    typedef TreeNode<Type>* TreeNodePointer;
    RbTree();
    ~RbTree();
    void Insert(const Type&);
    void Delete(const Type&);
    void ShowNode(TreeNodePointer);					//���ݽڵ��ָ���ַ��ʵ�ڵ��ֵ
    TreeNodePointer Successor(TreeNodePointer);		//���ؽڵ��̽ڵ��ָ��
    TreeNodePointer Search(const Type&);			//����ֵ�����ڵ��ָ��
    void Show();									//�����������ֵ
private:
    void LeftRotate(TreeNodePointer);				//����ת
    void RightRotate(TreeNodePointer);				//����ת
    void InsertFixup(TreeNodePointer);				//����֮�󣬵���������ɫ��ʹ����������
    void DeleteFixup(TreeNodePointer);				//ɾ��֮�󣬵���������ɫ��ʹ����������
    TreeRoot m_root;								//���ĸ�ָ��
    TreeNode<Type> m_nil;							//�൱�ڿ�ָ��
};
#endif
