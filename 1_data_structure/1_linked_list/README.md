## 1. 비교함수가 있는 양방향 연결리스트 
### (void) list_init(t_list *list, comp_func f) 
- 리스트의 헤드에 더미노드 생성
- 헤드가 NULL을 가리킴
- 비교함수 설정
### (void) list_insert_comp(t_list *list, list_data data)
- 새로운 노드를 만들고 그노드에 데이터 삽입
- 비교함수를 통해 들어갈 위치를 찾음
- 찾은 위치에 새로운 노드연결
### (list_data) list_remove(t_list *list)
- 지워질 노드의 주변노드들을 서로 연결
- 현재노드를 한칸 앞으로 이동
- node 메모리 해제 
### (int) list_next_node(t_list *list, list_data *data)
- 다음 노드가 없으면 0 반환
- 현재노드를 한칸 뒤로 이동
- 이동된 현재노드의 데이터를 data에 저장 
## 2. 비교함수가 없는 양방향 연결리스트
### (void) list_init(t_list *list)
- 리스트의 헤드에 더미노드 생성
- 헤드가 NULL을 가리킴
- 꼬리도 헤드와 같은위치로 설정
### (void) list_insert_tail(t_list *list, list_data data)
- 새로운 노드를 만들고 그노드에 데이터 삽입
- 꼬리뒤에 노드 새로운 노드 삽입
- 꼬리의 위치를 새로운 노드로 변경 
### (void) list_insert_head(t_list *list, list_data data)
- 새로운 노드를 만들고 그노드에 데이터 삽입
- 헤드뒤에 노드 새로운 노드 삽입
- 노드 삽입이 처음이라면 코리의 위치를 새로운 노드로 변경 
### (int) list_next_node(t_list *list, list_data *data)
- 다음 노드가 없으면 0 반환
- 현재노드를 한칸 뒤로 이동
- 이동된 현재노드의 데이터를 data에 저장 
### (list_data) list_remove(t_list *list)
- 지워질 노드의 주변노드들을 서로 연결
- 현재노드를 한칸 앞으로 이동
- node 메모리 해제 
## 3. 원형 연결리스트 
### (void) list_init(t_list *list)
- 리스트의 꼬리를 NULL로 초기화
### (void) list_insert(t_list *list, list_data data)
- 새로운 노드를 만들고 그노드에 데이터 삽입
- 꼬리뒤에 노드 새로운 노드 삽입
### (int) list_next_node(t_list *list, list_data *data)
- 리스트에 아무노드가 없으면 0변환 
- 현재노드를 한칸 뒤로 이동
- 이동된 현재노드의 데이터를 data에 저장 
### (list_data) list_remove(t_list *list)
- 지워질 노드가 한개면 꼬리를 NULL로 초기화 
- 지워질 노드의 주변노드들을 서로 연결
- 현재노드를 한칸 앞으로 이동
- 지워지는 노드가 꼬리노드라면 꼬리노드도 한칸 앞으로 이동 
- node 메모리 해제 
