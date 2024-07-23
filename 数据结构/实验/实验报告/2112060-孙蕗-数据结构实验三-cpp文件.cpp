#include <iostream>
#include<cstring>
#include<string>
using namespace std;
//ջ�Ķ���
template<class T>
class Stack 
{ 
public:
    int top = -1;
    T stack[50];
    bool IsEmpty() const { return top == -1; }
    T Top();
    void Push(T x);
    void Pop();
};
template<class T>
T Stack<T>::Top() 
{
	return stack[top];
} 
template<class T>
void Stack<T>::Push(T x)
{
    top++;
    stack[top] = x;
}
template<class T>
void Stack<T>::Pop()
{
    top--;
}

//��������ȼ�
int priority(char ch)
{
    if (ch == '(' || ch == ')')
    {
        return 3;
    }
    if (ch == '*' || ch == '/')
    {
        return 2;
    }
    if (ch == '+' || ch == '-')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//�������������������������������
float calculate(float num1, float num2, char ch)
{
    switch (ch)
    {
    case '+':
        return num1 + num2;
        break;
    case '-':
        return num1 - num2;
        break;
    case '*':
        return num1 * num2;
        break;
    case '/':
        return num1 / num2;
        break;
    default:
        break;
    }
}
bool Float(int i,char *str)
{
    for (; str[i]!='+'&&str[i]!='-'&&str[i]!='*'&&str[i]!='/'&&str[i]!='('&&str[i]!=')' && i < strlen(str); i++)//�������������ֻ�������ֺ�.
    {
        if (str[i]=='.')
        {
            return true;
        }
    }
    return false;
}
int main()
{
    Stack<float> num;//�����ֵ�ջ
    Stack<char> operators;//���������ջ
    char str[50];
    cin >> str;//�����ַ���
    int len = strlen(str);
    int i = 0;
    for (i = 0; i < len; i++)
    {
        if (str[i] < '0' || str[i]>'9')//�Ƿ��Ų�������
        {
            if (str[i] == '('||operators.IsEmpty())
            {
                operators.Push(str[i]);
            }
            else
            {
                if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
                {
                    if (priority(str[i]) > priority(operators.Top()))//���ȼ���ջ�׸�ֱ��ѹ��ջ
                    {
                        operators.Push(str[i]);
                    }
                    else
                    {
                        while ((priority(str[i]) <= priority(operators.Top())) && !operators.IsEmpty()&&operators.Top()!='(')//ֱ���������ȼ�����С����ѹ��ջ
                        {
                            float num2 = num.Top();
                            num.Pop();
                            float num1 = num.Top();
                            num.Pop();
                            char ch = operators.Top();
                            operators.Pop();
                            num.Push(calculate(num1, num2, ch));
                        }
                        operators.Push(str[i]);
                    }
                }
                else//��(
                {
                    while (operators.Top() != '(')
                    {
                        float num2 = num.Top();
                        num.Pop();
                        float num1 = num.Top();
                        num.Pop();
                        char ch = operators.Top();
                        operators.Pop();
                        num.Push(calculate(num1, num2, ch));
                    }
                    operators.Pop();
                }
            }
        }
        else//�����֣��п��ܶ�λ�����п���С��
        {
            float tempnum = 0;
            if (!Float(i,str))//����û��.�Ϳ϶�����С����
            {
                for (; str[i] <= '9' && str[i] >= '0' && i < len; i++)
                {
                    if ((str[i] >= '0') && (str[i] <= '9'))
                    {
                        tempnum = tempnum * 10 + str[i] - '0';
                    }
                }
            }
            else//��С��
            {
                double tmp10 = 10;
                for (; str[i] <= '9' && str[i] >= '0' && i < len&&str[i]!='.'; i++)//����С������������
                {
                    if ((str[i] >= '0') && (str[i] <= '9'))
                    {
                        tempnum = tempnum * 10 + str[i] - '0';
                    }
                }
                i++;//'.'
                for (; str[i] <= '9' && str[i] >= '0' && i < len; i++)//����С����С������
                {
                    if ((str[i] >= '0') && (str[i] <= '9'))
                    {
                        tempnum+= float(str[i] - '0')/tmp10;
                    }
                    tmp10 *= 10;
                }
            }
            num.Push(tempnum);
            i--;
        }
    }
    while (!operators.IsEmpty())//ֱ������ջ������������
    {
        float num2 = num.Top();
        num.Pop();
        float num1 = num.Top();
        num.Pop();
        char ch = operators.Top();
        operators.Pop();
        num.Push(calculate(num1, num2, ch));
    }
    cout << num.Top();//��ʱ����ջջ��Ԫ�ؾ���������
	return 0;
}