## 탐색
### 보간탐색
- 데이터의 위치를 고려하여 탐색
- arr : 탐색 대상 배열 
- first : 탐색 대상의 시작
- last : 탐색 대상의 끝
- target : 찾는 데이터의 위치
- (arr[last] - arr[first]) : (arr[target] - arr[first]) = (last - first) : (target - first)
- target = (arr[target] - arr[first]) * (last - first) / (arr[last] - arr[first]) + first
### 이진 탐색트리
- 노드의 key는 유일
- 왼쪽 서브트리의 모든 노드들의 key보다 루트 노드의 key가 크다.
- 오른쪽 서브트리의 모든 노드들의 key보다 루트 노드의 key가 작다. 
#### 이진 탐색트리의 삭제구현
##### 1. 삭제할 노드가 단말노드인 경우
##### 2. 삭제할 노드가 하나의 서브트리를 가질 경우 
##### 3. 삭제할 노드가 두개의 서브트리를 가질 경우 
