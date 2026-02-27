from multiprocessing import Process, Queue

def producer(q):
    for i in range(5):
        q.put(i)
        print(f"Produced: {i}")

def consumer(q):
    while True:
        item = q.get()
        if item is None:  # 结束标志
            break
        print(f"Consumed: {item}")

if __name__ == "__main__":
    q = Queue()
    p1 = Process(target=producer, args=(q,))
    p2 = Process(target=consumer, args=(q,))
    p1.start()
    p2.start()
    p1.join()
    q.put(None)  # 通知消费者结束
    p2.join()