## @file
# @brief This file contains the ft_otp program.

import sys
import os
import getpass
import hashlib
import hmac
import struct
import time
import argparse
import pyotp

## Constants.
KEY_SIZE = 64
SALT_SIZE = 16
ITERATIONS = 100000

def print_error(message):
    ## Print an error message and exit the program.
    # @param message The error message to display.
    sys.stderr.write("Error: {}\n".format(message))
    sys.exit(1)

def derive_key(password, salt):
    ## Derive a key using the PBKDF2 algorithm with SHA256 hash.
    # @param password The password used for key derivation.
    # @param salt The salt used in key derivation.
    # @return The derived key.
    kdf = hashlib.pbkdf2_hmac("sha256", password, salt, ITERATIONS, dklen=KEY_SIZE)
    return kdf

def generate_key(key_file, key=None):
    ## Generate and encrypt a key, saving it to a file.
    # @param key_file The name of the file to save the encrypted key.
    # @param key Optional hexadecimal key to use for encryption.
    try:
        with open(key_file, "wb") as file:
            if not key:
                key = getpass.getpass("Enter a hexadecimal key of at least 64 characters: ")

            if len(key) < KEY_SIZE:
                print_error("Key must be at least 64 characters.")

            key_bytes = bytes.fromhex(key)
            salt = os.urandom(SALT_SIZE)
            derived_key = derive_key(key_bytes, salt)

            file.write(salt)
            file.write(derived_key)

        encrypted_file = "ft_otp.key"
        password = getpass.getpass("Enter a password to encrypt the key: ")
        confirm_password = getpass.getpass("Confirm the password: ")

        if password != confirm_password:
            print_error("Failed to encrypt the key. Passwords do not match.")

        password = password.encode("utf-8")

        with open(key_file, "rb") as file:
            salt = file.read(SALT_SIZE)
            derived_key = file.read(KEY_SIZE)

        hmac_key = hmac.new(password, derived_key, hashlib.sha256)
        encrypted_key = hmac_key.digest()

        with open(encrypted_file, "wb") as file:
            file.write(encrypted_key)

        print("Key was successfully saved in {}.".format(encrypted_file))
    except Exception as e:
        print_error("Failed to generate key: {}".format(str(e)))

def generate_temp_password(key_file):
    ## Generate a temporary password using the Time-based One-Time Password (TOTP) algorithm.
    # @param key_file The name of the file containing the encrypted key.
    try:
        password = getpass.getpass("Enter the password for the key file: ").encode("utf-8")

        with open(key_file, "rb") as file:
            salt = file.read(SALT_SIZE)
            derived_key = file.read(KEY_SIZE)

        hmac_key = hmac.new(password, derived_key, hashlib.sha256)
        encrypted_key = hmac_key.digest()

        current_time = int(time.time())
        counter = int(current_time / 30)

        hmac_result = hmac.new(encrypted_key, struct.pack(">Q", counter), hashlib.sha1)
        truncated_code = struct.unpack(">I", hmac_result.digest()[-4:])[0] & 0x7FFFFFFF
        totp_token = "{:06d}".format(truncated_code % 1000000)

        print("Your temporary password is: {}".format(totp_token))
    except Exception as e:
        print_error("Failed to generate temporary password: {}".format(str(e)))


## @fn main.
def main():
    parser = argparse.ArgumentParser(description="One-Time Password Generator")
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument("-g", "--generate-key", dest="key_file", help="Generate and encrypt a key")
    group.add_argument("-k", "--generate-temp-password", dest="key_file", help="Generate a temporary password")

    args = parser.parse_args()

    if args.key_file:
        if args.generate_key:
            generate_key(args.key_file)
        elif args.generate_temp_password:
            generate_temp_password(args.key_file)
            

## @fn __name__.
if __name__ == "__main__":
    main()