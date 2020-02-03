mkdir build

python3 gen2.py pybv build headers.txt

g++ -shared -rdynamic -g -O3 -Wall -fPIC \
bv.cpp src/imgMap.cpp \
-DMODULE_STR=kosutils -DMODULE_PREFIX=pykosutils \
-DNDEBUG -DPY_MAJOR_VERSION=3 \
`pkg-config --cflags --libs opencv`  \
`python3-config --includes --ldflags` \
-I . -I/usr/local/lib/python3.5/dist-packages/numpy/core/include \
-o build/kosutils.so


python3 demo.py
