#include "Huffman.h"
int main() {




    string ab = "commercommecommerce";
    string a = "bcaadddccacacac";
    string ac = "abcdabcabcdaabcabce";

    //vector <LZ78Node> result = LZ78Compress(ac);
    //for (auto i : result) {
    //    cout << i.codeword << " " << i.index<<endl;

    //}
    map<char,int> result = formHuffmanList(a);
    vector<HuffmanNode> result2 = convertMap(result);
    HuffmanTree tree;
    tree.buildHuffmansTree(result2);
     tree.formDictionary(result);
    return 0;

}