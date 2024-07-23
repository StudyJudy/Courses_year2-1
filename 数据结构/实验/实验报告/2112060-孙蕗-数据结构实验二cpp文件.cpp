#include<iostream>
using namespace std;
template<class T>
class ChainNode
{
public:
    T data;
    ChainNode<T>* link;
};
template<class T>
class CircularChain//ѭ������
{
public:
    CircularChain();
    bool IsEmpty() const { return first == 0; }
    int Length();
    CircularChain<T>& Insert(int k, T& x);
    void print(int k);
    CircularChain<T>& Reverse();
    CircularChain<T>& Append(const T& x);
    ChainNode<T>* first;// ͷָ��
    ChainNode<T>* last;//βָ��
};
template<class T>
CircularChain<T>::CircularChain()//ͷβָ��ĳ�ʼ��
{
    first = nullptr;
    last = nullptr;
}
template<class T>
int CircularChain<T>::Length()//����ѭ������ĳ���
{
    int len = 0;
    if (first == nullptr)//ͷָ��գ�Ϊ������
    {
        return 0;
    }
    else
    {
        ChainNode<T>* current = first;
        if (first == last)//ͷβָ����ȣ�������ֻ��һ��Ԫ��
        {
            return 1;
        }
        else
        {
            while (current->link != this->first)
            {
                len++;
                current = current->link;
            }
            len++;
            return len;
        }
    }
}
template<class T>
void CircularChain<T>::print(int k)//���
{
    ChainNode<T>* current;
    int i = 1;
    for (current = first; i <= k && current; current = current->link)
    {
        cout << current->data << " ";
        i++;
    }
}
template<class T>
CircularChain<T>& CircularChain<T>::Insert(int k, T& x)//���루��k=0ʱ��Ϊͷ�壩
{
    ChainNode<T>* p = first;
    for (int index = 1; index < k && p; index++)
        p = p->link;
    ChainNode<T>* y = new ChainNode<T>; //�½ڵ�
    y->data = x;
    if (k) //k!=0,�����м�
    {
        y->link = p->link;
        p->link = y;
    }
    else//k=0��ͷ��
    {
        y->link = first;//�½��ڵ�Ϊͷ�ڵ�
        first = y;
    }
    return *this;
}
template<class T>
CircularChain<T>& CircularChain<T>::Append(const T& x)//β��
{
    ChainNode<T>* y = new ChainNode<T>;//�½ڵ�
    y->data = x;
    if (this->Length() != 0) //�ǿ�����
    {
        y->link = first;
        last->link = y;
        last = y;
        last->link = first;
    }
    else // ������ͷβָ��ָ��ͬһ��Ԫ��
    {
        first = y;
        last = y;
    }
    return *this;
}
template<class T>
CircularChain<T>& CircularChain<T>::Reverse()//ѭ������ķ�ת��ͷ�巭ת
{
    int k = this->Length();
    ChainNode<T>* p = first->link;
    last = first;//��ԭ����ͷ�ڵ���β�ڵ㣬ͷβָ�붼ָ��ͷԪ��
    for (int i = 1; i < k; i++)//��ͷ�ڵ���Ԫ�ذ�˳��ͷ��
    {
        this->Insert(0, p->data);
        p = p->link;
    }
    last->link = first;//��ת��ԭ����β�ڵ���ͷ�ڵ㣬ԭ����ͷ�ڵ���β�ڵ㣬ѭ��Ҳ���ŷ�ת
    return *this;
}

