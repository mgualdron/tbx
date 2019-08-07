# tbx

## Description

Small command-line utility to display delimited text in tabular form.

For a brief usage:

```
tbx -h

Usage: tbx [OPTION]... [FILE]...
Display a delimited file in tabular form.
More than one FILE can be specified.

  -d, --delimiter=DELIM  the delimiting character for the input FILE(s)
  -C  --csv              parse CSV files
  -Q, --csv-quote        CSV quoting character (ignored unless --csv)
  -x, --transpose        transpose the output
```

## Examples

The default delimiter is a tab, so if you have a simple tab-delimited file 
like:

```
cat test_file.tab

HEADER_1        HEADER_2        HEADER_3        HEADER_4        HEADER_5
COL1ROW1        COL2ROW1        COL3ROW1        COL4ROW1        COL5ROW1
COL1ROW2        COL2ROW2        COL3ROW2        COL4ROW2        COL5ROW2
COL1ROW3        COL2ROW3        COL3ROW3        COL4ROW3        COL5ROW3
COL1ROW4        COL2ROW4        COL3ROW4        COL4ROW4        COL5ROW4
COL1ROW5        COL2ROW5        COL3ROW5        COL4ROW5        COL5ROW5
COL1ROW6        COL2ROW6        COL3ROW6        COL4ROW6        COL5ROW6
```


You can display it in table form as follows:

```
tbx test_file.tab

╔══════════╦══════════╦══════════╦══════════╦══════════╗
║ HEADER_1 ║ HEADER_2 ║ HEADER_3 ║ HEADER_4 ║ HEADER_5 ║
╠══════════╬══════════╬══════════╬══════════╬══════════╣
║ COL1ROW1 ║ COL2ROW1 ║ COL3ROW1 ║ COL4ROW1 ║ COL5ROW1 ║
║ COL1ROW2 ║ COL2ROW2 ║ COL3ROW2 ║ COL4ROW2 ║ COL5ROW2 ║
║ COL1ROW3 ║ COL2ROW3 ║ COL3ROW3 ║ COL4ROW3 ║ COL5ROW3 ║
║ COL1ROW4 ║ COL2ROW4 ║ COL3ROW4 ║ COL4ROW4 ║ COL5ROW4 ║
║ COL1ROW5 ║ COL2ROW5 ║ COL3ROW5 ║ COL4ROW5 ║ COL5ROW5 ║
║ COL1ROW6 ║ COL2ROW6 ║ COL3ROW6 ║ COL4ROW6 ║ COL5ROW6 ║
╚══════════╩══════════╩══════════╩══════════╩══════════╝
```

The `--csv` option supports CSV files with optional quoting and/or embedded 
new-lines.

```
cat test_file.csv

HEADER_1,HEADER_2,HEADER_3,HEADER_4,HEADER_5
COL1ROW1,COL2ROW1,COL3ROW1,COL4ROW1,COL5ROW1
COL1ROW2,COL2ROW2,COL3ROW2,COL4ROW2,COL5ROW2
COL1ROW3,COL2ROW3,COL3ROW3,COL4ROW3,COL5ROW3
COL1ROW4,COL2ROW4,COL3ROW4,COL4ROW4,COL5ROW4
COL1ROW5,COL2ROW5,COL3ROW5,COL4ROW5,COL5ROW5
COL1ROW6,COL2ROW6,COL3ROW6,COL4ROW6,COL5ROW6
```

Render it in table form as follows:

```
tbx --csv test_file.csv

╔══════════╦══════════╦══════════╦══════════╦══════════╗
║ HEADER_1 ║ HEADER_2 ║ HEADER_3 ║ HEADER_4 ║ HEADER_5 ║
╠══════════╬══════════╬══════════╬══════════╬══════════╣
║ COL1ROW1 ║ COL2ROW1 ║ COL3ROW1 ║ COL4ROW1 ║ COL5ROW1 ║
║ COL1ROW2 ║ COL2ROW2 ║ COL3ROW2 ║ COL4ROW2 ║ COL5ROW2 ║
║ COL1ROW3 ║ COL2ROW3 ║ COL3ROW3 ║ COL4ROW3 ║ COL5ROW3 ║
║ COL1ROW4 ║ COL2ROW4 ║ COL3ROW4 ║ COL4ROW4 ║ COL5ROW4 ║
║ COL1ROW5 ║ COL2ROW5 ║ COL3ROW5 ║ COL4ROW5 ║ COL5ROW5 ║
║ COL1ROW6 ║ COL2ROW6 ║ COL3ROW6 ║ COL4ROW6 ║ COL5ROW6 ║
╚══════════╩══════════╩══════════╩══════════╩══════════╝
```

You can also transpose the data:

```
tbx --csv --transpose test_file.csv

╔═════╦═════════════╦══════════╦══════════╦══════════╦══════════╦══════════╦══════════╗
║ COL ║ FIELD NAMES ║ RECORD 1 ║ RECORD 2 ║ RECORD 3 ║ RECORD 4 ║ RECORD 5 ║ RECORD 6 ║
╠═════╬═════════════╬══════════╬══════════╬══════════╬══════════╬══════════╬══════════╣
║ 1   ║ HEADER_1    ║ COL1ROW1 ║ COL1ROW2 ║ COL1ROW3 ║ COL1ROW4 ║ COL1ROW5 ║ COL1ROW6 ║
║ 2   ║ HEADER_2    ║ COL2ROW1 ║ COL2ROW2 ║ COL2ROW3 ║ COL2ROW4 ║ COL2ROW5 ║ COL2ROW6 ║
║ 3   ║ HEADER_3    ║ COL3ROW1 ║ COL3ROW2 ║ COL3ROW3 ║ COL3ROW4 ║ COL3ROW5 ║ COL3ROW6 ║
║ 4   ║ HEADER_4    ║ COL4ROW1 ║ COL4ROW2 ║ COL4ROW3 ║ COL4ROW4 ║ COL4ROW5 ║ COL4ROW6 ║
║ 5   ║ HEADER_5    ║ COL5ROW1 ║ COL5ROW2 ║ COL5ROW3 ║ COL5ROW4 ║ COL5ROW5 ║ COL5ROW6 ║
╚═════╩═════════════╩══════════╩══════════╩══════════╩══════════╩══════════╩══════════╝
```

## Building tbx

Install the following required libraries in your `$HOME/local` directory:

- [libcsv](https://github.com/rgamble/libcsv)
- [libfort](https://github.com/seleznevae/libfort)

Make the binary as follows:

```
cd tbx

make
```

Copy it somewhere in your path, like `$HOME/bin`:

```
cp ./bin/tbx $HOME/bin
```

## TODO

Limit the number of records processed, so the program can display selected 
rows from a file.

