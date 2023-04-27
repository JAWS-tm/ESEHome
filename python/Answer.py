from multiprocessing import RLock
from Cypher import Cypher
from InternalDB import InternalDB
import numpy as np

class Answer :

	def __init__(self, shared = {}, lock = RLock, framedData = {}):
		self.shared = shared
		self.lock = lock
		self.framedData = framedData
		self.ackWait = {}
		self.toSendFramedData = {}
		self.cipher = Cypher()
		self.listPubA = np.array
		self.listPG = np.array
		self.baseSationMacID = 0x99
		self.internalDB = InternalDB()

	def globalAnswer(self,framedData):
		id = framedData['id']
		match id:
			case 0x02: #RECENT_RESET
				self.recentReset()
			case 0x03: #ASK_FOR_SOFTWARE_RESET
				self.ask_for_software_reset()
			case 0x11: #ACKNOWLEDGE
				self.acknowledge
			case 0x16: #PING
				self.ping()
			case 0x06: #PONG
				self.pong()
			case 0x30: #EVENT_OCCURED
				self.event_occured()
			case 0x40: #PARAMETER_IS
				self.parameter_is()
			case 0x41: #PARAMETER_ASK
				self.parameter_ask()
			case 0x42: #PARAMETER_WRITE
				self.parameter_write()
			case 0x51: #KEY EXCHANGE
				self.key_exchange()
			case 0x52: #KEY EXCHANGE
				self.key_exchange()
			case 0xFD: #I_HAVE_NO_SERVER_ID
				self.i_have_no_server_id()
			case 0xFE: #YOUR_SERVER_ID_IS
				self.your_server_id_is()
		return self.toSendFramedData

	def recentReset(self):
		#TODO
		pass

	def ask_for_software_reset(self):
		#TODO
		pass

	def acknowledge(self):
		#TODO
		if self.framedData['emitter'] in self.ackWait:
			self.ackWait[self.framedData['emitter']] = True

	def ping(self):
		#TODO
		pass

	def pong(self):
		#TODO
		pass

	def event_occured(self):
		#TODO
		pass

	def parameter_is(self):
		#TODO
		pass

	def parameter_ask(self):
		#TODO
		pass

	def parameter_write(self):
		#TODO
		pass

	def key_exchange(self):
		if self.framedData['emitter'] not in self.listPubA:
			self.toSendFramedData = {
			"data_size": 0x14,
			"emitter" : self.baseSationMacID,
			"receiver" : self.framedData['emitter'],
			"cnt" : self.framedData['cnt']+1,
			"id" : 0x51,
			"message" : self.cipher.pubA
			}
			self.list.append(self.framedData['emitter'])

		elif self.framedData['emitter'] not in self.listPG:
			self.toSendFramedData = {
			"data_size": 0x14,
			"emitter" : self.baseSationMacID,
			"receiver" : self.framedData['emitter'],
			"cnt" : self.framedData['cnt']+1,
			"id" : 0x51,
			"message" : str(self.cipher.g) + str(self.cipher.p)
			}
			self.list.append(self.framedData['emitter'])
		else:
			self.toSendFramedData = {
			"data_size": 0x0,
			"emitter" : self.baseSationMacID,
			"receiver" : self.framedData['emitter'],
			"cnt" : self.framedData['cnt']+1,
			"id" : 0x11
			}
			self.internalDB.insert_key(self.framedData['emitter'],self.cipher.setPubB(self.framedData['message']))


	def i_have_no_server_id(self):
		self.toSendFramedData = {
			"data_size": 0x00,
			"emitter" : self.baseSationMacID,
			"receiver" : self.framedData['emitter'],
			"cnt" : self.framedData['cnt']+1,
			"id" : 0xFE
		}

	def your_server_id_is(self):
		pass


			
