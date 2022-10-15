#include <cstdio>
#include <queue>
#include <cstring>
#include <map>
#include "symbol.h"
#include "automata.h"
using namespace std;

// DFA描述结构
map<char, int> p;


// 存放解析的结果
queue<int> SYM;
queue<char*> ID;
queue<int> NUM;

void generate_DFA() {
    // 初始化关键字及特殊字符的
    int n = sizeof(syms) / sizeof(syms[0]);
    int tag = 1;
    int pos = 0;
    for (int i = 0; i < n; i++) {
        int cur = 0;
        for (int j = 0; syms[i][j]; j++) {
            char c = syms[i][j];
            if (node_save_word[cur].next[p[c]] != 0) {
                cur = node_save_word[cur].next[p[c]];
            } else {
                cur = node_save_word[cur].next[p[c]] = ++pos;
            }
        }
        node_save_word[cur].state = tag++;
    }
    /* 初始化标识符和数字识别的DFA，退出状态是-1 */
    node_num_and_identifier[0].next[0] = 1;
    node_num_and_identifier[1].next[0] = 1;
    node_num_and_identifier[2].next[0] = -1;
    node_num_and_identifier[0].next[1] = 2;
    node_num_and_identifier[1].next[1] = 1;
    node_num_and_identifier[2].next[1] = 2;
    node_num_and_identifier[1].state = IDENTIFIER;
    node_num_and_identifier[2].state = NUMBER;
}

void init_map() {
    int cnt = 0;
    for (int i = 0; i <= 9; i++) {
        p[i + '0'] = cnt++;
    }
    for (int i = 0; i <= 25; i++) {
        p[i + 'a'] = cnt++;
    }
    for (int i = 0; i <= 25; i++) {
        p[i + 'A'] = cnt++;
    }
    p['{'] = cnt++;
    p['}'] = cnt++;
    p['('] = cnt++;
    p[')'] = cnt++;
    p[';'] = cnt++;
    p[','] = cnt++;
    p['+'] = cnt++;
    p['-'] = cnt++;
    p['*'] = cnt++;
    p['/'] = cnt++;
    p['>'] = cnt++;
    p['<'] = cnt++;
    p['='] = cnt++;
    p[':'] = cnt++;
    p['#'] = cnt++;
    p[' '] = cnt++;
}

char GETCH() {
    return getchar();
}

int next_save_word_dfa(int pos, char c) {
    printf("pos = %d, c = %c, next = %d\n", pos, c, node_save_word[pos].next[p[c]]);
    return node_save_word[pos].next[p[c]];
}

int next_identifier_and_num_dfa(int pos, char c) {
    int order;
    if (p[c] < 10) {
        order = 1;
    } else if (p[c] < 62) {
        order = 0;
    } else {
        return -1;
    }
    return node_num_and_identifier[pos].next[order];
}

void GETSYM() {
    char c;
    int pos1 = 0, pos2 = 0;
    bool pass = false;  // 不进行GETCH()
    bool end = false;
    while(pass || (c = GETCH()) != EOF) {
        pass = false;
        printf("read %c\n", c);
        if (c == '\n')  c = ' ';
        // 如果是特殊字符，单纯的分割作用
        if (p[c] >= 62) {
            int state1 = node_save_word[pos1].state;
            int state2 = node_num_and_identifier[pos2].state;
            // printf("state1 = %d, pos1 = %d, state2 = %d, pos2 = %d\n", state1, pos1, state2, pos2);
            if (state1 != 0) {
                SYM.push(state1);
            } else if (state2 != 0){
                SYM.push(state2);
            } else if (pos1 != 0 && pos2 != 0){
                printf("error occur\n");
                return;
            }
            pos1 = 0, pos2 = 0;

            // 如果是空格，就一直读到第一个非空格的地方
            if (c == ' ') {
                while (1) {
                    c = GETCH();
                    if (c == EOF) {
                        end = true;
                        break;
                    }
                    if (c != ' ') {
                        pass = true;
                        break;
                    }
                }
            }
            if (pass || end)    continue;

            // 如果是非空格就进行匹配
            printf("asdadsasd\n");
            while(1) {
                pos1 = next_save_word_dfa(pos1, c);
                if ((c = GETCH()) == EOF) {
                    end = true;
                    break;
                }
                if (p[c] < 62 || c == ' ') {
                    int state1 = node_save_word[pos1].state;
                    if (state1 == 0) {
                        printf("error: don't match\n");
                        return;
                    } else {
                        SYM.push(state1);
                    }
                    pass = true;
                    pos1 = 0;
                    break;
                }
            }
        } else {
            pos1 = next_save_word_dfa(pos1, c);
            pos2 = next_identifier_and_num_dfa(pos2, c);
            printf("pos1 = %d, pos2 = %d, c = %c\n", pos1, pos2, c);
        }
        if (end) break;
    }
    
    /*完成之后，写入最后一个*/
    int state1 = node_save_word[pos1].state;
    int state2 = node_num_and_identifier[pos2].state;
    printf("state1 = %d, pos1 = %d, state2 = %d, pos2 = %d\n", state1, pos1, state2, pos2);
    if (state1 != 0) {
        SYM.push(state1);
    } else if (state2 != 0){
        SYM.push(state2);
    } else if (pos1 != 0 && pos2 != 0){
        printf("error occur\n");
        return;
    }
    
    /*写入#*/
    SYM.push(HASHTAG_SYM);
}

void out() {
    printf("\n********* RESULT *********\n");
    bool first = true;
    while(!SYM.empty()) {
        first = false;
        int t = SYM.front();
        printf("%s(%d)\n", syms[t - 1], t - 1);
        SYM.pop();
    }
    printf("\n");
    while(!ID.empty()) {
        if (!first) {
            printf(", ");
        }
        first = false;
        char* t = ID.front();
        printf("%s", t);
        ID.pop();
    }
    printf("\n");
    while(!NUM.empty()) {
        if (!first) {
            printf(", ");
        }
        first = false;
        int t = NUM.front();
        printf("%d", t);
        NUM.pop();
    }
    printf("\n");
}

int main() {
    memset(node_num_and_identifier, 0, sizeof(node_num_and_identifier));
    memset(node_save_word, 0, sizeof(node_save_word));
    init_map();
    generate_DFA();
    freopen("code.txt", "r", stdin);
    GETSYM();
    out();
    return 0;
}