#include "BSTree.hpp"

BSTree * BSTreeCreate()
{
	BSTree * pTree = new BSTree;
	pTree->m_pRoot = nullptr;
	return pTree;
}

void BSTreeDestroy(BSTree::Node * _pNode)
{
	if (!_pNode)
		return;

	BSTreeDestroy(_pNode->m_pLeft);
	BSTreeDestroy(_pNode->m_pRight);
	delete _pNode;
}

void BSTreeDestroy(BSTree * _pTree)
{
	BSTreeDestroy(_pTree->m_pRoot);
	delete _pTree;
	_pTree = nullptr;
}

BSTree::Node * BSTreeCreateNode(int _key)
{
	BSTree::Node * pNewNode = new BSTree::Node;
	pNewNode->m_maxKey = _key;
	pNewNode->m_minKey = _key;
	pNewNode->m_pLeft = pNewNode->m_pRight = pNewNode->m_pParent = nullptr;
	return pNewNode;
}

void BSTreeInsertKey(BSTree & _tree, int _key)
{
	BSTree::Node * pCurrent = _tree.m_pRoot;
	if (!pCurrent)
	{
		_tree.m_pRoot = BSTreeCreateNode(_key);
		return;
	}

	while (pCurrent)
	{
		if (pCurrent->m_minKey <= _key && pCurrent->m_maxKey >= _key)
			return;

		else if (BSTreeFindRange(pCurrent, _key) == inclusionInNode::margeLeft)
		{
			pCurrent->m_minKey = _key;	
			BSTreeRebuildАfterInsert(_tree, pCurrent);
			return;
		}

		else if (BSTreeFindRange(pCurrent, _key) == inclusionInNode::margeRight)
		{
			pCurrent->m_maxKey = _key;
			BSTreeRebuildАfterInsert(_tree, pCurrent);
			return;
		}

		else if (_key < pCurrent->m_minKey)
		{
			if (pCurrent->m_pLeft)
				pCurrent = pCurrent->m_pLeft;

			else
			{
				BSTree::Node * pNewNode = BSTreeCreateNode(_key);
				pNewNode->m_pParent = pCurrent;
				pCurrent->m_pLeft = pNewNode;
				return;
			}
		}

		else
		{
			if (pCurrent->m_pRight)
				pCurrent = pCurrent->m_pRight;

			else
			{
				BSTree::Node * pNewNode = BSTreeCreateNode(_key);
				pNewNode->m_pParent = pCurrent;
				pCurrent->m_pRight = pNewNode;
				return;
			}
		}
	}
}

BSTree::Node * BSTreeFindKeyNode(const BSTree & _tree, int _key)
{
	BSTree::Node * pCurrent = _tree.m_pRoot;
	while (pCurrent)
	{
		if (pCurrent->m_minKey <= _key && pCurrent->m_maxKey >= _key)
			return pCurrent;

		else if (_key < pCurrent->m_minKey)
			pCurrent = pCurrent->m_pLeft;

		else
			pCurrent = pCurrent->m_pRight;
	}

	return nullptr;
}

bool BSTreeHasKey(const BSTree & _tree, int _key)
{
	return BSTreeFindKeyNode(_tree, _key) != nullptr;
}

BSTree::Node * BSTreeMinimumNode(BSTree::Node * _pNode)
{
	assert(_pNode);

	BSTree::Node * pCurrent = _pNode;
	while (pCurrent && pCurrent->m_pLeft)
		pCurrent = pCurrent->m_pLeft;

	return pCurrent;
}

int BSTreeMinimum(const BSTree & _tree)
{
	BSTree::Node * pMinimumNode = BSTreeMinimumNode(_tree.m_pRoot);
	return pMinimumNode->m_minKey;
}

int BSTreeMaximum(const BSTree & _tree)
{
	assert(_tree.m_pRoot);

	const BSTree::Node * pCurrent = _tree.m_pRoot;
	while (pCurrent && pCurrent->m_pRight)
		pCurrent = pCurrent->m_pRight;

	return pCurrent->m_maxKey;
}

