#include "test.hpp"


void TestBSTreeCreate()
{
	BSTree * pTree = BSTreeCreate();
	assert(pTree);

	assert(pTree->m_pRoot == nullptr);
	BSTreeDestroy(pTree);
	assert(!pTree);
}

void TestBSTreeInsertOneKey()
{
	BSTree * pTree = BSTreeCreate();
	assert(pTree);

	BSTreeInsertKey(*pTree, 10);
	assert(BSTreeHasKey(*pTree, 10));

	BSTreeDestroy(pTree);
	assert(!pTree);
}

void TestBSTreeInsertManyKeys()
{
	BSTree * pTree = BSTreeCreate();

	int keys[] = { 5, 2, 7, 3, 9, 0, 1, 4, 6, 8 };
	int nKeys = sizeof(keys) / sizeof(int);

	for (int i = 0; i < nKeys; i++)
		BSTreeInsertKey(*pTree, keys[i]);

	for (int i = 0; i < nKeys; i++)
		assert(BSTreeHasKey(*pTree, keys[i]));

	BSTreeDestroy(pTree);
	assert(!pTree);
}

void TestBSTreeMinimumAndMaximum()
{
	BSTree * pTree = BSTreeCreate();

	int keys[] = { 5, 2, 7, 3, 9, 0, 1, 4, 6, 8 };
	int nKeys = sizeof(keys) / sizeof(int);

	for (int i = 0; i < nKeys; i++)
		BSTreeInsertKey(*pTree, keys[i]);

	for (int i = 0; i < nKeys; i++)
		assert(BSTreeHasKey(*pTree, keys[i]));

	assert(BSTreeMinimum(*pTree) == 0);
	assert(BSTreeMaximum(*pTree) == 9);

	BSTreeDestroy(pTree);
	assert(!pTree);
}

void TestBSTreeDeleteKey()
{
	BSTree * pTree = BSTreeCreate();

	BSTreeInsertKey(*pTree, 10);
	assert(BSTreeHasKey(*pTree, 10));

	BSTreeDeleteKey(*pTree, 10);
	assert(!BSTreeHasKey(*pTree, 10));

	assert(pTree->m_pRoot == nullptr);
	BSTreeDestroy(pTree);
	assert(!pTree);
}

void TestBSTreeDeleteManyKeys()
{
	BSTree * pTree = BSTreeCreate();

	int keys[] = { 5, 2, 7, 3, 9, 0, 1, 4, 6, 8 };
	int nKeys = sizeof(keys) / sizeof(int);

	for (int i = 0; i < nKeys; i++)
		BSTreeInsertKey(*pTree, keys[i]);

	for (int i = 0; i < nKeys; i++)
		assert(BSTreeHasKey(*pTree, keys[i]));

	for (int i = 0; i < nKeys; i++)
	{
		BSTreeDeleteKey(*pTree, keys[i]);

		assert(!BSTreeHasKey(*pTree, keys[i]));

		for (int k = i + 1; k < nKeys; k++)
			assert(BSTreeHasKey(*pTree, keys[k]));
	}

	assert(pTree->m_pRoot == nullptr);
	BSTreeDestroy(pTree);
	assert(!pTree);
}

void TestBSTreeInsertOneRangeKey()
{
	BSTree * pTree = BSTreeCreate();

	BSTreeInsertRange(*pTree, 5, 10);

	for(int i = 5 ; i < 11 ;i++)
		assert(BSTreeHasKey(*pTree, i));

	assert(BSTreeMinimum(*pTree) == 5);
	assert(BSTreeMaximum(*pTree) == 10);

	BSTreeDestroy(pTree);
}

void TestBSTreeInsertManyRangeKeys()
{
	BSTree * pTree = BSTreeCreate();

	for(int i = 0; i < 10; i++)
		BSTreeInsertRange(*pTree, i, i*2);

	for (int i = 0; i < 10; i++)
	{
		for (int j = i; j < i * 2; j++)
		{
			assert(BSTreeHasKey(*pTree, j));
		}
	}

	assert(BSTreeMinimum(*pTree) == 0);
	assert(BSTreeMaximum(*pTree) == 9*2);

	BSTreeDestroy(pTree);
}

