#define NODE_SAVE_WORD_NUM 100005
#define NODE_NUM_AND_IDENTIFIER_NUM 100005
#define SEPERATOR_NUM 1005

struct Node_save_word {
    int next[100];
    int state;
} node_save_word[NODE_SAVE_WORD_NUM];


struct Node_num_and_identifier {
    int next[5];
    int state;
} node_num_and_identifier[NODE_NUM_AND_IDENTIFIER_NUM];


struct Node_seperator {
    int next[20];
    int state;
} seperator[SEPERATOR_NUM];
