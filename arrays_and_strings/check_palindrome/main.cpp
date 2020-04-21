#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

bool isPalindrome(const std::string& s) {
    if (s.size() < 2) {
        return true;
    }

    size_t i = 0;
    size_t j = s.size() - 1;
    while (i < j) {
        if (!std::isalpha(s[i])) {
            i++;
        } else if (!std::isalpha(s[j])) {
            j--;
        } else {
            if (std::tolower(s[i]) != std::tolower(s[j])) { // tolower can be forgotten
                return false;
            }

            i++;
            j--;
        }
    }

    return true;
}

int main() {
    const std::vector<std::pair<std::string, bool>> tests {
        {"Do geese see God?", true},
        {"Madam, I’m Adam", true},
        {"Hello World", false},
        {"", true},
        {"I", true},
        {"Hi", false}
    };

    for (const auto& x : tests) {
        const bool ok = isPalindrome(x.first) == x.second;
        std::cerr << (ok ? "OK" : "ERROR") << "\t" << x.first << std::endl;
    }
}
