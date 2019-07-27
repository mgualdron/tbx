// -------------------------------------------------------------------------
// Program Name:    tbx.c
//
// Purpose:         To display a delimited file in a text-formatted table at 
//                  the command-line.
//
// -------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "util/dbg.h"
#include <csv.h>
#include <fort.h>

static const char *program_name = "tbx";
static char *delim_arg = "\t";
static char *delim = "\t";
static char delim_csv = CSV_COMMA;
static char *quote_arg = NULL;
static char quote = CSV_QUOTE;
static int ignore_this = 0;

// The callbacks for CSV processing:
void cb1 (void *s, size_t len, void *data);
void cb2 (int c, void *data);

static void try_help (int status) {
    printf("Try '%s --help' for more information.\n", program_name);
    exit(status);
}


static void usage (int status) {
    if (status != 0) {
        try_help(status);
    }
    else {
      printf ("\
Usage: %s [OPTION]... [FILE]...\n\
", program_name);

      printf ("\
Display a delimited file in tabular form.\n\
More than one FILE can be specified.\n\
");

      printf ("\
\n\
  -d, --delimiter=DELIM  the delimiting character for the input FILE(s)\n\
      --csv              parse CSV files\n\
  -Q, --csv-quote        CSV quoting character (ignored unless --csv)\n\
");
    }

    exit (status);
}


static struct option long_options[] = {
    {"csv",       no_argument,       0, 'C'},
    {"delimiter", required_argument, 0, 'd'},
    {"csv-quote", required_argument, 0, 'Q'},
    {"help",      no_argument,       0, 'h'},
    {0, 0, 0, 0}
};


/* Remove trailing CR/LF */
void chomp(char *s) {
    while(*s && *s != '\n' && *s != '\r') s++;
 
    *s = 0;
}


/* Process a regular delimited file */
int print_table_from_file(char *filename, ft_table_t *table)
{
    char *line = NULL;
    FILE *fp = NULL;
    size_t len = 0;         // allocated size for line
    ssize_t bytes_read = 0; // num of chars read

    if (filename[0] == '-') {
        fp = stdin;
    }
    else {
        fp = fopen(filename, "rb");
    }

    check(fp != NULL, "Error opening file: %s.", filename);

    while ((bytes_read = getline(&line, &len, fp)) != -1) {

        chomp(line);

        char *p = strtok (line, delim);
        while (p != NULL)
        {
            ft_write(table, p);
            p = strtok (NULL, delim);
        }
        ft_ln(table);

    }

    printf("%s\n", ft_to_string(table));

    free(line);
    fclose(fp);

    return 0;

error:
    return -1;
}

// Callback 1 for CSV support, called whenever a field is processed:
void cb1 (void *s, size_t len, void *data)
{
    check( ft_write((ft_table_t *)data, (char *)s) == 0, "Error writing to text table." );
    ignore_this = len;

    return;

error:
    exit(1);
}

// Callback 2 for CSV support, called whenever a record is processed:
void cb2 (int c, void *data)
{
    ft_ln((ft_table_t *)data);
    ignore_this = c;
}


/* Process a CSV file */
int print_table_from_csv_file(char *filename, ft_table_t *table)
{
    struct csv_parser p;
    char buf[1024];
    FILE *fp = NULL;
    size_t bytes_read = 0; // num of chars read

    if (filename[0] == '-') {
        fp = stdin;
    }
    else {
        fp = fopen(filename, "rb");
    }

    check(fp != NULL, "Error opening file: %s.", filename);
    check(csv_init(&p, CSV_APPEND_NULL) == 0, "Error initializing CSV parser.");

    csv_set_delim(&p, delim_csv);
    csv_set_quote(&p, quote);

    while ((bytes_read=fread(buf, 1, 1024, fp)) > 0) {
        check(csv_parse(&p, buf, bytes_read, cb1, cb2, table) == bytes_read, "Error while parsing file: %s", csv_strerror(csv_error(&p)));
    }

    check(csv_fini(&p, cb1, cb2, table) == 0, "Error finishing CSV processing.");

    printf("%s\n", ft_to_string(table));

    csv_free(&p);
    fclose(fp);

    return 0;

error:
    return -1;
}


/* The main function */
int main (int argc, char *argv[])
{
    int c;
    int csv_mode = 0;
    int delim_arg_flag = 0;

    while (1) {

        // getopt_long stores the option index here.
        int option_index = 0;

        c = getopt_long (argc, argv, "hd:Q:", long_options, &option_index);

        // Detect the end of the options.
        if (c == -1) break;

        switch (c) {
            case 0:
                // If this option set a flag, do nothing else now.
                break;

            case 'd':
                debug("option -d with value `%s'", optarg);
                delim_arg = optarg;
                delim_arg_flag = 1;
                break;

            case 'h':
                debug("option -h");
                usage(0);
                break;

            case 'C':
                debug("option -C");
                csv_mode = 1;
                break;

            case 'Q':
                debug("option -Q");
                quote_arg = optarg;
                //check(strlen(quote_arg) == 1, "ERROR: CSV quoting character must be exactly one byte long");
                //quote = quote_arg[0];
                break;

            case ':':   /* missing option argument */
                fprintf(stderr, "%s: option '-%c' requires an argument\n",
                        argv[0], optopt);
                break;

            // getopt_long already printed an error message.
            case '?':
                usage(1);
                break;

            default:
                usage(1);
        }
    }

    if (csv_mode && delim_arg_flag) {
        check(strlen(delim_arg) == 1, "ERROR: CSV delimiter must be exactly one byte long");
        delim_csv = delim_arg[0];
    }
    else if (!csv_mode && delim_arg_flag) {
        delim = delim_arg;
    }

    int j = optind;  // A copy of optind (the number of options at the command-line),
                     // which is not the same as argc, as that counts ALL
                     // arguments.  (optind <= argc).

    // Process any remaining command line arguments (input files).
    do {

        char *filename = NULL;

        /* The table to be displayed */
        ft_table_t *table = ft_create_table();

        /* Set "header" type for the first row */
        ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);

        /* Change border style */
        ft_set_border_style(table, FT_NICE_STYLE);

        // Assume STDIN if no additional arguments, else loop through them:
        if (optind == argc) {
            filename = "-";
        }
        else if (optind < argc) {
            filename = argv[j];
        }
        else if (optind > argc) {
            break;
        }
        debug("The input filename is %s\n", filename);

        // Display the file:
        if (csv_mode) {
            check(print_table_from_csv_file(filename, table) == 0, "Error counting CSV file: %s", filename);
        }
        else {
            check(print_table_from_file(filename, table) == 0, "Error processing file: %s", filename);
        }

        ft_destroy_table(table);

        j++;

    } while (j < argc);

    return 0;

error:
    return -1;
}
