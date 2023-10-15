#include <iostream>
using namespace std;

int main(){
    // 前置處理
    char tmp[1000];
    int index = 0;
    while (true){
        char ch = getchar();
        if (ch == EOF) break;
        else if (ch == '\n') continue;
        else{
            tmp[index] = ch;
            index++;
        }
    }

    int pre = 0, id = 0;
    bool status = false;
    while (id < index){
        if(tmp[id] >= '0' && tmp[id] <= '9'){
            if(!status) {
                status = true;
                cout << "NUM ";
            }
            cout << tmp[id];
        }else{
            if(status) {
                status = false;
                cout << endl;
            }
            if(isspace( tmp[id])){
            }else if(tmp[id] == '+'){
                cout << "PLUS" << endl;
            }else if(tmp[id] == '-'){
                cout << "MINUS" << endl;
            }else if(tmp[id] == '*'){
                cout << "MUL" << endl;
            }else if(tmp[id] == '/'){
                cout << "DIV" << endl;
            }else if(tmp[id] == '('){
                cout << "LPR" << endl;
            }else if(tmp[id] == ')'){
                cout << "RPR" << endl;
            }
        }
        id ++;
    }

    return 0;
}