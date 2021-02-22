# tbx

## Description

Small command-line utility to display delimited text in tabular form.

For a brief usage:

```
tbx -h

Usage: tbx [OPTION]... [FILE]...
Display a delimited file in tabular form.
More than one FILE can be specified.

  -d, --delim=DELIM    the delimiting character for the input FILE(s)
  -C, --csv            parse CSV files
  -Q, --csv-quote      CSV quoting character (ignored unless --csv)
  -H, --header         include the first line in the file (header) -- not always needed
  -x, --transpose      transpose the output
  -l, --from-line=NUM  process starting from this line number (default is 1)
  -r, --rows=NUM       process this many rows starting at -l (default is 10 or 1 if -x)
  -w, --wrap=NUM       wrap each column to this length (default is 50)
  -F, --full           process the whole file (ignoring -r)
  -T, --text           render table border in plain text
  -h, --help           this help
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

Note that `tbx` behaves a little like the `head` command, and by default
displays the first ten (10) rows of your file.  To get the full file use the
`-F` (`--full`) option.

```
tbx -F test_file.tab
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

The main goal of `tbx` is not to display hundreds of rows of data, but to
zero-in on a specific handful of rows you'd like to examine carefully.

See the included manual page for more details and examples.

## Building tbx

Install the following required libraries.

- [libcsv](https://github.com/rgamble/libcsv)
- [libfort](https://github.com/seleznevae/libfort)

These can be installed in the standard system locations or in your `$HOME` directory.

Note that this git repository does not include a `configure` script like a 
distribution tarball normally does.  If you don't want to bother with 
installing `autoconf` and `automake`, then download a distribution package 
and run `configure`:

```
./configure
```

If some of the required libraries are in your `$HOME` directory, 
and if you also want the `tbx` binary installed in your `$HOME/bin`, you should 
run something like:

```
./configure CPPFLAGS="-I$HOME/include" LDFLAGS="-L$HOME/lib" --prefix=$HOME
```

If you're building from a copy of this git repository, you'll need to have 
`autoconf` and `automake` installed on your system, and run the following 
command to generate a `configure` script:

```
autoreconf -i
```

...and subsequently run `configure` as mentioned before.

After `configure` completes successfully, you can do the usual:

```
make
make check
make install
```

## Author

Miguel Gualdron (dev at gualdron.com).
