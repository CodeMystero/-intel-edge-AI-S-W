import cv2
import datetime
from PIL import ImageFont, ImageDraw, Image
import numpy as np


# 카메라 영상을 받아올 객체 선언 및 설정(영상 소스, 해상도 설정)
capture = cv2.VideoCapture(1)
capture.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
capture.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

fourcc = cv2.VideoWriter_fourcc(*'XVID')    # 영상을 기록할 코덱 설정
font = ImageFont.truetype('fonts/SCDream6.otf', 20) # 글꼴파일을 불러옴
is_record = False                           # 녹화상태는 처음엔 거짓으로 설정

# 무한루프
while True:
    # 현재시각을 불러와 문자열로저장
    now = datetime.datetime.now()
    nowDatetime = now.strftime('%Y-%m-%d %H:%M:%S')
    nowDatetime_path = now.strftime('%Y-%m-%d %H_%M_%S') # 파일이름으로는 :를 못쓰기 때문에 따로 만들어줌
    ret, frame = capture.read()     # 카메라로부터 현재 영상을 받아 frame에 저장, 잘 받았다면 ret가 참
    
    # 글자가 잘보이도록 배경을 넣어줌
    # img는 사각형을 넣을 이미지, pt1, pt2는 사각형의 시작점과 끝점, color는 색상(파랑,초록,빨강), tickness는 선굵기(-1은 내부를 채우는 것)
    cv2.rectangle(img=frame, pt1=(10, 15), pt2=(340, 35), color=(0,0,0), thickness=-1)     
    
    # 아래의 4줄은 글자를 영상에 더해주는 역할을 함    
    frame = Image.fromarray(frame)    
    draw = ImageDraw.Draw(frame)    
    # xy는 텍스트 시작위치, text는 출력할 문자열, font는 글꼴, fill은 글자색(파랑,초록,빨강)   
    draw.text(xy=(10, 15),  text="웹캠 "+nowDatetime, font=font, fill=(255, 255, 255))
    frame = np.array(frame)

    
    key = cv2.waitKey(30)   # 30ms 동안 키입력 대기
    if key == ord('r') and is_record == False:  # 현재 녹화상태가 아니며 r 키를 누르면
        is_record = True            # 녹화상태로 만들어줌
        # 비디오 객체에 (파일이름(한글가능), 인코더, 초당프레임률(정확하지 않음), 영상크기) 로 영상을 쓸 준비
        video = cv2.VideoWriter("웹캠 " + nowDatetime_path + ".avi", fourcc, 15, (frame.shape[1], frame.shape[0]))
    elif key == ord('r') and is_record == True: # 녹화중인 상태에서 다시 r키를 누르면
        is_record = False       # 녹화상태를 꺼줌
        video.release()         # 녹화 종료
    elif key == ord('c'):       # c 키를 누르면
        # (파일이름(한글불가, 영어만), 이미지)로 영상을 캡쳐하여 그림파일로 저장
        cv2.imwrite("capture " + nowDatetime_path + ".png", frame)  # 파일이름(한글안됨), 이미지 
    elif key == ord('q'):  # 키보드의 q 를 누르면 무한루프가 멈춤
            break
    if is_record == True:       # 현재 녹화상태이면            
        # 비디오 객체에 현재 프레임 저장
        video.write(frame)
        # 녹화중이라는 것을 보여주기 위해 보여주는 화면에는 빨간색 점을 표시해줌
        cv2.circle(img=frame, center=(620, 15), radius=5, color=(0,0,255), thickness=-1)
    cv2.imshow("output", frame)   # 현재 시간을 표시하는 글자를 써준 영상 출력
    
capture.release()                   # 캡처 객체를 없애줌
cv2.destroyAllWindows()             # 모든 영상 창을 닫아줌