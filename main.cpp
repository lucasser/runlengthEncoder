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
        string txt = "";
        string out;
        string printout() {
            out.push_back(escChar);
            out.append(escStr);
            out.append(txt);
            return out;
        }
        void uncompile(string str) {
            escChar = str.at(0);
            escStr = str.substr(1, 5);
            txt = str.substr(5);
        }
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
    vector<int> chars(94, 0);
    heading encoded;
    long unsigned int i;

    for (i = 0; i < str.size(); i++) {
        if (str.at(i) != ' ') {
            chars.at(str.at(i)-33)++;
        }
    }

    int index = 0;
    for (i = 0; i < 94; i++) {
        if (i >= 15 && i <= 24) {
            continue;
        }
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

    string out = "";
    string tmp;
    tmp.push_back(str.at(0));
    for (i = 1; i < str.size()+1; i++) {
        //remove escChar
        if (i == str.size()) {
            if (tmp.size() > 1) {
                out.push_back(encoded.escChar);
                out.push_back(tmp.at(0));
                out.append(to_string(tmp.size()));
                out.push_back(encoded.escChar);
            } else {
                out.push_back(tmp.at(0));
            }
            break;
        }
        if (str.at(i) == tmp.at(0)) {
            tmp.push_back(str.at(i));
        } else {
            if (tmp.size() > 1) {
                out.push_back(encoded.escChar);
                if (tmp.at(0) == encoded.escChar) {
                    out.append(encoded.escStr);
                } else {
                    out.push_back(tmp.at(0));
                }
                out.append(to_string(tmp.size()));
                out.push_back(encoded.escChar);
            } else {
                if (tmp.at(0) == encoded.escChar) {
                    out.append(encoded.escStr);
                } else {
                    out.push_back(tmp.at(0));
                }
            }
            tmp = "";
            tmp.push_back(str.at(i));
        }
    }
    encoded.txt = out;

    return encoded.printout();
}

string decode(string str) {
    heading decoded;
    decoded.uncompile(str);
    str = decoded.txt;
    string out = "";
    string tmp;
    for (long unsigned int i = 1; i < str.size(); i++) {
        if (str.at(i) == decoded.escChar) {
            tmp = str.substr(i + 1, str.substr(i+1).find(decoded.escChar) + i - 1);
        for (int j = 0; j < stoi(tmp.substr(1)); j++) {
            out.push_back(tmp.at(0));
        }
        i = str.substr(i+1).find(decoded.escChar) + i + 1;
        } else {
            out.push_back(str.at(i));
        }
    }

    return out;
}


int main() {
    string str = "";
    for (int i = 0; i < 93; i++) {
        for (int j = 0; j < rand() % 9 + 2; j++) {
            str.push_back(i + 33);
        }
    }
    cout << str << endl << endl;
    string out;
    out = encode(str);
    cout << out << endl << endl;
    out = decode(out);
    cout << out << endl << endl;
    return 0;
}

