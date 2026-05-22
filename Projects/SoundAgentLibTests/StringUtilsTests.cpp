#include "stdafx.h"

#include <CppUnitTest.h>

#include "internal/StringUtils.h"
using namespace std::literals;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ed::tests
{
    TEST_CLASS(StringUtilsTests)
    {
    public:
        TEST_METHOD(EmptyInput)
        {
            const std::string expected{};
            const auto actual = ed::Utf16ToUtf8(L"");
            Assert::AreEqual(expected, actual);
        }

        TEST_METHOD(AsciiRoundTrip)
        {
            const std::string expected = "Hello, world";
            const auto actual = ed::Utf16ToUtf8(L"Hello, world");
            Assert::AreEqual(expected, actual);
        }

        // BMP = Basic Multilingual Plane(Unicode)
        TEST_METHOD(NonAsciiBmp)
        {
            const auto utf16UnderTest = L"Привет1";
            const auto utf8Expected = u8"Привет1";

            Assert::IsTrue(std::wstring(utf16UnderTest).size() == 7);
            Assert::IsTrue(std::string(reinterpret_cast<const char*>(utf8Expected)).size() == 2 * 6 + 1);

            const auto expected = std::string(reinterpret_cast<const char*>(utf8Expected));

            const auto actual = ed::Utf16ToUtf8(utf16UnderTest);
            Assert::AreEqual(expected, actual);
        }
    };
}
