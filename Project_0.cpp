#include <bits/stdc++.h>
#include <openssl/sha.h>

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
        if(ency_table.find(i) != ency_table.end()){ // found
            cipher += ency_table[i];
        }
        // else{cipher += i;} // if not found
    }
    string hash_cipher = generate_hash(p);
    cipher += hash_cipher;
    return cipher;
}

// Hash function to generate a recognizable plaintext
string generate_hash(const std::string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input.c_str(), input.size());
    SHA256_Final(hash, &sha256);

    stringstream ss;
    for (int i = 0; i < 4; ++i) { // First 4 bytes = 8 hex characters
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

string decrypt(string c, unordered_map<string,char>& decy_table){
    string p = "";
    string k="";
    int len = c.size();  // no need to divide since char is of 1 byte only
    for(int i=0;i<=len;i++){
        // base case
        k = "";  // make it count from starting
        if(c[i] == '0' || c[i] == '1'){
        k += c[i];
        if(i+1 < len) k+=c[i+1];
        if(i+2 < len) k+=c[i+2];
            if(decy_table.find(k) != decy_table.end()){
                p += decy_table[k];
            } 
        i += 2; 
        }         // if any char not in table
        else{
            p += c[i];
        }
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
    string p = "A" ;
    string cipher_text = encrypt(p,ency_table);
    cout << "Encryption Process " << endl;
    cout << "Plain text : " << p << endl;
    cout << "Cipher text : " << cipher_text << endl;
    cout << "Decryption Process " << endl;
    string decrypt_text = decrypt(cipher_text,decy_table);
    cout << "Plain text : " << decrypt_text << endl;
    string output22 = generate_hash(p);
    cout << "Hasher is here " << output22 << " " << endl;;
    return 0;

}