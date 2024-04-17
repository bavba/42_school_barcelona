import os
import subprocess
import datetime

## @file
# @brief This script provides functions to extract forensic information from a Windows system.
# It includes functions to extract information related to registry changes, recent files,
# installed programs, opened programs, browsing history, connected devices, and log events.

## @brief Extracts registry changes within a specified time range.
# @param start_time The start of the time range.
# @param end_time The end of the time range.
def extract_registry_changes(start_time, end_time):
    command = 'reg query HKLM\Software\Microsoft\Windows\CurrentVersion\Run /s'
    process = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)
    output, _ = process.communicate()
    # Process the output and extract relevant information.

## @brief Extracts recently modified or created files within a specified time range.
# @param start_time The start of the time range.
# @param end_time The end of the time range.
def extract_recent_files(start_time, end_time):
    # Extract recent files based on their creation or modification time.
    recent_files = []
    for root, dirs, files in os.walk(os.path.expanduser('~')):
        for file in files:
            path = os.path.join(root, file)
            file_info = os.stat(path)
            file_time = datetime.datetime.fromtimestamp(file_info.st_mtime)
            if start_time <= file_time <= end_time:
                recent_files.append(path)

## @brief Extracts installed programs within a specified time range.
# @param start_time The start of the time range.
# @param end_time The end of the time range.
def extract_installed_programs(start_time, end_time):
    # Extract installed programs from the Windows registry or other sources.
    installed_programs = []
    command = 'wmic product get Name, InstallDate /format:csv'
    process = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)
    output, _ = process.communicate()
    # Process the output and extract relevant information.

## @brief Extracts information about opened programs within a specified time range.
# @param start_time The start of the time range.
# @param end_time The end of the time range.
def extract_opened_programs(start_time, end_time):
    # Extract information about currently running processes or open windows.
    opened_programs = []
    command = 'tasklist /v /fo csv'
    process = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)
    output, _ = process.communicate()
    # Process the output and extract relevant information.

## @brief Extracts browsing history within a specified time range.
# @param start_time The start of the time range.
# @param end_time The end of the time range.
def extract_browsing_history(start_time, end_time):
    # Extract browsing history from browsers' cache or other sources
    browsing_history = []
    # Implement the logic to extract browsing history based on the browser you want to target.

## @brief Extracts information about connected devices within a specified time range.
# @param start_time The start of the time range.
# @param end_time The end of the time range.
def extract_connected_devices(start_time, end_time):
    # Extract information about connected devices (e.g., USB drives, external storage)
    connected_devices = []
    command = 'wmic logicaldisk get Caption, VolumeName, Description /format:csv'
    process = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)
    output, _ = process.communicate()
    # Process the output and extract relevant information
    # Example: Filter devices based on connection time within the time range

## @brief Extracts relevant log events from the Windows Event Log within a specified time range.
# @param start_time The start of the time range.
# @param end_time The end of the time range.
def extract_log_events(start_time, end_time):
    # Extract relevant log events from the Windows Event Log
    log_events = []
    command = 'wevtutil qe System /f:text /q:"*[System[(EventRecordID>0) and (TimeCreated[@SystemTime>="YYYY-MM-DDTHH:MM:SS"] and TimeCreated[@SystemTime<="YYYY-MM-DDTHH:MM:SS"])]]"'
    command = command.replace("YYYY-MM-DDTHH:MM:SS", start_time.strftime("%Y-%m-%dT%H:%M:%S"))
    command = command.replace("YYYY-MM-DDTHH:MM:SS", end_time.strftime("%Y-%m-%dT%H:%M:%S"))
    process = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)
    output, _ = process.communicate()
    # Process the output and extract relevant log events
    # Example: Filter log events based on the specified time range

## @brief Orchestrates the extraction of various forensic information based on the specified time range.
# @param start_time The start of the time range (optional, default is 24 hours before the current time).
# @param end_time The end of the time range (optional, default is the current time).
def forensic_tool(start_time=None, end_time=None):
    # Set default time range if not provided
    if not start_time:
        end_time = datetime.datetime.now()
        start_time = end_time - datetime.timedelta(days=1)
    # Extract information based on the specified time range
    extract_registry_changes(start_time, end_time)
    extract_recent_files(start_time, end_time)
    extract_installed_programs(start_time, end_time)
    extract_opened_programs(start_time, end_time)
    extract_browsing_history(start_time, end_time)
    extract_connected_devices(start_time, end_time)
    extract_log_events(start_time, end_time)

## @brief The main entry point for the forensic analysis.
def main():
    # Define the start and end time for the analysis
    start_time = datetime.datetime(2023, 5, 1)
    end_time = datetime.datetime(2023, 5, 28)

    # Call the forensic_tool function with the specified time range
    forensic_tool(start_time=start_time, end_time=end_time)

# Call the main function if the script is run directly
if __name__ == "__main__":
    main()