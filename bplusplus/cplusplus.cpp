#include "cplusplus.h"
#include <queue>


void Bplusplus::Create() {
	root = new BTNode();
}

Bplusplus::Bplusplus() {
	Create();
}

void Bplusplus::Split(PBTNode parent, int childIndex, PBTNode child) {
	/**
	*parent:		���׽ڵ�
	*childIndex��	���׽ڵ���key��������
	*child:			child = parent->childs[childIndex],����Ҫ���в�ֵĽڵ�
	*child�������ӽڵ㣬��parent�ǲ����Ľڵ㣬���Ƚ�child��ֳ������ӽڵ㣬ÿһ�ӽڵ�Ĵ�СΪMaxKeys,
	*Ȼ���м��key��������parent�У������²�ֵ��ӽڵ���뵽parent��childs�С�
	*/
	PBTNode newNode = new BTNode();
	newNode->hasLeaf = child->hasLeaf;
	newNode->numKeys = MaxKeys;
	for (int i=0; i<MaxKeys; i++) {						//��child�ڵ��еĺ�MaxKeys��keys��values���뵽�½��Ķ��ڵ���
		newNode->keys[i] = child->keys[MaxKeys+1+i];
		newNode->values[i] = child->values[MaxKeys+1+i];
	}
	if (!child->hasLeaf) {								//���child���ӽڵ㣬û�б�Ҫ���ýڵ�childs���е��½ڵ�
		for (int j=0; j<MaxKeys+1; ++j) {
			newNode->childs[j] = child->childs[j+MaxKeys+1];
		}
	}
	child->numKeys = MaxKeys;

	for (int k=2*MaxKeys; k>childIndex; --k) {			//parent˳����λ��Ϊ��������key��λ��
		parent->keys[k] = parent->keys[k-1];
		parent->values[k] = parent->values[k-1];
	}
	parent->keys[childIndex] = child->keys[MaxKeys];
	parent->values[childIndex]  = child->values[MaxKeys];
	parent->numKeys++;
	for (int k=2*MaxKeys+1; k>childIndex+1; --k) {		//��parent������½����ӽڵ�
		parent->childs[k] = parent->childs[k-1];
	}
	parent->childs[childIndex+1] = newNode;
}

void Bplusplus::Insert(Tkey key, Tvalue value) {
	PBTNode child = root;
	if (root->numKeys == 2*MaxKeys+1) {			//������ڵ������ģ�������Ҫ�½�һ���ڵ���Ϊ���ڵ㣬Ȼ���֡����롣
		PBTNode newNode = new BTNode();
		newNode->hasLeaf = false;
		newNode->numKeys = 0;
		newNode->childs[0] = root;
		root = newNode;
		Split(root,0,child);
		InsertNonFull(root,key,value);
	} else {
		InsertNonFull(root,key,value);
	} 
}

void Bplusplus::InsertNonFull(PBTNode parent, Tkey key, Tvalue value) {
	/**
	*��key��value���뵽�ڵ��С�
	*�����жϸýڵ��Ƿ�ΪҶ�ӽڵ㣬����ǣ���ֱ�Ӳ��룬��ϡ�
	*�������Ҷ�ӽڵ㣬�ҵ����ڵ��ӽڵ㣬�ж��Ƿ�����������֣����֮���ж�key�������Ǹ��µ��ӽڵ��У��ݹ�
	**/
	int num = parent->numKeys-1;
	if (parent->hasLeaf) {
		while (num>=0 && key<parent->keys[num]) {
			parent->keys[num+1] = parent->keys[num];
			parent->values[num+1] = parent->values[num];
			num--;
		}
		parent->keys[num+1] = key;
		parent->values[num+1] = value;
		parent->numKeys++;
	} else {
		while (num>=0 && key<parent->keys[num]) {
			num--;
		};
		num++;
		PBTNode newNode = parent->childs[num];
		if (newNode->numKeys == 2*MaxKeys+1) {
			Split(parent,num,newNode);
			if (key > parent->keys[num])
				num++;
		}
		InsertNonFull(parent->childs[num],key,value);
	}
}

