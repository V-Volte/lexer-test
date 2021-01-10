#include <iostream>
#include <cstdlib>
#include <vector>

#define uniqueptr unique_ptr

namespace lexer {

    static std::string IdentStr;
    static double dVal;
    static long iVal;
    static std::string sVal;
    static char cVal;
    static bool bVal;
    static bool isFloat = false;

    enum Token {
        tokInt = -151,
        tokStr = -152,
        tokBool = -153,
        tokFloat = -154,
        tokChar = -155,

        tokEof = -200,
        tokIdent = -201,
        tokNewLine = -202,
        tokSpace = -203,
        tokTab = -204,    
    };

    static std::vector<std::string> keywords = {"int string char bool float fput fputl fputs putl put puts vget putsl fputsl putnl if else case switch or while for fget fgets putfs fputfs true false xor nor xnor and not"};

    static int checkKeyword(std::string keyword);
    static int getToken(void);

    class ExpressionAST {
        std::string VarType;
        
        public:
            virtual ~ExpressionAST() {}
    };

    class dExpressionAST : public ExpressionAST {
        double Val;

        public:
            dExpressionAST(double Val) : Val(Val) {}
    };

    class iExpressionAST : public ExpressionAST {
        long Val;

        public:
            iExpressionAST(long Val) : Val(Val) {}
    };

    class bExpressionAST : public ExpressionAST {
        bool Val;

        public:
            bExpressionAST(bool Val) : Val(Val) {}
    };

    class cExpressionAST : public ExpressionAST {
        char Val;

        public:
            cExpressionAST(char Val) : Val(Val) {}
    };

    class sExpressionAST : public ExpressionAST {
        std::string Val;

        public:
            sExpressionAST(std::string &Val) : Val(Val) {}
    };

    class VarExpressionAST : public ExpressionAST {
        std::string VarName;

        public:
            VarExpressionAST(const std::string &VarName) : VarName(VarName) {}
    };

    class BinaryExpressionAST : public ExpressionAST {
        std::uniqueptr<ExpressionAST> LHS, RHS;
        char Operator;

        public:
            BinaryExpressionAST(char _Operator, std::uniqueptr<ExpressionAST> LHS, std::uniqueptr<ExpressionAST> RHS) : Operator(_Operator), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
    };

    class CallExpressionAST : public ExpressionAST {
        std::string Function;
        std::vector<std::uniqueptr<ExpressionAST>> Args;

        public:
            CallExpressionAST(std::string Function, std::vector<std::uniqueptr<ExpressionAST>> &Args) : Function(Function), Args(std::move(Args)) {} 
    };

    class FunctionPrototypeAST {
        std::string FunctionName;
        std::vector<std::string> Args;

        public:
            FunctionPrototypeAST(std::string &_FunctionName, std::vector<std::string> Args) : FunctionName(_FunctionName), Args(std::move(Args)) {}
    };

    class FunctionAST {
        std::uniqueptr<FunctionPrototypeAST> Prototype;
        std::uniqueptr<ExpressionAST> Body;

        public:
            FunctionAST(std::uniqueptr<FunctionPrototypeAST> Prototype, std::uniqueptr<ExpressionAST> Body) : Prototype(std::move(Prototype)), Body(std::move(Body)) {}
    };

    
}
