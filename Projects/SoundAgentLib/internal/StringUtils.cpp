// ReSharper disable once CppUnusedIncludeDirective
#include "os-dependencies.h"

#include "StringUtils.h"


std::string ed::Utf16ToUtf8(const std::wstring& str)
{
    if (str.empty())
    {
        return {};
    }

    const int sizeNeeded = WideCharToMultiByte(
        CP_UTF8,
        0,
        str.data(),
        static_cast<int>(str.size()),
        nullptr,
        0,
        nullptr,
        nullptr);

    if (sizeNeeded <= 0)
    {
        return {};
    }

    std::string result(static_cast<size_t>(sizeNeeded), '\0');

    const int converted = WideCharToMultiByte(
        CP_UTF8,
        0,
        str.data(),
        static_cast<int>(str.size()),
        result.data(),
        sizeNeeded,
        nullptr,
        nullptr);

    if (converted == 0)
    {
        return {};
    }

    return result;
}
