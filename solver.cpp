#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
#define COLFILENAME "hoge.col";
#define DATFILENAME "fuga.dat";

vector<unsigned long long> binaly(64, 1);

struct nodes {
    unsigned long long left;
    unsigned long long right; // leftの0ビット目が0、rightの63ビット目が127番ノード(ただし、実際に使用するのは1番ノードから100番ノードまで)

    void set(int n){
        if(n<=63){
            left += binaly[n];
        }else{
            right += binaly[n-64];
        }
    }

    void erase(int n){
        if(n<=63){
            left -= binaly[n];
        }else{
            right -= binaly[n-64];
        }
    }
};

nodes start = {0, 0};
nodes target = {0, 0};

int number_node;
int number_edge;
vector<vector<int>> edges;

vector<string> split(string str, char c) {
    vector<string> vec;
    string tmp = "";
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == c) {
            vec.push_back(tmp);
            tmp = "";
        }
        else {
            tmp += str[i];
        }
    }
    vec.push_back(tmp);
    return vec;
}

void inputFiles() {
    string colFileName = COLFILENAME;
    string datFileName = DATFILENAME;
    ifstream col(colFileName);
    ifstream dat(datFileName);

    if (col.fail() || dat.fail()) {
        cerr << "Failed to open file." << endl;
        return;
    }
    
    string str;
    while (getline(col, str)) {
        vector<string> line = split(str, ' ');
        if (line.at(0) == "p") { // ノードとエッジの数を取得
            number_node = stoi(line.at(1));
            number_edge = stoi(line.at(2));
            edges.resize(number_node + 1);
        }
        else { // エッジの情報を取得
            int l, r;
            l = stoi(line.at(1));
            r = stoi(line.at(2));
            edges.at(l).push_back(r);
            edges.at(r).push_back(l);
        }
    }

    while (getline(dat, str)) { // startとtargetを取得
        vector<string> line = split(str, ' ');
        if(line.at(0) == "s"){
            for(int i=1; i<line.size(); i++){
                start.set(stoi(line.at(i)));
            }
        }else if(line.at(0) == "t"){
            for(int i=1; i<line.size(); i++){
                target.set(stoi(line.at(i)));
            }
        }
    }
}

void outputAnswer() {

}

void initializeBinaly(){
    for(int i=1;i<64;i++){
        binaly.at(i) = binaly.at(i-1)*2;
    }
}

int main(void) {
    initializeBinaly();
    inputFiles();
    
}
