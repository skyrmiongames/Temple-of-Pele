#include "CppUnitTest.h"

#include "../../Game/src/Helpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests {
	TEST_CLASS(Helpers) {
public:

	TEST_METHOD(oneof_positive) {
		Assert::IsTrue(oneof(1, 3, 1, 2, 3), (const wchar_t*) "Line one.");
		Assert::IsTrue(oneof(2, 5, 1, 2, 3, 4, 5));
	}

	TEST_METHOD(oneof_negative) {
		Assert::IsFalse(oneof(1, 3, 2, 3, 4));
	}

	};
}
