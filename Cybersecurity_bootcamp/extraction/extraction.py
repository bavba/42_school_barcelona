/**
 * @file
 * @brief This script is used to scan for and recover deleted files from an NTFS disk image.
 *
 * This script takes command-line arguments for the directory to start searching for deleted files
 * and the path to the NTFS disk image. It uses the pytsk3 library to interact with the image and filesystem.
 * It scans the directory and its subdirectories for deleted files, checks their status in the MFT,
 * and can optionally recover them if desired by the user.
 */

import os
import argparse
import pytsk3

/**
 * @brief Scans the specified directory and its subdirectories for deleted files in the given NTFS disk image.
 * @param directory The starting directory for the search.
 * @param img_path The path to the NTFS disk image.
 * @return A list of paths to deleted files found in the directory and its subdirectories.
 */
def scan_files(directory, img_path):
    deleted_files = []
    image = pytsk3.Img_Info(img_path)
    fs_info = pytsk3.FS_Info(image)

    for directory_entry in fs_info.recurse(directory):
        file_path = os.path.join(directory_entry.parent_path, directory_entry.info.name.name)
        if directory_entry.info.meta.type == pytsk3.TSK_FS_META_TYPE_REG and is_file_deleted(directory_entry):
            deleted_files.append(file_path)

    return deleted_files

/**
 * @brief Checks if a given directory entry represents a deleted file based on its MFT flags.
 * @param directory_entry The directory entry to check.
 * @return True if the file is marked as deleted, False otherwise.
 */
def is_file_deleted(directory_entry):
    flags = directory_entry.info.meta.flags
    if flags == pytsk3.TSK_FS_META_FLAG_ALLOC:
        return False
    elif flags == pytsk3.TSK_FS_META_FLAG_UNALLOC:
        return True
    else:
        return False

/**
 * @brief Recovers selected deleted files from the NTFS disk image and saves them to the current working directory.
 * @param file_paths A list of paths to deleted files to be recovered.
 * @param img_path The path to the NTFS disk image.
 */
def recover_files(file_paths, img_path):
    image = pytsk3.Img_Info(img_path)
    fs_info = pytsk3.FS_Info(image)

    for file_path in file_paths:
        directory_entry = fs_info.open(file_path)
        if directory_entry:
            file_data = directory_entry.read_random(0, directory_entry.info.meta.size)
            new_file_path = f"recovered_{os.path.basename(file_path)}"
            with open(new_file_path, "wb") as recovered_file:
                recovered_file.write(file_data)
                print(f"Recovered file: {new_file_path}")

/**
 * @brief Main function that parses command-line arguments, scans for deleted files, and offers recovery options.
 */
def main():
    parser = argparse.ArgumentParser(description="Deleted File Recovery Tool for NTFS")
    parser.add_argument("-d", "--directory", help="Starting directory for deleted file search")
    parser.add_argument("-i", "--image", help="Path to the NTFS disk image")
    args = parser.parse_args()

    if not args.image:
        print("You must specify the path to the NTFS disk image.")
        return

    img_path = args.image

    if args.directory:
        directory = args.directory
    else:
        directory = "/"

    deleted_files = scan_files(directory, img_path)

    if deleted_files:
        print("Deleted files found:")
        for file_path in deleted_files:
            print(file_path)
        choice = input("Do you want to recover the files? (y/n): ")
        if choice.lower() == "y":
            recover_files(deleted_files, img_path)
    else:
        print("No deleted files found.")

if __name__ == "__main__":
    main()
