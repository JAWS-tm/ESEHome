#import cryptography
import libnum
import random
import pytest

#from cryptography import Cipher, algorithms, modes

from Cypher import Cypher

#pytest -q test_internaldb.py

def test_encryption_decryption():
    cypher = Cypher()
    pubB = random.randint(100, 200)
    key = cypher.setPubB(pubB)

    message = b'This is a secret'
    encrypted_message = cypher.encryption(message, key)
    decrypted_message = cypher.decryption(encrypted_message, key)

    assert message == decrypted_message


def test_setPubB():
    cypher = Cypher()
    pubB = random.randint(100, 200)
    #cypher.pubB = pubB
    key = cypher.setPubB(pubB)

    expected_key = pow(pubB, cypher.privA, cypher.p).to_bytes(16, byteorder='big')
    assert key == expected_key


def test_p_is_prime():
    cypher = Cypher()
    assert libnum.prime_test_miller_rabin(cypher.p)