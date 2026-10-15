#include<string.h>
#include "testheader.h"
#define max 100
#define add 5 + 10
#define SQUARE(x) ((x) * (x))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define GET() 10
#define VALUE 100

int main()
{
    int x = add;
    int y = max;
    int x = SQUARE(5);
    int y = MAX(10, 20);
    int z = GET();
    int n = VALUE;

    // Test 1: complete comments
    // remove this line
    printf("start");

    // Test 2: comments after code
    x = 100; // remove this comment
    y = 200; // remove this too

    // Test 3: // inside strings
    printf("hello // world");
    printf("http://example.com");
    printf("abc // xyz");

    // Test 4: /* */ inside strings
    printf("/* keep this */");
    printf("hello /* keep this too */");
    printf("abc /* xyz */ def");

    // Test 5: same-line block comments
    int a = /* remove */ 10;
    int b = 20 /* remove */ + 30;
    int c = 40 + /* remove */ 50;

    // Test 6: multiple block comments
    int p = /* one */ 10; /* two */ p++;
    printf("test"); /* three */ printf("again"); /* four */

    // Test 7: multiline block comment
    /*
        remove this whole comment
        this is another line
        this should also disappear
    */
    printf("after comment");

    // Test 8: multiline comment between code
    int m = 100;
    /*
        middle comment
        should disappear
    */
    int n = 200;

    // Test 9: code before and after comment on surrounding lines
    m = 10;
    /*
        remove this
        comment
    */ n = 20;

    // Test 10: several strings on one line
    printf("one // string"); printf("two /* string */"); printf("three");

    // Test 11: comment-looking strings
    printf("//");
    printf("/*");
    printf("*/");
    printf("///");
    printf("/**/");
    printf("////");

    // Test 12: real comments after strings
    printf("hello // world"); // remove real comment
    printf("/* hello */"); /* remove real comment */
    printf("abc // xyz"); /* remove this */

    // Test 13: empty-looking areas
    printf("before");

    // remove this

    /*
        remove this too
    */

    printf("after");

    // Test 14: final code
    x = 500;
    y = 600;
    printf("x = %d\n", x);
    printf("y = %d\n", y);

    return 0;
}
