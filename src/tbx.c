// -------------------------------------------------------------------------
// Program Name:    tbx.c
//
// Purpose:         To display a delimited file in a text-formatted table at 
//                  the command-line.
//
// -------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <getopt.h>
#include <wchar.h>
#include <util/dbg.h>
#include <util/darray.h>
#include <csv.h>
#include <fort.h>
#define INT_SIZE 16

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

// Callbacks for loading steps (in case transposing is done):
void cb1_x (void *s, size_t len, void *data);
void cb2_x (int c, void *data);

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
  -C  --csv              parse CSV files\n\
  -Q, --csv-quote        CSV quoting character (ignored unless --csv)\n\
  -x, --transpose        transpose the output\n\
");
    }

    exit (status);
}


static struct option long_options[] = {
    {"csv",       no_argument,       0, 'C'},
    {"delimiter", required_argument, 0, 'd'},
    {"csv-quote", required_argument, 0, 'Q'},
    {"transpose", no_argument,       0, 'x'},
    {"help",      no_argument,       0, 'h'},
    {0, 0, 0, 0}
};


/* Remove trailing CR/LF */
void chomp(char *s) {
    while(*s && *s != '\n' && *s != '\r') s++;
    *s = 0;
}


/* Print an array of arrays in table form */
void print_table_from_matrix(DArray *master)
{

    int i, j;
    DArray *record;
    setlocale(LC_CTYPE, "");  // Avoid printing blank

    /* The table to be displayed */
    ft_table_t *table = ft_create_table();

    /* Set "header" type for the first row */
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);

    /* Change border style */
    ft_set_border_style(table, FT_NICE_STYLE);

    for (i = 0; i < DArray_count(master); i++) {

        record = (DArray *)(master->contents[i]);

        if ( DArray_end(record) > 0 ) {

            for (j = 0; j < DArray_count(record); j++) {
                char *p = (char *)(record->contents[j]);
                wchar_t w[strlen(p)+1];              /* VLA */
                swprintf(w, strlen(p)+1, L"%s", p);  /* Convert char to wchar_t */
                ft_wwrite(table, w);                 /* Put w on the heap */
            }

            ft_ln(table);
        }

    }

    printf("%ls\n", ft_to_wstring(table));
    ft_destroy_table(table);
}

/* Destroy 2-D arrays */
void master_destroy ( DArray *master )
{
    int i;

    /* Destroy the individual record arrays */
    for (i = 0; i < DArray_count(master); i++) {
        DArray *record = DArray_get(master, i);
        DArray_destroy(record);
    }

    /* Destroy the master array */
    DArray_destroy(master);
}

/* Find the max number of columns in any record of master */
int DArray_maxcols( DArray *master )
{
    int i;
    int max = 0;
    DArray *record;

    for (i = 0; i < DArray_count(master); i++) {
        record = (DArray *)(master->contents[i]);
        if ( DArray_count(record) > max ) {
            max = DArray_count(record);
        }
    }

    return max;
}

/* Transpose the 2-D array and return another 2-D array */
DArray *transpose( DArray *master )
{
    int i, j;
    DArray *xpose  = DArray_create(sizeof(DArray *), 10);
    DArray *record = DArray_create(sizeof(char *), 10);
    DArray *xhead  = DArray_create(sizeof(char *), 10);
    char *copy = NULL;
    char *blank = strdup("");  /* a heap-allocated empty string */

    copy = strdup("COL");
    DArray_push(xhead, copy);
    copy = strdup("FIELD NAMES");
    DArray_push(xhead, copy);

    /* The Header */
    for (i = 0; i < DArray_count(master) - 1; i++) {

        record = (DArray *)(master->contents[i + 1]);

        if ( DArray_end(record) > 0 ) {
            char val[INT_SIZE + 7];
            snprintf(val, INT_SIZE + 7, "RECORD %d", i + 1);
            char *copy = strdup(val);
            DArray_push(xhead, copy);
        }
    }

    DArray_push(xpose, xhead);

    for (j = 0; j < DArray_maxcols(master); j++) {

        DArray *xrec = DArray_create(sizeof(char *), 10);

        for (i = 0; i < DArray_count(master); i++) {

            record = (DArray *)(master->contents[i]);

            if ( DArray_end(record) > 0 ) {

                if ( i == 0 ) {
                    char val[INT_SIZE];
                    snprintf(val, INT_SIZE, "%d", j + 1);
                    char *copy = strdup(val);
                    DArray_push(xrec, copy);
                }

                if ( j >= DArray_count(record) ) {
                    DArray_push(xrec, blank);
                }
                else {
                    DArray_push(xrec, (char *)(record->contents[j]));
                }

            }

        }
        
        DArray_push(xpose, xrec);
    }

    return xpose;
}

/* Simply print the 2-D array */
void tb_print( DArray *master )
{
    int i, j, col;
    DArray *record;
    setlocale(LC_CTYPE, "");  // Avoid printing blank

    for (i = 0; i < DArray_count(master); i++) {

        record = (DArray *)(master->contents[i]);
        debug("row %d: ", i + 1);

        col = 0;
        for (j = 0; j < DArray_count(record); j++) {
            col++;
            if ( j > 0 ) {
                printf("\t");
            }
            //printf("col %d: %s", col, (char *)(record->contents[j]));
            printf("%s", (char *)(record->contents[j]));
        }
        printf("\n");

    }
}

