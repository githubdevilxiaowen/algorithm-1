#ifndef CPLUSPLUS_H
#define CPLUSPLUS_H
#include <iostream>

static const int MaxKeys = 3;				//����B���Ķȣ�ÿ���ڵ�Ĺؼ��֣�����ΪMaxKeys�����Ϊ2*MaxKeys+1��
											//��Ӧ���ӽڵ�������MaxKeys+1.���2*MaxKeys + 2

typedef int Tvalue;
typedef int Tkey;

class BTNode {
public:
	Tkey keys[2*MaxKeys+1];					//�洢�ýڵ��keys��ֱ�����ó����ֵ
	Tvalue values[2*MaxKeys+1];
	int numKeys;
	bool hasLeaf;							//��ʶ�ýڵ��Ƿ����ӽڵ�
	BTNode* childs[2*MaxKeys + 2];
	BTNode() : numKeys(0), hasLeaf(true) {	//�ڹ��캯���У���ʼ�������Ľڵ�
		for (int i=0; i<2*MaxKeys+2; ++i)
			childs[i] = NULL;
	}
};

typedef BTNode* PBTNode;

class Bplusplus {
public:
	Bplusplus();
	void Create();										//����һ���յ�B��
	void Split(PBTNode, int, PBTNode);					//��һ����������ʶ���ڵ㣻�ڶ������������ڵ���key�ؼ��ֵ�index��
														//��������������Ҫ��ֵ��ӽڵ�
	void Search(Tkey);
	void Insert(Tkey, Tvalue);
	void Show(PBTNode);
	void Show();
	void InsertNonFull(PBTNode, Tkey, Tvalue);
	void Delete(PBTNode, Tkey);
	void Delete(Tkey);
	int isKeyInNode(PBTNode, Tkey);						//�������ڵ�keys�е�λ��
	void DeleteKeyInLeafNode(PBTNode, int);				//ɾ���ӽڵ��е�keyֵ
	void MergeNodes(PBTNode, Tkey, Tvalue, PBTNode);	//���ӽڵ�1+���ڵ��е�key+�ӽڵ�2�ϲ����ӽڵ�1
	PBTNode Recuision(PBTNode, Tkey);					//�Խڵ���еݹ������ֱ���ҵ�������key�Ľڵ�
private:
	PBTNode root;
};
#endif