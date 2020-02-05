# PixoCube
PixoCube is a digital version of photo cubes that people usually gift others. It is basically a 3D cube with different images consisting of different sides of the cube. The interesting part of this project is I used concepts of **camera projection** and only opencv functions to render the cube. Moreover the camera view point is rendered such that it shifts based on the movement of users face.

![Altext](gif3.gif)

## Instructions to setup and run the project demo

1. When running demo.py for the first time, use the following command `bash script.sh`.
2. When not running it for the first time use the following command `python3 demo.py`

## Key points of the project

* Understanding all the components of a camera projection matrix.
* Developing a virtual camera using a self defined camera projection matrix.
* Calculating pixel coordinates of vertices of a 3D cube when projected into the virtual camera.
* Using the projected pixel coordinates and perspective transform, rendering sides of the cube with different images.
* Using dlib based face detection method and controling camera position coordinates as the user moves her/his face, giving the 3D effect.
* Created a python wrapper for the C++ based code.

[**Detailed explaination of the concepts used in the project can be found at this link**]

