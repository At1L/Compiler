#include "lexicalAnalyzer.h"

lexicalAnalyzer::lexicalAnalyzer()
{
}
//take string parce it on tokens and add in vector of tokens
void lexicalAnalyzer::addTokens(string& line)
{
	Automat automat;
	vector<ourToken> buffTokens = automat.getTokens(line);
	for (auto t : buffTokens) {
		this->tokens.push_back(t);
	}
}
void lexicalAnalyzer::backPos(ifstream& in, string s)
{
    reverse(s.begin(), s.end());
    
    for (char& c : s) {
        in.putback(c);
    }
}
bool isDel(std::vector<char>& dels, char c) {
	for (char ch : dels) {
		if (ch == c) return true;
	}
	return false;
}
bool isDel(char c) {
    vector<char> sym = { ' ', '\n', '\t', '\0'};
    for (char ch : sym) if (ch == c) return true;
    return false;
}
bool isDCom(char c) {
    vector<char> sym = { ',', ':', ';', '(', ')'};
    for (char ch : sym) if (ch == c) return true;
    return false;
}
bool isOp(char c) {
    vector<char> sym = { '+', '-'};
    for (char ch : sym) if (ch == c) return true;
    return false;
}
string lexicalAnalyzer::curWord(ifstream& fin)
{
    string tmp = "";

    while (true)
    {
        char c = fin.get();
        if (isDel(c))
        {
            if (!tmp.empty())
            {
                fin.unget();
                return tmp;
            }
            else
            {
                continue;
            }
        }
        if (c < 0 && tmp.size() != 0) return tmp;
        else if (c < 0 && tmp.size() == 0) return "";
        if (fin.eof())
        {
            break;
        }

        
        if (isOp(c)) 
        {
            if (!tmp.empty())
            {
                fin.unget();
                return tmp;
            }
            else
            {
                tmp += c;
                return tmp;
            }
        }
        if (isDCom(c))
        {
            if (c == ':' && fin.peek() == '=')
            {
                if (!tmp.empty())
                {
                    fin.unget();
                    return tmp;
                }
                else
                {
                    tmp += c;
                    tmp += fin.get();
                    return tmp;
                }
            }
            else
            {
                if (!tmp.empty())
                {
                    fin.unget();
                    return tmp;
                }
                else
                {
                    tmp += c;
                    return tmp;
                }
            }
        }

        tmp += c;
    }

    return tmp;
}

void lexicalAnalyzer::pushHash(string& str)
{
    Automat autom;
    hash.addToken(autom.getTokens(str)[0]);
}

ourToken lexicalAnalyzer::parse(ifstream& in)
{
	Automat a;
	string buff = curWord(in);
    if (buff == ":=") {
        ourToken ourToken;
        ourToken.name = ":=";
        ourToken.type = "Op";
        return ourToken;
    }
    if (buff.empty()) return ourToken();
    ourToken ourToken = a.getTokens(buff)[0];
	return ourToken;
}
