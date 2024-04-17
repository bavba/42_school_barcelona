import os
import OpenSSL.crypto
from OpenSSL.crypto import FILETYPE_PEM, FILETYPE_ASN1
from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography.hazmat.primitives import serialization
import hashlib
import logging

logging.basicConfig(filename='decryption.log', level=logging.INFO)

def read_public_key(cert_file):
    with open(cert_file, 'rb') as file:
        cert_data = file.read()
        cert = OpenSSL.crypto.load_certificate(FILETYPE_ASN1, cert_data)
        public_key = cert.get_pubkey()
        rsa_key = public_key.to_cryptography_key().public_key().rsa_public_key()
        return rsa_key

def calculate_private_key(p, q, n):
    private_key = rsa.RSAPrivateKey.construct((n, e, d, p, q))
    return private_key

def decrypt_message(private_key, ciphertext):
    plaintext = private_key.decrypt(ciphertext, None)
    return plaintext

if __name__ == '__main__':
    folder_path = "files_to_decrypt"
    file_extension = ".bin"
    hash_algorithm = hashlib.sha256()
    
    # Get all .pem files in the folder
    pem_files = [file for file in os.listdir(folder_path) if file.endswith(".pem")]
    
    for pem_file in pem_files:
        pem_path = os.path.join(folder_path, pem_file)
        
        # Validate and sanitize file path
        if not os.path.isfile(pem_path):
            logging.error(f"Invalid file path: {pem_path}")
            continue
        
        public_key = read_public_key(pem_path)
        
        # Obtain the necessary data from the public key
        p = public_key.p
        q = public_key.q
        n = public_key.n
        e = public_key.e
        d = private_key.d
        
        # Calculate the private key
        private_key = calculate_private_key(p, q, n)
        
        # Decrypt each corresponding .bin file
        bin_file = pem_file.replace(".pem", file_extension)
        bin_path = os.path.join(folder_path, bin_file)
        
        # Validate and sanitize file path
        if not os.path.isfile(bin_path):
            logging.error(f"Invalid file path: {bin_path}")
            continue
        
        # Verify file integrity with hash
        with open(bin_path, 'rb') as file:
            ciphertext = file.read()
        
        file_hash = hash_algorithm.update(ciphertext).digest()
        
        # Decrypt the message using the private key
        try:
            plaintext = decrypt_message(private_key, ciphertext)
            decrypted_message = plaintext.decode('utf-8')
            
            # Clear data from memory
            del plaintext
            
            print("Decrypted message from", bin_file, ":", decrypted_message)
            logging.info(f"Decrypted message from {bin_file}: {decrypted_message}")
            
        except Exception as e:
            logging.error(f"Decryption error for {bin_file}: {str(e)}")
        
        # Cleanup
        del public_key
        del private_key
        
        # Clear file data from memory
        del cert_data
        del ciphertext
        
    # Clear hash algorithm data from memory
    del hash_algorithm
