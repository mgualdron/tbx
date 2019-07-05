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
      --csv              parse CSV files
  -Q, --csv-quote        CSV quoting character (ignored unless --csv)
```

## Examples

The default delimiter is a tab, so if you have a simple tab-delimited file 
like:

```
cat test_file.tab

HEADER1 HEADER2 HEADER3 HEADER4 HEADER5
ROW1    ROW2    ROW3    ROW4    ROW5
ROW1    ROW2    ROW3    ROW4    ROW5
ROW1    ROW2    ROW3    ROW4    ROW5
ROW1    ROW2    ROW3    ROW4    ROW5
ROW1    ROW2    ROW3    ROW4    ROW5
ROW1    ROW2    ROW3    ROW4    ROW5
```


You can display it in table form as follows:

```
tbx test_file.tab

╔═════════╦═════════╦═════════╦═════════╦═════════╗
║ HEADER1 ║ HEADER2 ║ HEADER3 ║ HEADER4 ║ HEADER5 ║
╠═════════╬═════════╬═════════╬═════════╬═════════╣
║ ROW1    ║ ROW2    ║ ROW3    ║ ROW4    ║ ROW5    ║
║ ROW1    ║ ROW2    ║ ROW3    ║ ROW4    ║ ROW5    ║
║ ROW1    ║ ROW2    ║ ROW3    ║ ROW4    ║ ROW5    ║
║ ROW1    ║ ROW2    ║ ROW3    ║ ROW4    ║ ROW5    ║
║ ROW1    ║ ROW2    ║ ROW3    ║ ROW4    ║ ROW5    ║
║ ROW1    ║ ROW2    ║ ROW3    ║ ROW4    ║ ROW5    ║
╚═════════╩═════════╩═════════╩═════════╩═════════╝

```

The `--csv` option supports CSV files with optional quoting and/or embedded 
new-lines.

```
cat test_file.csv
HEADER1,HEADER2,HEADER3,HEADER4,HEADER5
ROW1,ROW2,ROW3,ROW4,ROW5
ROW1,ROW2,ROW3,ROW4,ROW5
ROW1,ROW2,ROW3,ROW4,ROW5
ROW1,ROW2,ROW3,ROW4,ROW5
ROW1,ROW2,ROW3,ROW4,ROW5
ROW1,ROW2,ROW3,ROW4,ROW5
```

Render it in table form as follows:

```
tbx --csv test_file.csv
╔═════════╦═════════╦═════════╦═════════╦═════════╗
║ HEADER1 ║ HEADER2 ║ HEADER3 ║ HEADER4 ║ HEADER5 ║
╠═════════╬═════════╬═════════╬═════════╬═════════╣
║ ROW1    ║ ROW2    ║ ROW3    ║ ROW4    ║ ROW5    ║
║ ROW1    ║ ROW2    ║ ROW3    ║ ROW4    ║ ROW5    ║
║ ROW1    ║ ROW2    ║ ROW3    ║ ROW4    ║ ROW5    ║
║ ROW1    ║ ROW2    ║ ROW3    ║ ROW4    ║ ROW5    ║
║ ROW1    ║ ROW2    ║ ROW3    ║ ROW4    ║ ROW5    ║
║ ROW1    ║ ROW2    ║ ROW3    ║ ROW4    ║ ROW5    ║
╚═════════╩═════════╩═════════╩═════════╩═════════╝
```

## Building tbx

Install the following required libraries in your `$HOME/local` directory:

```
libcsv
libfort
```

Make the binary as follows:

```
cd tbx

make tbx
```

Copy it somewhere in your path, like `$HOME/bin`:

```
cp tbx $HOME/bin
```