void TestBSTreeInsertRandomKey()
{
	BSTree * pTree = BSTreeCreate();

	int nKeys = 10;
	int * keys = new int [nKeys];

	for (int i = 0; i < nKeys; i++)
		keys[i] = rand() % 200;
	
	for (int i = 0; i < nKeys; i++)
		BSTreeInsertKey(*pTree, keys[i]);

	for (int i = 0; i < nKeys; i++)
		assert(BSTreeHasKey(*pTree, keys[i]));

	for (int i = 0; i < nKeys; i++)
	{
		BSTreeDeleteKey(*pTree, keys[i]);

		assert(!BSTreeHasKey(*pTree, keys[i]));

		for (int k = i + 1; k < nKeys; k++)
			assert(BSTreeHasKey(*pTree, keys[k]));
	}

	assert(pTree->m_pRoot == nullptr);
	BSTreeDestroy(pTree);
	assert(!pTree);
}

void TestBSTreeInsertRandomMillionKeys()
{
	BSTree * pTree = BSTreeCreate();

	int nKeys = 1000000;
	int * keys = new int[nKeys];

	for (int i = 0; i < nKeys; i++)
		keys[i] = rand() % 32000;

	for (int i = 0; i < nKeys; i++)
		BSTreeInsertKey(*pTree, keys[i]);

	for (int i = 0; i < nKeys; i++)
		assert(BSTreeHasKey(*pTree, keys[i]));

	BSTreeSymmetricWalk(*pTree, &printNode);
	std::cout << std::endl;


	assert(BSTreeFindKeyNode(*pTree, 10)->m_maxKey == 31999);
	assert(BSTreeFindKeyNode(*pTree, 10)->m_minKey == 0);

	for (int i = 0; i < nKeys; i++)
	{
		BSTreeDeleteKey(*pTree, keys[i]);
		assert(!BSTreeHasKey(*pTree, keys[i]));
	}

	assert(BSTreeFindKeyNode(*pTree, 10) == nullptr);

	assert(pTree->m_pRoot == nullptr);
	BSTreeDestroy(pTree);
	assert(!pTree);
}

void TestMergingOfTwoNodesWithRanges()			// Test слияние двух узлов с диапазонами
{
	BSTree * pTree = BSTreeCreate();

	int keys[] = { 5, 8, 9, 11, 12, 13 };
	int nKeys = sizeof(keys) / sizeof(int);

	for (int i = 0; i < nKeys; i++)
		BSTreeInsertKey(*pTree, keys[i]);

	for (int i = 0; i < nKeys; i++)
		assert(BSTreeHasKey(*pTree, keys[i]));

	assert(BSTreeFindKeyNode(*pTree, 9)->m_maxKey == 9);
	assert(BSTreeFindKeyNode(*pTree, 9)->m_minKey == 8);

	BSTreeInsertKey(*pTree, 10);
	assert(BSTreeHasKey(*pTree, 10));

	assert(BSTreeFindKeyNode(*pTree, 9)->m_maxKey == 13);
	assert(BSTreeFindKeyNode(*pTree, 9)->m_minKey == 8);

	BSTreeDestroy(pTree);
	assert(!pTree);
}

void TestAddingKeyToRangeOnRight()			// Test добавление элемента в диапазон справа
{
	BSTree * pTree = BSTreeCreate();

	int keys[] = { 11, 12, 13, 16, 1 };
	int nKeys = sizeof(keys) / sizeof(int);

	for (int i = 0; i < nKeys; i++)
		BSTreeInsertKey(*pTree, keys[i]);

	for (int i = 0; i < nKeys; i++)
		assert(BSTreeHasKey(*pTree, keys[i]));

	assert(BSTreeFindKeyNode(*pTree, 11)->m_maxKey == 13);
	assert(BSTreeFindKeyNode(*pTree, 11)->m_minKey == 11);

	BSTreeInsertKey(*pTree, 14);
	assert(BSTreeHasKey(*pTree, 14));

	assert(BSTreeFindKeyNode(*pTree, 11)->m_maxKey == 14);
	assert(BSTreeFindKeyNode(*pTree, 11)->m_minKey == 11);

	BSTreeDestroy(pTree);
	assert(!pTree);
}