void Bplusplus::Show(PBTNode newNode) {
	/*�����е�Ҷ�ӽڵ����
	std::queue<PBTNode> queue;
	if (NULL!=root) {
		queue.push(root);
		while(!queue.empty()) {
			PBTNode newNode = queue.front();
			queue.pop();
			if (newNode->hasLeaf) {
				for (int i=0; i<newNode->numKeys; ++i)
					std::cout << newNode->values[i] << std::endl;
			} else {
				for (int i=0; i<newNode->numKeys+1; ++i)
					queue.push(newNode->childs[i]);
			}
		}
	}
	*/
	/*
	*���õݹ�ķ�ʽ���B����ֵ
	*/
	if (NULL == newNode)
		return;
	for (int i=0; i<newNode->numKeys; ++i) {
		Show(newNode->childs[i]);
		std::cout << newNode->values[i] << std::endl;
	}
	Show(newNode->childs[newNode->numKeys]);
}

void Bplusplus::Show() {
	Show(root);
}

int Bplusplus::isKeyInNode(PBTNode pNode, Tkey key) {
	//�ж�key�Ƿ��ڸýڵ���
	for (int i=0; i<pNode->numKeys; ++i) {
		if (key == pNode->keys[i])
			return i+1;
	}
	return 0;
}

void Bplusplus::DeleteKeyInLeafNode(PBTNode pNode, int keyIndex) {
	pNode->numKeys--;
	for (int i=keyIndex; i<pNode->numKeys; ++i) {
		pNode->keys[i] = pNode->keys[i+1];
		pNode->values[i] = pNode->values[i+1];
	}
}

void Bplusplus::MergeNodes(PBTNode pNode1, Tkey key, Tvalue value, PBTNode pNode2) {
	pNode1->keys[pNode1->numKeys] = key;
	pNode1->values[pNode1->numKeys] = value;
	pNode1->numKeys++;
	int i=0;
	for (; i<pNode2->numKeys; ++i) {
		pNode1->keys[pNode1->numKeys+i] = pNode2->keys[i];
		pNode1->values[pNode1->numKeys+i] = pNode2->values[i];
		pNode1->childs[pNode1->numKeys+i] = pNode2->childs[i];
	}
	pNode1->numKeys += pNode2->numKeys;
	pNode1->childs[pNode1->numKeys] = pNode2->childs[i];
}

