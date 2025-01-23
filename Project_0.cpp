#include <bits/stdc++.h>
using namespace std;

void initialize_ency_table( unordered_map<char, string>& ency_table) {
    ency_table['A'] = "000";
    ency_table['B'] = "001";
    ency_table['C'] = "010";
    ency_table['D'] = "011";
    ency_table['E'] = "100";
    ency_table['F'] = "101";
    ency_table['G'] = "110";
    ency_table['H'] = "111";
}

// Initialize the decryption table
void initialize_decy_table(unordered_map<string , char> &decy_table) {
    decy_table["000"] = 'A';
    decy_table["001"] = 'B';
    decy_table["010"] = 'C';
    decy_table["011"] = 'D';
    decy_table["100"] = 'E';
    decy_table["101"] = 'F';
    decy_table["110"] = 'G';
    decy_table["111"] = 'H';
}

string encrypt(string p, unordered_map<char,string>& ency_table){
    string cipher = "";
    for(auto i : p){
        auto it = ency_table.find(i);
        if(it != ency_table.end()){ // found
            cipher += it->second;
        }
        else{cipher += i;} // if not found
    }
    return cipher;
}

string decrypt(string c, unordered_map<string,char>& decy_table){
    string p = "";
    string k="";
    int len = c.size();  // no need to divide since char is of 1 byte only
    for(int i=0;i<=len-3;i+=3){
        // base case
        k = "";  // make it count from starting
        k += c[i];
        k += c[i+1];
        k += c[i+2];
        auto it = decy_table.find(k);
        if(it != decy_table.end()){
            p += (it->second);
        }  // else could be updated as required later
    }
    return p;
}

int main(){
    cout << "Your are in the encryption house" << endl;
    unordered_map<char, string> ency_table;
    unordered_map<string, char> decy_table;
    // initialising table
    initialize_ency_table(ency_table);
    initialize_decy_table(decy_table);
    // plain text
    string p = "ADCBCCDE" ;
    string cipher_text = encrypt(p,ency_table);
    cout << "Encryption Process " << endl;
    cout << "Plain text : " << p << endl;
    cout << "Cipher text : " << cipher_text << endl;
    cout << "Decryption Process " << endl;
    string decrypt_text = decrypt(cipher_text,decy_table);
    cout << "Plain text : " << decrypt_text << endl;
    return 0;

}