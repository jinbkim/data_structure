## �켱���� ť ADT (�켱������ ���� �����Ͱ� ���� ����)
-
-
-
-
-
### ��
- complete binary tree : node�� ������ �Ʒ���,  
  ���ʿ��� ���������� ������� ä����  ����Ʈ��
- ���� complete binary tree �̸鼭,  
  ���parent node�� ���� childe node�� ������ ũ�ų� ���ƾ� ��
- �ִ� �� : ��Ʈ ���� �ö󰥼��� ���� Ŀ���� ���� ����Ʈ��
- �ּ� �� : ��Ʈ ���� �ö󰥼��� ���� �۾����� ���� ����Ʈ��
### ���� ������ �������
- ���ο� �����͸� ������ ��ġ�� ����
- parent node�� �켱������ ��
- ���ο� �������� �켱������ ������ ��ġ �ٲٱ�
- �񱳰����� �ݺ��Ͽ� ��ġ ���� 
### ���� ������ ��������
- ��Ʈ ��忡 ������ �����͸� ����
- child node�� �켱������ ���� node�� �켱������ ��
- ���ο� �������� �켱������ ������ ��ġ �ٲٱ�
- �񱳰����� �ݺ��Ͽ� ��ġ ���� 
### �迭��� ��
- �ε��� 0�� ��Ҵ� �����. 
- ���� ����� ����� ������ ������ ����� �ε����� ��ġ 
- left child node�� �ε��� = parent node �ȵ��� * 2
- right child node�� �ε��� = parent node �ȵ��� * 2 + 1
- parent node�� �ε��� = child node �ȵ��� / 2