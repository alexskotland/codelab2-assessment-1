#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Book {
public:
    string title, author, id;
    int pages;
    bool borrowed;

    void show() const {
        cout << "ID: " << id << " | " << title << " by " << author
             << " | " << pages << " pages | "
             << (borrowed ? "Borrowed" : "Available") << "\n";
    }
};

vector<Book> loadBooks(const string& filename) {
    ifstream file(filename);
    vector<Book> books;
    string line;
    while (getline(file, line)) {
        stringstream row(line);
        string title, author, pages, id, status;
        if (getline(row, title, ',') && getline(row, author, ',') &&
            getline(row, pages, ',') && getline(row, id, ',') &&
            getline(row, status)) {
            try { books.push_back({title, author, id, stoi(pages), status == "true"}); }
            catch (...) { cout << "Skipping invalid book record.\n"; }
        }
    }
    return books;
}

void saveBooks(const vector<Book>& books, const string& filename) {
    ofstream file(filename);
    for (const Book& book : books) {
        file << book.title << ',' << book.author << ',' << book.pages << ','
             << book.id << ',' << (book.borrowed ? "true" : "false") << '\n';
    }
}

Book* findBook(vector<Book>& books, const string& id) {
    for (Book& book : books) if (book.id == id) return &book;
    return nullptr;
}

int main() {
    const string filename = "bookData.txt";
    ifstream check(filename);
    if (!check) {
        cout << "Cannot open bookData.txt. Put it next to the program.\n";
        return 1;
    }
    check.close();
    vector<Book> books = loadBooks(filename);
    if (books.empty()) { cout << "No books found.\n"; return 1; }

    string choice, id;
    while (true) {
        cout << "\n1. View all books\n2. View one book\n"
             << "3. Borrow a book\n4. Return a book\n5. Quit\nChoose: ";
        if (!getline(cin, choice) || choice == "5") break;
        if (choice == "1") {
            for (const Book& book : books) book.show();
        } else if (choice == "2" || choice == "3" || choice == "4") {
            cout << "Enter book ID (e.g. 001): ";
            if (!getline(cin, id)) break;
            Book* book = findBook(books, id);
            if (!book) { cout << "Book not found.\n"; continue; }
            if (choice == "2") book->show();
            else if (choice == "3") {
                if (book->borrowed) cout << "This book is already borrowed.\n";
                else { book->borrowed = true; saveBooks(books, filename); cout << "Book borrowed.\n"; }
            } else {
                if (!book->borrowed) cout << "This book is already available.\n";
                else { book->borrowed = false; saveBooks(books, filename); cout << "Book returned.\n"; }
            }
        } else cout << "Invalid choice.\n";
    }
    cout << "Goodbye!\n";
    return 0;
}
