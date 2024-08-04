# Study game server
대학교 졸업 작품을 만들기 위해서 혼자 공부해보는 게임 서버
## 환경 설정
솔루션 파일 내에 **Binary**와 **Libraries** 폴더를 생성한다.   
```ServerCore```는 **정적 라이브러리**이다. 나머지 두 프로젝트에서 사용될 것이다.   
```DummyClient```와 ```GameServer```, 이 두 프로젝트 각각의 **속성**에서   
**VC++ 디렉터리 -> 포함 디렉터리와 라이브러리 디렉터리**에 아래의 경로를 추가한다.   
```
$(SolutionDir)ServerCore\
$(SolutionDir)Libraries\
```
.lib 파일은 코드로 불러온다.
```
#ifdef _DEBUG
#pragma comment(lib, "Debug/ServerCore.lib")
#else
#pragma comment(lib, "Release/ServerCore.lib")
#endif
```
```DummyClient```와 ```GameServer```의 출력 디렉터리는   
```$(SolutionDir)Binary\$(Configuration)\```,   
```ServerCore```는   
```$(SolutionDir)Libraries\$(configuration)\```으로 설정한다.