PBTNode Bplusplus::Recuision(PBTNode pNode, Tkey key) {
	/*
	*���key����pNode�У���һֱ�ݹ���ã�ֱ���ҵ�key���ڵĽڵ�
	*����ýڵ��keys��������maxkeys����ݹ���á�
	*���С�ڵ���maxkeys����Ҫ�����ҵ��ֵܽڵ㣬������ҵ��ֵܽڵ���һ���ڵ��keys��ʽ����maxkeys��
	*�򽫸ýڵ��һ���ؼ��֣��ᵽ���׽ڵ㣬�����׽ڵ�Ĺؼ������Ƶ��ýڵ㣬�Ըýڵ���еݹ顣
	*�����С�ڵ���maxkeys������кϲ������µĽڵ���еݹ�
	*/
	if (!isKeyInNode(pNode,key)) {
		int childIndex = pNode->numKeys-1;
		while (childIndex>=0 && key<pNode->keys[childIndex])
			childIndex--;
		childIndex++;
		PBTNode childNode = pNode->childs[childIndex];
		if (pNode->childs[childIndex]->numKeys <= MaxKeys) {
			if (childIndex>0 && pNode->childs[childIndex-1]->numKeys>MaxKeys) {
				pNode->childs[childIndex]->childs[pNode->childs[childIndex]->numKeys+1] = pNode->childs[childIndex]->childs[pNode->childs[childIndex]->numKeys];
				for (int i=pNode->childs[childIndex]->numKeys; i>0; --i) {
					pNode->childs[childIndex]->keys[i] = pNode->childs[childIndex]->keys[i-1];
					pNode->childs[childIndex]->values[i] = pNode->childs[childIndex]->values[i-1];
					pNode->childs[childIndex]->childs[i] = pNode->childs[childIndex]->childs[i-1];
				}
				pNode->childs[childIndex]->keys[0] = pNode->keys[childIndex-1];
				pNode->childs[childIndex]->values[0] = pNode->values[childIndex-1];
				pNode->childs[childIndex]->childs[0] = pNode->childs[childIndex-1]->childs[pNode->childs[childIndex-1]->numKeys];
				pNode->keys[childIndex-1] = pNode->childs[childIndex-1]->keys[pNode->childs[childIndex-1]->numKeys-1];
				pNode->values[childIndex-1] = pNode->childs[childIndex-1]->values[pNode->childs[childIndex-1]->numKeys-1];
				pNode->childs[childIndex-1]->numKeys--;
			} else if (childIndex<pNode->numKeys && pNode->childs[childIndex+1]->numKeys>MaxKeys) {
				pNode->childs[childIndex]->keys[pNode->childs[childIndex]->numKeys] = pNode->keys[childIndex];
				pNode->childs[childIndex]->values[pNode->childs[childIndex]->numKeys] = pNode->values[childIndex];
				pNode->childs[childIndex]->childs[pNode->childs[childIndex]->numKeys+1] = pNode->childs[childIndex+1]->childs[0];
				pNode->keys[childIndex] = pNode->childs[childIndex+1]->keys[0];
				pNode->values[childIndex] = pNode->childs[childIndex+1]->values[0];
				pNode->childs[childIndex]->numKeys++;
				int i=0;
				for (; i<pNode->childs[childIndex+1]->numKeys-1; ++i) {
					pNode->childs[childIndex+1]->keys[i] = pNode->childs[childIndex+1]->keys[i+1];
					pNode->childs[childIndex+1]->values[i] = pNode->childs[childIndex+1]->values[i+1];
					pNode->childs[childIndex+1]->childs[i] = pNode->childs[childIndex+1]->childs[i+1];
				}
				pNode->childs[childIndex+1]->childs[i] =pNode->childs[childIndex+1]->childs[i+1];
				pNode->childs[childIndex+1]->numKeys--;
			} else {
				if (childIndex>0 && childIndex<=pNode->numKeys)
					MergeNodes(pNode->childs[childIndex-1], key,  pNode->values[childIndex-1], pNode->childs[childIndex]);
				else
					MergeNodes(pNode->childs[childIndex], key,  pNode->values[childIndex], pNode->childs[childIndex+1]);
			}
		}
		return Recuision(pNode->childs[childIndex], key);
	}
	return pNode;
}

void Bplusplus::Delete(PBTNode pNode, Tkey key) {
	if (isKeyInNode(pNode,key)) {
		int keyIndex = isKeyInNode(pNode,key)-1;
		if (pNode->hasLeaf)							//���key�ڸýڵ��У����ҽڵ����ӽڵ㣬��ֱ��ɾ��key
			DeleteKeyInLeafNode(pNode,keyIndex);
		else {										//���key�ڸýڵ��У����ҽڵ����ڽڵ�
			if (pNode->childs[keyIndex]->numKeys > MaxKeys) {	//���key��Ҷ�ӽڵ��key��������ΪMaxKeys+1��
				pNode->keys[keyIndex] = pNode->childs[keyIndex]->keys[pNode->childs[keyIndex]->numKeys-1]; //��key���ӽڵ��ǰ�������Լ�
				pNode->values[keyIndex] = pNode->childs[keyIndex]->values[pNode->childs[keyIndex]->numKeys-1];
				Delete(pNode->childs[keyIndex], pNode->keys[keyIndex]);									//�ݹ��ɾ���ӽڵ��keyֵ
			} else if (pNode->childs[keyIndex+1]->numKeys > MaxKeys) {
				pNode->keys[keyIndex] = pNode->childs[keyIndex+1]->keys[0]; //��key���ӽڵ��ǰ�������Լ�
				Delete(pNode->childs[keyIndex+1], pNode->keys[keyIndex]);	
			} else {
				MergeNodes(pNode->childs[keyIndex], key, pNode->values[keyIndex], pNode->childs[keyIndex+1]);
				DeleteKeyInLeafNode(pNode,keyIndex);
				for (int i=keyIndex+1; i<pNode->numKeys; ++i) {
					pNode->childs[i] = pNode->childs[i+1];
				}
			}
		}//if else end
	} else {
		PBTNode pNewNode = Recuision(pNode, key); //�ҵ�key���ڵĽڵ�
		Delete(pNewNode, key);
	}
}

void Bplusplus::Delete(Tkey key) {
	Delete(root,key);
}