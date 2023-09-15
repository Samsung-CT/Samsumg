#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <iostream>
using namespace std;

struct car_fee{
    string car_num;
    int fee;
};

int ttoi(string a){
    return stoi(a.substr(0,2)) * 60 + stoi(a.substr(3,2));
}

string stocn(string a){
    return a.substr(6,4);
}

vector<int> solution(vector<int> fees, vector<string> records) {
    map<string, int> m;
    map<string, int> m2;
    for(int i=0; i<records.size(); i++){
        if(m.find(stocn(records[i])) == m.end() || m[stocn(records[i])] == -1){
            m[stocn(records[i])] = ttoi(records[i]);
        }
        else{
            int t = ttoi(records[i]) - m[stocn(records[i])];
            if(m2.find(stocn(records[i])) == m2.end()){
                m2[stocn(records[i])] = t;
            }
            else{
                m2[stocn(records[i])] += t;
            }
            m[stocn(records[i])] = -1;
        }
    }
    for(auto temp : m){
        if(temp.second != -1){
            int t = 23*60 + 59 - temp.second;
            if(m2.find(temp.first) == m2.end()){
                m2[temp.first] = t;
            }
            else{
                m2[temp.first] += t;
            }
        }
    }
    
    vector<int> answer;
    for(auto temp : m2){
        if(temp.second <= fees[0]){
            answer.push_back(fees[1]);
        }
        else{
            answer.push_back(fees[1] + ceil((temp.second - fees[0]) / (double)fees[2]) * fees[3]);
        }
    }
    
    return answer;
}
