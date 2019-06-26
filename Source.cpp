#include "test.hpp"

int main()
{
	TestBSTreeCreate();
	TestBSTreeInsertOneKey();
	TestBSTreeInsertManyKeys();
	TestBSTreeMinimumAndMaximum();
	TestBSTreeDeleteKey();
	TestBSTreeDeleteManyKeys();
	TestBSTreeInsertOneRangeKey();
	TestBSTreeInsertManyRangeKeys();
	TestBSTreeInsertRandomKey();
	TestBSTreeInsertRandomMillionKeys();
	TestMergingOfTwoNodesWithRanges();
	TestAddingKeyToRangeOnRight();
	TestAddingKeyToRangeOnLeft();
	TestRemovingKeyToRangeOnRight();
	TestRemovingKeyToRangeOnLeft();
	TestRemovingMidKeyFromRange();
	TestFusionDistantNodes_NoSubtree();
	TestFusionDistantNodes_LeftSubtree();
	TestFusionDistantNodes_RightSubtree();

	return 0;
}
