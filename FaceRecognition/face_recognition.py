import subprocess
import requests
from sklearn.neighbors import KNeighborsClassifier
from sklearn.preprocessing import LabelEncoder
import joblib
import dlib
import numpy as np
import cv2
import sys
import signal
import time
import json

detector = dlib.get_frontal_face_detector()
sp = dlib.shape_predictor("models/shape_predictor_68_face_landmarks.dat")
facerec = dlib.face_recognition_model_v1("models/dlib_face_recognition_resnet_model_v1.dat")

def signal_handler(sig, frame):
    cv2.destroyAllWindows()
    sys.exit()

signal.signal(signal.SIGINT, signal_handler)

def find_faces(img):
    dets = detector(img, 1)
    if len(dets) == 0:
        return []
    shapes = []
    for d in dets:
        shape = sp(img, d)
        shapes.append(shape)
    return shapes

#스트리밍 url
stream_url = 'http://192.168.137.2:5000/video_feed'

#서버 url
url = "http://192.168.137.100:8080/attendance"


knn = joblib.load('face_recognition_model.joblib')
label_encoder = LabelEncoder()
label_encoder.classes_ = np.load('label_encoder_classes.npy')

check_time = time.time()
recognized_ids = {}
face_encodings = {}

while True:
    try:
        response = requests.get(stream_url, stream=True)
        if response.status_code == 200:
            bytes_data = bytes()
            for chunk in response.iter_content(chunk_size=1024):
                bytes_data += chunk
                a = bytes_data.find(b'\xff\xd8')
                b = bytes_data.find(b'\xff\xd9')
                if a != -1 and b != -1:
                    jpg = bytes_data[a:b + 2]
                    bytes_data = bytes_data[b + 2:]

                    frame = cv2.imdecode(np.frombuffer(jpg, dtype=np.uint8), cv2.IMREAD_COLOR)
                    img_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

                    faces = find_faces(img_rgb)
                    face_detected = False

                    for face in faces:
                        face_id = (face.rect.left(), face.rect.top(), face.rect.right(), face.rect.bottom())

                        # 저장된 인코딩 확인
                        if face_id in face_encodings:
                            face_descriptor = face_encodings[face_id]
                        else:
                            # 인코딩 계산
                            shape = sp(img_rgb, face.rect)
                            face_descriptor = np.array(facerec.compute_face_descriptor(img_rgb, shape))
                            face_encodings[face_id] = face_descriptor
                        check_time = time.time()
                        label = knn.predict([face_descriptor])[0]
                        dist = knn.kneighbors([face_descriptor])[0][0][0]                    

                        threshold = 0.4

                        if dist < threshold:
                            name = label_encoder.inverse_transform([label])[0]
                            if name in recognized_ids:
                                if time.time() - recognized_ids[name] >= 2:
                                    datas = {
                                        'stdId': name
                                    }
                                    headers = {
                                        "Content-Type": "application/json"
                                    }
                                    print(name + " 출석 성공")
                                    recognized_ids[name] = time.time()
                                    try:
                                        response = requests.post(url, data=json.dumps(datas), headers=headers, verify=False)
                                        if response.status_code == 200:
                                            print("Student ID sent successfully.")
                                        else:
                                            print("Failed to send student ID.")
                                    except requests.exceptions.RequestException as e:
                                        print("Failed to connect to the server:", str(e))
                                        exit()
                            else:
                                recognized_ids[name] = time.time()
                        else:
                            name = "unknown"
                        left = face.rect.left()
                        top = face.rect.top()
                        right = face.rect.right()
                        bottom = face.rect.bottom()

                        cv2.rectangle(frame, (left, top), (right, bottom), color=(255, 0, 0), thickness=2)
                        cv2.putText(frame, name, (left, top - 10), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), thickness=2)

                    cv2.imshow('Video Stream', frame)

                    if cv2.waitKey(1) & 0xFF == ord('q'):
                        cv2.destroyAllWindows()
                        sys.exit()
    
    except Exception as e:
        print(f"Error: {e}")
