## 1. Ʈ�� ���
- node : Ʈ���� ������� 
- edge : node�� node�� �����ϴ� ���ἱ
- root node : tree �������� �ֻ����� �����ϴ� node
- terminal node : �Ʒ��� �ٸ� node�� ����Ǿ� ���� ���� node
- internal node : terminal node�� ������ ��� node
- parent node : ���� ����� node
- child node : �Ʒ��� ����� node
- level : Ʈ���� �������� 0�� �������� ���ڸ� �ű��
- height : Ʈ���� �ְ� level 
## 2. ����Ʈ��
### ����Ʈ�� ���� 
- root node�� �߽����� �ΰ��� ���� Ʈ���� ����������
- �������� ���� Ʈ���� ���� Ʈ�� �̾�� �Ѵ�
- full binary tree : ��� level �� ���� ���� Ʈ��  
- complete binary tree : node�� ������ �Ʒ���,  
  ���ʿ��� ���������� ������� ä����  ���� Ʈ��
### (t_bt_node) *make_bt_node(bt_data data)
- ���ο� ��带 �����ϰ� �׳�忡 ������ ����
- ���ο� ����� ���ʰ� ������ �ڽ� ��� �ʱ�ȭ
### (void) make_left_sub_free(t_bt_node *parent, t_bt_node *child)
- ���� �ڽĳ�尡 �ִٸ� �� ���� �ڽĳ�� �޸� ����
- ���� �ڽĳ�� ����
### (void) make_right_sub_free(t_bt_node *parent, t_bt_node *child)
- ������ �ڽĳ�尡 �ִٸ� �� ������ �ڽĳ�� �޸� ����
- ������ �ڽĳ�� ����
### (void) preorder_traverse(t_bt_node *node, show_func f)
- ���� ��ȸ : ��Ʈ��� -> ���ʳ�� -> �����ʳ��
### (void) inorder_traverse(t_bt_node *node, show_func f)
- ���� ���� : ���ʳ�� -> ��Ʈ��� -> �����ʳ��
### (void) postorder_traverse(t_bt_node *node, show_func f)
- ���� ��ȸ : ���ʳ�� -> �����ʳ�� -> ��Ʈ���
## 3. ����Ʈ��
### ���� ǥ����� ������� Ʈ�� ����
1. �ǿ����ڴ� �������� �̵�
2. �����ڰ� �����ϸ�, �ΰ��� �ǿ����ڸ� ���ÿ��� ������  
   �������� child node�� �����ϰ�, �ٽ� �������� �̵�
### ���� Ʈ���� ��� (��� ȣ��)
1. ���� ����Ʈ�� ���
2. ������ ����Ʈ�� ���
3. �������� ���¿� ���� ���
