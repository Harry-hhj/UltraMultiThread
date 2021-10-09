import time
import threading
import Message_int  # Contains the data type and the corresponding P/S pair.
                    # The name is the same as the name registered in cpp.
import Message_MSG
from Message_MSG import MSG


def Publisher_B():
    pub = Message_int.Publisher("link_B")

    i: int = 0
    while True:
        pub.push(i)
        time.sleep(0.5)


def Subscriber_B():
    sub = Message_int.Subscriber("link_B", 1)

    while True:
        # don't forget try-except block for subscriber
        try:
            data: int = sub.pop()
            print("link B: [LOGINFO] id = %d" % data)
        except:
            print("[WARNING] pub_B not ready.")
            time.sleep(0.2)


def Subscriber_C():
    sub = Message_MSG.Subscriber("link_C")

    while True:
        try:
            data:MSG = sub.pop()
            print("Link C: ", end='', flush=True)
            data.print()
        except:
            print("[WARNING] pub_C not ready.")
            time.sleep(0.2)


def Publisher_D():
    pub = Message_MSG.Publisher("link_D");

    cnt: int = 0
    while True:
        pub.push(MSG(cnt, "Hello world."))
        cnt = cnt + 1

        time.sleep(0.5)


threading.Thread(target=Publisher_B, daemon=True).start()
threading.Thread(target=Subscriber_B, daemon=True).start()
threading.Thread(target=Subscriber_C, daemon=True).start()
threading.Thread(target=Publisher_D, daemon=True).start()