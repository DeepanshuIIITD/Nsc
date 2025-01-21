#include <bits/stdc++.h>
using namespace std;

unordered_map<string, int> ency_table;

void initialize_tables() {
    ency_table["A"] = 0b000;
    ency_table["B"] = 0b001;
    ency_table["C"] = 0b010;
    ency_table["D"] = 0b011;
    ency_table["E"] = 0b100;
    ency_table["F"] = 0b101;
    ency_table["G"] = 0b110;
    ency_table["H"] = 0b111;
}

int main() {
    initialize_tables();
    string p = "abc";
    for(auto &i : p){
        cout << i << endl;
    }
    // cout << "done ";
    // Use the table
}
