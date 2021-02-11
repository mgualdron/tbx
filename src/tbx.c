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
#include <ctype.h>
#include <wchar.h>
#include <util/dbg.h>
#include <util/darray.h>
#include <csv.h>
#include <fort.h>
#include "config.h"
#define INT_SIZE 16
#define DEFAULT_ROWS 10
#define IS_CTRL  (1 << 0)

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
static int header_arg = 0;
static int wchar_mode  = 1;
static char *rdelim = "\n";
static wchar_t *wrdelim = L"\n";
static size_t rlen = 0;
static int wrap_len   = 50;
static int text_style = 0;
static unsigned int char_tbl[256] = {0};
//static char *lc_ctype = NULL;

// The callbacks for CSV processing:
static void cb1_x (void *s, size_t len, void *data);
static void cb2_x (int c, void *data);

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
  -d, --delim=DELIM    the delimiting character for the input FILE(s)\n\
  -C, --csv            parse CSV files\n\
  -Q, --csv-quote      CSV quoting character (ignored unless --csv)\n\
  -H, --header         include the first line in the file (header) -- not always needed\n\
  -x, --transpose      transpose the output\n\
  -l, --from-line=NUM  process starting from this line number (default is 1)\n\
  -r, --rows=NUM       process this many rows starting at -l (default is 10 or 1 if -x)\n\
  -w, --wrap=NUM       wrap each column to this length (default is 50)\n\
  -N, --no-wchar       process the input as non-wide characters (not as reliable)\n\
  -F, --full           process the whole file (ignoring -r)\n\
  -T, --text           render table border in plain text\n\
  -h, --help           this help\n\
");
    }

    exit (status);
}


static struct option long_options[] = {
    {"csv"       , no_argument,       0, 'C'},
    {"delim"     , required_argument, 0, 'd'},
    {"csv-quote" , required_argument, 0, 'Q'},
    {"transpose" , no_argument,       0, 'x'},
    {"from-line" , required_argument, 0, 'l'},
    {"rows"      , required_argument, 0, 'r'},
    {"wrap"      , required_argument, 0, 'w'},
    {"no-wchar"  , no_argument,       0, 'N'},
    {"header"    , no_argument,       0, 'H'},
    {"full"      , no_argument,       0, 'F'},
    {"text"      , no_argument,       0, 'T'},
    {"help"      , no_argument,       0, 'h'},
    {0, 0, 0, 0}
};

/* Remove trailing CR/LF */
static void chomp(char *s) {
    while(*s && *s != '\n' && *s != '\r') s++;
    *s = 0;
}

/* Check if a string contains numeric data */
static int isNumeric (const char * s)
{
    if (s == NULL || *s == '\0' || isspace((unsigned int)*s))
      return 0;
    char * p;
    strtod (s, &p);
    return *p == '\0';
}

/*
int replacechar(char *input, char orig, char rep) {
    char *ix = input;
    int n = 0;
    while((ix = strchr(ix, orig)) != NULL) {
        *ix++ = rep;
        n++;
    }
    return n;
}
*/
 
/* List of unprintable characters to replace. */
static void init_table()
{
	int i;
 
	for (i = 0; i < 32; i++)
        char_tbl[i] |= IS_CTRL;

	char_tbl[127] |= IS_CTRL;
}
 
static void replacechars(char * str, int what, const char repl)
{
	unsigned char *ptr, *s = (void*)str;
	ptr = s;
	while (*s != '\0') {

        // If we match the what, we get non-zero and exclude the char.
		if ((char_tbl[(int)*s] & what) == 0) {  // If we don't match, we get 0 and keep the char.
			*(ptr++) = *s;
        }
        else {
			*(ptr++) = repl;   // Otherwise, replace it.
        }
		s++;
	}
	*ptr = '\0';
}

