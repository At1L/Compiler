#include <iostream>
#include <fstream>
#include <vector>
#include "lexicalAnalyzer.h"
#include "syntaxAnalyzer.h"
#include "semantica.h"
#include "semantica.h"

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    syntaxAnalyzer sint("input.txt");
    semantica semant;
    if (sint.analys(sint.tree)) {
        sint.print(out);
        semant.Procedure(sint.tree);

    }
    else {
        cout << "Error happened\n";
    }

    
    out.close();
    in.close();
    return 0;
}
