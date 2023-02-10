from multiprocessing import RLock, Manager, Process
from MainURC import mainURC



if __name__ == '__main__':
	with Manager() as manager:
		# Shared memory
		with Process:
			shared = manager.dict()
			# Shared lock
			lock = RLock()

			# Start process
			p = Process(target=mainURC, args=(shared, lock))
			#p.start()
			#p.join()

			# Do something with shared memory
			print(shared)
			# Lock is not needed here since the process is already finished