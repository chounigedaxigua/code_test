from multiprocessing import Process
from multiprocessing.shared_memory import SharedMemory
import struct

def writer(shm_name, size):
    existing_shm = SharedMemory(name=shm_name)
    buffer = existing_shm.buf
    # 写入 4 个 int: 10, 20, 30, 40
    struct.pack_into('iiii', buffer, 0, 10, 20, 30, 40)
    existing_shm.close()

def reader(shm_name, size):
    existing_shm = SharedMemory(name=shm_name)
    buffer = existing_shm.buf
    data = struct.unpack_from('iiii', buffer, 0)
    print("Read from shared memory:", data)
    existing_shm.close()
    existing_shm.unlink()  # 释放资源

if __name__ == "__main__":
    shm = SharedMemory(create=True, size=16)  # 4 个 int
    p1 = Process(target=writer, args=(shm.name, shm.size))
    p2 = Process(target=reader, args=(shm.name, shm.size))
    p1.start()
    p2.start()
    p1.join()
    p2.join()