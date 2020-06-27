#include <string>
#include <vector>
#include <cstdio>
#include<sstream>
#include<iostream>
#include<unordered_map>

using namespace std;

unordered_map<string, string> map;

vector<string> solution(vector<string> record) {
    vector<string> answer;
    int size = record.size();
    string one,two,three;
    vector<string> oneV;
    vector<string> twoV;
    vector<string> thrV;
    for(int i = 0 ; i < size ; i++){
        stringstream ss(record[i]);
        ss >> one;
        ss >> two;
        ss >> three;
        if( one == "Enter"){
            map[two]= three;
            oneV.push_back(" 들어왔습니다.");
        }
        else if( one == "Change"){
            map[two] = three;
            oneV.push_back(one);
        }
        else if(one == "Leave"){
            three = map[two];
            oneV.push_back(" 나갔습니다.");
        }
       // cout << one << " " << two << " " << three << endl;
        twoV.push_back(two);
        thrV.push_back(three);
    }
    string finalV;
    for(int i = 0 ; i < size; i++){
        if(oneV[i] != "Change"){
            finalV +=map[twoV[i]] + "님이" + oneV[i];
            //cout << finalV << endl;
            answer.push_back(finalV);
            finalV = "";
        }
    }

    return answer;
}
