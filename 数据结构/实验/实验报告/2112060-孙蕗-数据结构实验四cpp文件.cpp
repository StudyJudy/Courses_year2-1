#include<iostream>
#include<queue>
#include <cstring>
#include<string>
#include<vector>
using namespace std;
int Count = 0;
bool IsGo = true;
template <class T>
class BinaryTreeNode
{
public:
    friend void Visit(BinaryTreeNode<T>*);
    friend void InOrder(BinaryTreeNode<T>*);
    friend void PreOrder(BinaryTreeNode<T>*);
    friend void PostOrder(BinaryTreeNode<T>*);
    friend void LevelOrder(BinaryTreeNode<T>*);
    T data;
    int height;
    BinaryTreeNode<T>* LeftChild;    // ����
    BinaryTreeNode<T>* RightChild;   // �Һ���
    BinaryTreeNode() {}
    BinaryTreeNode(T data) : data(data), LeftChild(nullptr), RightChild(nullptr) {};
    ~BinaryTreeNode() {}
};
template <class T>
void Visit(BinaryTreeNode<T>* x)//�����ǰ�ڵ��ֵ
{
    if (x)
    {
        cout << x->data << ' ';
    }
}
template <class T>
void PreOrder(BinaryTreeNode<T>* t)//DLR
{
    if (t)
    {
        Visit(t);                 		// ���ʸ��ڵ� 
        PreOrder(t->LeftChild);    	// ���������� 
        PreOrder(t->RightChild);  	//���������� 
    }
}
template <class T>
void InOrder(BinaryTreeNode<T>* t)//LDR
{
    if (t) {
        InOrder(t->LeftChild); 	//���������� 
        Visit(t); 				//���ʸ��ڵ� 
        InOrder(t->RightChild); 	//���ʸ��ڵ� 
    }
}
template <class T>
void PostOrder(BinaryTreeNode<T>* t)//LRD
{
    if (t)
    {
        PostOrder(t->LeftChild);    //���������� 
        PostOrder(t->RightChild);  //���������� 
        Visit(t);                      //���ʸ��ڵ� 
    }
}
template <class T>
void LevelOrder(BinaryTreeNode<T>* t)//����
{
    queue <BinaryTreeNode<T>*>  Q;
    while (t)
    {
        Visit(t); 
        //��t�ĺ��ӷ������ 
        if (t->LeftChild) Q.push(t->LeftChild);//��
        if (t->RightChild) Q.push(t->RightChild);//��
        //������һ���ڵ�
    }
}

template<class T>
class BinaryTree
{
public:
    ~BinaryTree() {};
    void PreOrder(void(*Visit) (BinaryTreeNode<T>* u))
    {
        PreOrder(Visit, root);
    }
    void InOrder(void(*Visit)(BinaryTreeNode<T>* u))
    {
        InOrder(Visit, root);
    }
    void PostOrder(void(*Visit)(BinaryTreeNode<T>* u))
    {
        PostOrder(Visit, root);
    }
    BinaryTreeNode<T>* root;
    BinaryTreeNode<T>* root2;
    vector<T>datas;//������
    vector<T>origin;
    void CreateTree();//�������뽨��������
    void CreateCompleteTree(BinaryTreeNode<T>*& u);//������ȫ������
    int Height(BinaryTreeNode<T>* u, T t);//���
    BinaryTreeNode<T>* Find(BinaryTreeNode<T>* u, T node);//����ĳ���ڵ�
    void PreOrder(void(*Visit) (BinaryTreeNode<T>* u), BinaryTreeNode<T>* t);//ǰ��
    void InOrder(void(*Visit) (BinaryTreeNode<T>* u), BinaryTreeNode<T>* t);//����
    void PostOrder(void(*Visit)(BinaryTreeNode<T>* u), BinaryTreeNode<T>* t);//����
    void LevelOrder(void(*Visit)(BinaryTreeNode<T>* t), BinaryTreeNode<T>* u);//����
    bool IsCompleteTree(BinaryTreeNode<T>* u); //�ж��ǲ�����ȫ������
    void ToCompleteTree(BinaryTreeNode<T>* u);//������ȫ������
};
template <class T>
void BinaryTree<T>::PreOrder(void(*Visit)(BinaryTreeNode<T>* u), BinaryTreeNode<T>* t)//ǰ��
{
    if (t)
    {
        Visit(t);//DLR
        PreOrder(Visit, t->LeftChild);
        PreOrder(Visit, t->RightChild);
    }
}
template <class T>
void BinaryTree<T>::InOrder(void(*Visit)(BinaryTreeNode<T>* u), BinaryTreeNode<T>* t)//����
{
    if (t)
    {
        InOrder(Visit, t->LeftChild);//LDR
        Visit(t);
        InOrder(Visit, t->RightChild);
    }
}
template <class T>
void BinaryTree<T>::PostOrder(void(*Visit)(BinaryTreeNode<T>* u), BinaryTreeNode<T>* t)//����
{
    if (t) 
    {
        PostOrder(Visit, t->LeftChild);//LRD
        PostOrder(Visit, t->RightChild);
        Visit(t);
    }
}

