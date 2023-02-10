import pytest
import os
import sqlite3
from InternalDB import InternalDB
#import Answer
#import Cypher
import numpy as np
from multiprocessing import RLock

#pytest -q test_internaldb.py

def test_internal_db():
    # Test insert_key
    db = InternalDB()
    object_mac_id = "test_object_mac_id"
    key = b"test_key"
    db.insert_key(object_mac_id, key)
    result = db.get_key(object_mac_id)
    assert result == key

    db.delete_key(object_mac_id)

    # Test insert_waiting and get_waiting
    object_mac_id = "test_object_mac_id_2"
    msg_id = 1
    cnt = 2
    state = "test_state"
    db.insert_waiting(object_mac_id, msg_id, cnt, state)
    result = db.get_waiting(object_mac_id)
    assert result == (msg_id, cnt, state)

    # Test delete_waiting
    db.delete_waiting(object_mac_id)
    result = db.get_waiting(object_mac_id)
    assert result is None