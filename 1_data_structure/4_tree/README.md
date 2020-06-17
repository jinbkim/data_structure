## 1. 트리 용어
- node : 트리의 구성요소 
- edge : node와 node를 연결하는 연결선
- root node : tree 구조에서 최상위에 존재하는 node
- terminal node : 아래로 다른 node가 연결되어 있지 않은 node
- internal node : terminal node를 제외한 모든 node
- parent node : 위로 연결된 node
- child node : 아래로 연결된 node
- level : 트리의 맨위에서 0을 시작으로 숫자를 매긴것
- height : 트리의 최고 level 
## 2. 이진트리
### 이진트리 정의 
- root node를 중심으로 두개의 서브 트리로 나누어진다
- 나뉘어진 서브 트리도 이진 트리 이어야 한다
- full binary tree : 모든 level 이 꽉찬 이진 트리  
- complete binary tree : node가 위에서 아래로,  
  왼쪽에서 오른쪽으로 순서대로 채워진  이진 트리
### (t_bt_node) *make_bt_node(bt_data data)
- 새로운 노드를 생성하고 그노드에 데이터 삽입
- 새로운 노드의 왼쪽과 오른쪽 자식 노드 초기화
### (void) make_left_sub_free(t_bt_node *parent, t_bt_node *child)
- 왼쪽 자식노드가 있다면 그 왼쪽 자식노드 메모리 해제
- 왼쪽 자식노드 설정
### (void) make_right_sub_free(t_bt_node *parent, t_bt_node *child)
- 오른쪽 자식노드가 있다면 그 오른쪽 자식노드 메모리 해제
- 오른쪽 자식노드 설정
### (void) preorder_traverse(t_bt_node *node, show_func f)
- 전위 순회 : 루트노드 -> 왼쪽노드 -> 오른쪽노드
### (void) inorder_traverse(t_bt_node *node, show_func f)
- 중위 순휘 : 왼쪽노드 -> 루트노드 -> 오른쪽노드
### (void) postorder_traverse(t_bt_node *node, show_func f)
- 후위 순회 : 왼쪽노드 -> 오른쪽노드 -> 루트노드
## 3. 수식트리
### 후위 표기법을 기반으로 트리 구성
1. 피연산자는 스택으로 이동
2. 연산자가 등장하면, 두개의 피연산자를 스택에서 꺼내어  
   연산자의 child node로 연결하고, 다시 스택으로 이동
### 수식 트리의 계산 (재귀 호출)
1. 왼쪽 서브트리 계산
2. 오른쪽 서브트리 계산
3. 연산자의 형태에 맞춰 계산
