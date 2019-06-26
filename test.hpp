#ifndef _TEST_HPP_
#define _TEST_HPP_

#include "BSTree.hpp"

void TestBSTreeCreate();

void TestBSTreeInsertOneKey();

void TestBSTreeInsertManyKeys();

void TestBSTreeMinimumAndMaximum();

void TestBSTreeDeleteKey();

void TestBSTreeDeleteManyKeys();

void TestBSTreeInsertOneRangeKey();

void TestBSTreeInsertManyRangeKeys();

void TestBSTreeInsertRandomKey();

void TestBSTreeInsertRandomMillionKeys();

void TestMergingOfTwoNodesWithRanges();

void TestAddingKeyToRangeOnRight();

void TestAddingKeyToRangeOnLeft();

void TestRemovingKeyToRangeOnRight();

void TestRemovingKeyToRangeOnLeft();

void TestRemovingMidKeyFromRange();

void TestFusionDistantNodes_NoSubtree();

void TestFusionDistantNodes_LeftSubtree();

void TestFusionDistantNodes_RightSubtree();

void printNode(const BSTree::Node & _node);


#endif
