#include <iostream>
#include <string>



std::string removingVowels(std::string string) {
    std::string vowels {"AEIOUYaeiouy"};
    std::string right_word;
    for(int i = 0; i < string.length(); ++i) {
        if(vowels.find(string[i]) != std::string::npos) {
            continue;
        } else {
            right_word += string[i];
        }
    }


    return right_word;
}