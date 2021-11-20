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

    //문자열 입력
    void inputString() {
        while (1) {
            cout << ">>";
            cin >> this->str;
            stringIsValid(this->str);
        }
    }


    void stringIsValid(string str) {

        //여는 괄호, 닫는 괄호의 개수
        int left = 0, right = 0;


        for (int i = 0; i < this->str.size(); i++) {
            if ((this->str[i] >= 48 && this->str[i] <= 57) || this->str[i] == '+' || this->str[i] == '-' || this->str[i] == '*' || this->str[i] == '/' || this->str[i] == '(' || this->str[i] == ')')
            {
                if (this->str[i] == '+' || this->str[i] == '-' || this->str[i] == '*' || this->str[i] == '/' || this->str[i] == '(') {
                    if (this->str[i + 1] == '+' || this->str[i + 1] == '-' || this->str[i + 1] == '*' || this->str[i + 1] == '/' || this->str[i + 1] == ')') {
                        //기호가 연속 2번 인경우

                        cout << "입력이 잘못되었습니다." << endl;
                        inputString();
                    }
                }

                //숫자 다음에 여는 괄호가 오는 경우
                if (this->str[i] >= 48 && this->str[i] <= 57) {
                    if (this->str[i + 1] == '(') {
                        cout << "입력이 잘못되었습니다." << endl;
                        inputString();
                    }
                }

                //여는 괄호, 닫는 괄호의 개수를 센다
                if (this->str[i] == '(') {
                    left++;
                }
                if (this->str[i] == ')') {
                    //닫는 괄호가 더 많아질 경우
                    if (left == right) {
                        cout << "입력이 잘못되었습니다." << endl;
                        inputString();
                    }
                    right++;
                }

                //2진수,16진수 입력
                if (this->str[i] == 48)
                {
                    int k = 3;
                    if (this->str[i + 1] == 'b' || this->str[i + 1] == 'B') {
                        if (this->str[i + 2] != 48 && this->str[i + 2] != 49) {
                            //2진수의 형식이 아닐 경우, ex) 0b99
                            cout << "2진수 입력이 잘못되었습니다." << endl;
                            inputString();
                        }
                        for (int j = i + 3; j < this->str.size(); j++) {
                            if (this->str[j] == '+' || this->str[j] == '-' || this->str[j] == '*' || this->str[j] == '/' || this->str[j] == ')') {
                                break;
                            }
                            k++;
                        }

                        // 2진수 -> 10진수
                        int a = stoi(this->str.substr(i + 2, k), NULL, 2);
                        string s = to_string(a);

                        this->str.replace(i, k, s);

                    }
                    if (this->str[i + 1] == 'x' || this->str[i + 1] == 'X') {
                        if (!(this->str[i + 2] >= 48 && this->str[i + 2] <= 57 || this->str[i + 2] >= 65 && this->str[i + 2] <= 70 || this->str[i + 2] >= 97 && this->str[i + 2] <= 102)) {
                            //16진수의 형식이 아닐 경우
                            cout << "16진수 입력이 잘못되었습니다." << endl;
                            inputString();
                        }
                        for (int j = i + 3; j < this->str.size(); j++) {
                            if (this->str[j] == '+' || this->str[j] == '-' || this->str[j] == '*' || this->str[j] == '/' || this->str[j] == ')') {
                                break;
                            }
                            k++;
                        }

                        //16진수 -> 10진수
                        int a = stoi(this->str.substr(i + 2, k), NULL, 16);
                        string s = to_string(a);

                        this->str.replace(i, k, s);
                    }

                }

            }
            else
            {
                cout << "이상한 기호가 입력되었습니다." << endl;
                inputString();
            }
        }

        //입력을 마친 후
        //처음에 기호가 들어가는 경우 + - * /
        if (this->str[0] == '+' || this->str[0] == '-' || this->str[0] == '*' || this->str[0] == '/') {
            cout << "입력이 잘못되었습니다." << endl;
            inputString();
        }

        //괄호의 개수가 안맞는 경우
        if (left > right) {
            cout << "입력이 잘못되었습니다." << endl;
            inputString();
        }
        stringToInt(this->str, this->str.size());
    }

    //문자열을 정수로 바꾼다.
    void stringToInt(string str, int size) {
        int k = 0;
        int stringToInt[100] = {};

        //정수문자열 부분을 정수로 변환
        for (int i = 0; i < size; i++) {
            if (str[i] >= 48 && str[i] <= 57) {
                stringToInt[k] = stringToInt[k] * 10 + str[i] - 48;
                if (!(str[i + 1] >= 48 && str[i + 1] <= 57)) {
                    k++;
                }
            }
            //기호를 특정 정수로 변환(-1 ~ -6)
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

    //중위 표기식 --> 후위 표기식
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

    //후위표기법으로 수식 계산
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

    //실제로 사칙연산을 계산
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
                cout << "0으로 나눌 수 없습니다." << endl;
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