void BSTreeSymmetricWalk(const BSTree::Node * _pNode, BSTreeWalkFunction _f)
{
	if (!_pNode)
		return;

	BSTreeSymmetricWalk(_pNode->m_pLeft, _f);
	(*_f)(*_pNode);
	BSTreeSymmetricWalk(_pNode->m_pRight, _f);
}

void BSTreeSymmetricWalk(const BSTree & _tree, BSTreeWalkFunction _f)
{
	BSTreeSymmetricWalk(_tree.m_pRoot, _f);
}

void BSTreeTransplant(BSTree & _tree, BSTree::Node * _pNode, BSTree::Node * _pOtherNode)
{
	if (!_pNode->m_pParent)
	{
		assert(_pNode == _tree.m_pRoot);
		_tree.m_pRoot = _pOtherNode;
	}

	else if (_pNode->m_pParent->m_pLeft == _pNode)
		_pNode->m_pParent->m_pLeft = _pOtherNode;

	else if (_pNode->m_pParent->m_pRight == _pNode)
		_pNode->m_pParent->m_pRight = _pOtherNode;

	else
		assert(0);

	if (_pOtherNode)
		_pOtherNode->m_pParent = _pNode->m_pParent;
}

void BSTreeDeleteKey(BSTree & _tree, int _key)
{
	BSTree::Node * pNode = BSTreeFindKeyNode(_tree, _key);
	if (!pNode)
		return;

	if (pNode->m_minKey != pNode->m_maxKey)
	{
		if (_key == pNode->m_minKey)
		{
			pNode->m_minKey++;
		}

		else if (_key == pNode->m_maxKey)
		{
			pNode->m_maxKey--;
		}

		else if (_key > pNode->m_minKey && _key < pNode->m_maxKey)
		{
			int m_newMaxKey = pNode->m_maxKey;
			pNode->m_maxKey = _key - 1;

			if (m_newMaxKey > _key + 1)
				BSTreeInsertRange(_tree, _key + 1, m_newMaxKey);

			else
				BSTreeInsertKey(_tree, m_newMaxKey);
		}
	}

	else
	{
		if (!pNode->m_pLeft)
		{
			BSTreeTransplant(_tree, pNode, pNode->m_pRight);
		}

		else if (!pNode->m_pRight)
		{
			BSTreeTransplant(_tree, pNode, pNode->m_pLeft);
		}

		else
		{
			BSTree::Node * pNextNode = BSTreeMinimumNode(pNode->m_pRight);
			if (pNextNode->m_pParent != pNode)
			{
				BSTreeTransplant(_tree, pNextNode, pNextNode->m_pRight);
				pNextNode->m_pRight = pNode->m_pRight;
				pNextNode->m_pRight->m_pParent = pNextNode;
			}

			BSTreeTransplant(_tree, pNode, pNextNode);
			pNextNode->m_pLeft = pNode->m_pLeft;
			pNextNode->m_pLeft->m_pParent = pNextNode;
		}
		delete pNode;
	}
}

inclusionInNode  BSTreeFindRange(BSTree::Node * pCurrent, int _key)
{
	if (_key + 1 == pCurrent->m_minKey)
		return inclusionInNode::margeLeft;

	else if (_key - 1 == pCurrent->m_maxKey)
		return inclusionInNode::margeRight;

	return inclusionInNode::noMarge;
}

inclusionInNode  BSTreeFindRange(BSTree::Node * pCurrent, int _keyMin, int _keyMax)
{
	if (_keyMax + 1 == pCurrent->m_minKey)
		return inclusionInNode::margeLeft;

	else if(pCurrent->m_minKey <= _keyMin && pCurrent->m_maxKey >= _keyMin)
		return inclusionInNode::margeRight;

	else if (pCurrent->m_minKey <= _keyMax && pCurrent->m_maxKey >= _keyMax)
		return inclusionInNode::margeLeft;

	else if (_keyMin - 1 == pCurrent->m_maxKey)
		return inclusionInNode::margeRight;

	return inclusionInNode::noMarge;
}

