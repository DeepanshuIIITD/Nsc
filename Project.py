import hashlib
import itertools


class EncryptionSystem:
    def __init__(self):
        # default settings of table
        self._default_ency_table = {
            'A': '010', 'B': '101', 'C': '000', 'D': '100', 
            'E': '110', 'F': '111', 'G': '011', 'H': '001'
        }
        self._default_decy_table = {v: k for k, v in self._default_ency_table.items()}
        
        self.ency_table = self._default_ency_table.copy()
        self.decy_table = self._default_decy_table.copy()

    @staticmethod
    def generate_hash(input_str):
        """Generate an 8-bit hash for the input string"""
        hash_obj = hashlib.sha256(input_str.encode())
        binary_hash = bin(int(hash_obj.hexdigest(), 16))[2:].zfill(256)
        return binary_hash[:8]

    def encrypt(self, plain_text):
        """Encrypt the plain text using current encryption table"""
        plain_text = ''.join(char for char in plain_text.upper() if char in self.ency_table)
        
        if not plain_text:
            return None
        
        cipher = ""
        for char in plain_text:
            cipher += self.ency_table[char]
        
        hash_cipher = self.generate_hash(plain_text)
        return cipher + hash_cipher

    def decrypt(self, cipher_text):
        """Decrypt the cipher text using current decryption table"""
        plain_text = ""
        i = 0
        while i < len(cipher_text) - 8:  # Ignore last 8 bits (hash)
            chunk = cipher_text[i:i+3]
            if chunk in self.decy_table:
                plain_text += self.decy_table[chunk]
                i += 3
            else:
                plain_text += cipher_text[i]
                i += 1
        
        return plain_text

    def brute_force_decrypt(self, cipher_text):
        """Perform brute force decryption"""
        possible_keys = {v: k for k, v in self._default_ency_table.items()}
        
        for perm in itertools.permutations(possible_keys.keys()):
            trial_key = {k: v for k, v in zip(perm, possible_keys.values())}
            self.ency_table = {v: k for k, v in trial_key.items()}
            self.decy_table = trial_key
            
            decrypted_text = self.decrypt(cipher_text)
            generated_hash = self.generate_hash(decrypted_text)
            
            if generated_hash == cipher_text[-8:]:
                return decrypted_text, trial_key
        
        return None, None

    def custom_key_setup(self):
        """Allow user to set up a custom encryption/decryption key"""
        print("\n--- Custom Key Setup ---")
        print("Enter 3-bit binary codes for A-H (e.g., A=010, B=101)")
        custom_table = {}
        
        for char in 'ABCDEFGH':
            while True:
                code = input(f"Enter 3-bit code for {char}: ").strip()
                if len(code) == 3 and set(code).issubset({'0', '1'}):
                    if code not in custom_table.values():
                        custom_table[char] = code
                        break
                    else:
                        print("Error: This code is already used. Try again.")
                else:
                    print("Invalid input. Use only 0 and 1, 3 bits long.")
        
        # Update tables
        self.ency_table = custom_table
        self.decy_table = {v: k for k, v in custom_table.items()}
        print("Custom key setup complete!")

def main_menu():
    """Display the main menu and handle user interactions"""
    system = EncryptionSystem()
    
    while True:
        print("\n--- Encryption System Menu ---")
        print("1. Encrypt Plain Text")
        print("2. Decrypt Cipher Text")
        print("3. Brute Force Decryption")
        print("4. Set Custom Encryption Key")
        print("5. View Current Encryption/Decryption Tables")
        print("9. Exit")
        
        choice = input("Enter your choice: ").strip()
        
        try:
            if choice == '1':
                # Encryption
                plain_text = input("Enter plain text to encrypt (A-H only): ").upper()
                cipher_text = system.encrypt(plain_text)
                if cipher_text:
                    print("Cipher Text:", cipher_text)
                    print("Hash:", cipher_text[-8:])
                else:
                    print("Invalid input. Use only A-H characters.")
            
            elif choice == '2':
                # Decryption
                cipher_text = input("Enter cipher text to decrypt: ").strip()
                decrypted_text = system.decrypt(cipher_text)
                print("Decrypted Text:", decrypted_text)
            
            elif choice == '3':
                # Brute Force
                cipher_text = input("Enter cipher text for brute force decryption: ").strip()
                decrypted_text, found_key = system.brute_force_decrypt(cipher_text)
                if decrypted_text:
                    print("Brute Force Successful!")
                    print("Decrypted Text:", decrypted_text)
                    print("Found Key:", found_key)
                else:
                    print("Brute force decryption failed.")
            
            elif choice == '4':
                # Custom Key Setup
                system.custom_key_setup()
            
            elif choice == '5':
                # View Current Tables
                print("\n--- Current Encryption Table ---")
                for char, code in system.ency_table.items():
                    print(f"{char}: {code}")
                print("\n--- Current Decryption Table ---")
                for code, char in system.decy_table.items():
                    print(f"{code}: {char}")
            
            elif choice == '9':
                print("Exiting the Encryption System. Goodbye!")
                break
            
            else:
                print("Invalid choice. Please try again.")
        
        except Exception as e:
            print(f"An error occurred: {e}")
            print("Please try again.")

if __name__ == "__main__":
    main_menu()