/* Sample c++ code to generate enums and their strings
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

// generic macros to generate enums and enum strings
#define CONCATENATE_NAMES(x, y) x##y
#define GENERATE_ENUM_NAME(VAR) VAR,
#define GENERATE_ENUM_STRING(VAR) #VAR,

#define DECLARE_ENUM_NAMES(x, y) \
    enum class x                 \
    {                            \
        y                        \
    };

#define DECLARE_ENUM_STRINGS(x, y) \
    std::vector<std::string> CONCATENATE_NAMES(x, Strings) = {y};

// macro for a specific enum
#define MY_ENUM_NAME MyEnum
#define MY_ENUM_LIST(LIST) \
    LIST(Foo)              \
    LIST(Bar)              \
    LIST(Baz)

DECLARE_ENUM_NAMES(MY_ENUM_NAME, MY_ENUM_LIST(GENERATE_ENUM_NAME))
DECLARE_ENUM_STRINGS(MY_ENUM_NAME, MY_ENUM_LIST(GENERATE_ENUM_STRING))

/*int main(int argc, char **argv)
{
    cout << MyEnumStrings[static_cast<size_t>(MyEnum::Bar)] << endl;
    cout << static_cast<size_t>(MyEnum::Bar) << endl;
    //cout << MyEnumStrings[Bar] << endl;
    return 0;
}*/
