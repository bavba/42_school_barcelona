import logging
from flask import Flask, jsonify, request
from werkzeug.exceptions import BadRequest
from flask_limiter import Limiter
from flask_limiter.util import get_remote_address
from flask_bcrypt import Bcrypt
from flask_jwt_extended import JWTManager, create_access_token, jwt_required, get_jwt_identity
from flask_talisman import Talisman
import hashlib
import json
from time import time
from urllib.parse import urlparse
from uuid import uuid4

# Configure logging
logging.basicConfig(level=logging.INFO)

# Create a Flask application instance
app = Flask(__name__)
app.config['SECRET_KEY'] = 'your-secret-key'

# Configure rate limiting
limiter = Limiter(app, key_func=get_remote_address)

# Configure bcrypt for password hashing
bcrypt = Bcrypt(app)

# Configure JWT for authentication
jwt = JWTManager(app)

# Configure Talisman for security headers
csp = {
    'default-src': '\'self\'',
    'script-src': '\'self\'',
    'style-src': '\'self\'',
    'img-src': '\'self\'',
    'font-src': '\'self\'',
    'frame-ancestors': '\'self\'',
}
talisman = Talisman(app, content_security_policy=csp)

# Custom error handler for BadRequest exception
@app.errorhandler(BadRequest)
def handle_bad_request(e):
    response = jsonify({'error': 'Bad request'})
    response.status_code = e.code
    return response

class Blockchain:
    def __init__(self):
        self.chain = []
        self.current_transactions = []
        self.nodes = set()
        self.difficulty = 2  # Initial PoW difficulty
        self.pending_transactions = []
        self.create_block(previous_hash='1', proof=100)  # Genesis block
        self.stakeholders = {}

    def create_block(self, proof, previous_hash):
        block = {
            'index': len(self.chain) + 1,
            'timestamp': time(),
            'transactions': self.current_transactions,
            'proof': proof,
            'previous_hash': previous_hash or self.hash(self.chain[-1]),
        }
        self.current_transactions = []
        self.chain.append(block)
        return block

    def new_transaction(self, sender, recipient, amount):
        self.current_transactions.append({
            'sender': sender,
            'recipient': recipient,
            'amount': amount,
        })
        return self.last_block['index'] + 1

    @staticmethod
    def hash(block):
        block_string = json.dumps(block, sort_keys=True).encode()
        return hashlib.sha256(block_string).hexdigest()

    @property
    def last_block(self):
        return self.chain[-1]

    def proof_of_work(self, last_proof):
        proof = 0
        while self.valid_proof(last_proof, proof) is False:
            proof += 1
        return proof

    def valid_proof(self, last_proof, proof):
        guess = f'{last_proof}{proof}'.encode()
        guess_hash = hashlib.sha256(guess).hexdigest()
        return guess_hash[-4:] == '4242'  # PoW condition

    def register_node(self, address):
        parsed_url = urlparse(address)
        self.nodes.add(parsed_url.netloc)

    def valid_chain(self, chain):
        last_block = chain[0]
        current_index = 1

        while current_index < len(chain):
            block = chain[current_index]
            if block['previous_hash'] != self.hash(last_block):
                return False
            if not self.valid_proof(last_block['proof'], block['proof']):
                return False
            last_block = block
            current_index += 1

        return True

    def resolve_conflicts(self):
        neighbors = self.nodes
        new_chain = None

        max_length = len(self.chain)

        for node in neighbors:
            response = requests.get(f'http://{node}/chain')

            if response.status_code == 200:
                length = response.json()['length']
                chain = response.json()['chain']

                if length > max_length and self.valid_chain(chain):
                    max_length = length
                    new_chain = chain

        if new_chain:
            self.chain = new_chain
            return True

        return False

    def calculate_difficulty(self):
        last_block = self.last_block
        if last_block['index'] % 5 == 0:  # Increase difficulty every 5 blocks
            self.difficulty += 1

    def add_pending_transaction(self, sender, recipient, amount):
        self.pending_transactions.append({
            'sender': sender,
            'recipient': recipient,
            'amount': amount
        })

    def stake(self, node_identifier):
        self.stakeholders[node_identifier] = 100  # Initialize stake with 100 tokens

    def get_stakeholders(self):
        return self.stakeholders

    def proof_of_stake(self):
        total_stake = sum(self.stakeholders.values())
        probabilities = {node: stake / total_stake for node, stake in self.stakeholders.items()}
        sorted_probabilities = sorted(probabilities.items(), key=lambda x: x[1], reverse=True)
        return sorted_probabilities[0][0]

    def mine(self):
        if not self.pending_transactions:
            return False

        last_block = self.last_block
        last_proof = last_block['proof']
        proof = self.proof_of_work(last_proof)

        self.calculate_difficulty()

        self.new_transaction(sender='0', recipient=self.proof_of_stake(), amount=1)

        previous_hash = self.hash(last_block)
        block = self.create_block(proof, previous_hash)

        return block

# Create an instance of the Blockchain
blockchain = Blockchain()


@app.route('/transactions/new', methods=['POST'])
@limiter.limit("10/minute")  # Limit requests to 10 per minute
def new_transaction():
    values = request.get_json()
    logging.info('Received new transaction request: %s', values)

    required = ['sender', 'recipient', 'amount']
    if not all(k in values for k in required):
        raise BadRequest

    index = blockchain.new_transaction(values['sender'], values['recipient'], values['amount'])
    response = {'message': f'Transaction will be added to block {index}'}
    return jsonify(response), 201


@app.route('/mine', methods=['GET'])
def mine():
    logging.info('Received mine request')
    block = blockchain.mine()
    if block:
        response = {
            'message': 'New block mined',
            'index': block['index'],
            'transactions': block['transactions'],
            'proof': block['proof'],
            'previous_hash': block['previous_hash'],
        }
        return jsonify(response), 200
    else:
        return 'No pending transactions to mine', 400


@app.route('/chain', methods=['GET'])
def full_chain():
    logging.info('Received chain request')
    response = {
        'chain': blockchain.chain,
        'length': len(blockchain.chain),
    }
    return jsonify(response), 200


@app.route('/nodes/register', methods=['POST'])
def register_nodes():
    values = request.get_json()
    logging.info('Received register nodes request: %s', values)

    nodes = values.get('nodes')
    if nodes is None:
        raise BadRequest("Error: Expecting a valid list of nodes")

    for node in nodes:
        blockchain.register_node(node)

    response = {
        'message': 'New nodes have been added',
        'total_nodes': list(blockchain.nodes),
    }
    return jsonify(response), 201


@app.route('/nodes/resolve', methods=['GET'])
def consensus():
    logging.info('Received consensus request')
    replaced = blockchain.resolve_conflicts()

    if replaced:
        response = {
            'message': 'The chain was replaced',
            'new_chain': blockchain.chain
        }
    else:
        response = {
            'message': 'The chain is authoritative',
            'chain': blockchain.chain
        }

    return jsonify(response), 200


@app.route('/stake', methods=['POST'])
def stake():
    logging.info('Received stake request')
    blockchain.stake(node_identifier)
    response = {'message': 'Stake performed successfully'}
    return jsonify(response), 200


@app.route('/stakeholders', methods=['GET'])
def get_stakeholders():
    logging.info('Received get stakeholders request')
    stakeholders = blockchain.get_stakeholders()
    response = {'stakeholders': stakeholders}
    return jsonify(response), 200


# Start the Flask server
if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
