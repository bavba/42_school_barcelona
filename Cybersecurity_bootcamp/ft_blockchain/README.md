# ft_blockchain

ft_blockchain is a simple blockchain API built using Flask. It allows users to create transactions, mine blocks, view the blockchain, register nodes, resolve conflicts, and perform stake operations.

### Installation:
ft_blockchain requires Python 3. Install the necessary dependencies by running the following command:

```pip3 install Flask```

```pip3 install Flask-Limiter```

```pip3 install Flask-Bcrypt```

```pip3 install Flask-JWT-Extended```

```pip3 install Flask-Talisman```

```pip3 install Werkzeug```

### Usage:
Start the Flask server:

```python ft_blockchain.py```

The API will be accessible at http://localhost:5000

Use an API testing tool like Postman to interact with the API endpoints.

#### API Endpoints

```POST /transactions/new``` Create a new transaction.

```GET /mine``` Mine a new block.

```GET /chain``` View the full blockchain.

```POST /nodes/register``` Register new nodes.

```GET /nodes/resolve``` Resolve conflicts between nodes.

```POST /stake``` Perform a stake operation.

```GET /stakeholders``` View the stakeholders.


#### Rate Limiting
The API has rate limiting enabled to prevent abuse. By default, each IP address is limited to 10 requests per minute.

#### Security
The API uses Flask-Talisman to add security headers to the responses, including a Content Security Policy (CSP) that restricts resource loading to only trusted sources.

#### Authentication
Certain API endpoints require authentication. JWT (JSON Web Tokens) are used for authentication. Include the JWT token in the request headers as follows:

```Authorization: Bearer <token>```

#### Error Handling
The API handles various types of errors and returns appropriate error responses.


## Security:

The ft_blockchain project follows certain security mesures to enhance the security and integrity of the code and the tools it provides:

- [x] **Rate Limiting:** The flask-limiter library is used to limit the number of requests to the /transactions/new endpoint to 10 requests per minute. This helps protect against abuse and DDoS attacks.

- [x] **Password Hashing:** The flask-bcrypt library is used to hash passwords, ensuring that user passwords are securely stored in the application.

- [x] **JWT Authentication:** The flask-jwt-extended library is used to implement JSON Web Tokens (JWT) for authentication. The /stake endpoint is protected with the ```@jwt_required```, ensuring that only authenticated users can perform the stake operation.

- [x] **Security Headers:** The flask-talisman library is used to set Content Security Policies (CSP) for the application. The defined CSP restricts resource loading to only trusted sources, reducing the risk of cross-site scripting (XSS) attacks.

It's important to note that while these guidelines aim to enhance the security of the code and tools, no system is completely immune to security risks.