void TestAddingKeyToRangeOnLeft()			// Test добавление элемента в диапазон слева
{
	BSTree * pTree = BSTreeCreate();

	int keys[] = { 11, 12, 13, 16, 1 };
	int nKeys = sizeof(keys) / sizeof(int);

	for (int i = 0; i < nKeys; i++)
		BSTreeInsertKey(*pTree, keys[i]);

	for (int i = 0; i < nKeys; i++)
		assert(BSTreeHasKey(*pTree, keys[i]));

	assert(BSTreeFindKeyNode(*pTree, 11)->m_maxKey == 13);
	assert(BSTreeFindKeyNode(*pTree, 11)->m_minKey == 11);

	BSTreeInsertKey(*pTree, 10);
	assert(BSTreeHasKey(*pTree, 10));

	assert(BSTreeFindKeyNode(*pTree, 11)->m_maxKey == 13);
	assert(BSTreeFindKeyNode(*pTree, 11)->m_minKey == 10);

	BSTreeDestroy(pTree);
	assert(!pTree);
}

void TestRemovingKeyToRangeOnRight()			// Test удаление максимального элемента в диапазоне
{
	BSTree * pTree = BSTreeCreate();

	int keys[] = { 11, 12, 13, 16, 1 };
	int nKeys = sizeof(keys) / sizeof(int);

	for (int i = 0; i < nKeys; i++)
		BSTreeInsertKey(*pTree, keys[i]);

	for (int i = 0; i < nKeys; i++)
		assert(BSTreeHasKey(*pTree, keys[i]));

	assert(BSTreeFindKeyNode(*pTree, 12)->m_maxKey == 13);
	assert(BSTreeFindKeyNode(*pTree, 12)->m_minKey == 11);

	BSTreeDeleteKey(*pTree, 13);
	assert(!BSTreeHasKey(*pTree, 13));

	assert(BSTreeFindKeyNode(*pTree, 12)->m_maxKey == 12);
	assert(BSTreeFindKeyNode(*pTree, 12)->m_minKey == 11);

	BSTreeDestroy(pTree);
	assert(!pTree);
}

void TestRemovingKeyToRangeOnLeft()			// Test добавление элемента в диапазон слева
{
	BSTree * pTree = BSTreeCreate();

	int keys[] = { 11, 12, 13, 16, 1 };
	int nKeys = sizeof(keys) / sizeof(int);

	for (int i = 0; i < nKeys; i++)
		BSTreeInsertKey(*pTree, keys[i]);

	for (int i = 0; i < nKeys; i++)
		assert(BSTreeHasKey(*pTree, keys[i]));

	assert(BSTreeFindKeyNode(*pTree, 12)->m_maxKey == 13);
	assert(BSTreeFindKeyNode(*pTree, 12)->m_minKey == 11);

	BSTreeDeleteKey(*pTree, 11);
	assert(!BSTreeHasKey(*pTree, 11));

	assert(BSTreeFindKeyNode(*pTree, 12)->m_maxKey == 13);
	assert(BSTreeFindKeyNode(*pTree, 12)->m_minKey == 12);

	BSTreeDestroy(pTree);
	assert(!pTree);
}

void TestRemovingMidKeyFromRange()			// Test распада узла на 2 части
{
	BSTree * pTree = BSTreeCreate();

	int keys[] = { 5, 6, 7, 8, 9, 1, 15};
	int nKeys = sizeof(keys) / sizeof(int);

	for (int i = 0; i < nKeys; i++)
		BSTreeInsertKey(*pTree, keys[i]);

	for (int i = 0; i < nKeys; i++)
		assert(BSTreeHasKey(*pTree, keys[i]));

	assert(BSTreeFindKeyNode(*pTree, 8)->m_maxKey == 9);
	assert(BSTreeFindKeyNode(*pTree, 8)->m_minKey == 5);

	BSTreeDeleteKey(*pTree, 7);
	assert(!BSTreeHasKey(*pTree, 7));

	assert(BSTreeFindKeyNode(*pTree, 6)->m_maxKey == 6);
	assert(BSTreeFindKeyNode(*pTree, 6)->m_minKey == 5);

	assert(BSTreeFindKeyNode(*pTree, 8)->m_maxKey == 9);
	assert(BSTreeFindKeyNode(*pTree, 8)->m_minKey == 8);

	BSTreeDestroy(pTree);
	assert(!pTree);
}

