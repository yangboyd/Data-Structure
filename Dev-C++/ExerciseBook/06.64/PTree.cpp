/*==================
 * ����˫�ױ��洢��ʾ
 ===================*/

#include "PTree.h"

/*
 * ��ʼ��
 *
 * ���������
 */
Status InitTree(PTree* T) {
    if(T == NULL) {
        return ERROR;
    }
    
    T->n = 0;
    
    // ������������
    memset(T->nodes, 0, sizeof(T->nodes));
    
    return OK;
}

/*
 * ����
 *
 * ����Ԥ��Ķ�������������
 * ����Լ��ʹ�á��������С�����������
 *
 *
 *����ע��
 *
 * �̲���Ĭ�ϴӿ���̨��ȡ���ݡ�
 * ����Ϊ�˷�����ԣ�����ÿ�����ж��ֶ��������ݣ�
 * �������ѡ���Ԥ����ļ�path�ж�ȡ�������ݡ�
 *
 * �����Ҫ�ӿ���̨��ȡ���ݣ���pathΪNULL����Ϊ�մ���
 * �����Ҫ���ļ��ж�ȡ���ݣ�����Ҫ��path����д�ļ�����Ϣ��
 */
Status CreateTree(PTree* T, char* path) {
    FILE* fp;
    int readFromConsole;    // �Ƿ�ӿ���̨��ȡ����
    
    // ���û���ļ�·����Ϣ����ӿ���̨��ȡ����
    readFromConsole = path == NULL || strcmp(path, "") == 0;
    
    if(readFromConsole) {
        printf("����������Ԫ����Ϣ�����ڿս�㣬ʹ��^����...\n");
        Create(T, NULL);
    } else {
        // ���ļ���׼����ȡ��������
        fp = fopen(path, "r");
        if(fp == NULL) {
            return ERROR;
        }
        Create(T, fp);
        fclose(fp);
    }
    
    return OK;
}

/*
 * �п�
 *
 * �ж����Ƿ�Ϊ������
 */
Status TreeEmpty(PTree T) {
    return T.n == 0 ? TRUE : FALSE;
}

/*
 * ����
 *
 * ����������ȣ���������
 */
int TreeDepth(PTree T) {
    int k, level;
    
    // ���������������������
    if(TreeEmpty(T)) {
        return 0;
    }
    
    /*
     * ��k��ʼ��Ϊ���һ������λ��
     * �������Ľ�㰴����洢�������洢�Ľ��ض�λ������
     */
    k = (T.r + T.n - 1) % MAX_TREE_SIZE;
    level = 0;
    
    do {
        level++;
        k = T.nodes[k].parent;
    } while(k != -1);
    
    return level;
}


/*�������������������������������������������� �����ڲ�ʹ�õĺ��� ��������������������������������������������*/

// ���������ڲ�����
static void Create(PTree* T, FILE* fp) {
    int r;          // ���ĸ�����λ�ã�������
    int n;          // ��¼Ԫ������
    int cur;        // �α�
    TElemType ch;
    LinkQueue Q;
    QElemType e;    // ����Ԫ��ָʾ����λ��
    char s[MAX_CHILD_COUNT + 1];
    int i;
    
    InitQueue(&Q);
    
    n = 0;
    
    // ��ȡ������λ��
    if(fp == NULL) {
        printf("�����������λ��(0~%d)��", MAX_TREE_SIZE - 1);
        scanf("%d", &r);
        cur = r;
        
        printf("�����������ֵ��");
        scanf("%s", s);
        ch = s[0];
        
        // �������
        EnQueue(&Q, cur);
        T->nodes[cur].data = ch;
        T->nodes[cur].parent = -1;
        cur = (cur + 1) % MAX_TREE_SIZE;
        n++;
        
        while(!QueueEmpty(Q)) {
            DeQueue(&Q, &e);    // �����λ�ó���
            
            printf("���������� %c �ĺ��ӽ�㣬�����ں���ʱ����һ��^��", T->nodes[e].data);
            scanf("%s", s);
            for(i = 0; i < strlen(s); i++) {
                if(s[i] == '^') {
                    break;
                }
                
                EnQueue(&Q, cur); // ��ǰ���λ�����
                T->nodes[cur].data = s[i];
                T->nodes[cur].parent = e;
                cur = (cur + 1) % MAX_TREE_SIZE;
                n++;
            }
        }
    } else {
        // ¼�������λ��
        ReadData(fp, "%d", &r);
        cur = r;
        
        // ¼�������ֵ
        ReadData(fp, "%s", s);
        ch = s[0];
        printf("¼�������ֵ��%c\n", ch);
        
        // �������
        EnQueue(&Q, cur);
        T->nodes[cur].data = ch;
        T->nodes[cur].parent = -1;
        cur = (cur + 1) % MAX_TREE_SIZE;
        n++;
        
        while(!QueueEmpty(Q)) {
            ReadData(fp, "%s", s);
            ch = s[0];
            printf("����¼�� %c ���ĺ��ӣ�", ch);
            
            // ¼�뺢�ӽ��
            ReadData(fp, "%s", s);
            printf("%s\n", s);
            
            DeQueue(&Q, &e);    // �����λ�ó���
            
            // ��������
            for(i = 0; i < strlen(s); i++) {
                if(s[i] == '^') {
                    break;
                }
                
                EnQueue(&Q, cur); // ��ǰ���λ�����
                T->nodes[cur].data = s[i];
                T->nodes[cur].parent = e;
                cur = (cur + 1) % MAX_TREE_SIZE;
                n++;
            }
        }
    }
    
    T->r = r;
    T->n = n;
}