template <class T>
void BinaryTree<T>::LevelOrder(void(*Visit)(BinaryTreeNode<T>* t), BinaryTreeNode<T>* u)//����
{
    int times = 0;
    int p = 1;
    queue<BinaryTreeNode<T>*> Q;
    if (u != nullptr)
    {
        Q.push(u);
    }
    while (!Q.empty())
    {
        BinaryTreeNode<T>* t = Q.front();
        Visit(t);
        if (t->LeftChild)
        {
            Q.push(t->LeftChild);//�����Ӿͼӽ�����
        };
        if (t->RightChild)
        {
            Q.push(t->RightChild);//���Һ��Ӿͼӽ�����
        }
        Q.pop();
        times++;
        if (times == p)
        {
            cout << endl;//��ȫ������ʱ��Ļ������
            p = p * 2 + 1;
        }
    }
}
template<class T>
BinaryTreeNode<T>* BinaryTree<T>::Find(BinaryTreeNode<T>* u, T node)
{
    if (u == nullptr)//�սڵ�ɶҲ����
    {
        return nullptr;
    }
    if (u->data == node)//�ҵ��ڵ���
    {
        return u;
    }
    BinaryTreeNode<T>* lresult = Find(u->LeftChild, node);//���Ӳ���
    BinaryTreeNode<T>* rresult = Find(u->RightChild, node);//�Һ��Ӳ���
    return lresult != nullptr ? lresult : rresult;
}
/*template <class T>
int BinaryTree<T>::Height(BinaryTreeNode<T>* u)
{// �������ĸ߶� .'
    if (u==nullptr) return 0;                    // empty tree
    else
    {
        int hl = Height(u->LeftChild);  // height of left
        int hr = Height(u->RightChild); // height of right
        if (hl > hr)
        {
            return ++hl;
        }
        else
            return ++hr;
    }
}*/
template<class T>
void BinaryTree<T>::CreateTree()
{
    int i;
    BinaryTreeNode <T>* t = new BinaryTreeNode <T>(this->origin[0]);//���ڵ�
    t->height = 1;//���ڵ�߶�Ϊ1
    root = t;
    this->root->height = 1;
    for (i = 0; (i <= origin.size() / 2 - 1) && (Find(root, origin[i]) != nullptr); i++)//���ݶ����������ʣ�ֻ��һ��Ľڵ��п����к���
    {
        if (2 * i + 1 < origin.size())//�����ó�����������
        {
            if (origin[2 * i + 1] != -100000)//����#
            {
                Find(root, origin[i])->LeftChild = new BinaryTreeNode<T>(origin[2 * i + 1]);//�����븸�ڵ�Ĺ�ϵ
                Find(root, origin[i])->LeftChild->height = Find(root, origin[i])->height + 1;//���ӵĸ߶��Ǹ��ڵ�ĸ߶�+1
            }
            else
            {
                Find(root, origin[i])->LeftChild = nullptr;//��#
            }
        }
        else
        {
            break;
        }
        if (2 * i + 2 < origin.size())
        {
            if (origin[2 * i + 2] != -100000)//����#
            {
                Find(root, origin[i])->RightChild = new BinaryTreeNode<T>(origin[2 * i + 2]);//�Һ����븸�ڵ�Ĺ�ϵ
                Find(root, origin[i])->RightChild->height = Find(root, origin[i])->height + 1;//���ӵĸ߶��Ǹ��ڵ�ĸ߶�+1
            }
            else
            {
                Find(root, origin[i])->RightChild = nullptr;//��#
            }
        }
        else
        {
            break;
        }

    }
    return;
}

