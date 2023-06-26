#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

class heading {
    public:
        void setVal(int charIn) {
            escChar = charIn;
        }
        void genEsc(int len) {
            escStr = rngStr(len);
        }
        char escChar;
        string escStr = ".....";
    private:
        string rngStr(int len) {
            string out;
            char tmp;
            int itmp;
            for (int i = 0; i < len; i++) {
                itmp = rand() % 95;
                tmp = itmp + 33;
                out.push_back(tmp);
            }
            return out;
        }
};

string encode(string str) {
    vector<int> chars(95, 0);
    heading encoded;
    long unsigned int i;

    for (i = 0; i < str.size(); i++) {
        if (str.at(i) != ' ') {
            chars.at(str.at(i)-33)++;
        }
    }

    int index = 0;
    for (i = 0; i < 95; i++) {
        if (chars.at(i) < chars.at(index)) {
            index = i; 
        }
    }
    index += 33;
    encoded.setVal(index);

    bool done = false;
    while (!done) {
        encoded.genEsc(5);
        string tmp;
        done = true;
        if (encoded.escStr.at(0) == encoded.escStr.at(1)) {
            encoded.genEsc(5);
        }
        for (i = 0; i < str.size(); i++) {
            tmp.push_back(str.at(i));
            if (tmp != encoded.escStr.substr(0, tmp.size())) {
                tmp = "";
            } else if (tmp.size() == encoded.escStr.size()) {
                done = false;
                break;
            };
        }
    }
    cout << encoded.escStr << endl;
    cout << encoded.escChar << endl;

    string out = "";
    string tmp;
    tmp.push_back(str.at(0));
    for (i = 1; i < str.size()+1; i++) {
        //remove escChar
        if (str.at(i) == encoded.escChar){
            out.append(encoded.escStr);
        } else if (i == str.size() || str.at(i) != tmp.at(0)) {
            if (tmp.size() > 1) {
                out.push_back(encoded.escChar);
                out.push_back(tmp.at(0));
                out.append(to_string(tmp.size()));
                out.push_back(encoded.escChar);
            } else {
                out.push_back(tmp.at(0));
            }
            return out;
        } else {
            tmp.push_back(str.at(i));
        }
        if (str.at(i) == tmp.at(0)) {
            tmp.push_back(str.at(i));
        } else {
            if (tmp.size() > 1) {
                out.push_back(encoded.escChar);
                out.push_back(tmp.at(0));
                out.append(to_string(tmp.size()));
                out.push_back(encoded.escChar);
            } else {
                out.push_back(tmp.at(0));
            }
            tmp = "";
            tmp.push_back(str.at(i));
        }
    }
    return out;
}

/*
string decode(string str) {
    string out = "";
    string tmp;
    for (int i = 1; i < str.size(); i++) {
        if (to_string(str.at(i)) == "\\") {
            for (int j = 0; j < to_string(str.at(i+2)); j++) {
                out.push_back(str.at(i+1));
            }
        } else {
            out.push_back(str.at(i));
        }
    }
    return out;
}*/

int main() {
    string str = "hello llell\"!o|7]Q";
    string out;
    out = encode(str);
    cout << out << endl;
    //out = decode(out);
    //cout << out << endl;
    return 0;
}