/* Wrap a string to a specified width */
static void wrap(char *input, char *output, size_t wlen)
{
    size_t p = 0;
    size_t n = 0;
    size_t nnl = 0;   // number of newlines to add to input
    size_t olen = strlen(input);  // output length

    if ( wlen <= 0 || olen <= wlen ) {
        strncpy(output, input, olen + 1);
    }
    else {
        nnl = ( strlen(input) / wlen );   // Number of newlines to add
        olen += (nnl*rlen);

        p=0;
        while(1)
        {
            strncpy(output+p, input+(n*wlen), wlen);
            p += wlen;
            strncpy(output+p, rdelim, rlen);
            p += rlen;
            n++;

            if ( p >= olen ) {
                break;
            }
        }
    }
}

/* Wrap a string to a specified width */
static void wwrap(wchar_t *input, wchar_t *output, size_t wlen)
{
    size_t p = 0;
    size_t n = 0;
    size_t nnl = 0;   // number of newlines to add to input
    size_t olen = wcslen(input);  // output length

    if ( wlen <= 0 || olen <= wlen ) {
        wcsncpy(output, input, olen + 1);
    }
    else {
        nnl = ( wcslen(input) / wlen );   // Number of newlines to add
        olen += (nnl*rlen);

        p=0;
        while(1)
        {
            wcsncpy(output+p, input+(n*wlen), wlen);
            p += wlen;
            wcsncpy(output+p, wrdelim, rlen);
            p += rlen;
            n++;

            if ( p >= olen ) {
                break;
            }
        }
    }
}


/* Print an array of arrays in char table form */
static int table_from_matrix(DArray *matrix)
{

    int i, j, nnl;
    DArray *record;

    // setlocale(LC_CTYPE, "");  // Set the original value
    // printf("Locale is set to %s\n", lc_ctype);

    /* The table to be displayed */
    ft_table_t *table = ft_create_table();

    /* Set "header" type for the first row */
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);

    /* Change border style */
    if ( text_style ) {
        ft_set_border_style(table, FT_BASIC_STYLE);
    }
    else {
        ft_set_border_style(table, FT_NICE_STYLE);
    }

    for (i = 0; i < DArray_count(matrix); i++) {

        record = (DArray *)(matrix->contents[i]);

        if ( DArray_end(record) > 0 ) {

            for (j = 0; j < DArray_count(record); j++) {
                char *p = (char *)(record->contents[j]);
                //replacechar(p,'\t',' ');           // ft_write() doesn't like TABs
                replacechars(p, IS_CTRL, ' ');       // ft_write() doesn't like unprintables.
                if ( isNumeric(p) ) {
                    ft_set_cell_prop(table, i, j, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_RIGHT);
                }

                nnl = ( strlen(p) / wrap_len );      // Number of newlines to add
                char o[strlen(p) + (nnl*rlen) + 1];  // VLA
                wrap(p, o, wrap_len);

                ft_u8write(table, o);                 /* Put o on the heap */
            }

            ft_ln(table);
        }

    }

    // printf("%ls\n", ft_to_wstring(table));
    const char *table_str = ft_to_string(table);
    if (table_str) {
        fprintf(stdout, "%s", table_str);
        ft_destroy_table(table);
        return 0;
    } else {
        ft_destroy_table(table);
        return 1;
    }

}


/* Print an array of arrays in wchar table form */
static int wtable_from_matrix(DArray *matrix)
{

    int i, j, nnl;
    DArray *record;

    setlocale(LC_CTYPE, "");  // Avoid printing '(null)'
    // printf("Locale is set to %s\n", lc_ctype);

    /* The table to be displayed */
    ft_table_t *table = ft_create_table();

    /* Set "header" type for the first row */
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);

    /* Change border style */
    if ( text_style ) {
        ft_set_border_style(table, FT_BASIC_STYLE);
    }
    else {
        ft_set_border_style(table, FT_NICE_STYLE);
    }

    for (i = 0; i < DArray_count(matrix); i++) {

        record = (DArray *)(matrix->contents[i]);

        if ( DArray_end(record) > 0 ) {

            for (j = 0; j < DArray_count(record); j++) {
                char *p = (char *)(record->contents[j]);
                //replacechar(p,'\t',' ');           // ft_write() doesn't like TABs
                replacechars(p, IS_CTRL, ' ');       // ft_write() doesn't like unprintables.
                if ( isNumeric(p) ) {
                    ft_set_cell_prop(table, i, j, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_RIGHT);
                }
                wchar_t w[strlen(p)+1];              /* VLA */
                swprintf(w, strlen(p)+1, L"%s", p);  /* Convert char to wchar_t */

                nnl = ( wcslen(w) / wrap_len );      // Number of newlines to add
                wchar_t o[wcslen(w) + (nnl*rlen) + 1];   // VLA
                wwrap(w, o, wrap_len);

                ft_wwrite(table, o);                 /* Put o on the heap */
            }

            ft_ln(table);
        }

    }

    // printf("%ls\n", ft_to_wstring(table));
    const wchar_t *table_wstr = ft_to_wstring(table);
    if (table_wstr) {
        fwprintf(stdout, L"%ls", table_wstr);
        ft_destroy_table(table);
        return 0;
    } else {
        // fwprintf(stderr, L"Table conversion failed !!!\n ");
        ft_destroy_table(table);
        return 1;
    }

}





