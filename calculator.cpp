#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Calculator {
private:
    string str;

    Calculator() {}
    ~Calculator() {}

public:
    static Calculator& getInstance() {
        static Calculator c;
        return c;
    }

    //���ڿ� �Է�
    void inputString() {
        while (1) {
            cout << ">>";
            cin >> this->str;
            stringIsValid(this->str);
        }
    }


    void stringIsValid(string str) {

        //���� ��ȣ, �ݴ� ��ȣ�� ����
        int left = 0, right = 0;


        for (int i = 0; i < this->str.size(); i++) {
            if ((this->str[i] >= 48 && this->str[i] <= 57) || this->str[i] == '+' || this->str[i] == '-' || this->str[i] == '*' || this->str[i] == '/' || this->str[i] == '(' || this->str[i] == ')')
            {
                if (this->str[i] == '+' || this->str[i] == '-' || this->str[i] == '*' || this->str[i] == '/' || this->str[i] == '(') {
                    if (this->str[i + 1] == '+' || this->str[i + 1] == '-' || this->str[i + 1] == '*' || this->str[i + 1] == '/' || this->str[i + 1] == ')') {
                        //��ȣ�� ���� 2�� �ΰ��

                        cout << "�Է��� �߸��Ǿ����ϴ�." << endl;
                        inputString();
                    }
                }

                //���� ������ ���� ��ȣ�� ���� ���
                if (this->str[i] >= 48 && this->str[i] <= 57) {
                    if (this->str[i + 1] == '(') {
                        cout << "�Է��� �߸��Ǿ����ϴ�." << endl;
                        inputString();
                    }
                }

                //���� ��ȣ, �ݴ� ��ȣ�� ������ ����
                if (this->str[i] == '(') {
                    left++;
                }
                if (this->str[i] == ')') {
                    //�ݴ� ��ȣ�� �� ������ ���
                    if (left == right) {
                        cout << "�Է��� �߸��Ǿ����ϴ�." << endl;
                        inputString();
                    }
                    right++;
                }

                //2����,16���� �Է�
                if (this->str[i] == 48)
                {
                    int k = 3;
                    if (this->str[i + 1] == 'b' || this->str[i + 1] == 'B') {
                        if (this->str[i + 2] != 48 && this->str[i + 2] != 49) {
                            //2������ ������ �ƴ� ���, ex) 0b99
                            cout << "2���� �Է��� �߸��Ǿ����ϴ�." << endl;
                            inputString();
                        }
                        for (int j = i + 3; j < this->str.size(); j++) {
                            if (this->str[j] == '+' || this->str[j] == '-' || this->str[j] == '*' || this->str[j] == '/' || this->str[j] == ')') {
                                break;
                            }
                            k++;
                        }

                        // 2���� -> 10����
                        int a = stoi(this->str.substr(i + 2, k), NULL, 2);
                        string s = to_string(a);

                        this->str.replace(i, k, s);

                    }
                    if (this->str[i + 1] == 'x' || this->str[i + 1] == 'X') {
                        if (!(this->str[i + 2] >= 48 && this->str[i + 2] <= 57 || this->str[i + 2] >= 65 && this->str[i + 2] <= 70 || this->str[i + 2] >= 97 && this->str[i + 2] <= 102)) {
                            //16������ ������ �ƴ� ���
                            cout << "16���� �Է��� �߸��Ǿ����ϴ�." << endl;
                            inputString();
                        }
                        for (int j = i + 3; j < this->str.size(); j++) {
                            if (this->str[j] == '+' || this->str[j] == '-' || this->str[j] == '*' || this->str[j] == '/' || this->str[j] == ')') {
                                break;
                            }
                            k++;
                        }

                        //16���� -> 10����
                        int a = stoi(this->str.substr(i + 2, k), NULL, 16);
                        string s = to_string(a);

                        this->str.replace(i, k, s);
                    }

                }

            }
            else
            {
                cout << "�̻��� ��ȣ�� �ԷµǾ����ϴ�." << endl;
                inputString();
            }
        }

        //�Է��� ��ģ ��
        //ó���� ��ȣ�� ���� ��� + - * /
        if (this->str[0] == '+' || this->str[0] == '-' || this->str[0] == '*' || this->str[0] == '/') {
            cout << "�Է��� �߸��Ǿ����ϴ�." << endl;
            inputString();
        }

        //��ȣ�� ������ �ȸ´� ���
        if (left > right) {
            cout << "�Է��� �߸��Ǿ����ϴ�." << endl;
            inputString();
        }
        stringToInt(this->str, this->str.size());
    }

    //���ڿ��� ������ �ٲ۴�.
    void stringToInt(string str, int size) {
        int k = 0;
        int stringToInt[100] = {};

        //�������ڿ� �κ��� ������ ��ȯ
        for (int i = 0; i < size; i++) {
            if (str[i] >= 48 && str[i] <= 57) {
                stringToInt[k] = stringToInt[k] * 10 + str[i] - 48;
                if (!(str[i + 1] >= 48 && str[i + 1] <= 57)) {
                    k++;
                }
            }
            //��ȣ�� Ư�� ������ ��ȯ(-1 ~ -6)
            else {
                if (str[i] == '+')
                    stringToInt[k] = -1;
                if (str[i] == '-')
                    stringToInt[k] = -2;
                if (str[i] == '*')
                    stringToInt[k] = -3;
                if (str[i] == '/')
                    stringToInt[k] = -4;
                if (str[i] == '(')
                    stringToInt[k] = -5;
                if (str[i] == ')')
                    stringToInt[k] = -6;
                k++;
            }
        }

        infixToPostfix(stringToInt, k);
    }

    //���� ǥ��� --> ���� ǥ���
    void infixToPostfix(int arr[], int size) {
        int arr2[100];
        int k = 0;
        stack<int> st;
        for (int i = 0; i < size; i++) {
            if (arr[i] >= 0) {
                arr2[k] = arr[i];
                k++;
            }
            if (arr[i] < 0) {
                if (arr[i] == -5)
                {
                    st.push(arr[i]);
                    continue;
                }
                if (arr[i] == -6)
                {
                    while (!(st.top() == -5)) {
                        arr2[k] = st.top();
                        st.pop();
                        k++;
                    }
                    st.pop();
                    continue;
                }
                if (st.empty()) {
                    st.push(arr[i]);
                }
                else
                {
                    if (arr[i] == -1 || arr[i] == -2) {
                        if (st.top() == -5) {
                            st.push(arr[i]);
                        }
                        else {
                            arr2[k] = st.top();
                            k++;
                            st.pop();
                            st.push(arr[i]);
                        }
                    }
                    if (arr[i] == -3 || arr[i] == -4) {
                        if (st.top() == -1 || st.top() == -2 || st.top() == -5) {
                            st.push(arr[i]);
                        }
                        else
                        {
                            arr2[k] = st.top();
                            k++;
                            st.pop();
                            st.push(arr[i]);
                        }
                    }
                }
            }
        }

        while (!st.empty()) {
            arr2[k] = st.top();
            k++;
            st.pop();
        }

        postFix(arr2, k);
    }

    //����ǥ������� ���� ���
    int postFix(int arr[], int size) {
        stack<double> st;
        double a, b;
        int oper;

        for (int i = 0; i < size; i++) {
            if (arr[i] >= 0) {
                st.push(arr[i]);
            }
            else {
                a = st.top();
                st.pop();
                b = st.top();
                st.pop();
                oper = arr[i];
                st.push(calculate(a, b, oper));
            }
        }
        cout << "answer : " << st.top() << endl;
        return st.top();
    }

    //������ ��Ģ������ ���
    double calculate(double a, double b, int oper) {
        double result = 0;
        switch (oper) {
        case -1:
            result = b + a;
            break;
        case -2:
            result = b - a;
            break;
        case -3:
            result = b * a;
            break;
        case -4:
            if (a == 0) {
                cout << "0���� ���� �� �����ϴ�." << endl;
                inputString();
            }
            else {
                result = b / a;
                break;
            }
        }
        return result;
    }


};

int main() {
    Calculator& c = Calculator::getInstance();


    c.inputString();

}
