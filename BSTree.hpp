#ifndef _BSTREE_HPP_
#define _BSTREE_HPP_

#include <iostream>
#include <cassert>

enum class inclusionInNode { margeLeft , margeRight, noMarge };

struct BSTree
{
	struct Node
	{
		int m_minKey;
		int m_maxKey;

		Node * m_pParent;
		Node * m_pLeft;
		Node * m_pRight;
	};

	Node * m_pRoot;
};

BSTree * BSTreeCreate();


void BSTreeDestroy(BSTree * _pTree);


void BSTreeInsertKey(BSTree & _tree, int _key);


bool BSTreeHasKey(const BSTree & _tree, int _key);


BSTree::Node * BSTreeFindKeyNode(const BSTree & _tree, int _key);


int BSTreeMinimum(const BSTree & _tree);


int BSTreeMaximum(const BSTree & _tree);


typedef void(*BSTreeWalkFunction) (const BSTree::Node & _node);
void BSTreeSymmetricWalk(const BSTree & _tree, BSTreeWalkFunction _f);


void BSTreeDeleteKey(BSTree & _tree, int _key);


BSTree::Node * BSTreeCreateNode(int _keyMin, int _keyMax);

inclusionInNode BSTreeFindRange(BSTree::Node * pCurrent, int _key);

inclusionInNode BSTreeFindRange(BSTree::Node * pCurrent, int _keyMin, int _keyMax);

void BSTreeRebuildАfterInsert(BSTree & _tree, BSTree::Node * pCurrent);

void BSTreeInsertRange(BSTree & _tree, int _keyMin, int _keyMax);

void BSTreeNodeChildren(BSTree & _tree, BSTree::Node * pDyingNode);


#endif

