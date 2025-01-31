import hashlib


def initialize_ency_table():
    return {
        'A': "000", 'B': "001", 'C': "010", 'D': "011",
        'E': "100", 'F': "101", 'G': "110", 'H': "111"
    }

def initialize_decy_table():
    return {v: k for k, v in initialize_ency_table().items()}

def generate_hash(input_str):
    hash_obj = hashlib.sha256(input_str.encode())
    binary_hash = bin(int(hash_obj.hexdigest(), 16))[2:].zfill(256)  # Convert hex to binary
    return binary_hash[:8]  # First 8 bits

def encrypt(plain_text, ency_table):
    cipher = "".join(ency_table.get(char, '') for char in plain_text)
    hash_cipher = generate_hash(plain_text)
    return cipher + hash_cipher

def decrypt(cipher_text, decy_table):
    plain_text = ""
    i = 0
    while i < len(cipher_text) - 8:  # Ignore last 8 bits (hash)
        chunk = cipher_text[i:i+3]
        if chunk in decy_table:
            plain_text += decy_table[chunk]
            i += 3
        else:
            plain_text += cipher_text[i]
            i += 1
    
    if not authenticate_plain_text(plain_text, cipher_text[-8:]):
        raise ValueError("Invalid hash")
    else:
        return plain_text

def authenticate_plain_text(plain_text, hash_cipher):
    return hash_cipher == generate_hash(plain_text)


def main():
    print("You are in the encryption house")
    ency_table = initialize_ency_table()
    decy_table = initialize_decy_table()
    
    plain_text = "ACCDEBBH"
    cipher_text = encrypt(plain_text, ency_table)
    print("Encryption Process")
    print("Plain text:", plain_text)
    print("Cipher text:", cipher_text)
    
    print("Decryption Process")
    decrypted_text = decrypt(cipher_text, decy_table)
    print("Plain text:", decrypted_text)
    print("Brute force")
    brute_force(cipher_text)
    
if __name__ == "__main__":
    main()
