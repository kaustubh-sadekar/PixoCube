#!/usr/bin/env python

import numpy as np
import cv2
import dlib

p1x_ = 0
p1y_ = 0

class tracker:
  
  def __init__(self,PATH):

    # Get the face detector
    self.faceDetector = dlib.get_frontal_face_detector()

    # The landmark detector is implemented in the shape_predictor class
    self.landmarkDetector = dlib.shape_predictor(PATH)
    self.face_width = 0
    self.rect = None

  def getNose(self,p1x_,p1y_,frame):
    imDlib = cv2.cvtColor(frame,cv2.COLOR_BGR2RGB)
    # Detect faces in the image
    faceRects = self.faceDetector(imDlib, 0)
    i = 0
    try:
      self.face_width = abs(int(faceRects[i].right()) - int(faceRects[i].left()))
      # self.rect = (int(faceRects[i].left()),int(faceRects[i].top()),int(faceRects[i].right()),int(faceRects[i].bottom()))
      # newRect = dlib.rectangle(int(faceRects[i].left()),int(faceRects[i].top()),int(faceRects[i].right()),int(faceRects[i].bottom()))
      # landmarks = self.landmarkDetector(imDlib, newRect)
      p1x = (int(faceRects[i].right()) + int(faceRects[i].left()))//2
      p1y = (int(faceRects[i].top()) + int(faceRects[i].bottom()))//2
      # print(p1x,p1y)
        # for i, part in enumerate(landmarks.parts()):
        #   px = int(part.x)
        #   py = int(part.y)
        #   if i == 4:
        #       p1x = px
        #       p1y = py
    except:
      p1x = p1x_
      p1y = p1y_
  
    return p1x,p1y

  # def getNose(self,p1x_,p1y_,frame):
  #   imDlib = cv2.cvtColor(frame,cv2.COLOR_BGR2RGB)
  #   # Detect faces in the image
  #   faceRects = self.faceDetector(imDlib, 0)
  #   i = 0
  #   try:
  #     self.face_width = abs(int(faceRects[i].right()) - int(faceRects[i].left()))
  #     newRect = dlib.rectangle(int(faceRects[i].left()),int(faceRects[i].top()),int(faceRects[i].right()),int(faceRects[i].bottom()))
  #     landmarks = self.landmarkDetector(imDlib, newRect)
  #     p1x = None
  #     p1y = None
  #     for i, part in enumerate(landmarks.parts()):
  #       px = int(part.x)
  #       py = int(part.y)
  #       if i == 4:
  #           p1x = px
  #           p1y = py
  #   except:
  #     p1x = p1x_
  #     p1y = p1y_
  
  #   return p1x,p1y



# Landmark model location
# PREDICTOR_PATH = "../../models/shape_predictor_68_face_landmarks.dat"
PREDICTOR_PATH = "../shape_predictor_5_face_landmarks.dat"

# cv2.namedWindow('image',cv2.WINDOW_NORMAL)

"""
# Use case example

cap = cv2.VideoCapture(0)
tr = tracker(PREDICTOR_PATH)

while True:
    
    ret, frame = cap.read()
    ret = 1
    if ret:
        frame = cv2.flip(frame,1)
        img = np.copy(frame)
        size = img.shape
        x,y = tr.getNose(p1x_,p1y_,frame)
        img = cv2.circle(img,(x,y),5,(0,255,0),-1)
        p1x_ = x
        p1y_ = y    
        cv2.imshow('image',img)
        k = cv2.waitKey(1) & 0xFF
        if k == 27:
            break
"""