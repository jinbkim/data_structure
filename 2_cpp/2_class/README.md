## 2. 클래스 
### 2.1) C++에서의 구조체

- c++ 에서 데이터의 입출력은 별도의 포맷지정이 필요없음
- 지연변수 선언은 함수 내 어디든 삽입 가능 
- std::cout<< : 출력 
- std::endl : 개행
- std::cin>> : 입력
### 1.2) 함수 오버로딩
- 함수이름이 같아도 함수인자의 자료형이나 개수가 다르면  
  동일한 이름의 함수정의가 가능
### 1.3) 매개변수의 디폴트 값
- 함수의 매개변수를 초기화하는 형태로 선언 가능 
- 함수 호출시 인자를 전달하지 않으면 위에 선언한 값이 전달된 것으로 간주
- 오른쪽 매개변수의 디폴트 값부터 채우는 형태로 정의해야함
- 함수 오버로딩과 매개변수의 디폴트를 동시에 할수 없음
### 1.4) 이름공간
- ***using std::cout*** 선언을 하면 앞으로는 namespace를  
  지정하지않고 cout 호출 가능 
- ***using name std*** 선언을 하면 namespace std에  
  선언된 모든 것에 대해 namepace 생략 가능
- ***using name std*** 대신에 일일이 using 선언을 하는것이 좋은습관임
- ***namespace A = B::C::D*** 같이 namespace의 별칭 지정 가능
### 1.4) const 사용법
- const int A : A(int) 변경 불가
- const int *A : *A(int) 변경 불가 
- int *const A : A(int *) 변경불가
- const int *const A : A(int *), *A(int) 변경불가 
### 1.5) 자료형 bool
- true와 false는 참과 거짓을 표현하기 위한 1 바이트 크기의 데이터 
- 실제값은 각각 1과 0이 아님
### 1.5) 참조자
- 자신이 참조하는 변수를 대신할 수있는 또하나의 이름
- 참조자는 변수에 대해서만 선언가능
- 선언됨과 동시에 누군가를 참조해야함
- A 함수는 반환형이 참조형, B 함수는 반환형이 기본자료형이라 정의
- int &num2 = A(num1)***(O)***, int num2 = A(num1)***(O)***
- int &num2 = B(num1)***(X)***, int num2 = B(num1)***(O)***
- const int A = 10. const int &B = A. 
- 위처럼 참조자가 상수도 참조 가능
### 1.6) new, delete
- new는 malloc 함수를 대신하는 키워드  
  int *ptr = new int[3]; : 길이가 3인 int형 배열 할당  
- delete는 free 함수를 대신하는 키워드  
  delete []ptr : 앞서 할당한 int형 배열 소멸
### 1.7) c++에서 c언어의 표준함수 호출
- c를 더하고.h빼기  
  ex) stdio.h -> cstdio

### 복습할것
- 참조자  
