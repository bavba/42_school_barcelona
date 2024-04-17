# coRSAir

coRSAir is a Python tool that allows you to decrypt multiple files using RSA encryption with OpenSSL and cryptography libraries. It reads RSA public key certificates (.pem) and corresponding encrypted files (.bin) to perform decryption using the private key.

### Installation:
coRSAir requires Python 3. Install the necessary dependencies by running the following command:

```pip3 install cryptography```

Ensure that OpenSSL library is installed on your system. You can download it from the official [OpenSSL website](https://www.openssl.org) and follow the installation instructions specific to your operating system.

### Usage:

Place the PEM-encoded RSA public key certificates (.pem files) and their corresponding encrypted files (.bin files) in a folder named ```files_to_decrypt```.

Run the script by executing the following command:

```python3 coRSAir.py```

The script will process each public key certificate and its corresponding encrypted file in the "files_to_decrypt" folder. It will decrypt the files using the private key extracted from the certificate and display the decrypted message on the console.

The decrypted messages and any encountered errors will be logged in the "decryption.log" file for reference and troubleshooting.

## Security:

The coRSAir project follows certain security mesures to enhance the security and integrity of the code and the tools it provides:

- [x] **Secure file handling:** Each file path is validated and sanitized using ```os.path.isfile``` to ensure it points to a valid file. File integrity is verified by calculating the hash of the ciphertext using a secure hash algorithm (SHA-256) and securely clearing the hash algorithm data from memory.

- [x] **Input validation and sanitization:** File paths are validated to prevent directory traversal attacks and path manipulation vulnerabilities.

- [x] **Error handling and logging:** Errors and exceptions are properly logged to a secure log file (decryption.log) instead of displaying sensitive error messages to users.

- [x] **Encryption and decryption security:** The code assumes the use of secure encryption algorithms and modes based on the provided libraries (OpenSSL and cryptography).
      
- [x] **Secure memory management:** Sensitive data, such as decrypted plaintext and the hash algorithm, is explicitly cleared from memory using ```del``` statements to minimize the risk of memory leaks and unauthorized access.

- [x] **Secure dependencies:** It's assumed that the OpenSSL and cryptography libraries are obtained from reputable sources and are kept up to date with security patches.

It's important to note that while these guidelines aim to enhance the security of the code and tools, no system is completely immune to security risks.
