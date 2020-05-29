## 트리 ADT
-
-
-
-
-
### 트리 용어
- node : 트리의 구성요소 
- edge : node와 node를 연결하는 연결선
- root node : tree 구조에서 최상위에 존재하는 node
- terminal node : 아래로 다른 node가 연결되어 있지 않은 node
- internal node : terminal node를 제외한 모든 node
- parent node : 위로 연결된 node
- child node : 아래로 연결된 node
- level : 트리의 맨위에서 0을 시작으로 숫자를 매긴것
- height : 트리의 최고 level 
### 이진 트리 
- root node를 중심으로 두개의 서브 트리로 나누어진다
- 나뉘어진 서브 트리도 이진 트리 이어야 한다
- full binary tree : 모든 level 이 꽉찬 이진 트리  
- complete binary tree : node가 위에서 아래로,  
  왼쪽에서 오른쪽으로 순서대로 채워진  이진 트리
### 이진트리의 순회
- 전위 순회 : 루트노드 -> 왼쪽노드 -> 오른쪽노드
- 중위 순휘 : 왼쪽노드 -> 루트노드 -> 오른쪽노드
- 후위 순회 : 왼쪽노드 -> 오른쪽노드 -> 루트노드 
