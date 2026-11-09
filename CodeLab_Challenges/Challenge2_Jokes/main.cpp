#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
using namespace std;

int main() {
    ifstream file("randomJokes.txt");
    if (!file) {
        cout << "Cannot open randomJokes.txt. Put it next to the program.\n";
        return 1;
    }

    vector<string> jokes;
    string line;
    while (getline(file, line)) {
        if (line.find('?') != string::npos) jokes.push_back(line);
    }
    if (jokes.empty()) {
        cout << "No valid jokes found.\n";
        return 1;
    }

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<size_t> pick(0, jokes.size() - 1);
    cout << "Type Alexa, tell me a joke (or quit to exit).\n";
    while (true) {
        cout << "\n> ";
        if (!getline(cin, line) || line == "quit") break;
        if (line != "Alexa, tell me a joke") {
            cout << "Please use the exact phrase or type quit.\n";
            continue;
        }
        string joke = jokes[pick(generator)];
        size_t questionMark = joke.find('?');
        cout << joke.substr(0, questionMark + 1) << "\n";
        cout << "Press Enter for the punchline...";
        if (!getline(cin, line)) break;
        cout << joke.substr(questionMark + 1) << "\n";
    }
    cout << "Goodbye!\n";
    return 0;
}
