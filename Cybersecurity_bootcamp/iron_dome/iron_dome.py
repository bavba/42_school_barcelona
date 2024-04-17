import os
import sys
import shutil
import psutil
import hashlib
import logging
import time
from daemonize import Daemonize

# Path to the log file
LOG_FILE = '/var/log/irondome/irondome.log'

# Critical path to monitor
CRITICAL_PATH = ''

# Setting minimum entropy change to trigger a warning
ENTROPY_THRESHOLD = 0.01

# Setting backup interval in seconds
BACKUP_INTERVAL = 3600

# Setting maximum memory usage to 100 MB (in bytes)
MAX_MEMORY_USAGE = 100 * 1024 * 1024

# Setting maximum disk read speed to 10 MB (in bytes)
MAX_DISK_READ_SPEED = 10 * 1024 * 1024

# Setting maximum number of cryptographic processes that will trigger a warning for anomalous cryptographic activity
MAX_CRYPTO_PROC_THRESHOLD = 5

def setup_logger():
    # Configure the logging module to write logs 
    logging.basicConfig(filename=LOG_FILE, level=logging.INFO, format='%(asctime)s %(levelname)s: %(message)s')

def check_root():
    # Check if the script is executed with root user privileges
    if os.geteuid() != 0:
        logging.error("The program should be executed with root user privileges.")
        sys.exit(1)

def monitor_disk_usage():
    # Monitor the disk usage of the critical path
    total_disk_usage = psutil.disk_usage(CRITICAL_PATH)
    if total_disk_usage.percent > 90:
        logging.warning(f"Disk usage on {CRITICAL_PATH} has exceeded 90%.")

def monitor_disk_reading(file_path):
    # Monitor the reading speed of a file
    with open(file_path, 'rb') as file:
        data = file.read()
        read_speed = len(data) / BACKUP_INTERVAL
        if read_speed > MAX_DISK_READ_SPEED:
            logging.warning(f"Abuse in disk reading detected for file: {file_path}")

def monitor_crypto_activity(file_path):
    # Monitor cryptographic activity of a file
    with open(file_path, 'rb') as file:
        data = file.read()
        hash_value = hashlib.sha256(data).hexdigest()
        if hash_value == 'e9a3c8db17fd4583fa15c55f4bf1d6b6':
            # Pattern of the type of anomalous cryptographic activity to detect
            logging.warning(f"Anomalous cryptographic activity detected for file: {file_path}")

def calculate_entropy(file_path):
    try:
        # Calculate the entropy of a file using SHA-256 hash
        with open(file_path, 'rb') as file:
            data = file.read()
            entropy = hashlib.sha256(data).hexdigest()
        return entropy
    except Exception as e:
        logging.error(f"Could not compute entropy for file {file_path}: {str(e)}")
        return None

def monitor_entropy_change(file_path):
    previous_entropy = calculate_entropy(file_path)
    while True:
        time.sleep(BACKUP_INTERVAL)
        current_entropy = calculate_entropy(file_path)
        if current_entropy and current_entropy != previous_entropy:
            entropy_diff = abs(hash(current_entropy) - hash(previous_entropy))
            if entropy_diff >= ENTROPY_THRESHOLD:
                logging.warning(f"File {file_path} has experienced a significant change in entropy.")
            previous_entropy = current_entropy

def create_backup_folder():
    # Create a backup folder in the user's home directory if it doesn't exist
    home_dir = os.path.expanduser("~")
    backup_folder = os.path.join(home_dir, "backup")
    if not os.path.exists(backup_folder):
        os.makedirs(backup_folder)
    return backup_folder

def perform_backup(backup_folder):
    timestamp = int(time.time())
    backup_path = os.path.join(backup_folder, f"backup_{timestamp}")
    # Create a backup of the critical path directory
    shutil.copytree(CRITICAL_PATH, backup_path)
    logging.info(f"Backup successfully created at {backup_path}.")

def monitor_files(file_paths):
    for file_path in file_paths:
        # Monitor disk reading and cryptographic activity for each file
        monitor_disk_reading(file_path)
        monitor_crypto_activity(file_path)

def main():
    if len(sys.argv) < 2:
        # Check if the critical path is provided as a command-line argument
        logging.error("Please provide the critical path to monitor as an argument.")
        sys.exit(1)

    setup_logger()
    check_root()
    CRITICAL_PATH = sys.argv[1]

    if len(sys.argv) > 2:
        file_extensions = sys.argv[2:]
        file_paths = []
        for root, dirs, files in os.walk(CRITICAL_PATH):
            for file in files:
                file_ext = os.path.splitext(file)[1]
                if file_ext in file_extensions:
                    file_paths.append(os.path.join(root, file))
    else:
        file_paths = []
        for root, dirs, files in os.walk(CRITICAL_PATH):
            for file in files:
                file_paths.append(os.path.join(root, file))

    backup_folder = create_backup_folder()

    while True:
        monitor_disk_usage()
        monitor_files(file_paths)
        for file_path in file_paths:
            monitor_entropy_change(file_path)

        perform_backup(backup_folder)

        # Check memory usage and exit if it exceeds the limit
        memory_usage = psutil.Process(os.getpid()).memory_info().rss
        if memory_usage > MAX_MEMORY_USAGE:
            logging.error("Memory usage has exceeded the limit.")
            sys.exit(1)

if __name__ == '__main__':
    # Running as a daemon
    daemon = Daemonize(app="irondome", pid="/tmp/irondome.pid", action=main)
    daemon.start()
