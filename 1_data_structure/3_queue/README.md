## 1. 배열 기반 큐
### (void) queue_init(t_queue *q)
- 큐의 맨앞과 맨뒤 초기화
### (void) enter_queue(t_queue *q, queue_data data)
- 큐의 맨뒤에 데이터 삽입
### (int) queue_is_empty(t_queue *q) 
- 큐의 맨앞과 맨뒤가 같으면 큐가 빈것이므로 1반환, 아니면 0반환 
### (queue_data) delete_queue(t_queue *q)
- 큐의 맨앞 데이터 제거
## 2. 연결리스트 기반 큐
### (void) queue_init(t_queue *q)
- 큐의 맨앞을 NULL로 초기화 
### (void) enter_queue(t_queue *q, queue_data data)
- 새로운 노드를 생성하고 그노드에 데이터 삽입
- 큐의 맨뒤와 노드를 연결하고 큐의 맨앞과 맨뒤 위치조정
### (int) queue_is_empty(t_queue *q) 
- 큐의 맨앞이 NULL이면 빈것이므로 1반환, 아니면 0반환 
### (queue_data) delete_queue(t_queue *q)
- 큐의 맨앞 위치 조정
- 맨앞이었던 노드 메모리 해제
## 3. 양방향 큐인 덱
### (void) deque_init(t_deque *deque)
- 덱의 머리와 꼬리 초기화
### (int) deque_is_empty(t_deque *deque)
- 덱이 비어있으면 0, 아니면 1반환 
### (void) deque_add_head(t_deque *deque, deque_data data)
- 새로운 노드를 생성하고 그노드에 데이터 삽입
- 덱의 맨앞과 노드를 연결하고 덱의 맨앞과 맨뒤 위치조정
### (void) deque_add_tail(t_deque *deque, deque_data data)
- 새로운 노드를 생성하고 그노드에 데이터 삽입
- 덱의 맨뒤와 노드를 연결하고 덱의 맨앞과 맨뒤 위치조정
### (deque_data) deque_remove_head(t_deque *deque)
- 덱의 맨앞 위치 조정
- 맨앞이었던 노드 메모리 해제 
### (deque_data) deque_remove_tail(t_deque *deque)
- 덱의 맨뒤 위치 조정
- 맨뒤였던 노드 메모리 해제 