template<class T>
class Chain {
public:
    Chain() { first = nullptr; }//��ʼ��ͷ�ڵ�
    bool IsEmpty() const { return first == 0; }
    int Length();
    Chain<T>& Insert(int k, T& x);
    Chain<T>& Reverse();
    Chain<T>& Append(T& x);
    T knumber(int k);
    void print(int k);
    ChainNode<T>* first;
    ChainNode<T>* last;
    Chain<T>& DeleteB(CircularChain<T>& B);
};
template<class T>
int Chain<T>::Length()//����Ԫ�ظ���
{
    ChainNode<T>* current = first;
    int len = 0;
    while (current)
    {
        len++;
        current = current->link;
    }
    return len;
}
template<class T>
void Chain<T>::print(int k)//���Ԫ��
{
    ChainNode<T>* current;
    int i = 1;
    for (current = first; i <= k + 1 && current; current = current->link)
    {
        cout << current->data << " ";
        i++;
    }
}
template<class T>
Chain<T>& Chain<T>::Insert(int k, T& x)//����
{
    ChainNode<T>* p = first;
    for (int index = 1; index < k && p; index++)
        p = p->link;
    ChainNode<T>* y = new ChainNode<T>; //�½��ڵ�
    y->data = x;
    if (k) //�м����
    {
        y->link = p->link; p->link = y;
    }
    else //ͷ��
    {
        y->link = first;  first = y;
    }
    return *this;
}
template<class T>
Chain<T>& Chain<T>::Append(T& x)//β��
{
    ChainNode<T>* y = new ChainNode<T>;//�½ڵ�
    y->data = x;
    if (this->Length() != 0) //�ǿ�����
    {
        last->link = y;
        y->link = nullptr;
        last = y;
    }
    else
    {
        first = y;
        last = y;
        last->link = nullptr;
    }
    return *this;
}
template<class T>
Chain<T>& Chain<T>::Reverse()//�͵ط�ת
{
    if (this->first == nullptr)//������ 
    {
        return *this;
    }
    ChainNode<T>* p1 = this->first->link;//p1Ϊ����Ҫ��ת��Ԫ��
    ChainNode<T>* p2 = nullptr;//p2Ϊ��һ��Ҫ��ת��Ԫ��
    this->first->link = nullptr;//��β�ڵ�
    while (p1 != nullptr)
    {
        p2 = p1->link;//��һ��Ҫ��ת��Ԫ��
        p1->link = this->first;//��ת
        this->first = p1;//����ͷ֮�󣬱��ͷ���
        p1 = p2;//��һ��Ҫ��ת��Ԫ��
    }
    return *this;
}
template<class T>
T Chain<T>::knumber(int k)//����ָ�룬�м��k-1��Ԫ��
{
    ChainNode<T>* p1 = first;
    for (int i = 1; i < k + 1 && p1; i++)
    {
        p1 = p1->link;
    }
    ChainNode<T>* p2 = first;
    for (int i = 1; p1; i++)
    {
        p1 = p1->link;
        p2 = p2->link;
    }
    return p2->data;
}
template<class T>
Chain<T>& Chain<T>::DeleteB(CircularChain<T>& B)//ɾ��A��B���ֵ�Ԫ��
{
    ChainNode<T>* a1 = this->first;//A��ָ�벻������B��
    ChainNode<T>* a2 = a1;//a2ָ�����a1��ǰһ��
    int i = 0;
    while (a1 != 0)//û��β
    {
        ChainNode<T>* b1 = B.first;
        int i = 1;
        while (a1->data != b1->data && i <= B.Length())//a1������b1
        {
            b1 = b1->link;
            i++;
        }
        if (a1->data == b1->data)//�ҵ��ˣ�����ͬ��Ԫ�أ�Ҫɾ��A�нڵ�
        {
            if (a1 == this->first)//�����A��ͷ�ڵ�
                first = first->link;//ֱ��ָ����һ��
            else
            {
                a2->link = a1->link;//a2��a1��ǰһ����ɾ��a1�ڵ���ζ��a2��һ��ָ�����a1����һ��
                a1 = a1->link;//a1ָ��a1����һ��Ԫ�أ���ɾ��a1��a1Ҳ��ǰ����һ��  
            }
        }
        else//A�г���Ԫ��B��û�У�Ҫ����
        {
            a2 = a1;
            a1 = a1->link;//a2ָ����a1��ǰһ����a1��ǰ��һ����������
        }
    }
    return *this;
}
int main()
{
    Chain<int> ForwardchainA;
    CircularChain<int> circlechainB;
    int n;
    int k;
    cin >> k;
    while (cin >> n)
    {
        ForwardchainA.Append(n);
    }
    int B[10] = { 0,1,2,3,4,5,6,7,8,9 };
    for (int i = 0; i < 10; i++)
    {
        circlechainB.Append(B[i]);
    }
    cout << endl;
    cout << "B.Length():" << circlechainB.Length() << endl;
    cout << "A:";
    ForwardchainA.print(ForwardchainA.Length());
    cout << endl;
    cout << "B:";
    circlechainB.print(circlechainB.Length());
    cout << endl;
    cout << "A Reverse:";
    ForwardchainA.Reverse();
    ForwardchainA.print(ForwardchainA.Length());
    cout << endl;
    cout << "B Reverse:";
    circlechainB.Reverse();
    circlechainB.print(circlechainB.Length());
    cout << endl;
    cout << "circlechainB first:" << circlechainB.first->data << "    " << "circlechainB last:" << circlechainB.last->data << endl;
    cout << "A delete_B:";
    ForwardchainA.DeleteB(circlechainB);
    ForwardchainA.print(ForwardchainA.Length());
    cout << endl;
    cout << "delete A_k:";
    cout << ForwardchainA.knumber(k);
    cout << endl;
    return 0;
}