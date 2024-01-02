#include "Egzaminas.h"

int main() {

    setlocale(LC_ALL, "lt_LT.UTF-8");

    ifstream infailas("tekstas.txt");
    if (!infailas.is_open()) {
        cout << "Nepavyko atidaryti failo!";
        return 1;
    }

    string line;
    map<string, int> wordDaznis;
    map<string, vector<int>> wordVieta;
    set<string> urls;
    regex urlRegex("(https?://\\S+)|(www\\.\\S+)");
    smatch matches;
    

    int lineNumber = 1;
    while (getline(infailas, line)) {
        vector<string> words = splitWords(line);
      

        for (const string& word : words) {
            wordDaznis[word]++;
            wordVieta[word].push_back(lineNumber);
        }

        while (regex_search(line, matches, urlRegex)) {
            for (const auto& match : matches) {
                urls.insert(match.str());
            }
            line = matches.suffix().str();//Pašaliname, kad nesidubliuotų
        }

        lineNumber++;
    }

   
    ofstream outfailas("rezultatai.txt"); 
    if (!outfailas.is_open()) {
        cout << "Nepavyko atidaryti rezultatų failo!";
        return 1;
    }

    int index = 0;
    int kiekis1 = 0;
    outfailas << "Different words in the file:\n";
    outfailas << left << setw(30) << "Word" << setw(30) << "       Number" << "\n";
    outfailas <<"---------------------------------------------------- \n";
    for (const auto& pair : wordDaznis) { // Išvedame pasikartojančius žodžius ir jų dažnius
        index++;
        kiekis1 += pair.second;
        if (pair.second > 1) {
            int papild = pair.first.size() - tolygumas(pair.first);
            outfailas << left << setw(30+papild) << pair.first << setw(10) <<" | "<< setw(10) << pair.second << setw(10) << " | " <<endl;
            outfailas << "---------------------------------------------------- \n";
        
        }
        if (index == wordDaznis.size() - 2) {
            break;
        }
    }

   
    int index1 = 0;
    outfailas << "\nWhere these words are in the file:\n";
    outfailas << left << setw(30) << "Word" << setw(30) << "       Lines" << "\n";
    outfailas << "--------------------------------------------------------------------------------------------------------------------------------------------- \n";
    for (const auto& pair : wordVieta){  // Išvedame žodžių pasikartojimo vietas
        index1++;
        if (pair.second.size() > 1){
            int papild = pair.first.size() - tolygumas(pair.first);
            outfailas << left << setw(30 + papild) << pair.first <<  setw(10) << " | " ;
            for (const int& line : pair.second) {
                outfailas << line << " ";
            }
            outfailas << "\n";
            outfailas << "--------------------------------------------------------------------------------------------------------------------------------------------- \n";
        }
        if (index1 == wordVieta.size() - 2) {
            break;
        }
    }

    // Išvedame surastus URL adresus
    outfailas << "\nFound URL :\n";
    for (const string& url : urls) {
        outfailas << url << "\n";
    }

    infailas.close();
    outfailas.close();


    cout << "Number of words in the file: " <<  kiekis1 << endl;
    cout << "All rezults are in the rezultatai.txt" << endl;

    return 0;
}
