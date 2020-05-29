## 큐 ADT (FIRST In, First Out) 
- queue_init : 큐 초기화
- queue_is_full : 큐가 가득 찼는지 확인 
- queue_is_empty : 큐가 비었는지 확인 
- enter_queue : 큐에 데이터 추가 
- delete_queue : 먼저 넣은 큐의 데이터 삭제
- queue_peek : 먼저 넣은 큐의 데이터 출력
### 큐 사용법 
- 데이터의 개수가 정해져있고, 데이터의 삽입과 삭제가 많지 않으면  -> 배열기반 큐
- 데이터의 개수가 정해져 있지않고, 데이터의 삽입과 삭제가 많으면  -> 연결리스트기반 큐
## 덱 ADT
- 앞 뒤로 넣고, 뺄 수 있는 자료구조
- 양방향 연결리스트로 구현
- deque_init : 덱 초기화
- deque_is_empty : 덱 비었는지 확인 
- deque_add_head : 덱 앞으로 데이터 추가 
- deque_add_tail : 덱 뒤로 데이터 추가
- deque_remove_head : 덱 맨앞 데이터 삭제
- deque_remove_tail : 덱 맨뒤 데이터 삭제
