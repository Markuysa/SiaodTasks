#include "Test.h"
int main() {




    string ab = "commercommecommerce";
    string a = "bcaadddccacacac";
    string ac = "abcdabcabcdaabcabce";

    //ShannonFanoTree tree;
    //ShannonFanoNode* root = tree.getRoot();
    //tree.fillFrequencyDict(a);
    //cout<<tree.encode(a);
    HuffmanTree tree;

    tree.buildHuffmansTree(ab);
    
}