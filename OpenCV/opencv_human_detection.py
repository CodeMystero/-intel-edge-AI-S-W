
#   opencv python 코딩
#   얼굴을 인식한 상태에만 자동으로 촬영
#

import cv2

# opencv python 코딩 기본 틀
# 카메라 영상을 받아올 객체 선언 및 설정(영상 소스, 해상도 설정)
capture = cv2.VideoCapture(1)
capture.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
capture.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

# haar cascade 검출기 객체 선언
face_cascade = cv2.CascadeClassifier('haarcascade/haarcascade_frontalface_default.xml')
eye_cascade = cv2.CascadeClassifier('haarcascade/haarcascade_eye.xml')
# 무한루프
while True:    
    ret, frame = capture.read()     # 카메라로부터 현재 영상을 받아 frame에 저장, 잘 받았다면 ret가 참
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)  # 영상을 흑백으로 바꿔줌

    # scaleFactor를 1에 가깝게 해주면 정확도가 상승하나 시간이 오래걸림
    # minNeighbors를 높여주면 검출률이 상승하나 오탐지율도 상승
    faces = face_cascade.detectMultiScale(gray, scaleFactor= 1.5, minNeighbors=3, minSize=(20,20))
    eyes = eye_cascade.detectMultiScale(gray, scaleFactor= 1.5, minNeighbors=3, minSize=(10,10))
    # print(faces)
    
    # 찾은 얼굴이 있으면
    # 얼굴 영역을 영상에 사각형으로 표시
    if len(faces) :
        for  x, y, w, h in faces :
            cv2.rectangle(frame, (x, y), (x + w, y + h), (255,255,255), 2, cv2.LINE_4)
    if len(eyes) :
        for  x, y, w, h in eyes :
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0,0,255), 2, cv2.LINE_4)
    cv2.imshow("original", frame)   # frame(카메라 영상)을 original 이라는 창에 띄워줌 
    if cv2.waitKey(1) == ord('q'):  # 키보드의 q 를 누르면 무한루프가 멈춤
            break

capture.release()                   # 캡처 객체를 없애줌
cv2.destroyAllWindows()             # 모든 영상 창을 닫아줌