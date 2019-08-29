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
static int just_pushed_record = 0;
static DArray *current_record = NULL;
static int delim_len  = 0;
static int line_num   = 0;
static int full_mode  = -1;
static int line_arg   = 1;
static int row_arg    = 1;
static int header_arg = 1;

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
  -l, --from-line=NUM    process starting from this line number\n\
  -r, --row-number=NUM   process this number of rows starting at -l\n\
  -H, --header           process the first line in the file (header)\n\
  -A, --add-header       file has no header, so build a generic one (col1  col2  ...)\n\
  -F, --full             process the whole file (default if not transposing)\n\
  -h, --help             this help\n\
");
    }

    exit (status);
}


static struct option long_options[] = {
    {"csv"       , no_argument,       0, 'C'},
    {"delimiter" , required_argument, 0, 'd'},
    {"csv-quote" , required_argument, 0, 'Q'},
    {"transpose" , no_argument,       0, 'x'},
    {"from-line" , required_argument, 0, 'l'},
    {"rows"      , required_argument, 0, 'r'},
    {"add-header", no_argument,       0, 'A'},
    {"header"    , no_argument,       0, 'H'},
    {"full"      , no_argument,       0, 'F'},
    {"help"      , no_argument,       0, 'h'},
    {0, 0, 0, 0}
};

/* Remove trailing CR/LF */
void chomp(char *s) {
    while(*s && *s != '\n' && *s != '\r') s++;
    *s = 0;
}


