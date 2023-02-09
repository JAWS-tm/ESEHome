from multiprocessing import Rlock, Manager, Process
from MainURC import mainURC

if __name__ == '__main__':

	with Process:
		manager = Manager()
		# Shared memory
		shared = manager.dict()
		# Shared lock
		lock = Rlock()

		# Start process
		p = Process(target=mainURC, args=(shared, lock))
		p.start()
		p.join()

		# Do something with shared memory
		print(shared)
		# Lock is not needed here since the process is already finished