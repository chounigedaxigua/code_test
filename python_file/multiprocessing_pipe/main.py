from multiprocessing import Process, Pipe

def child(conn):
    conn.send("Hello from child")
    print("Child received:", conn.recv())
    conn.close()

if __name__ == "__main__":
    parent_conn, child_conn = Pipe()
    p = Process(target=child, args=(child_conn,))
    p.start()
    print("Parent received:", parent_conn.recv())
    parent_conn.send("Hi from parent")
    p.join()