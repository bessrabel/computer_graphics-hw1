# computer_graphics-hw1
---
## CGIP_hw1
---

### Prerequisites
#### 1. Visual Studio Code & Extensions
Visual Studio Code 설치 및 아래의 2개 확장 설치 필요
1. C/C++ (Microsoft)
(이미지)
2. C/C++ Extension Pack
(이미지)

#### 2. g++
Using GCC with MinGW
설치 참조: <https://code.visualstudio.com/docs/cpp/config-mingw#_create-hello-world>

PATH 추가 필수
---

### Directory Layout
>.vscode
builds
include
lib
src
readmePng
screenshot

#### .vscode
visual studio code 프로젝트 설정 파일들 폴더

#### builds
실제 프로젝트가 빌드되는 폴더

#### include & lib
라이브러리 폴더
GLFW (Version 3.3.bin.win32)
GLAD (gl: 4.6, profile: Core, extensions: none)
GLM (Version 0.9.9.6)

#### readmePng
README.md 파일 이미지 첨부를 위한 폴더

#### screenshot
스크린샷

#### src
소스 코드 폴더 (.cpp 및 .h 파일)
Antialiasing.cpp - 과제 3: Antialiasing된 이미지 출력 코드
camera.h - camera(e, u, v, w) 정의 & getRay, getRandomRay 함수
hitSurface.h - hitSurface(hitSurface, t) 정의
light.h - light(point, color, intensity) 정의 
Ray Intersection.cpp - 과제 1: Ray Intersection된 이미지 출력 코드
ray.h - ray 정의 & evaluate 함수
scene.h - scene(surface들의 집합) 정의 & trace 함수
Shading.cpp - 과제 2: Shading된 이미지 출력 코드
surface.h - surface(각 오브젝트) 정의 & intersect, getnormal, shade 함수
viewingRegion.h - viewingRegion(l, r, b, t, d) 정의

### compilation instructions

1. Prerequisites를 참고해 요구사항 완료 
2. 프로젝트 클론하여 visual studio code workspace로 이동
3. 각 Ray Intersection.cpp, Shading.cpp, Antialiasing.cpp 파일을 빌드
이때 .vscode 폴더 > tasks.json을 실행시키고 싶은 파일로 바꿔 빌드 가능

1. Ray Intersection
task.json

result

2. Shading Intersection
task.json

result

3. Antialiasing
task.json

result


