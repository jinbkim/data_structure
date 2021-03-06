## 1. 배열 기반 스택
### (void) stack_init(t_stack *stack) 
- top 인덱스를 -1 로 초기화
### (void) stack_push(t_stack *stack, stack_data data)
- 스택 top에 데이터 넣기
### (int) stack_is_empty(t_stack *stack)
- 스택이 비어있으면 1, 아니면 0 반환
### (stack_data) stack_pop(t_stack *stack)
- 스택 top에 있는 데이터 빼기 
## 2. 연결리스트 기반 스택 
### (void) stack_init(t_stack *stack) 
- stack의 head를 NULL로 초기화 
### (void) stack_push(t_stack *stack, stack_data data)
- 새로운 노드를 생성하고 그노드에 데이터 삽입
- 노드를 연결하고 헤드의 위치 변경
### (int) stack_is_empty(t_stack *stack)
- 스택이 비어있으면 1, 아니면 0 반환
### (stack_data) stack_pop(t_stack *stack)
- 헤드의 위치변경
- 헤드 였었던 노드 메모리 해제 
## 3. 계산기 프로그램
### 표기법
1. 전위표기법 : 연산자를 먼저 표시하고, 피연산자를 나중에 표기하는 방법  
   ((A+B)*(C-D))(중위표기법) -> *(+(AB)-(CD)) ->*+AB-CD
2. 후위표기법 : 피연산자를 먼저 표시하고, 연산자를 나중에 표기하는 방법  
   ((A+B)*(C-D))(중위표기법) -> ((AB)+(CD)-)* -> AB+CD-*
3. 중위표기법 : 연산자를 두 피연산자 사이에 표기하는 방법   
   *+AB-CD(전위표기법) -> *(+(AB)-(CD)) -> (A+B)*(C-D)  
   AB+CD-*(후위표기법) -> ((AB)+(CD)-)* -> (A+B)*(C-D)
### 알고리즘
#### 중위 표기법을 후위표기법으로 변환
1. '(' 는 스택으로 이동 
2. 피연산자는 변환될 수식으로 이동
3. 연산자는 스택의 top에 있는 연산자와 우선순위를 비교  
   스택의 top이 우선순위가 낮으면, 연산자는 스택으로 이동  
   같거나 높으면, 스택의 top은 변환될 수식으로 이동하고, 연산자는 스택으로 이동   
4. ')' 는 '(' 를 만나기 전까지 스택의 모든 데이터를 변환될 수식으로 이동 (괄호는 이동 x) 
#### 후위표기법으로 표현된 수식을 계산 
1. 피연산자는 스택으로 이동
2. 연산자를 만나면 스택에서 두개의 피연산자를 꺼내어 계산
3. 계산결과는 다시 스택으로 이동
 
