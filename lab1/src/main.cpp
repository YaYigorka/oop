#include <iostream>
#include <string>
#include "removingVowels.h"


int main(int argc, char * argv[]) {
	std::string test_word;
	std::getline(std::cin, test_word);
	test_word = removingVowels(test_word);
	std::cout << test_word << std::endl;
	
	
	return 0;
}