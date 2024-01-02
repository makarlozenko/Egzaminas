#include "Egzaminas.h"

vector<string> splitWords(const string& text) {
    vector<string> words;
    istringstream iss(text);
    string word;
    while (iss >> word) {
        word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());// Šaliname skyrybos ženklus
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        words.push_back(word);       
    }
    return words;
}

int tolygumas(const std::string& str) {
    int count = 0;
    for (unsigned char c : str) {
        if ((c & 0xC0) != 0x80) {
            ++count;            
        }
    }
    return count;
}
