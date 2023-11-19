#include <iostream>
#include <fstream>
#include <vector>
#include "lexicalAnalyzer.h"
int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    string str;
    lexicalAnalyzer lexAn;
    //read file lines and parce it to tokens
    while(getline(in, str)) {
        lexAn.addTokens(str);
    } 
    //push tokens to hash table
    for (int i = 0; i < lexAn.tokens.size(); ++i) {
        Token t = lexAn.tokens[i];
        //need to detect ":=" 
        if (t.name == ":") {
            //if we meet : and next char dont gonna go out of the range we need to check is that = char
            if (i < lexAn.tokens.size() - 1) {
                //if thats true create buffToken and push it
                if (lexAn.tokens[i + 1].name == "=") {
                    Token buffToken;
                    buffToken.type = "Op";
                    buffToken.name = ":=";
                    lexAn.hash.addToken(buffToken);
                    //cuz we already add i and i + 1 char we need to make i++ to skip = char
                    i++;
                    continue;
                }
            }
        }
        lexAn.hash.addToken(t);
    }
    //outer for our hash
    for (int i = 0; i < 100000; ++i) {
        Node* node = &lexAn.hash.table[i];
        if (node->val.type != "None" && node->val.name != "None") {
            out << i << ": ";
        }
        else continue;
        while (node != NULL) {
            out << "{" << node->val.type << " | " << node->val.name << "} ";
            node = node->next;
        } 
        out << "\n";
    }
    out.close();
    in.close();
    return 0;
}
