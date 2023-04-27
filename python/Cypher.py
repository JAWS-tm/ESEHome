#import cryptography 
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
import sys
import libnum
import random

class Cypher:
    def __init__ (self, bitsize = 128, gSize = 8):
        self.privA = 462
        self.p = libnum.generate_prime(bitsize)
        self.g = int.from_bytes(  random.randbytes(gSize) )
        self.pubA = pow(self.g, self.privA, self.p)
        self.iv = random.randbytes(16)

    def setPubB(self, pubB):
        key = pow(pubB, self.privA, self.p)
        return key.to_bytes(16, byteorder='big')

    def encryption(self, message, key):
        cipher = Cipher(algorithms.AES(key), modes.CBC(self.iv))
        return cipher.encryptor().update(message) + cipher.encryptor().finalize()

    def decryption(self, message, key):
        cipher = Cipher(algorithms.AES(key), modes.CBC(self.iv))
        return cipher.decryptor().update(message) + cipher.decryptor().finalize()


