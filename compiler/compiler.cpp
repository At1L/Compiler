#include <iostream>
#include <fstream>
#include <vector>
#include "lexicalAnalyzer.h"
#include "syntaxAnalyzer.h"

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    syntaxAnalyzer sint("input.txt");
    if (sint.analys(sint.tree)) {
        sint.print(out);
    }
    else {
        cout << "Error happened\n";
    }

    
    out.close();
    in.close();
    return 0;
}