/* Process a regular delimited file */
int file_load(char *filename, DArray *master)
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

        // DArray *record = DArray_new(master);

        DArray *record = DArray_create(sizeof(char *), 10);

        char *p = strsep (&line, delim);
        while (p != NULL)
        {
            char *cell = (char *)malloc(sizeof(char) * (strlen(p) + 1));
            strcpy(cell, p);
            DArray_push(record, cell);
            debug("Processing >>%s<<\n", cell);
            p = strsep (&line, delim);
        }
        DArray_push(master, record);
        debug("Loaded record: %d\n", DArray_count(master));

    }

    debug("Read a total of %d records\n", DArray_count(master));

    free(line);
    fclose(fp);

    return 0;

error:
    return -1;
}

// Callback 1 for CSV support, called whenever a field is processed:
void cb1_x (void *s, size_t len, void *data)
{
    DArray *master = (DArray *)data;
    int end = DArray_end(master) - 1;

    if (end == -1) {
        DArray *record = DArray_create(sizeof(char *), 10);
        DArray_push(master, record);
        end = DArray_end(master) - 1;
    }

    DArray *record = (DArray *)(master->contents[end]);

    char *copy = (char *)malloc(sizeof(char) * (len + 1));
    strcpy(copy, s);
    DArray_push(record, copy);
}

// Callback 2 for CSV support, called whenever a record is processed:
void cb2_x (int c, void *data)
{
    DArray *record = DArray_create(sizeof(char *), 10);
    DArray_push((DArray *)data, record);
    ignore_this = c;
}

/* Process a CSV file */
int csv_file_load(char *filename, DArray *master)
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

    debug("ready to read some CSV data");

    while ((bytes_read=fread(buf, 1, 1024, fp)) > 0) {
        check(csv_parse(&p, buf, bytes_read, cb1_x, cb2_x, master) == bytes_read
                , "Error while parsing file: %s", csv_strerror(csv_error(&p)));
    }

    check(csv_fini(&p, cb1, cb2, master) == 0, "Error finishing CSV processing.");

    csv_free(&p);
    fclose(fp);

    return 0;

error:
    return -1;
}

// Callback 1 for CSV support, called whenever a field is processed:
void cb1 (void *s, size_t len, void *data)
{
    wchar_t w[strlen((char *)s)+1];                       /* VLA */
    swprintf(w, strlen((char *)s)+1, L"%s", (char *)s);   /* Convert char to wchar_t */

    check( ft_wwrite((ft_table_t *)data, w) == 0, "Error writing to text table." );
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
    size_t bytes_read = 0;    // num of chars read
    setlocale(LC_CTYPE, "");  // Avoid printing blank

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

    printf("%ls\n", ft_to_wstring(table));

    csv_free(&p);
    fclose(fp);

    return 0;

error:
    return -1;
}

/* Process a regular delimited file */
int print_table_from_file(char *filename, ft_table_t *table)
{
    char *line = NULL;
    FILE *fp = NULL;
    size_t len = 0;           // allocated size for line
    ssize_t bytes_read = 0;   // num of chars read
    setlocale(LC_CTYPE, "");  // Avoid printing blank

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
            wchar_t w[strlen(p)+1];              /* VLA */
            swprintf(w, strlen(p)+1, L"%s", p);  /* Convert char to wchar_t */
            ft_wwrite(table, w);                 /* Put w in the table */
            p = strtok (NULL, delim);
        }
        ft_ln(table);

    }

    printf("%ls\n", ft_to_wstring(table));

    free(line);
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
    int xpose_arg      = 0;

    while (1) {

        // getopt_long stores the option index here.
        int option_index = 0;

        c = getopt_long (argc, argv, "hxCd:Q:", long_options, &option_index);

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

            case 'x':
                debug("option -x");
                xpose_arg = 1;
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


        // If we are transposing:
        if (xpose_arg) {
            DArray *master = DArray_create(sizeof(DArray *), 10);
            if (csv_mode) {
                debug("Selected CSV mode");
                check(csv_file_load(filename, master) == 0, "Error loading csv file: %s", filename);
            }
            else {
                debug("Selected DELIM mode");
                check(file_load(filename, master) == 0, "Error loading delimited file: %s", filename);
            }

            DArray *xpose = transpose(master);
            check( xpose != NULL, "Error transposing file: %s", filename);

            print_table_from_matrix(xpose);

            master_destroy(master);
            master_destroy(xpose);
        }
        // Otherwise, don't load, go from file to table:
        else {
            ft_table_t *table = ft_create_table();
            ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
            ft_set_border_style(table, FT_NICE_STYLE);

            if (csv_mode) {
                check(print_table_from_csv_file(filename, table) == 0, "Error counting CSV file: %s", filename);
            }
            else {
                check(print_table_from_file(filename, table) == 0, "Error processing file: %s", filename);
            }

            ft_destroy_table(table);
        }


        j++;

    } while (j < argc);

    return 0;

error:
    return -1;
}
