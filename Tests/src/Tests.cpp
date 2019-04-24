#include "CppUnitTest.h"

#include "../../Game/src/Helpers.h"
#include "../../Game/src/enums.h"

#include "../../Game/src/UpdateList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests {
	TEST_CLASS(Helpers) {
	public:

		TEST_METHOD(oneof_positive) {
			Assert::IsTrue(oneof(1, 3, 1, 2, 3), (const wchar_t*) "Line one.");
			Assert::IsTrue(oneof(2, 5, 1, 2, 3, 4, 5));
			Assert::IsTrue(oneof(North, 3, Northeast, North, Southeast));
		}

		TEST_METHOD(oneof_negative) {
			Assert::IsFalse(oneof(1, 3, 2, 3, 4));
			Assert::IsFalse(oneof(North, 3, Northeast, East, Southeast));
		}

		TEST_METHOD(angleCalc) {
			Assert::AreEqual(angleTo(sf::Vector2f(0, 0), sf::Vector2f(5,0)), 0.0f);
		}
	};

	TEST_CLASS(UpdateList) {
	public:
		TEST_METHOD(node_update) {
			//Create testing node
			Node *testNode = new testNode;
			UpdateList::add_node(testNode);

			//Check start conditions
			Assert::IsFalse(testNode->collided);
			Assert::IsFalse(testNode->updated);

			//Run single update
			UpdateList::update(5);

			//Check final condition
			Assert::IsFalse(testNode->collided);
			Assert::IsTrue(testNode->updated);
		}

		TEST_METHOD(node_update) {
			//Create testing node 1
			Node *testNode1 = new testNode;
			testNode1->setPosition(40, 40);
			UpdateList::add_node(testNode1);

			//Create testing node 2
			Node *testNode2 = new testNode;
			testNode2->setPosition(50, 50);
			UpdateList::add_node(testNode1);

			//Check start conditions
			Assert::IsFalse(testNode1->collided);
			Assert::IsFalse(testNode1->updated);
			Assert::IsFalse(testNode2->collided);
			Assert::IsFalse(testNode2->updated);

			//Run single update
			UpdateList::update(5);

			//Check final conditions
			Assert::IsTrue(testNode1->collided);
			Assert::IsTrue(testNode1->updated);
			Assert::IsTrue(testNode2->collided);
			Assert::IsTrue(testNode2->updated);
		}
	};
}
