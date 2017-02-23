%option noyywrap

%%

std::regex\(\".*\"\) { for(int i=0; i<yyleng; ++i) if(yytext[i]!=' ') printf("%c", yytext[i]); }

%%

int main()
{
    yylex();
}

