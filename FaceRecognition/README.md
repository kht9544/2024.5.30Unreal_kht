1. 프로젝트 개요 </br></br>
  이 시스템은 라즈베리파이와 **딥러닝 기반 얼굴 인식 기술(Dlib)**을 활용하여 실시간 얼굴 인식을 수행하고 출석 체크를 자동화하는 프로젝트입니다.</br></br>
2. 주요 구성 요소</br></br>
  1.얼굴 인식 데이터 수집 및 학습</br>
  train_model.py: 얼굴 데이터를 학습하여 KNN 기반 얼굴 인식 모델을 생성합니다.</br>
  align_dlib1.py: 얼굴 정렬을 수행하는 모듈로, Dlib을 활용하여 얼굴 특징점을 찾아 정렬합니다.</br></br> 
  2.라즈베리파이 카메라 스트리밍</br>
  raspi.py: 라즈베리파이에 연결된 카메라로 실시간 영상 스트리밍을 제공하는 Flask 서버입니다.</br>
  /video_feed 경로에서 스트리밍 영상을 확인할 수 있습니다.</br></br>
  3.실시간 얼굴 인식 및 출석 체크</br>
  face_recognition.py 및 test_local.py: 영상에서 얼굴을 탐지하고 KNN 모델을 통해 사용자를 식별합니다.</br>
  사용자가 인식되면 출석 정보가 서버로 전송됩니다.</br>
  test_local.py는 로컬 환경에서 실행되며, face_recognition.py는 출석 체크를 수행하는 메인 코드입니다.</br></br>
  4.서버 및 제어 시스템</br>
  main.py: Flask 기반 서버로, 얼굴 인식 프로세스를 실행/중지할 수 있는 API를 제공합니다.</br></br>
3. 프로젝트 작동 방식</br></br>
  1.사용자가 얼굴 사진을 등록하면, train_model.py에서 데이터를 학습하여 얼굴 인식 모델을 생성합니다.</br></br>
  2.raspi.py가 실행되면서 라즈베리파이 카메라에서 실시간 영상을 스트리밍합니다.</br></br>
  3.face_recognition.py 또는 test_local.py가 스트리밍된 영상을 받아 얼굴을 탐지하고, 학습된 KNN 모델을 이용해 사용자를 식별합니다.</br></br>
  4.인식된 사용자의 ID를 서버로 전송하여 출석을 기록합니다.</br></br>
  5.main.py를 통해 얼굴 인식 프로세스를 시작/중지할 수 있습니다.</br></br>
4. 사용 기술</br></br>
  얼굴 인식: Dlib의 frontal_face_detector, shape_predictor, face_recognition_model_v1 사용</br></br>
  머신러닝: KNeighborsClassifier를 활용한 얼굴 분류 모델</br></br>
  영상 처리: OpenCV를 활용한 실시간 영상 처리</br></br>
  서버: Flask 기반 REST API 서버</br></br>
5. 기대 효과</br></br>
  자동화된 출석 관리: 사용자의 얼굴을 인식하여 자동으로 출석 체크</br></br>
  비접촉 방식: QR코드나 수동 입력 없이 카메라만으로 출석 가능</br></br>
  실시간 처리: 실시간 얼굴 탐지 및 데이터 업데이트 가능
