#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

char look;

void init();

void nextChar();
void error(char *fmt, ...);

void fatal(char *fmt, ...);
void expected(char *fmt, ...);

void match(char c);
char getName();

char getNum();
void emit(char *fmt, ...);

void other();
void program();
void block();

                                /* PROGRAMA PRINCIPAL */
int main()
{
        init();

        program();

        return 0;
}

                                /* inicialização do compilador */
void init()

{
        nextChar();
}

                                /* lê próximo caracter da entrada */
void nextChar()

{
        look = getchar();
}

                                /* exibe uma mensagem de erro formatada */

void error(char *fmt, ...)
{
        va_list args;

        fputs("Error: ", stderr);

        va_start(args, fmt);

        vfprintf(stderr, fmt, args);
        va_end(args);
        
        fputc('\n', stderr);
}

        /* exibe uma mensagem de erro formatada e sai */

void fatal(char *fmt, ...)
{
        va_list args;
        
        fputs("Error: ", stderr);
        
        va_start(args, fmt);
        
        vfprintf(stderr, fmt, args);
        va_end(args);
        
        fputc('\n', stderr);
        
        exit(1);
        
}

        /* alerta sobre alguma entrada esperada */
void expected(char *fmt, ...)
{

        va_list args;
        
        fputs("Error: ", stderr);
        
        va_start(args, fmt);
        vfprintf(stderr, fmt, args);
        
        va_end(args);
        
        fputs(" expected!\n", stderr);
        
        exit(1);
}

        /* verifica se entrada combina com o esperado */
void match(char c)

{
        if (look != c)
                expected("'%c'", c);
        
        nextChar();
}

        /* recebe o nome de um identificador */
char getName()

{
        char name;
        
        if (!isalpha(look))

                expected("Name");
        name = toupper(look);
        
        nextChar();
        
        return name;
}

        /* recebe um número inteiro */

char getNum()
{
        char num;
        
        if (!isdigit(look))

                expected("Integer");
        num = look;
        nextChar();
        
        return num;
}

        /* emite uma instrução seguida por uma nova linha */
void emit(char *fmt, ...)

{
        va_list args;
        
        putchar('\t');
        
        va_start(args, fmt);
        vprintf(fmt, args);
        
        va_end(args);
        
        putchar('\n');
        
}

/* reconhece e traduz um comando qualquer */
void other()

{
        emit("# %c", getName());
}

 /* analisa e traduz um programa completo */
void program()

{
        block();
        if (look != 'e')

                expected("End");
        emit("END");
}

/* analisa e traduz um bloco de comandos */
void block()
{
        while (look != 'e') {

                other();
        }
}