#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
using namespace std;

string name1(string s, int p){
    return s.substr(0, p);
}

string name2(string s, int p){
    return s.substr(p + 1, s.size() - p - 1);
}

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    vector<int> answer;
    map<string, set<string>> m;//신고당한 사람, 신고한 이용자
    map<string, int> r;//신고한 사람, 횟수
    for(auto id : id_list){
        r[id] = 0;
    }
    
    for(int i=0; i<report.size(); i++){
        int pos = report[i].find(" ");
        if(m.find(name2(report[i], pos)) == m.end()){
            set<string> temp;
            temp.insert(name1(report[i], pos));
            m[name2(report[i], pos)] = temp;
        }
        else{
            if(m[name2(report[i], pos)].find(name1(report[i], pos)) == m[name2(report[i], pos)].end()){
                m[name2(report[i], pos)].insert(name1(report[i], pos));
            }
        }
    }
    
    for(auto a : m){
        if(a.second.size() >= k){
            for(auto t : a.second){
                r[t]++;
            }
        }
    }
    
    for(auto id : id_list){
        answer.push_back(r[id]);
    }
    
    return answer;
}
