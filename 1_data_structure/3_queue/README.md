## 1. �迭 ��� ť
### (void) queue_init(t_queue *q)
- ť�� �Ǿհ� �ǵ� �ʱ�ȭ
### (void) enter_queue(t_queue *q, queue_data data)
- ť�� �ǵڿ� ������ ����
### (int) queue_is_empty(t_queue *q) 
- ť�� �Ǿհ� �ǵڰ� ������ ť�� ����̹Ƿ� 1��ȯ, �ƴϸ� 0��ȯ 
### (queue_data) delete_queue(t_queue *q)
- ť�� �Ǿ� ������ ����
## 2. ���Ḯ��Ʈ ��� ť
### (void) queue_init(t_queue *q)
- ť�� �Ǿ��� NULL�� �ʱ�ȭ 
### (void) enter_queue(t_queue *q, queue_data data)
- ���ο� ��带 �����ϰ� �׳�忡 ������ ����
- ť�� �ǵڿ� ��带 �����ϰ� ť�� �Ǿհ� �ǵ� ��ġ����
### (int) queue_is_empty(t_queue *q) 
- ť�� �Ǿ��� NULL�̸� ����̹Ƿ� 1��ȯ, �ƴϸ� 0��ȯ 
### (queue_data) delete_queue(t_queue *q)
- ť�� �Ǿ� ��ġ ����
- �Ǿ��̾��� ��� �޸� ����
## 3. ����� ť�� ��
### (void) deque_init(t_deque *deque)
- ���� �Ӹ��� ���� �ʱ�ȭ
### (int) deque_is_empty(t_deque *deque)
- ���� ��������� 0, �ƴϸ� 1��ȯ 
### (void) deque_add_head(t_deque *deque, deque_data data)
- ���ο� ��带 �����ϰ� �׳�忡 ������ ����
- ���� �Ǿհ� ��带 �����ϰ� ���� �Ǿհ� �ǵ� ��ġ����
### (void) deque_add_tail(t_deque *deque, deque_data data)
- ���ο� ��带 �����ϰ� �׳�忡 ������ ����
- ���� �ǵڿ� ��带 �����ϰ� ���� �Ǿհ� �ǵ� ��ġ����
### (deque_data) deque_remove_head(t_deque *deque)
- ���� �Ǿ� ��ġ ����
- �Ǿ��̾��� ��� �޸� ���� 
### (deque_data) deque_remove_tail(t_deque *deque)
- ���� �ǵ� ��ġ ����
- �ǵڿ��� ��� �޸� ���� 
