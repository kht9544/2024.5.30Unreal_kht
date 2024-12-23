import os
import dlib
import cv2
import numpy as np
from sklearn.neighbors import KNeighborsClassifier
from sklearn.preprocessing import LabelEncoder
import joblib
import align_dlib1 as openface
import re

detector = dlib.get_frontal_face_detector()
sp = dlib.shape_predictor("models/shape_predictor_68_face_landmarks.dat")
facerec = dlib.face_recognition_model_v1("models/dlib_face_recognition_resnet_model_v1.dat")
#새로 추가된 모델
face_aligner = openface.AlignDlib("models/shape_predictor_68_face_landmarks.dat")

#사진 변환 전처리 -> 새로 추가
def take_face(filename):
    name = filename.split("_")[0]
    pattern = r"\d+"
    idx = re.search(pattern, filename.split("_")[1]).group()
    new_name = name + '_' + idx + '_complete.jpg'
    print(new_name)
    image = cv2.imread(filename)
    
    detected_faces = detector(image, 1)

    for i, face_rect in enumerate(detected_faces):
        pose_landmarks = sp(image, face_rect)
        alignedFace = face_aligner.align(534, image, face_rect, landmarkIndices=openface.AlignDlib.OUTER_EYES_AND_NOSE)
        cv2.imwrite(new_name, alignedFace) 
    os.remove(filename)

# 얼굴 찾는 함수
def find_faces(img):
    dets = detector(img, 1)

    if len(dets) == 0:
        return []

    shapes = []

    for d in dets:
        shape = sp(img, d)
        shapes.append(shape)

    return shapes

# 얼굴을 인코딩하는 함수
def encode_faces(img, shapes):
    face_descriptors = []

    for shape in shapes:
        face_descriptor = np.array(facerec.compute_face_descriptor(img, shape))
        face_descriptors.append(face_descriptor)

    return face_descriptors

# 트레이닝 데이터 리스트
X_train = []
y_train = []

image_folder = "images/"
person_info = {}

check_new_picture = False

#아직 변환되지 않은 사진이 있는지 탐색 -> 새로 추가
for filename in os.listdir(image_folder):
    if filename.endswith(".jpg"):
        if(len(filename.split("_")) == 2):
            check_new_picture = True
            image_path = os.path.join(image_folder, filename)
            take_face(image_path)

if(check_new_picture):
    for filename in os.listdir(image_folder):
        if filename.endswith(".jpg"):
            name = filename.split("_")[0]
            image_path = os.path.join(image_folder, filename)
            if name in person_info:
                person_info[name].append(image_path)
            else:
                person_info[name] = [image_path]

    for person_name, image_paths in person_info.items():
        for image_path in image_paths:
            img_bgr = cv2.imread(image_path)
            img_rgb = cv2.cvtColor(img_bgr, cv2.COLOR_BGR2RGB)

            faces = find_faces(img_rgb)
            face_descriptors = encode_faces(img_rgb, faces)

            for descriptor in face_descriptors:
                X_train.append(descriptor)
                y_train.append(person_name)

    # 레이블을 숫자로 변환
    label_encoder = LabelEncoder()
    y_train = label_encoder.fit_transform(y_train)

    # 최근접 이웃 분류기 생성 및 학습
    knn = KNeighborsClassifier(n_neighbors=3)
    knn.fit(X_train, y_train)

    # 모델 저장
    joblib.dump(knn, 'face_recognition_model.joblib')
    np.save('label_encoder_classes.npy', label_encoder.classes_)
    print("knn 모델 학습 완료")

else:
    print("이미 최신 모델입니다.")