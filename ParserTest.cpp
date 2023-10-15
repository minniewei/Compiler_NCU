#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <stdexcept>
using namespace std;

class Parser {
private:
    string input;
    size_t position;
    smatch matches;
    char nextChar;
    vector<string> output;

    // Helper function to check if a string matches a regular expression
    char match(const string& input, const string& regexPattern, smatch& matches) {
        regex pattern(regexPattern);
        if (regex_search(input, matches, pattern)) {
            if (matches.position(0) == 0) {
                if(regexPattern == ID_REGEX) output.push_back("ID "+ matches[0].str());
                else output.push_back("STRLIT "+ matches[0].str());
                position += matches.position(0) + matches.length(0);
                return 'Y';
            }
            return 'N';
        }
        return 'N';
    }

    // Helper function to check the next character
    char getNextChar() {
        if (position < input.length()) {
            return input[position++];
        }
        return '\0'; // Return null character if end of input is reached
    }

public:
    Parser(const std::string& inputText) : input(inputText), position(0) {}

    // Non-terminal: primary_tail → LBR stmt RBR primary_tail | λ
    void parsePrimaryTail() {
        nextChar = getNextChar();
        if (nextChar == '(') {
            output.push_back("LBR (");
            parseStmt();
            if (getNextChar() == ')') {
                output.push_back("RBR )");
                parsePrimaryTail();
            }else {
                throw runtime_error("Expected ')' after stmt in parsePrimaryTail");
            }
        }else if (nextChar == '.'){
            output.push_back("DOT .");
            if(match(input.substr(position), ID_REGEX, matches) == 'Y'){
                parsePrimaryTail();
            }else{
                throw runtime_error("Expected correct ID in parsePrimaryTail");
            }
        }else if (nextChar != '\0'){
            throw runtime_error("Expected correct PrimaryTail in parsePrimaryTail");
        }
    }
    
    // Non-terminal: primary_tail → ID primary_tail
    void parsePrimary() {
        if (match(input.substr(position), ID_REGEX, matches) == 'Y'){
            parsePrimaryTail();
        }else{
            if(getNextChar() == ')'){
                position --;
            }else{
                throw runtime_error("Expected correct ID in parsePrimary");
            }
        }
    }

    // Non-terminal: stmt → primary | STRLIT | λ
    void parseStmt() {
        if(getNextChar() != '\0'){
            position --;
            if(match(input.substr(position), STRLIT_REGEX, matches) != 'Y'){
                parsePrimary();
            }
        }
    }

    // Non-terminal: stmts -> stmt stmts | λ 
    void parseStmts(){
        if(getNextChar() != '\0'){
            position --;
            parseStmt();
            parseStmts();
        }
    }

    // Non-terminal: program -> stmts
    void program(){
        parseStmts();
    }

    // Initialize
    void parse(){
        program();
    }

    // PrintResult
    void PrintResult(){
        for(int i = 0 ; i < output.size() ; i ++){
            cout << output[i] << endl;
        }
    }
    
    // Terminal Regular Expressions
    const std::string ID_REGEX = "[A-Za-z_][A-Za-z0-9_]*";
    const std::string STRLIT_REGEX = "\"([^\"]*)\"";
};

int main() {
    string input;
    while(1){
        getline(cin, input);
        if(input.empty()) break;
        Parser parser(input);
        try {
            parser.parse();
            parser.PrintResult();
        } catch (const std::runtime_error& e) {
            cout << "invalid input" << endl;
        }
    }
    return 0;
}