/* Destroy 2-D arrays */
static void master_destroy ( DArray *matrix )
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
static int DArray_maxcols( DArray *matrix )
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
static DArray *transpose( DArray *matrix )
{
    int i, j, rec_num;
    DArray *xpose  = DArray_create(sizeof(DArray *), DEFAULT_ROWS);
    DArray *record = DArray_create(sizeof(char *), DEFAULT_ROWS);
    DArray *xhead  = DArray_create(sizeof(char *), DEFAULT_ROWS);
    char *copy = NULL;
    char *blank = strdup("");  /* a heap-allocated empty string */

    copy = strdup("COL");
    DArray_push(xhead, copy);
    copy = strdup("FIELD NAMES");
    DArray_push(xhead, copy);

    rec_num = line_arg == 1 ? 2 : line_arg;

    /* The Header */
    for (i = 0; i < DArray_count(matrix) - 1; i++) {

        record = (DArray *)(matrix->contents[i + 1]);

        if ( DArray_end(record) > 0 ) {
            char val[INT_SIZE + 7];
            snprintf(val, INT_SIZE + 7, "RECORD %d", rec_num + i - 1);
            char *copy = strndup(val, INT_SIZE + 7);
            DArray_push(xhead, copy);
        }
    }

    DArray_push(xpose, xhead);

    for (j = 0; j < DArray_maxcols(matrix); j++) {

        DArray *xrec = DArray_create(sizeof(char *), DEFAULT_ROWS);

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
/*
static void tb_print( DArray *matrix )
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
*/

/* Load a regular delimited file */
static int file_load(char *filename, DArray *matrix)
{
    char *line = NULL;
    FILE *fp = NULL;
    size_t len = 0;         // allocated size for line
    ssize_t bytes_read = 0; // num of chars read

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

        if ( full_mode ||
                ( header_arg && line_num == 1 ) ||
                ( (line_num >= line_arg) &&
                  (line_num <= line_arg + row_arg - 1) ) ) {

            DArray *record = DArray_create(sizeof(char *), DEFAULT_ROWS);

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

    }

    debug("Read a total of %d records\n", DArray_count(matrix));

    if ( line != NULL )
        free(line);
    fclose(fp);

    return 0;

error:
    return -1;
}

/* Load a regular delimited file with multi-character delimiters */
static int file_load_multi(char *filename, DArray *matrix)
{
    char *line = NULL;
    char *orig_line = NULL;
    FILE *fp = NULL;
    size_t len = 0;         // allocated size for line
    ssize_t bytes_read = 0; // num of chars read

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

        if ( full_mode || ( header_arg && line_num == 1 ) || ( (line_num >= line_arg) && (line_num <= line_arg + row_arg - 1) ) ) {

            orig_line = line;
            chomp(line);

            DArray *record = DArray_create(sizeof(char *), DEFAULT_ROWS);

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
    }

    debug("Read a total of %d records\n", DArray_count(matrix));

    fclose(fp);

    return 0;

error: return -1;
}

// Callback 1 for CSV support, called whenever a field is processed:
static void cb1_x (void *s, size_t len, void *data)
{
    if ( full_mode || ( header_arg && line_num == 1 ) || ( (line_num >= line_arg) && (line_num <= line_arg + row_arg - 1) ) ) {

        DArray *matrix = (DArray *)data;
        int last = DArray_end(matrix) - 1;

        if ( (last == -1 && current_record == NULL) || just_pushed_record ) {
            current_record = DArray_create(sizeof(char *), DEFAULT_ROWS);
            just_pushed_record = 0;
        }

        char *field = strndup(s, len);
        DArray_push(current_record, field);
    }
}

// Callback 2 for CSV support, called whenever a record is processed:
static void cb2_x (int c, void *data)
{

    if ( full_mode || ( header_arg && line_num == 1 ) || ( (line_num >= line_arg) && (line_num <= line_arg + row_arg - 1) ) ) {
        DArray_push((DArray *)data, current_record);
        just_pushed_record = 1;
        current_record = NULL;
    }
    line_num++;
    ignore_this = c;
}

/* Load a CSV file into a dynamic matrix */
static int file_load_csv(char *filename, DArray *matrix)
{
    struct csv_parser p;
    char buf[1024];
    FILE *fp = NULL;
    size_t bytes_read = 0; // num of chars read

    line_num = 1;   // Start at 1 since cb1_x is called before cb2_x.

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

        if ( full_mode == 0 && line_num > line_arg + row_arg - 1 ) {
            break;
        }
    }

    if ( full_mode ) {
        check(csv_fini(&p, cb1_x, cb2_x, matrix) == 0, "Error finishing CSV processing.");
    }

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
    int xpose_arg      = 0;
    int row_arg_flag   = 0;
    int retval = 0;

    /*
    lc_ctype = setlocale(LC_CTYPE, NULL);
    printf("Locale is detected as %s\n", lc_ctype);
    */
    rlen = wcslen(wrdelim);    // The length of the row delimiter (normally 1)
	init_table();

    /* Loop through the incoming command-line arguments. */
    while (1) {

        // getopt_long stores the option index here.
        int option_index = 0;

        c = getopt_long (argc, argv, "FHhNxCTd:l:Q:r:w:", long_options, &option_index);

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

            case 'N':
                debug("option -W");
                wchar_mode = 0;
                break;

            case 'w':
                debug("option -w with value `%s'", optarg);
                wrap_len = atoi(optarg);
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

            case 'T':
                debug("option -T");
                text_style = 1;
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
     *   - Option -H defaults to OFF
     *   - Option -l defaults to 1
     *   - Option -r defaults to 1
     *   - The net default effect is to output the first row in the file (the header)

     * - When NOT transposing:
     *   - Option -H defaults to OFF
     *   - Option -l defaults to 1
     *   - Option -r defaults to DEFAULT_ROWS
     *   - The net default effect is to output the first DEFAULT_ROWS rows in the file 
     *     (like the head command)
     *
     */

    check(wrap_len > 0, "ERROR: Wrap length must be greater than zero (0).");

    if ( full_mode == -1 ) {
        full_mode = 0;
    }

    if ( ! xpose_arg ) {
        if ( ! row_arg_flag ) {
            row_arg = DEFAULT_ROWS;
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

        /* Assume STDIN if no additional arguments, else loop through them: */
        char *filename = NULL;
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

        /* Load the data into a matrix first */
        DArray *matrix = DArray_create(sizeof(DArray *), DEFAULT_ROWS);

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

        /* Transpose the data if requested */
        if (xpose_arg) {
            DArray *xpose = transpose(matrix);
            check( xpose != NULL, "Error transposing file: %s", filename);

            if ( wchar_mode ) {
                retval = wtable_from_matrix(xpose);
            }
            else {
                retval = table_from_matrix(xpose);
            }

            master_destroy(xpose);
        }
        else {

            if ( wchar_mode ) {
                retval = wtable_from_matrix(matrix);
            }
            else {
                retval = table_from_matrix(matrix);
            }
        }

        master_destroy(matrix);
        check(retval == 0, "Error creating table.");

        j++;

    } while (j < argc);

    return 0;

error:
    return -1;
}
/*
 *
 * Copyright (C) 2020 Miguel Gualdron
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * See the file COPYING in this distribution, or http://www.gnu.org/licenses/gpl.txt
 *
 */
