# Set Python image.
FROM python:3.8-slim

# Set the working directory inside the container.
WORKDIR /app

# Copy the ransomware code into the container.
COPY stockholm.py .

# Install cryptography package.
RUN pip install cryptography

# Create the infection directory.
RUN mkdir -p /app/infection

# Make the Stockholm script executable.
RUN chmod +x stockholm.py

# Define the entry point for the container.
ENTRYPOINT ["./stockholm.py"]
