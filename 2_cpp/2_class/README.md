## 2. 클래스
### 2.1) C++에서의 구조체
- typedef 선언 없이도 struct를 안쓰고 구조체 선언 가능
- 구조체 안에 함수 삽입 가능
### 2.2) 클래스와 객체
#### 접근제어 지시자
- public : 어디서든 접근허용
- protected : 상속관계일때, 유도 클래스에서의 접근허용
- private : 클래스 내에서만 접근허용
#### 구조체와 클래스의 차이점
- 구조체는 접근제어 지시자가 없으면 public로 간주
- 클래스는 접근제어 지시자가 없으면 private로 간주
#### 인라인 함수는 헤더파일 안에 넣어야함
#### 클래스 멤버변수는 선언과 동시에 초기화 불가능
### 2.3) const 함수
- const 함수 내에서는 멤버변수의 값을 변경하지 않음
- const 함수 내에서는 const가 아닌 함수의 호출이 제한됨
- const 참조자를 대상으로 값의 변경하는 함수의 호출이 제한됨
### 2.4) 생성자
- 클래스의 이름과 동일하고 반환형이 선언되지 않음
- 함수의 일종으로 함수 오버로딩과 디폴트값 설정 가능
- 생성자를 생성하지 않은 클래스에는 내부적으로 아무런 일도 하지 않는 디폴트 생성자가 자동삽입됨
#### 멤버 이니셜라이저
- 멤버변수로 선언된 객체의 생성자 호출
- 객체의 멤버도 초기화 가능
### 2.5) 소멸자
- 클래스 이름앞에 ~가 붙은형태로 반환형이 선언되지 않음
- 매개변수가 void형이므로 함수 오버르딩과 디폴트값 설정 불가능
### 2.6) this 포인터
- 객체 자신의 주소값
- this를 이용해 멤버변수에 접근 가능