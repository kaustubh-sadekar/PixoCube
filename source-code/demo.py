import cv2
import numpy as np 
import sys
sys.path.append('build')
import kosutils
from tracker import *

H = 700
W = 700

dispWindow = np.zeros((H,W,3),dtype=np.uint8)
PREDICTOR_PATH = "../shape_predictor_5_face_landmarks.dat"


obj1 = kosutils.kos_Obj3D(dispWindow.shape[:2])
cam1 = kosutils.kos_vcam(dispWindow.shape[:2])
cap = cv2.VideoCapture(0)
tr = tracker(PREDICTOR_PATH)

angle = 0
diff = 0
while True:
    ret, frame = cap.read()
    if ret:
        frame = cv2.flip(frame,1)
        img = np.copy(frame)
        size = img.shape[:2]
        x,y = tr.getNose(p1x_,p1y_,frame)
        p1x_ = x
        p1y_ = y
        # rect = tr.rect
        angle+=2*np.pi/180;
        if(angle > 2*np.pi):
            angle = 0
        # try:
        #     cv2.rectangle(frame,(rect[0],rect[1]),(rect[2],rect[3]),(0,255,0),3)
        # except:
        #     pass
        # cv2.imshow("Face Tracking",frame)
        # cv2.waitKey(1)
        drift_x = x - size[1]//2
        drift_y = size[0]//2 - y
        drift_z = -cam1.focal_length-2*(500 - 2*tr.face_width)
        cam1.updtTxMat(drift_x,drift_y,drift_z)
        obj1.rotateObj(np.pi/4,angle,np.pi)
        cam1.render(obj1.pts3d,dispWindow)