template<class T>
bool BinaryTree<T>::IsCompleteTree(BinaryTreeNode<T>* u)//u��root
{
    if (u == nullptr)
        return false;
    queue<BinaryTreeNode<T>*> q;
    bool leaf = false;
    bool ans = true;
    q.push(u);
    while (!q.empty())
    {
        BinaryTreeNode<T>* tmp = q.front();
        q.pop();
        if (leaf)//���һ���ڵ�û���ӽڵ�ΪҶ�ӽڵ㣻�Ѿ������˿������Ľڵ㣬������ֵı�����Ҷ�ӽڵ㣨������������Ϊ�գ�
        {
            if (tmp->LeftChild != nullptr || tmp->RightChild != nullptr)
            {
                ans = false;
                break;
            }
        }
        else//����Ҷ�ӽڵ�
        {
            if (tmp->LeftChild != nullptr && tmp->RightChild != nullptr)//���Ҷ���
            {
                q.push(tmp->LeftChild);
                q.push(tmp->RightChild);
            }
            else if (tmp->LeftChild != nullptr && tmp->RightChild == nullptr)//�Һ���û��
            {
                leaf = true;//Ҷ�ӽڵ�
                q.push(tmp->LeftChild);//���Ӽӽ�ȥ
            }
            else if (tmp->LeftChild == nullptr && tmp->RightChild != nullptr)//����û��
            {
                ans = false;//�϶�����ȫ������
                break;
            }
            else
            {
                leaf = true;//Ҷ�ӽڵ�
            }
        }
    }
    return ans;
}
template<class T>
void BinaryTree<T>::CreateCompleteTree(BinaryTreeNode<T>*& u)
{
    int i;
    BinaryTreeNode <T>* t = new BinaryTreeNode <T>(this->datas.at(0));
    root2 = t;
    BinaryTreeNode <T>* m = root2;//�µĸ��ڵ�
    for (i = 0; i <= datas.size() / 2 - 1; i++)
    {
        if (2 * i + 1 < datas.size())//�����ó�����������
        {
            Find(root2, datas[i])->LeftChild = new BinaryTreeNode<T>(datas[2 * i + 1]);
        }
        else
        {
            break;
        }
        if (2 * i + 2 < datas.size())
        {
            Find(root2, datas[i])->RightChild = new BinaryTreeNode<T>(datas[2 * i + 2]);
        }
        else
        {
            break;
        }

    }
}
template<class T>
void BinaryTree<T>::ToCompleteTree(BinaryTreeNode<T>* u)
{
    CreateCompleteTree(root2);
    LevelOrder(Visit, root2);
}

int main()
{
    BinaryTree<int> BT;
    BinaryTreeNode<int>* root = new BinaryTreeNode<int>();
    cout << "������������нڵ��ֵ��" << endl;
    char node2[50];
    cin.getline(node2,50);
    int data[20];
    int count = 0;
    int i = 0, j = 0;
    for (i = 0; i < strlen(node2); i++)//���ַ������봦��Ϊ������������vector��
    {
        int num = 0;
        if (node2[i] == '#')
        {
            data[count] = -100000;//#��ֵΪ-100000
            BT.origin.push_back(data[count]);//ֻ���ڶ�������vector��
            i++;
            count++;
        }
        else
        {
            for (j = i; j < strlen(node2) && node2[j] != ' '; j++) {}
            if (node2[i] != '-')//����
            {
                for (int m = i; m < j; m++)
                {
                    num = num * 10 + node2[m] - '0';//���������
                }
                data[count] = num;
                BT.datas.push_back(data[count]);//������ȫ��������vector
                BT.origin.push_back(data[count]);//���ڶ�������vector
                count++;
                i = j;
            }
            else
            {
                for (int m = i + 1; m < j; m++)
                {
                    num = num * 10 + node2[m] - '0';//���������
                }
                data[count] = 0 - num;//����
                BT.datas.push_back(data[count]);//������ȫ��������vector
                BT.origin.push_back(data[count]);//���ڶ�������vector
                count++;
                i = j;
            }
        }
    }
    BT.CreateTree();
    root = BT.root;
    int node;
    if (BT.IsCompleteTree(BT.root))
    {
        cout << "True" << endl;
        cout << "����ڵ�zֵ" << endl;
        cin >> node;
        cout << node << "�ڵ�ĸ߶�Ϊ��" << BT.Find(BT.root, node)->height << endl;
    }
    else
    {
        cout << "False" << endl;
        cout << "����ڵ�zֵ" << endl;
        cin >> node;
        cout << node << "�ڵ�ĸ߶�Ϊ��" << BT.Find(BT.root, node)->height << endl;
        BT.ToCompleteTree(BT.root2);
    }
    cout << endl;
    return 0;
}