#include <iostream>
#include <string>
using namespace std;

int sym1; //符号正负 1表示正，-1表示负
int sym2; //符号正负 1表示正，-1表示负


struct number {
    int data; //数，万进制
    number* brfor = nullptr; //前驱
    number* next = nullptr; //后继
    number(number* b = nullptr, int d = 0, number* n = nullptr) {
        brfor = b;
        data = d;
        next = n;
    }
};
struct link_2 {
    int size = 0; // 链表长度
    number* head = nullptr;
    number* tail = nullptr;
    void add(int num) {
        //在尾加入链表
        number* n = new number(nullptr, num, nullptr);
        if (head == nullptr) {
            head = n;
            tail = head;
            size++;
            return;
        }
        tail->next = n;
        n->brfor = tail;
        tail = n;
        size++;
    }
    void _delete_head() {
        if (head == nullptr) return;
        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
            size--;
            return;
        }
        head = head->next;
        delete head->brfor;
        head->brfor = nullptr;
        size--;
        return;

    }
    void _delete_tail() {
        if (head == nullptr) return;
        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
            size--;
            return;
        }
        number* t = tail;
        tail = tail->brfor;
        tail->next = nullptr;
        delete t;
        size--;
        return;
    }


    void print() {
        number* t = head;
        while (t != nullptr) {
            cout << t->data;
            t = t->next;
        }
        cout << endl;
    }
    void print_fan() {
        number* t = tail;
        while (t != nullptr) { //输出规整
            if(t != tail){ //补0
                if (t->data < 10) {
                    cout << "000";
                    cout << t->data;
                }
                else if (t->data < 100) {
                    cout << "00";
                    cout << t->data;
                }
                else if (t->data < 1000) {
                    cout << "0";
                    cout << t->data;
                }
                else {
                    cout << t->data;
                }
            }
            else { //第一个数直接打印，不用补0
                cout << t->data;
            }
            
            t = t->brfor;
        }
        cout << endl;
    }
    int _size() {
        return size;
    }
};

link_2 sum; //储存结果

bool chack(string a) { //判断是否合理
    for (int i = 0; i < a.size(); i++) {
        //判断字符是否为数字或运算符
        if ((a[i] < '0' || a[i] > '9') && a[i] != '=' && a[i] != '+' && a[i] != '-' && a[i] != '(' && a[i] != ')' && a[i] != ',' && a[i] != ' ') {
            return false;
        }
    }
    return true;
};

int bijiao(link_2 l1, link_2 l2) { //比较两个数大小若返回1则num1大，若返回2，则num2大，若返回0，则一般大。
    if (l1._size() > l2._size()) return 1;
    else if (l1._size() < l2._size()) return -1;
    else {
        number* t1 = l1.head;
        number* t2 = l2.head;
        while (t1 != nullptr) {
            if (t1->data > t2->data) return 1;
            else if (t1->data < t2->data) return -1;
            else if (t1->data == t2->data) {
                t1 = t1->next;
                t2 = t2->next;
            }
        }
        return 0;
    }
}
void jiaozheng(link_2 li) { //防止做减法时会出现负数，进行矫正
    number* t = li.head;
    while (t != nullptr) {
        if (t->data < 0 && t != li.head) {
            t->data = t->data + 10000;
            t->next->data = t->next->data - 1;
        }
        t = t->next;
    }
    number* t2 = li.tail; //若第一位是0，则删除，从第一个非0开始输出。
    while(t2 != nullptr) {
        if(t2 -> data == 0) sum._delete_tail();
        t2 = t2->brfor;
        if(t2 -> data != 0) break;
    }
}


void jia(link_2 l1, link_2 l2) {
    int jin = 0;
    number* t1 = l1.tail; //从各位开始加
    number* t2 = l2.tail;
    while (t1 != nullptr || t2 != nullptr || jin != 0) { //全部运算完
        int x = (t1 == nullptr ? 0 : t1->data) + (t2 == nullptr ? 0 : t2->data) + jin;
        jin = x / 10000; //判断是否进位
        sum.add(x % 10000); //四位一组
        if (t1 != nullptr) t1 = t1->brfor;
        if (t2 != nullptr) t2 = t2->brfor;
    }
    

}

void jian(link_2 l1, link_2 l2) {
    int jie = 0;
    number* t1 = l1.tail;
    number* t2 = l2.tail;
    while (t1 != nullptr || t2 != nullptr||jie != 0) {
        int x = (t1 == nullptr ? 0 : t1->data) - (t2 == nullptr ? 0 : t2->data) - jie;
        if (x < 0) {
            x = x + 10000;
            jie = 1;
        }
        else {
            jie = 0;
        }
        sum.add(x);
        if (t1 != nullptr) t1 = t1->brfor;
        if (t2 != nullptr) t2 = t2->brfor;
    }
    jiaozheng(sum);

}

void fuhao(string a) { // 符号判断
    sym1 = sym2 = 1;
    if (a[0] == '-') {
        sym1 = sym1 * (-1);

    }
    for (int i = 1; i < a.size(); i++) {
        if (a[i] == '-') { //每出现一次‘-’，变一次号
            sym2 = sym2 * (-1);
        }

    }
}

void chuli(string a) {
    if (!chack(a)){ //判断是否合理 通过
        cout << "ERROR" << endl;
        return ;
    }
    string b;
    //去除空格 通过
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == ' ' || a[i] == '(' || a[i] == ')') {
            continue;
        }
        b += a[i];
    }


    //判断符号
    fuhao(b);

    link_2 num1, num2; //两个链表 通过
    int time = 0;
    string c;
    for (int i = 0; i < b.size(); i++) {
        if (b[i] == ',') {
            if (time == 0) {
                num1.add(stoi(c)); //c华为整数加入链表
                c = "";
                continue;
            }
            else {
                num2.add(stoi(c));
                c = "";
                continue;
            }
        }
        else if (b[i] == '=') {
            num2.add(stoi(c));
            c = "";
            break;
        }
        else if (b[i] == '+') {
            if (i == 0) continue;
            if (c.length() != 0) {
                num1.add(stoi(c));
                c = "";
            }
            time++;
            continue;
        }
        else if (b[i] == '-') {
            if (i == 0) continue;
            if (c.length() != 0) {
                num1.add(stoi(c));
                c = "";
            }
            time++;
            continue;
        }
        else {
            c += b[i];
        }
    }

//判断用大的数减小数

    int bj = bijiao(num1, num2);

    if (sym1 == sym2) {
        if (sym1 > 0)
            jia(num1, num2);
        else if (sym1 < 0) {

            jia(num1, num2);
            /*sum.add('-' - '0');*/
            sum.tail->data *= -1; //结果为负数
        }
    }
    else {
        if (bj == 0) sum.add(0);
        else if (sym1 < 0 && sym2 > 0 && bj == -1) {
            jian(num2, num1);
            
        }
        else if(sym1 > 0 && sym2 < 0 && bj == -1){
            jian(num2, num1);
            sum.tail->data *= -1;
        }

        else if (sym1 < 0 && sym2 > 0 && bj == 1) {
            jian(num1, num2);
            sum.tail->data *= -1;
        }
        else if (sym1 > 0 && sym2 < 0 && bj == 1){
            jian(num1, num2);
        }
    }


    sum.print_fan(); // 结果
}

int main() {
    string a;
    cout << "please input a + b = , Four digits in a group" << endl;
    getline(cin, a);
    chuli(a);
    return 0;
}

