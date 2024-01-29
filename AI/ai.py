print("import modules")
from ultralytics import YOLO
from ultralytics.solutions import object_counter
import cv2
import threading
import socket


print("setting thread")
frame = None
ret = None
state = None
infered_frame = None
is_new_frame = False
end_thread_flag = False
is_full = False
server_ip = "0.0.0.0"
server_port = 12345


frame_lock = threading.Lock()
infered_frame_lock = threading.Lock()
state_lock = threading.Lock()


def read_frames():
    print("start cam thread")
    global frame
    global ret
    global end_thread_flag    

    print("load cam")
    cam = cv2.VideoCapture(0)
    cam.set(cv2.CAP_PROP_FRAME_WIDTH, 224)
    cam.set(cv2.CAP_PROP_FRAME_HEIGHT, 224)
    cam.set(cv2.CAP_PROP_FPS, 36)
    if(not cam.isOpened()):
        raise Exception("cam is closed")
    
    while True:
        while not is_full:
            pass

        current_ret, current_frame = cam.read()
        with frame_lock:
            if current_ret :
                frame = current_frame[:, :, [2, 1, 0]]
            ret = current_ret

        if end_thread_flag :
            break
    cam.release()
    print("end cam thread")

def check_object():
    print("start ai thread")
    global state
    global frame
    global infered_frame
    global end_thread_flag    
    global is_new_frame

    print("load model")
    model = YOLO("yolov8n.pt")
    while True:
        while is_full :
            pass


        with frame_lock:            
            current_frame = frame            
        if current_frame is None:
            continue
        results = model.predict(current_frame, imgsz=(224,224), device = "cpu")
        with infered_frame_lock:
            infered_frame = results
            is_new_frame = True
        if end_thread_flag :
            break
    print("end ai thread")


def send_congestion():
    global is_new_frame
    global frame
    while True:
        while not is_full :
            pass
        if is_new_frame :
            is_new_frame = False
            client_socket.send()
        else:
            continue

cam_thread = threading.Thread(target=read_frames)
cam_thread.start()

ai_thread = threading.Thread(target=check_object)
ai_thread.start()


server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((server_ip, server_port))
server_socket.listen()
client_socket, addr = server_socket.accept()

while(True):

    received = client_socket.recv(1024).decode().strip()
    if not received :
        is_full = False
        client_socket, addr = server_socket.accept()        
        continue
    elif received == "is full":
        if_full = True
    
    elif received == "not is full":
        is_full = False
        

end_thread_flag = True

cv2.destroyAllWindows()