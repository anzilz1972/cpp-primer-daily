#include <iostream>
#include <regex>
#include <vector>
#include <string>

std::vector<std::string> tokenize(const std::string& text) {
    std::regex pattern(R"((?:[a-zA-Z_]\w*(?:\+\+|--|\.\d+)*|\+\+|--|==|!=|<=|>=|->|\.\.|&&|\|\||[^\w\s]))");
    std::vector<std::string> tokens;
    
    auto begin = std::sregex_iterator(text.begin(), text.end(), pattern);
    auto end = std::sregex_iterator();
    
    for (auto it = begin; it != end; ++it) {
        tokens.push_back(it->str());
    }
    
    return tokens;
}

int main()
{
    std::string text = "I love c++ and Python3.0! Java++ is great, but c# is better. Use ++ and -- operators.";
    
    auto tokens = tokenize(text);
    
    std::cout << "Original: " << text << std::endl;
    std::cout << "Tokens: " << std::endl;
    for (const auto& token : tokens) {
        std::cout << "[" << token << "] " << std::endl;
    }
    std::cout << std::endl;
    
    return 0;
}
