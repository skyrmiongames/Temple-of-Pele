#include "CppUnitTest.h"

#include "../../Game/src/Helpers.h"
#include "../../Game/src/enums.h"
#include "../../Game/src/Player.h"

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
		Assert::AreEqual(angleTo(sf::Vector2f(0, 0), sf::Vector2f(5, 0)), 0.0f);
	}

	TEST_METHOD(takeDamage) {
		Player p;
		bool success = false;

		success = p.takeDamage(10);
		Assert::IsTrue(success);
	}

	TEST_METHOD(getKey) {
		Player p;
		bool success = false;

		p.setKey(true);

		success = p.getKey();
		Assert::IsTrue(success);
	};
	};
}
