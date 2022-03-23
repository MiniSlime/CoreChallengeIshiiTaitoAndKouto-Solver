#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
using namespace std;
#define COLFILENAME "hoge.col";
#define DATFILENAME "fuga.dat";
#define OUTFILENAME "piyo.out";

vector<unsigned long long> binaly(64, 1);

struct nodes {
    vector<bool> nodes_info;

    void set(int n){
        // if(n<=63){
        //     left += binaly[n];
        // }else{
        //     right += binaly[n-64];
        // }
        nodes_info.at(n) = 1;
    }

    void erase(int n){
        // if(n<=63){
        //     left -= binaly[n];
        // }else{
        //     right -= binaly[n-64];
        // }
        nodes_info.at(n) = 0;
    }

    // n番ノードが1かどうか
    bool test(int n){
        // if(n<=63){
        //     return (left & binaly[n]) != 0;
        // }else{
        //     return (right & binaly[n-64]) != 0;
        // }
        return nodes_info.at(n);
    }
};

nodes start = {vector<bool>(10000,0)};
nodes target = {vector<bool>(10000,0)};

int number_node;
int number_edge;
vector<vector<int>> edges;

struct state{
    nodes current;
    vector<nodes> history;
};

set<vector<bool>> visited;

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
        if(line.at(0) == "c") continue;

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

void outputAnswer(vector<nodes> ans) {
    string datFileName = DATFILENAME;
    string outFileName = OUTFILENAME;
    ifstream dat(datFileName);
    ofstream out(outFileName);

    if (dat.fail() || out.fail()) {
        cerr << "Failed to open file." << endl;
        return;
    }

    string str;
    while(getline(dat, str)){
        out<<str<<endl;
    }

    if(ans.size() == 0){
        out<<"a NO"<<endl;
    }else{
        out<<"a YES"<<endl;
        for(int i=0;i<ans.size();i++){
            out<<"a";
            nodes now = ans.at(i);
            for(int j=1;j<=100;j++){
                if(now.test(j)){
                    out<<" "<<j;
                }
            }
            out<<endl;
        }
    }
}

void initializeBinaly(){
    for(int i=1;i<64;i++){
        binaly.at(i) = binaly.at(i-1)*2;
    }
}

vector<nodes> bfs(){
    queue<state> que;
    state s={start, {start}};
    que.push(s);

    while(!que.empty()){
        state now = que.front();
        que.pop();

        if(now.current.nodes_info == target.nodes_info) {
            return now.history;
        }

        for(int i=1;i<=number_node;i++){
            if(now.current.test(i)){
                for(int j=1;j<=number_node;j++){
                    if(!now.current.test(j)){
                        bool flag = true;
                        vector<int> nextNeigh = edges.at(j);
                        for(auto a:nextNeigh){
                            if(a != i && now.current.test(a)){
                                flag = false;
                                break;
                            }
                        }

                        if(flag){
                            state next = now;
                            next.current.erase(i);
                            next.current.set(j);
                            next.history.push_back(next.current);

                            int bef = visited.size();
                            visited.insert(next.current.nodes_info);
                            if(visited.size() > bef){
                                que.push(next);
                            }
                        }
                    }
                }
            }
        }
    }

    return {};
}

int main(void) {
    initializeBinaly();
    inputFiles();
    vector<nodes> ans = {{}, {}};
    ans=bfs();
    outputAnswer(ans);
}