void TestFusionDistantNodes_NoSubtree()	// Test слияния узлов которые находятся не рядом друг с другом (удаляемый узел не имеет потдеревьев)		
{
	BSTree * pTree = BSTreeCreate();

	int keys[] = { 10, 6, 8, 4, 9 };
	int nKeys = sizeof(keys) / sizeof(int);

	for (int i = 0; i < nKeys; i++)
		BSTreeInsertKey(*pTree, keys[i]);

	for (int i = 0; i < nKeys; i++)
		assert(BSTreeHasKey(*pTree, keys[i]));

	assert(BSTreeFindKeyNode(*pTree, 9)->m_maxKey == 10);
	assert(BSTreeFindKeyNode(*pTree, 9)->m_minKey == 8);

	assert(BSTreeFindKeyNode(*pTree, 6)->m_maxKey == 6);
	assert(BSTreeFindKeyNode(*pTree, 6)->m_minKey == 6);

	BSTreeDeleteKey(*pTree, 9);
	assert(!BSTreeHasKey(*pTree, 9));

	assert(BSTreeFindKeyNode(*pTree, 8)->m_maxKey == 8);
	assert(BSTreeFindKeyNode(*pTree, 8)->m_minKey == 8);

	assert(BSTreeFindKeyNode(*pTree, 10)->m_maxKey == 8);
	assert(BSTreeFindKeyNode(*pTree, 10)->m_minKey == 8);

	for (int i = 0; i < nKeys - 1; i++)
		assert(BSTreeHasKey(*pTree, keys[i]));

	BSTreeDestroy(pTree);
	assert(!pTree);
}

void TestFusionDistantNodes_LeftSubtree()		// Test слияния узлов которые находятся не рядом друг с другом (удаляемый узел имеет левое поддерево)
{
	BSTree * pTree = BSTreeCreate();

	int keys[] = { 17, 18, 19 };
	int nKeys = sizeof(keys) / sizeof(int);

	for (int i = 0; i < nKeys; i++)
		BSTreeInsertKey(*pTree, keys[i]);

	for (int i = 0; i < nKeys; i++)
		assert(BSTreeHasKey(*pTree, keys[i]));

	assert(BSTreeFindKeyNode(*pTree, 18)->m_maxKey == 19);
	assert(BSTreeFindKeyNode(*pTree, 18)->m_minKey == 17);

	BSTreeDeleteKey(*pTree, 19);
	assert(!BSTreeHasKey(*pTree, 19));

	assert(BSTreeFindKeyNode(*pTree, 18)->m_maxKey == 18);
	assert(BSTreeFindKeyNode(*pTree, 18)->m_minKey == 17);

	for (int i = 0; i < nKeys - 1; i++)
		assert(BSTreeHasKey(*pTree, keys[i]));

	BSTreeDestroy(pTree);
	assert(!pTree);
}

void TestFusionDistantNodes_RightSubtree()		// Test слияния узлов которые находятся не рядом друг с другом (удаляемый узел имеет правое поддерево)
{
	BSTree * pTree = BSTreeCreate();

	int keys[] = { 5, 8 , 10, 7, 6};
	int nKeys = sizeof(keys) / sizeof(int);

	for (int i = 0; i < nKeys; i++)
		BSTreeInsertKey(*pTree, keys[i]);

	for (int i = 0; i < nKeys; i++)
		assert(BSTreeHasKey(*pTree, keys[i]));

	assert(BSTreeFindKeyNode(*pTree, 6)->m_maxKey == 8);
	assert(BSTreeFindKeyNode(*pTree, 6)->m_minKey == 5);

	assert(BSTreeFindKeyNode(*pTree, 10)->m_maxKey == 10);
	assert(BSTreeFindKeyNode(*pTree, 10)->m_minKey == 10);

	BSTreeDeleteKey(*pTree, 6);
	assert(!BSTreeHasKey(*pTree, 6));

	assert(BSTreeFindKeyNode(*pTree, 5)->m_maxKey == 5);
	assert(BSTreeFindKeyNode(*pTree, 5)->m_minKey == 5);

	assert(BSTreeFindKeyNode(*pTree, 7)->m_maxKey == 8);
	assert(BSTreeFindKeyNode(*pTree, 7)->m_minKey == 7);

	assert(BSTreeFindKeyNode(*pTree, 10)->m_maxKey == 10);
	assert(BSTreeFindKeyNode(*pTree, 10)->m_minKey == 10);


	for (int i = 0; i < nKeys - 1; i++)
		assert(BSTreeHasKey(*pTree, keys[i]));

	BSTreeDestroy(pTree);
	assert(!pTree);
}

void printNode(const BSTree::Node & _node)
{	
	if (_node.m_minKey == _node.m_maxKey)
		std::cout << _node.m_minKey << ' ';
	
	else
		std::cout << _node.m_minKey << '-' << _node.m_maxKey << ' ';
}



