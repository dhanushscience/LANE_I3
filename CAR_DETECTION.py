import cv2
import pandas as pd
import numpy as np
import serial
from ultralytics import YOLO
import cvzone
from vidgear.gears import CamGear
from tracker import *

model = YOLO('yolov8s.pt')

stream = cv2.VideoCapture(1)

def RGB(event, x, y, flags, param):
    if event == cv2.EVENT_MOUSEMOVE:
        colorsBGR = [x, y]
        print(colorsBGR)

cv2.namedWindow('RGB')
cv2.setMouseCallback('RGB', RGB)

my_file = open("coco.txt", "r")
data = my_file.read()
class_list = data.split("\n")

count = 0
tracker = Tracker()
area1 = [(551, 465), (975, 444), (728, 295), (501, 299)]

# Open serial connection outside the loop
ser = serial.Serial('COM36', 9600)

while True:
    grabbed, frame = stream.read()
    if not grabbed:
        break

    count += 1
    if count % 3 != 0:
        continue

    frame = cv2.resize(frame, (1020, 500))

    results = model.predict(frame)
    a = results[0].boxes.data
    px = pd.DataFrame(a).astype("float")
    detected_objects = []
    
    for index, row in px.iterrows():
        x1, y1, x2, y2, _, d = map(int, row[:6])
        c = class_list[d]

        if c == 'car' or c == 'motorcycle' or c=='truck':
            detected_objects.append([x1, y1, x2, y2])

    bbox_idx = tracker.update(detected_objects)

    for bbox in bbox_idx:
        x3, y3, x4, y4, id1 = bbox
        cx = (x3 + x4) // 2
        cy = (y3 + y4) // 2
        result = cv2.pointPolygonTest(np.array(area1, np.int32), (cx, cy), False)
        
        if result == 1.0:
            ser.write("detected\n".encode())
        
        cv2.circle(frame, (cx, cy), 4, (0, 0, 255), -1)
        cv2.rectangle(frame, (x3, y3), (x4, y4), (255, 255, 255), 2)
        cvzone.putTextRect(frame, f'{id1}', (x3, y3), 1, 1)

    cv2.polylines(frame, [np.array(area1, np.int32)], True, (0, 255, 0), 2)
    cv2.imshow("RGB", frame)

    if cv2.waitKey(1) & 0xFF == 27:
        break


ser.close()
stream.release()
cv2.destroyAllWindows()


