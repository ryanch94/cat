#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char const *version = "0.0.1";

static bool show_help = false;
static bool number = false;
static bool show_ver = false;
static bool show_ends = false;
static bool show_tabs = false;
static int cur_line = 1;

void print_version_info()
{
    printf("%s\n", version);
}

void print_next_line_no()
{
    printf("%6d  ", cur_line++);
}

void read_from_file(char *input_file)
{
    FILE *fd = fopen(input_file, "r");
    int c = fgetc(fd);


    if (number)
        print_next_line_no();

    while (c != EOF)
    {
        char ch = (char)c;

        if (ch == '\n' && show_ends)
            printf("$");

        if (ch == '\t' && show_tabs)
        {
            printf("^");
            ch = 'I';
        }

        printf("%c", ch);
        c = fgetc(fd);
        if (number && ch == '\n' && c != EOF)
            print_next_line_no();
    }

    fclose(fd);
}

void parse_args(int argc, char **argv)
{
    if (argc <= 1)
        return;

    for (int i = 1; i < argc; i++)
    {
        char *arg = argv[i];
        if (strcmp(arg, "--help") == 0)
            show_help = true;
        else if (strcmp(arg, "-n") == 0 || strcmp(arg, "--number") == 0)
            number = true;
        else if (strcmp(arg, "--version") == 0)
            show_ver = true;
        else if (strcmp(arg, "-E") == 0 || strcmp(arg, "--show-ends") == 0)
            show_ends = true;
        else if (strcmp(arg, "-T") == 0 || strcmp(arg, "--show-tabs") == 0)
            show_tabs = true;
    }
}

void print_help()
{
    printf("Usage: cat [OPTION]... [FILE]...\n\
Concatenate FILE(s) to standard output.\n\n\
With no FILE, or when FILE is -, read standard input. // TODO\n\n\
-A, --show-all           equivalent to -vET // TODO\n\
-b, --number-nonblank    number nonempty outputm lines, overrides -n // TODO\n\
-e                       equivalent to -vE // TODO\n\
-E, --show-ends          display $ at end of each line\n\
-n, --number             number all output lines\n\
-s, --squeeze-blank      suppress repeated empty output lines // TODO\n\
-t                       equivalent to -vT // TODO\n\
-T, --show-tabs          display TAB characters as ^I\n\
-u                       (ignored)\n\
-v, --show-nonprinting   use ^ and M- notation, except for LFD and TAB // TODO\n\
--help        display this help and exit\n\
--version     output version information and exit // TODO\n");
}

int main(int argc, char **argv)
{
    char *input_file = argv[1];
    parse_args(argc, argv);

    if (show_help)
        print_help();
    else if (show_ver)
        print_version_info();
    else
        read_from_file(input_file);

    return 0;
}
