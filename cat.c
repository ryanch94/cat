#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char const *version = "0.0.1";

static bool show_help = false;
static bool number = false;
static bool show_ver = false;
static bool show_ends = false;
static bool show_tabs = false;
static bool number_nonblank = false;
static bool show_nonprinting = false;
static int cur_line = 1;
static char* input_file_name;

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


    if (number || number_nonblank)
        print_next_line_no();

    while (c != EOF)
    {
        unsigned char ch = (unsigned char)c;

        if (ch == '\n' && show_ends)
            printf("$");

        if (ch == '\t' && show_tabs)
        {
            printf("^");
            ch = 'I';
        }

        if (show_nonprinting)
        {
            if (ch >= 32)
            {
                if (ch == 127)
                    printf("^?");
                else if (ch > 127)
                {
                    printf("M-");
                    if (ch >= 128 + 32)
                    {
                        if (ch < 128 + 127)
                            printf("%c", ch - 128);
                        else
                        {
                            printf("^?");
                        }
                    }
                    else
                    {
                        printf("^%c", ch - 128 + 64);
                    }
                }
                else
                    printf("%c", ch);
            }
            else if (ch == '\t' && !show_tabs)
                printf("%c", ch);
            else if (ch == '\n')
                printf("%c", ch);
            else
                printf("^%c", ch + 64);
        }
        else
            printf("%c", ch);
            
        c = fgetc(fd);
        if ((number || number_nonblank) && ch == '\n' && c != EOF)
        {
            if (number_nonblank && c == '\n') {}
            else
                print_next_line_no();
        }
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
        else if (strcmp(arg, "-b") == 0 || strcmp(arg, "--number-nonblank") == 0)
            number_nonblank = true;
        else if (strcmp(arg, "-v") == 0 || strcmp(arg, "--show-nonprinting") == 0)
            show_nonprinting = true;
        else if (strcmp(arg, "-A") == 0 || strcmp(arg, "--show-all") == 0)
        {
            show_nonprinting = true;
            show_ends = true;
            show_tabs = true;
        }
        else if (strcmp(arg, "-e") == 0)
        {
            show_nonprinting = true;
            show_ends = true;
        }
        else if (strcmp(arg, "-t") == 0)
        {
            show_nonprinting = true;
            show_tabs = true;
        }
        else // assume a file name
            input_file_name = arg;
    }
}

void print_help()
{
    printf("Usage: cat [OPTION]... [FILE]...\n\
Concatenate FILE(s) to standard output.\n\n\
With no FILE, or when FILE is -, read standard input. // TODO\n\n\
-A, --show-all           equivalent to -vET\n\
-b, --number-nonblank    number nonempty outputm lines, overrides -n\n\
-e                       equivalent to -vE\n\
-E, --show-ends          display $ at end of each line\n\
-n, --number             number all output lines\n\
-s, --squeeze-blank      suppress repeated empty output lines // TODO\n\
-t                       equivalent to -vT\n\
-T, --show-tabs          display TAB characters as ^I\n\
-u                       (ignored)\n\
-v, --show-nonprinting   use ^ and M- notation, except for LFD and TAB\n\
--help        display this help and exit\n\
--version     output version information and exit\n");
}

int main(int argc, char** argv)
{
    parse_args(argc, argv);

    if (show_help)
        print_help();
    else if (show_ver)
        print_version_info();
    else
        read_from_file(input_file_name);

    return 0;
}
