#include "lexer.hpp"

namespace lexer {
    static int checkKeyword(std::string keyword) {
        static int len = keywords.size();
        
        for(static int i = 0; i < len; i++) {
            if(keywords[i] == keyword) return i+1;
        }
        return 0;
    }

    static int getToken(void) {
        static int lastChar = ' ';

        while (isspace(lastChar)) lastChar = getchar();

        if(isalpha(lastChar)) {
            IdentStr = lastChar;
            while(isalnum(lastChar = getchar())) IdentStr += lastChar;
            static int pos = checkKeyword(IdentStr);
            
            if(pos != 0) return -pos;
            else return tokIdent;
        }

        if(isdigit(lastChar) || lastChar == '.') {
            std::string numString;
            if(lastChar == '.') isFloat = true;
            do {
                numString += lastChar;
                if(lastChar == '.') isFloat = true;
                lastChar = getchar();
            } while (isdigit(lastChar) || lastChar == '.');
            

            if (isFloat) {
                dVal = strtod(numString.c_str(), 0);
                isFloat = false;
                return tokFloat;
            }
            iVal = strtol(numString.c_str(), NULL, 10);
            return tokInt;
        }


        if(lastChar == '`') {
            do lastChar = getchar(); while (lastChar!=EOF && lastChar != '\n' && lastChar != '\r');
            if (lastChar != EOF) return getToken();
        }

        if(lastChar == EOF) return tokEof;
        if(lastChar == '\n') return tokNewLine;
        if(lastChar == '\t') return tokTab;

        int tChar = lastChar;
        lastChar = getchar();
        return tChar;
    }
}