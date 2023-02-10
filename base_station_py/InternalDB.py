import sqlite3
import os

class InternalDB:
    def __init__(self):
        self.conn = sqlite3.connect('internal.db', detect_types=sqlite3.PARSE_DECLTYPES|sqlite3.PARSE_COLNAMES)
        self.cursor = self.conn.cursor()

        self.cursor.execute(
            '''
            CREATE TABLE IF NOT EXISTS object_key (
                object_mac_id TEXT PRIMARY KEY,
                key BLOB
            )
            '''
        )
        self.cursor.execute(
            '''
            CREATE TABLE IF NOT EXISTS waiting (
                object_mac_id TEXT PRIMARY KEY,
                msg_id INTEGER,
                cnt INTEGER,
                state TEXT
            )
            '''
        )
        self.conn.commit()

    def insert_key(self, object_mac_id, key):
        self.cursor.execute(
            '''
            INSERT INTO object_key (object_mac_id, key)
            VALUES (?, ?)
            ''',
            (object_mac_id, key)
        )
        self.conn.commit()

    def get_key(self, object_mac_id):
        self.cursor.execute(
            '''
            SELECT key
            FROM object_key
            WHERE object_mac_id=?
            ''',
            (object_mac_id,)
        )
        return self.cursor.fetchone()[0]

    def insert_waiting(self, object_mac_id, msg_id, cnt, state):
        self.cursor.execute(
			'''
			INSERT INTO waiting (object_mac_id, msg_id, cnt, state)
			VALUES (?, ?, ?, ?)
			''',
			(object_mac_id, msg_id, cnt, state)
		)
        self.conn.commit()

    def get_waiting(self, object_mac_id):
        self.cursor.execute(
			'''
			SELECT msg_id, cnt, state
			FROM waiting
			WHERE object_mac_id=?
			''',
			(object_mac_id,)
		)
        return self.cursor.fetchone()

    def delete_waiting(self, object_mac_id):
        self.cursor.execute(
            '''
            DELETE FROM waiting
            WHERE object_mac_id=?
            ''',
            (object_mac_id,)
        )
        self.conn.commit()

    def delete_key(self, object_mac_id):
        self.cursor.execute(
            '''
            DELETE FROM object_key
            WHERE object_mac_id=?
            ''',
            (object_mac_id,)
        )
        self.conn.commit()