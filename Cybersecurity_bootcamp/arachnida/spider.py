## @file
# @brief This file contains the Spider program.

import argparse
import os
import requests
from bs4 import BeautifulSoup
from urllib.parse import urlparse, urljoin
import re
from html import escape

## @var ALLOWED_IMAGE_EXTENSIONS.
# @brief List of allowed image file extensions.
ALLOWED_IMAGE_EXTENSIONS = ['.jpg', '.jpeg', '.png', '.gif', '.bmp']

## @var ALLOWED_SCHEMES.
# @brief List of allowed URL schemes.
ALLOWED_SCHEMES = ['https']

## @var SAFE_CONTENT_TYPES.
# @brief List of safe content types for image files.
SAFE_CONTENT_TYPES = [
    'image/jpg',
    'image/jpeg',
    'image/png',
    'image/gif',
    'image/bmp',
]

## @var FILE_SIGNATURES.
# @brief Dictionary of file signatures and their corresponding content types.
FILE_SIGNATURES = {
    b'\xFF\xD8\xFF\xE0\x00\x10\x4A\x46\x49\x46\x00\x01': 'image/jpg',  
    b'\xFF\xD8\xFF': 'image/jpeg',  
    b'\x89\x50\x4E\x47\x0D\x0A\x1A\x0A': 'image/png',  
    b'\x47\x49\x46\x38\x37\x61': 'image/gif',  
    b'\x42\x4D': 'image/bmp',  
}

## @fn validate_input_path.
# @brief Validates the input file path.
# @param path The file path to be validated.
# @return The absolute and normalized file path.
def validate_input_path(path):
    # Implement input validation for file paths.
    if not os.path.isabs(path):
        raise ValueError("Path must be an absolute file path.")
    if not os.path.exists(path):
        raise ValueError("The specified path does not exist.")
    if not os.path.isfile(path):
        raise ValueError("The specified path is not a file.")
    return os.path.realpath(path)

## @fn validate_url.
# @brief Validates the input URL.
# @param url The URL to be validated.
# @return The valid URL.
def validate_url(url):
    # Implement input validation for URLs.
    parsed_url = urlparse(url)
    if parsed_url.scheme not in ALLOWED_SCHEMES:
        raise ValueError("Invalid URL scheme. Only HTTPS are allowed.")
    return url

## @fn download_file.
# @brief Downloads a file from the given URL and saves it to the specified path.
# @param url The URL of the file to be downloaded.
# @param path The path to save the downloaded file.
def download_file(url, path):
    response = requests.get(url, verify=True)  # Enable SSL verification.
    if response.status_code == 200:
        content_type = response.headers.get('Content-Type')
        if content_type not in SAFE_CONTENT_TYPES:
            raise ValueError("Unsupported or unsafe file type.")
        with open(path, 'wb') as file:
            file.write(response.content)

## @fn verify_file_type.
# @brief Verifies the file type by examining its contents.
# @param path The file path to be verified.
# @return The content type of the file.
def verify_file_type(path):
    # Verify the file type by examining its contents.
    with open(path, 'rb') as file:
        file_header = file.read(12)  # Read the first 12 bytes.

    for signature, file_type in FILE_SIGNATURES.items():
        if file_header.startswith(signature):
            return file_type

    raise ValueError("Unknown file type.")

## @fn sanitize_html.
# @brief Sanitizes HTML content to prevent cross-site scripting (XSS).
# @param html The HTML content to be sanitized.
# @return The sanitized HTML content.
def sanitize_html(html):
    # Implement HTML sanitization to prevent cross-site scripting (XSS).
    sanitized_html = re.sub(r'<script.*?</script>', '', html, flags=re.IGNORECASE)
    return sanitized_html

## @fn escape_html_attributes.
# @brief Escapes HTML attribute values to prevent attribute-based XSS attacks.
# @param attrs The dictionary of HTML attributes.
# @return The dictionary of escaped HTML attributes.
def escape_html_attributes(attrs):
    # Escape HTML attribute values to prevent attribute-based XSS attacks.
    return {key: escape(value) for key, value in attrs.items()}

## @fn sanitize_html_attributes.
# @brief Sanitizes HTML attributes to prevent attribute-based XSS attacks.
# @param soup The BeautifulSoup object representing the HTML content.
# @return The sanitized BeautifulSoup object.
def sanitize_html_attributes(soup):
    # Sanitize HTML attributes to prevent attribute-based XSS attacks.
    for element in soup.findAll():
        element.attrs = escape_html_attributes(element.attrs)
    return soup

## @fn spider.
# @brief Recursively extracts images from a website.
# @param url The URL of the website to crawl.
# @param max_depth The maximum depth level for recursive download.
# @param save_path The path to save the downloaded images.
def spider(url, max_depth, save_path):
    parsed_url = urlparse(url)
    base_url = parsed_url.scheme + '://' + parsed_url.netloc
    visited_urls = set()

    def crawl(url, depth):
        if depth > max_depth:
            return

        visited_urls.add(url)
        response = requests.get(url, verify=True)  # Enable SSL verification.
        if response.status_code == 200:
            sanitized_html = sanitize_html(response.text)
            soup = BeautifulSoup(sanitized_html, 'html.parser')
            soup = sanitize_html_attributes(soup)

            images = soup.find_all('img')
            for img in images:
                img_url = img.get('src')
                if img_url:
                    absolute_img_url = urljoin(base_url, img_url)
                    img_extension = os.path.splitext(absolute_img_url)[1].lower()
                    if img_extension in ALLOWED_IMAGE_EXTENSIONS:
                        img_path = os.path.join(save_path, os.path.basename(urlparse(absolute_img_url).path))
                        download_file(absolute_img_url, img_path)
                        try:
                            file_type = verify_file_type(img_path)
                            print(f"Downloaded image: {img_path} (Type: {file_type})")
                        except ValueError as e:
                            os.remove(img_path)
                            print(f"Failed to verify file type: {img_path}. Reason: {str(e)}")

            links = soup.find_all('a')
            for link in links:
                href = link.get('href')
                if href and urlparse(href).netloc == parsed_url.netloc and href not in visited_urls:
                    absolute_link_url = urljoin(base_url, href)
                    crawl(absolute_link_url, depth + 1)

    crawl(url, 1)

## @fn main.
def main():
    parser = argparse.ArgumentParser(description='Spider - Extract images recursively from a website')
    parser.add_argument('url', help='URL of the website')
    parser.add_argument('-r', action='store_true', help='Download images recursively')
    parser.add_argument('-l', type=int, default=5, help='Maximum depth level for recursive download')
    parser.add_argument('-p', dest='save_path', default='./data/', help='Path to save the downloaded images')
    args = parser.parse_args()

    try:
        # Validate inputs.
        save_path = validate_input_path(args.save_path)
        url = validate_url(args.url)

        if not os.path.exists(save_path):
            os.makedirs(save_path)

        if args.r:
            spider(url, args.l, save_path)
    except Exception as e:
        print(f"An error occurred: {str(e)}")

## @fn __name__.
if __name__ == '__main__':
    main()