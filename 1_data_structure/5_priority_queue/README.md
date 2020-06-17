## 힙(우선순위 큐)
### 힙 정의
- complete binary tree : node가 위에서 아래로,  
  왼쪽에서 오른쪽으로 순서대로 채워진  이진트리
- 힙은 complete binary tree 이면서,  
  모든parent node의 값은 childe node의 값보다 크거나 같아야 함
- 최대 힙 : 루트 노드로 올라갈수록 값이 커지는 완전 이진트리
- 최소 힙 : 루트 노드로 올라갈수록 값이 작아지는 완전 이진트리
### (void) p_queue_init(t_p_queue *pq, priority_comp f)
- 우선순위 큐의 데이터 개수, 비교함수 초기화 
### (void) enter_p_queue(t_p_queue *pq, pq_data data)
- 우선순위 큐의 데이터 개수를 한개 증가
- 맨마지막 인덱스를 시작으로 부모노드보다 우선순위가
  낮을때 까지 비교하면서 데이터 위치변경 
### (int) p_queue_is_empty(t_p_queue *pq)
- 우선순위 큐가 비었으면 1 반환, 아니면 0 반환 
### (pq_data) delete_p_queue(t_p_queue *pq)
- 우선순위 큐에서 맨마지막 인덱스를 가진 데이터를 A라고 정의 
- 루트노드를 시작으로 A가 자식노드보다 우선순위가 
  높을때 까지 비교하면서 데이터 위치변경
- 우선순위 큐의 데이터 개수 한개 감소 