void BSTreeRebuildАfterInsert(BSTree & _tree, BSTree::Node * pCurrent)
{
	BSTree::Node * pMargeLeftSideNode = BSTreeFindKeyNode(_tree, pCurrent->m_minKey - 1);
	BSTree::Node * pMargeRightSideNode = BSTreeFindKeyNode(_tree, pCurrent->m_maxKey + 1);

	if (pMargeLeftSideNode)
	{
		pCurrent->m_minKey = pMargeLeftSideNode->m_minKey;

		BSTreeNodeChildren(_tree, pMargeLeftSideNode);

		delete  pMargeLeftSideNode;
	}

	else if (pMargeRightSideNode)
	{
		pCurrent->m_maxKey = pMargeRightSideNode->m_maxKey;

		BSTreeNodeChildren(_tree, pMargeRightSideNode);

		delete  pMargeRightSideNode;
	}
}

void BSTreeNodeChildren(BSTree & _tree, BSTree::Node * pDyingNode)
{
	if (pDyingNode->m_pLeft)
		BSTreeTransplant(_tree, pDyingNode, pDyingNode->m_pLeft);
	
	else if (pDyingNode->m_pRight)
		BSTreeTransplant(_tree, pDyingNode, pDyingNode->m_pRight);

	else if (pDyingNode->m_pParent->m_pLeft == pDyingNode)
		pDyingNode->m_pParent->m_pLeft = nullptr;

	else if (pDyingNode->m_pParent->m_pRight == pDyingNode)
		pDyingNode->m_pParent->m_pRight = nullptr;
}

BSTree::Node * BSTreeCreateNode(int _keyMin, int _keyMax)
{
	BSTree::Node * pNewNode = new BSTree::Node;
	pNewNode->m_maxKey = _keyMax;
	pNewNode->m_minKey = _keyMin;
	pNewNode->m_pLeft = pNewNode->m_pRight = pNewNode->m_pParent = nullptr;
	return pNewNode;
}

void BSTreeInsertRange(BSTree & _tree, int _keyMin, int _keyMax)
{
	BSTree::Node * pCurrent = _tree.m_pRoot;
	if (!pCurrent)
	{
		_tree.m_pRoot = BSTreeCreateNode(_keyMin,_keyMax);
		return;
	}

	while (pCurrent)
	{
		if (pCurrent->m_minKey <= _keyMin && pCurrent->m_maxKey >= _keyMax)
			return;

		else if (BSTreeFindRange(pCurrent, _keyMin, _keyMax) == inclusionInNode::margeLeft)
		{
			pCurrent->m_minKey = _keyMin;
			BSTreeRebuildАfterInsert(_tree, pCurrent);
			return;
		}

		else if (BSTreeFindRange(pCurrent, _keyMin, _keyMax) == inclusionInNode::margeRight)
		{
			pCurrent->m_maxKey = _keyMax;
			BSTreeRebuildАfterInsert(_tree, pCurrent);
			return;
		}

		else if (_keyMax < pCurrent->m_minKey)
		{
			if (pCurrent->m_pLeft)
				pCurrent = pCurrent->m_pLeft;

			else
			{
				BSTree::Node * pNewNode = BSTreeCreateNode(_keyMin, _keyMax);
				pNewNode->m_pParent = pCurrent;
				pCurrent->m_pLeft = pNewNode;
				return;
			}
		}

		else
		{
			if (pCurrent->m_pRight)
				pCurrent = pCurrent->m_pRight;

			else
			{
				BSTree::Node * pNewNode = BSTreeCreateNode(_keyMin, _keyMax);
				pNewNode->m_pParent = pCurrent;
				pCurrent->m_pRight = pNewNode;
				return;
			}
		}
	}
}