// ��ȡ��T�Ľ����Ϣ�����������Щ��Ϣ�������Pos���͵Ķ���
static void getPos(PTree T, Pos pt[]) {
    LinkList Lt, Lt_parent, Lt_child;
    int m, n, p, k, s;
    int level;
    
    memset(pt, 0, MAX_TREE_SIZE * sizeof(Pos));
    
    // ���������������������
    if(TreeEmpty(T)) {
        return;
    }
    
    InitList(&Lt_parent);
    InitList(&Lt_child);
    
    // ������parentΪ-1
    ListInsert(Lt_parent, 1, -1);
    
    level = 1;
    k = T.r;
    m = n = 0;
    s = -1; // ��ʼ��ͷ���ĸ����Ϊ-1
    
    while(k != (T.r + T.n) % MAX_TREE_SIZE) {
        // ���k��һ�����������е�������ʼ��Ϊ-1
        pt[k].firstChild = -1;
        
        // ���k���һ�����������е�������ʼ��Ϊ-1
        pt[k].lastChild = -1;
        
        // ��ǰ���k�ĸ����
        p = T.nodes[k].parent;
        if(p != s) {
            s = p;  // ׷�ٸ����ı仯
            n = 0;  // �����ı�ʱ����Ҫ���¼���
        }
        
        // �жϵ�ǰ����Ƿ�Ϊ��level-1����ĺ���
        if(LocateElem(Lt_parent, p, Equal)) {
            ListInsert(Lt_child, ++m, k);
            
            pt[k].row = level;
            pt[k].col = m;
            pt[k].childIndex = ++n;
            
            // ȷ����ǰ��㸸������
            if(p != -1) {
                // ��һ�����������е�����
                if(pt[p].firstChild==-1) {
                    pt[p].firstChild = k;
                }
                
                // ���һ�����������е�����
                pt[p].lastChild = k;
            }
            
            k = (k + 1) % MAX_TREE_SIZE;
        } else {
            Lt = Lt_parent;
            Lt_parent = Lt_child;
            Lt_child = Lt;
            ClearList(Lt_child);
            
            level++;
            m = 0;
        }
    }
    
    DestroyList(&Lt_parent);
    DestroyList(&Lt_child);
}


/*�������������������������������������������� ͼ�λ���� ��������������������������������������������*/

// ��ͼ�λ���ʽ�����ǰ�ṹ
void PrintGraph(PTree T) {
    Pos pt[MAX_TREE_SIZE];
    
    // ���������������������
    if(TreeEmpty(T)) {
        printf("\n");
        return;
    }
    
    // ����T�н���λ����Ϣ
    getPos(T, pt);
    
    Print(T, pt, T.r);
    
    printf("\n");
    
    printf("�洢�ṹ��\n");
    PrintFramework(T);
}

// ͼ�λ������ǰ�ṹ�ڲ�ʵ��
static void Print(PTree T, Pos pt[], int i) {
    int firstChild;
    int rightBrother;
    int k;
    
    // ���ʵ�ǰ���
    printf("%c ", T.nodes[i].data);
    
    firstChild = pt[i].firstChild;
    
    // �������ӣ���Ҫ��ȷ�����ӵ����ݣ�
    if(firstChild != -1) {
        Print(T, pt, firstChild);
    }
    
    rightBrother = (i + 1) % MAX_TREE_SIZE;
    
    // �������ֵܣ���Ҫ��ȷ�����ֵܵ����ݣ�
    if(rightBrother != (T.r + T.n) % MAX_TREE_SIZE && T.nodes[i].parent == T.nodes[rightBrother].parent) {
        // ���ʵ�ǰ�������ֵ�ǰ�������ǰ��㲻�����һ�����ӣ������һ�λ���
        if(pt[T.nodes[i].parent].lastChild != i) {
            printf("\n");
            
            for(k = 0; k < pt[rightBrother].row - 1; k++) {
                printf(". ");
            }
        }
        
        Print(T, pt, rightBrother);
    }
}

// ͼ�λ�����������нṹ�������ڲ�����ʹ��
static void PrintFramework(PTree T) {
    int k;
    
    if(T.n == 0) {
        printf("\n");
        return;
    }
    
    printf("+---------+\n");
    printf("|  i e  p |\n");
    printf("+---------+\n");
    
    for(k = T.r; k != (T.r + T.n) % MAX_TREE_SIZE; k = (k + 1) % MAX_TREE_SIZE) {
        printf("| %2d %c %2d |\n", k, T.nodes[k].data, T.nodes[k].parent);
    }
    
    printf("+---------+\n");
}