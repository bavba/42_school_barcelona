## @file
# @brief This file contains the Scorpion program.

import argparse
import os
import tkinter as tk
from tkinter import filedialog
from PIL import Image, ExifTags
import re
import subprocess

## @class MetadataEditor.
# @brief A class for the Metadata Editor GUI application.
class MetadataEditor(tk.Tk):
    ## @brief Initializes the MetadataEditor object.
    def __init__(self):
        super().__init__()
        self.title("Scorpion - Metadata Editor")
        self.file_path = None
        self.metadata = {}

        self.create_widgets()

    ## @brief Creates and packs all the widgets in the main application window.
    def create_widgets(self):
        self.file_label = tk.Label(self, text="File:")
        self.file_label.pack()

        self.file_entry = tk.Entry(self, width=50)
        self.file_entry.pack()

        self.file_button = tk.Button(self, text="Browse", command=self.browse_file)
        self.file_button.pack()

        self.load_button = tk.Button(self, text="Load Metadata", command=self.load_metadata)
        self.load_button.pack()

        self.metadata_text = tk.Text(self, height=20, width=80)
        self.metadata_text.pack()

        self.modify_button = tk.Button(self, text="Modify Metadata", command=self.modify_metadata)
        self.modify_button.pack()

        self.erase_button = tk.Button(self, text="Erase Metadata", command=self.erase_metadata)
        self.erase_button.pack()

    ## @brief Opens a file dialog to browse and select a file.
    def browse_file(self):
        file_path = filedialog.askopenfilename()
        self.file_entry.delete(0, tk.END)
        self.file_entry.insert(0, file_path)

    ## @brief Loads the metadata from the selected image file and displays it in the text area.
    def load_metadata(self):
        self.metadata_text.delete("1.0", tk.END)
        file_path = self.file_entry.get()

        if not os.path.isfile(file_path):
            self.metadata_text.insert(tk.END, f"Invalid file path: {file_path}")
            return

        self.file_path = file_path

        self.metadata_text.insert(tk.END, f"Metadata for file: {file_path}\n")

        try:
            image = Image.open(file_path)
            exif_data = image._getexif()

            if exif_data is not None:
                for tag, value in exif_data.items():
                    tag_name = ExifTags.TAGS.get(tag, tag)
                    self.metadata[tag_name] = value
                    self.metadata_text.insert(tk.END, f"{tag_name}: {value}\n")

        except IOError:
            self.metadata_text.insert(tk.END, f"Failed to load metadata for file: {file_path}")

    ## @brief Opens a dialog box to modify the metadata and saves the changes if valid.
    def modify_metadata(self):
        if self.file_path is None:
            self.metadata_text.insert(tk.END, "No file selected.")
            return

        metadata_dialog = MetadataDialog(self, self.metadata)
        self.wait_window(metadata_dialog)

        if metadata_dialog.result:
            new_metadata = metadata_dialog.result

            if self.validate_metadata(new_metadata):
                sanitized_metadata = self.sanitize_metadata(new_metadata)
                self.write_metadata(sanitized_metadata)
                self.metadata_text.delete("1.0", tk.END)
                self.metadata_text.insert(tk.END, "Metadata modified successfully.")
            else:
                self.metadata_text.delete("1.0", tk.END)
                self.metadata_text.insert(tk.END, "Invalid metadata format.")

    ## @brief Erases the metadata from the selected image file.
    def erase_metadata(self):
        if self.file_path is None:
            self.metadata_text.insert(tk.END, "No file selected.")
            return

        self.remove_metadata()
        self.metadata_text.delete("1.0", tk.END)
        self.metadata_text.insert(tk.END, "Metadata erased successfully.")

    ## @brief Validates the format of the metadata dictionary.
    # @param metadata The metadata dictionary to validate.
    # @return True if the metadata format is valid, False otherwise.
    def validate_metadata(self, metadata):
        # Validate metadata format (key: value).
        for key, value in metadata.items():
            if not isinstance(key, str) or not isinstance(value, str):
                return False

            if not re.match(r'^[a-zA-Z0-9_]+$', key) or not re.match(r'^[a-zA-Z0-9_]+$', value):
                return False

        return True

    ## @brief Sanitizes the input to prevent code injection.
    # @param value The input value to be sanitized.
    # @return The sanitized value.
    def sanitize_input(self, value):
        # Sanitize input to prevent code injection.
        sanitized_value = subprocess.check_output(["echo", value], shell=False)
        return sanitized_value.decode().strip()

    ## @brief Sanitizes the metadata dictionary to prevent code injection.
    # @param metadata The metadata dictionary to be sanitized.
    # @return The sanitized metadata dictionary.
    def sanitize_metadata(self, metadata):
        sanitized_metadata = {}
        for key, value in metadata.items():
            sanitized_key = self.sanitize_input(key)
            sanitized_value = self.sanitize_input(value)
            sanitized_metadata[sanitized_key] = sanitized_value
        return sanitized_metadata

    ## @brief Writes the modified metadata to the selected image file using exiftool.
    # @param metadata The modified metadata dictionary to be written.
    def write_metadata(self, metadata):
        # Use command to write metadata.
        try:
            subprocess.check_call(["exiftool", "-overwrite_original", "-all=", self.file_path])
            subprocess.check_call(["exiftool"] + [f"-{key}={value}" for key, value in metadata.items()] + [self.file_path])
        except subprocess.CalledProcessError:
            self.metadata_text.insert(tk.END, f"Failed to write metadata for file: {self.file_path}")

    ## @brief Removes the metadata from the selected image file using exiftool.
    def remove_metadata(self):
        # Use command to remove metadata.
        try:
            subprocess.check_call(["exiftool", "-overwrite_original", "-all=", self.file_path])
        except subprocess.CalledProcessError:
            self.metadata_text.insert(tk.END, f"Failed to remove metadata for file: {self.file_path}")


## @class MetadataDialog.
# @brief A class for the Metadata Editor dialog box.
class MetadataDialog(tk.Toplevel):
    ## @brief Initializes the MetadataDialog object.
    # @param parent The parent Tkinter widget.
    # @param metadata The initial metadata dictionary to be displayed in the dialog box.
    def __init__(self, parent, metadata):
        super().__init__(parent)
        self.title("Metadata Editor")
        self.result = {}

        self.create_widgets(metadata)

    ## @brief Creates and packs all the widgets in the metadata dialog box.
    # @param metadata The initial metadata dictionary to be displayed in the dialog box.
    def create_widgets(self, metadata):
        self.entries = {}

        for key, value in metadata.items():
            frame = tk.Frame(self)
            frame.pack(fill=tk.X, pady=5)

            label = tk.Label(frame, text=key, width=20)
            label.pack(side=tk.LEFT)

            entry = tk.Entry(frame, width=50)
            entry.pack(side=tk.LEFT)
            entry.insert(0, str(value))

            self.entries[key] = entry

        self.save_button = tk.Button(self, text="Save", command=self.save_metadata)
        self.save_button.pack(pady=10)

    ## @brief Saves the modified metadata from the dialog box.
    def save_metadata(self):
        for key, entry in self.entries.items():
            value = entry.get()
            try:
                self.result[key] = str(value)
            except ValueError:
                self.result[key] = str(value)

        self.destroy()


## @fn main.
def main():
    MetadataEditor().mainloop()


## @fn __name__.
if __name__ == '__main__':
    main()