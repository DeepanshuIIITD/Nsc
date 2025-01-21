#include <bits/stdc++.h>
using namespace std;

// look_up_table
    // unordered_map<string, int> ency_table = {{"A",0b000}, {"B",0b001}, {"C",0b010}, {"D",0b011}, {"E",0b100},{"F",0b101},{"G",0b110},{"H",0b111}};
    unordered_map<string, int> ency_table;
    unordered_map<int , string> decy_table;
    // unordered_map<int, string> decy_table = {{0b000,"A"}, {0b001,"B"}, {0b010,"C"}, {0b011,"D"}, {0b100,"E"},{0b101,"F"},{0b110,"G"},{0b111,"H"}};
// table is ready
void initialize_ency_table() {
    ency_table["A"] = 0b000;
    ency_table["B"] = 0b001;
    ency_table["C"] = 0b010;
    ency_table["D"] = 0b011;
    ency_table["E"] = 0b100;
    ency_table["F"] = 0b101;
    ency_table["G"] = 0b110;
    ency_table["H"] = 0b111;
}

// Initialize the decryption table
void initialize_decy_table() {
    decy_table[0b000] = "A";
    decy_table[0b001] = "B";
    decy_table[0b010] = "C";
    decy_table[0b011] = "D";
    decy_table[0b100] = "E";
    decy_table[0b101] = "F";
    decy_table[0b110] = "G";
    decy_table[0b111] = "H";
}


string encrypt(string p){
    string cipher;
    for(char i : p){
        if(ency_table.find(i) != ency_table.end()){
            cipher +=  
        }
    }
    return cipher;
}

int main(){
    cout << "Your are in the encryption house" << endl;
    // initialising table
    initialize_ency_table();
    
    // plain text
    string p = "Hello my name is network";
    string cipher_text = encrypt(p);
    cout << cipher_text << endl;
    return 0;
}