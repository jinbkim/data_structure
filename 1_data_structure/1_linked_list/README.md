## 1. ���Լ��� �ִ� ����� ���Ḯ��Ʈ 
### (void) list_init(t_list *list, comp_func f) 
- ����Ʈ�� ��忡 ���̳�� ����
- ��尡 NULL�� ����Ŵ
- ���Լ� ����
### (void) list_insert_comp(t_list *list, list_data data)
- ���ο� ��带 ����� �׳�忡 ������ ����
- ���Լ��� ���� �� ��ġ�� ã��
- ã�� ��ġ�� ���ο� ��忬��
### (list_data) list_remove(t_list *list)
- ������ ����� �ֺ������� ���� ����
- �����带 ��ĭ ������ �̵�
- node �޸� ���� 
### (int) list_next_node(t_list *list, list_data *data)
- ���� ��尡 ������ 0 ��ȯ
- �����带 ��ĭ �ڷ� �̵�
- �̵��� �������� �����͸� data�� ���� 
## 2. ���Լ��� ���� ����� ���Ḯ��Ʈ
### (void) list_init(t_list *list)
- ����Ʈ�� ��忡 ���̳�� ����
- ��尡 NULL�� ����Ŵ
- ������ ���� ������ġ�� ����
### (void) list_insert_tail(t_list *list, list_data data)
- ���ο� ��带 ����� �׳�忡 ������ ����
- �����ڿ� ��� ���ο� ��� ����
- ������ ��ġ�� ���ο� ���� ���� 
### (void) list_insert_head(t_list *list, list_data data)
- ���ο� ��带 ����� �׳�忡 ������ ����
- ���ڿ� ��� ���ο� ��� ����
- ��� ������ ó���̶�� �ڸ��� ��ġ�� ���ο� ���� ���� 
### (int) list_next_node(t_list *list, list_data *data)
- ���� ��尡 ������ 0 ��ȯ
- �����带 ��ĭ �ڷ� �̵�
- �̵��� �������� �����͸� data�� ���� 
### (list_data) list_remove(t_list *list)
- ������ ����� �ֺ������� ���� ����
- �����带 ��ĭ ������ �̵�
- node �޸� ���� 
## 3. ���� ���Ḯ��Ʈ 
### (void) list_init(t_list *list)
- ����Ʈ�� ������ NULL�� �ʱ�ȭ
### (void) list_insert(t_list *list, list_data data)
- ���ο� ��带 ����� �׳�忡 ������ ����
- �����ڿ� ��� ���ο� ��� ����
### (int) list_next_node(t_list *list, list_data *data)
- ����Ʈ�� �ƹ���尡 ������ 0��ȯ 
- �����带 ��ĭ �ڷ� �̵�
- �̵��� �������� �����͸� data�� ���� 
### (list_data) list_remove(t_list *list)
- ������ ��尡 �Ѱ��� ������ NULL�� �ʱ�ȭ 
- ������ ����� �ֺ������� ���� ����
- �����带 ��ĭ ������ �̵�
- �������� ��尡 ��������� ������嵵 ��ĭ ������ �̵� 
- node �޸� ���� 