/* Print an array of arrays in table form */
void print_table_from_matrix(DArray *matrix)
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

    for (i = 0; i < DArray_count(matrix); i++) {

        record = (DArray *)(matrix->contents[i]);

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
void master_destroy ( DArray *matrix )
{
    int i;

    /* Destroy the individual record arrays */
    for (i = 0; i < DArray_count(matrix); i++) {
        DArray *record = DArray_get(matrix, i);
        DArray_destroy(record);
    }

    /* Destroy the matrix array */
    DArray_destroy(matrix);
}

/* Find the max number of columns in any record of matrix */
int DArray_maxcols( DArray *matrix )
{
    int i;
    int max = 0;
    DArray *record;

    for (i = 0; i < DArray_count(matrix); i++) {
        record = (DArray *)(matrix->contents[i]);
        if ( DArray_count(record) > max ) {
            max = DArray_count(record);
        }
    }

    return max;
}

/* Transpose the 2-D array and return another 2-D array */
DArray *transpose( DArray *matrix )
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
    for (i = 0; i < DArray_count(matrix) - 1; i++) {

        record = (DArray *)(matrix->contents[i + 1]);

        if ( DArray_end(record) > 0 ) {
            char val[INT_SIZE + 7];
            snprintf(val, INT_SIZE + 7, "RECORD %d", i + 1);
            char *copy = strndup(val, INT_SIZE + 7);
            DArray_push(xhead, copy);
        }
    }

    DArray_push(xpose, xhead);

    for (j = 0; j < DArray_maxcols(matrix); j++) {

        DArray *xrec = DArray_create(sizeof(char *), 10);

        for (i = 0; i < DArray_count(matrix); i++) {

            record = (DArray *)(matrix->contents[i]);

            if ( DArray_end(record) > 0 ) {

                if ( i == 0 ) {
                    char val[INT_SIZE];
                    snprintf(val, INT_SIZE, "%d", j + 1);
                    char *copy = strndup(val, INT_SIZE);
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
void tb_print( DArray *matrix )
{
    int i, j, col;
    DArray *record;
    setlocale(LC_CTYPE, "");  // Avoid printing blank

    for (i = 0; i < DArray_count(matrix); i++) {

        record = (DArray *)(matrix->contents[i]);
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
int file_load(char *filename, DArray *matrix)
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

        DArray *record = DArray_create(sizeof(char *), 10);

        char *p = strsep (&line, delim);
        while (p != NULL)
        {
            char *cell = strdup(p);
            DArray_push(record, cell);
            debug("Processing >>%s<<\n", cell);
            p = strsep (&line, delim);
        }
        DArray_push(matrix, record);
        debug("Loaded record: %d\n", DArray_count(matrix));

    }

    debug("Read a total of %d records\n", DArray_count(matrix));

    if ( line != NULL )
        free(line);
    fclose(fp);

    return 0;

error:
    return -1;
}

/* Process a regular delimited file with multi-char delims*/
int file_load_multi(char *filename, DArray *matrix)
{
    char *line = NULL;
    char *orig_line = NULL;
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

        orig_line = line;
        chomp(line);

        DArray *record = DArray_create(sizeof(char *), 10);

        // Search for tokens using strstr()
        char *p = strstr(line, delim);
        while ( p != NULL )
        {
            if (p) 
              *p = '\0';

            char *cell = strdup(line);
            DArray_push(record, cell);
            debug("Processing >>%s<<\n", cell);

            line = p + delim_len;
            p = strstr(line, delim);
        }
        // do one more (past the last delimiter):
        char *cell = strdup(line);
        DArray_push(record, cell);
        debug("Processing >>%s<<\n", cell);

        // Now put the whole record on the matrix array
        DArray_push(matrix, record);
        debug("Loaded record: %d\n", DArray_count(matrix));
        
        if ( orig_line != NULL )
            free(orig_line);
        line = NULL;
    }

    debug("Read a total of %d records\n", DArray_count(matrix));

    fclose(fp);

    return 0;

error:
    return -1;
}

// Callback 1 for CSV support, called whenever a field is processed:
void cb1_x (void *s, size_t len, void *data)
{
    DArray *matrix = (DArray *)data;
    int last = DArray_end(matrix) - 1;

    if ( (last == -1 && current_record == NULL) || just_pushed_record ) {
        current_record = DArray_create(sizeof(char *), 10);
        just_pushed_record = 0;
    }

    char *field = strndup(s, len);
    DArray_push(current_record, field);
}

// Callback 2 for CSV support, called whenever a record is processed:
void cb2_x (int c, void *data)
{
    DArray_push((DArray *)data, current_record);
    just_pushed_record = 1;
    current_record = NULL;
    ignore_this = c;
}

/* Load a CSV file into a dynamic matrix */
int file_load_csv(char *filename, DArray *matrix)
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
        check(csv_parse(&p, buf, bytes_read, cb1_x, cb2_x, matrix) == bytes_read
                , "Error while parsing file: %s", csv_strerror(csv_error(&p)));
    }

    check(csv_fini(&p, cb1, cb2, matrix) == 0, "Error finishing CSV processing.");

    csv_free(&p);
    fclose(fp);

    return 0;

error:
    return -1;
}

// Callback 1 for CSV support, called whenever a field is processed:
void cb1 (void *s, size_t len, void *data)
{
    if ( full_mode || ((line_num >= line_arg) && (line_num <= line_arg + row_arg - 1)) ) {
        wchar_t w[len + 1];                       /* VLA */
        swprintf(w, len + 1, L"%s", (char *)s);   /* Convert char to wchar_t */
        check( ft_wwrite((ft_table_t *)data, w) == 0, "Error writing to text table." );
    }

    return;

error:
    exit(1);
}

// Callback 2 for CSV support, called whenever a record is processed:
void cb2 (int c, void *data)
{
    line_num++;
    if ( full_mode || ((line_num >= line_arg) && (line_num <= line_arg + row_arg - 1)) ) {
        ft_ln((ft_table_t *)data);
    }
    ignore_this = c;
}


/* Process a CSV file */
int print_table_from_file_csv(char *filename, ft_table_t *table)
{
    struct csv_parser p;
    char buf[1024];
    FILE *fp = NULL;
    size_t bytes_read = 0;    // num of chars read
    setlocale(LC_CTYPE, "");  // Avoid printing blank

    line_num = 1;   // Start at 1 since cb1 is called before cb2.

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

        /*
        if ( full_mode == 0 && line_num > line_arg + row_arg - 1 ) {
            break;
        }
        */
    }

    if ( full_mode ) {
        check(csv_fini(&p, cb1, cb2, table) == 0, "Error finishing CSV processing.");
    }

    printf("%ls\n", ft_to_wstring(table));

    csv_free(&p);
    fclose(fp);

    return 0;

error:
    return -1;
}

/* Process a regular delimited file (single-char delimiter) */
int print_table_from_file(char *filename, ft_table_t *table)
{
    char *line = NULL;
    FILE *fp = NULL;
    size_t len = 0;           // allocated size for line
    ssize_t bytes_read = 0;   // num of chars read
    setlocale(LC_CTYPE, "");  // Avoid printing blank

    line_num = 0;

    if (filename[0] == '-') {
        fp = stdin;
    }
    else {
        fp = fopen(filename, "rb");
    }

    check(fp != NULL, "Error opening file: %s.", filename);

    while ((bytes_read = getline(&line, &len, fp)) != -1) {

        line_num++;
        chomp(line);

        debug("line=%d, full=%d, min=%d, max=%d", line_num, full_mode, line_arg, line_arg + row_arg - 1);

        if ( full_mode || ((line_num >= line_arg) && (line_num <= line_arg + row_arg - 1)) ) {

            char *p = strsep (&line, delim);
            while (p != NULL)
            {
                wchar_t w[strlen(p)+1];              /* VLA */
                swprintf(w, strlen(p)+1, L"%s", p);  /* Convert char to wchar_t */
                ft_wwrite(table, w);                 /* Put w on the heap */
                p = strsep (&line, delim);
            }

            ft_ln(table);

        }
        else if ( line_num > line_arg + row_arg - 1 ) {
            break;
        }

    }

    printf("%ls\n", ft_to_wstring(table));

    if ( line != NULL )
        free(line);
    fclose(fp);

    return 0;

error:
    return -1;
}

/* Process a regular delimited file (multi-char delimiter) */
int print_table_from_file_multi(char *filename, ft_table_t *table)
{
    char *line = NULL;
    FILE *fp = NULL;
    size_t len = 0;           // allocated size for line
    ssize_t bytes_read = 0;   // num of chars read
    setlocale(LC_CTYPE, "");  // Avoid printing blank

    line_num = 0;

    if (filename[0] == '-') {
        fp = stdin;
    }
    else {
        fp = fopen(filename, "rb");
    }

    check(fp != NULL, "Error opening file: %s.", filename);

    while ((bytes_read = getline(&line, &len, fp)) != -1) {

        line_num++;
        chomp(line);

        if ( full_mode || ((line_num >= line_arg) && (line_num <= line_arg + row_arg - 1)) ) {

            // Search for tokens using strstr()
            char *p = strstr(line, delim);
            while ( p != NULL )
            {
                if (p) 
                  *p = '\0';

                debug("TOKEN: %s", line);
                wchar_t w[strlen(line)+1];                 /* VLA */
                swprintf(w, strlen(line)+1, L"%s", line);  /* Convert char to wchar_t */
                ft_wwrite(table, w);                       /* Put w on the heap */

                line = p + delim_len;
                p = strstr(line, delim);
            }
            // do one more (past the last delimiter):
            debug("TOKEN: %s", line);
            wchar_t w[strlen(line)+1];                 /* VLA */
            swprintf(w, strlen(line)+1, L"%s", line);  /* Convert char to wchar_t */
            ft_wwrite(table, w);                       /* Put w on the heap */
            
            ft_ln(table);
        }
        else if ( line_num > line_arg + row_arg - 1 ) {
            break;
        }
    }

    printf("%ls\n", ft_to_wstring(table));

    if ( line != NULL )
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
    int line_arg_flag  = 0;
    int row_arg_flag   = 0;
    //int add_header_arg = 1;

    /* Loop through the incoming command-line arguments. */
    while (1) {

        // getopt_long stores the option index here.
        int option_index = 0;

        c = getopt_long (argc, argv, "AFHhxCd:Q:l:r:", long_options, &option_index);

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

            case 'l':
                debug("option -l with value `%s'", optarg);
                line_arg = atoi(optarg);
                line_arg_flag = 1;
                break;

            case 'r':
                debug("option -r with value `%s'", optarg);
                row_arg = atoi(optarg);
                row_arg_flag = 1;
                break;

            case 'x':
                debug("option -x");
                xpose_arg = 1;
                break;

            case 'A':
                debug("option -A");
                //add_header_arg = 1;
                break;

            case 'F':
                debug("option -F");
                full_mode = 1;
                break;

            case 'H':
                debug("option -H");
                header_arg = 1;
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
    

    /*
     * Notes:
     *
     * - When transposing:
     *   - Option -H defaults to ON
     *   - Option -l defaults to 1
     *   - Option -r defaults to 1
     *   - The net default effect is to output the first row in the file (the header)
     *
     * - When NOT transposing:
     *   - Option -F defaults to ON
     *     - This causes -l and -r to be ignored
     *   - The net default effect is to output the entire file.
     *
     */

    if ( xpose_arg ) {
        if ( full_mode == -1 ) {
            full_mode = 0;
        }
    }
    else {
        if ( full_mode == -1 ) {
            if ( line_arg_flag || row_arg_flag ) {
                full_mode = 0;
            }
            else {
                full_mode = 1;
            }
        }
    }

    if (csv_mode && delim_arg_flag) {
        check(strlen(delim_arg) == 1, "ERROR: CSV delimiter must be exactly one byte long");
        delim_csv = delim_arg[0];
    }
    else if (!csv_mode && delim_arg_flag) {
        delim = delim_arg;
    }

    delim_len = strlen(delim);

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


        // If we are transposing, load the file into a dynamic 2D array 
        // first, then transpose it, and print it:
        if (xpose_arg) {
            DArray *matrix = DArray_create(sizeof(DArray *), 10);
            if (csv_mode) {
                debug("Selected CSV mode");
                check(file_load_csv(filename, matrix) == 0, "Error loading csv file: %s", filename);
            }
            else {
                debug("Selected DELIM mode");
                if ( delim_len > 1 ) {
                    check(file_load_multi(filename, matrix) == 0, "Error loading delimited file: %s", filename);
                    debug("Completed file_load_multi()");
                }
                else {
                    check(file_load(filename, matrix) == 0, "Error loading delimited file: %s", filename);
                }
            }

            DArray *xpose = transpose(matrix);
            check( xpose != NULL, "Error transposing file: %s", filename);

            print_table_from_matrix(xpose);

            master_destroy(matrix);
            master_destroy(xpose);
        }
        // Otherwise, don't load to a matrix, go from file to table:
        else {
            ft_table_t *table = ft_create_table();
            ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
            ft_set_border_style(table, FT_NICE_STYLE);

            if (csv_mode) {
                check(print_table_from_file_csv(filename, table) == 0, "Error counting CSV file: %s", filename);
            }
            else {
                if ( delim_len > 1 ) {
                    check(print_table_from_file_multi(filename, table) == 0, "Error processing file: %s", filename);
                }
                else {
                    check(print_table_from_file(filename, table) == 0, "Error processing file: %s", filename);
                }
            }

            ft_destroy_table(table);
        }


        j++;

    } while (j < argc);

    return 0;

error:
    return -1;
}
