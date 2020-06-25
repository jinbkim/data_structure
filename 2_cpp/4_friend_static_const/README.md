## 4. friend, static, const
### 4.1) frined
- A클래스가 B대상으로 friend 선언을 하면 B클래스는
  A클래스의 private 멤버에 직접 접근 가능
### 4.2) static
- 전역변수에 선언된 static : 선언된 파일 내에서만 참조허용
- 함수내에 선언된 static : 한번만 초기화되고, 함수를 빠져나가도 소멸 x
#### static 멤버변수
- 클래스당 하나씩만 생성가능
- 객체 외부에 있지만, 멤버 변수처럼 접근 가능
- 클래스 외부에서 초기화
#### static 멤버함수
- 객체의 멤버로 존재하지 않음
- static 멤버함수 내에서는 static 멤버변수와 static 멤버함수만 호출 가능
### 4.3) const
#### const와 함수오버로딩
- const의 유무도 함수오버로딩의 조건이 됨
#### const static
- const 멤버변수의 초기화는 이니셜라이저를 통해야만 가능
- const static 으로 선언되는 멤버변수는 선언과 동시에 초기화 가능