#include "Automat.h"
Automat::Automat()
{
    this->TransitTable = vector<vector<int>>(4, vector<int>(256, 3));
    //fill table as our rule (ask author)
    for (int i = 'a'; i <= 'z'; i++) {
        this->TransitTable[0][i] = 1;
        this->TransitTable[1][i] = 1;
        this->TransitTable[2][i] = 3;
    }
    for (int i = 'A'; i <= 'Z'; i++) {
        this->TransitTable[0][i] = 1;
        this->TransitTable[1][i] = 1;
        this->TransitTable[2][i] = 3;
    }
    for (int i = '0'; i <= '9'; i++) {
        this->TransitTable[0][i] = 2;
        this->TransitTable[1][i] = 3;
        this->TransitTable[2][i] = 2;
    }  
}
void distributeByState(int& curState, string& buff, vector<Token>& tokens, vector<string>& keywords) {
    Token buffToken;
    if (curState == 1) {
        buffToken.type = "Id";
        for (string key : keywords) {
            if (buff == key) {
                buffToken.type = "Keyword";
            }
        }
        buffToken.name = buff;
        tokens.push_back(buffToken);
    }
    if (curState == 2) {
        buffToken.type = "Const";
        buffToken.name = buff;
        tokens.push_back(buffToken);
    }
    if (curState == 3) {
        buffToken.type = "Error";
        buffToken.name = buff;
        tokens.push_back(buffToken);
    }
}
bool isOp(vector<Token>& tokens, char c, string& buff, int& curState, vector<string>& keywords, vector<char>& opExpr) {
    for (char op : opExpr) {
        //if c(char) is op we must save token for word befor c and then save c
        if (c == op) {
            Token buffToken;
            //save token for word befor c
            distributeByState(curState, buff, tokens, keywords);
            //save c token
            curState = 0;
            buff = "";
            buffToken.type = "Op";
            buffToken.name = c;
            tokens.push_back(buffToken);
            //also if c is a op we return true else return false
            return true;
        }
    }
    return false;
}
//same as isOp but for delimiters
bool isDelimiter(vector<Token>& tokens, char c, string& buff, int& curState, vector<string>& keywords, vector<char>& delExpr) {
    for (char del : delExpr) {
        //if c(char) is delimiter we must save token for word befor c and then save c
        if (c == del) {
            Token buffToken;
            //save token for word befor c
            distributeByState(curState, buff, tokens, keywords);
            //save c token
            curState = 0;
            buff = "";
            buffToken.type = "Del";
            buffToken.name = c;
            tokens.push_back(buffToken);
            //also if c is a delimiter we return true else return false
            return true;
        }
    }
    return false;
}
vector<Token> Automat::getTokens(string& line)
{
    vector<Token> tokens;
    string buff = "";
    int curState = 0;
    for (int i = 0; i < line.size(); ++i) {
        char c = line[i];
        if (c == '"') {
            string strBuff = "";
            strBuff += '"';
            i++;
            while (line[i] != '"')
            {
                strBuff += line[i];
                i++;
            }
            strBuff += '"';
            Token buffToken;
            buffToken.type = "strConst";
            buffToken.name = strBuff;
            tokens.push_back(buffToken);
            continue;
        }
        //if we meet delimiter char or op char
        if (isOp(tokens, c, buff, curState, this->keywords, this->opExpr)) continue;
        if (isDelimiter(tokens, c, buff, curState, this->keywords, this->delExpr)) continue;
        //if we meet delimiters 
        if (c == '\t' || c == ' ') {
            //we got 3 state pos first for key, second for const and third for error
            distributeByState(curState, buff, tokens, this->keywords);
            curState = 0;
            buff = "";
        }
        //if we dont meet delimiters still read word
        else {
            //change state by cur pos of automat and way by char
            curState = TransitTable[curState][c];
            buff += c;
        }
    }
    //check if line ended but state is not zero
    if (curState != 0) {
        distributeByState(curState, buff, tokens, this->keywords);
    }
    return tokens;
}
