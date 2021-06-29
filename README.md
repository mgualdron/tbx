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
  -b, --bot-line       add a separating line above the last row of output (ignored if -x)
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

One of the most useful features is to be able to transpose the data, in
combination with being able to select specific rows with `-l` and `-r`.

For example, we have a wide file delimited by pipes:


```
head -3 fakedata.txt

NAME|PHONE|EMAIL|update_dt|ORG_ID|RUT|PID|OID|Address|city|zip|region|country|lat_long|PAN
Leo|0800 1111|Sed.eu@dolorsitamet.edu|Feb 15, 2022|117985069-00006|10699987-2|16240903 6494|708521 9637|P.O. Box 710, 9971 Proin Rd.|Sukabumi|66967-564|JB|Dominican Republic|4.65026, 164.7462|542065 0974506092
Edward|055 6837 8442|turpis.Nulla@tellusSuspendisse.edu|Jul 23, 2021|569153687-00003|19619579-3|16580925 3585|633719 7286|Ap #623-5708 Cursus Ave|Ajax|95186|ON|Switzerland|22.52987, 10.37935|5232 2479 1716 6403
```

If we want to look at two records starting at line 57 (including the header):


```
tbx -x -H -l57 -r2 -d'|' fakedata.txt

╔═════╦═════════════╦═══════════════════════════════╦═════════════════════╗
║ COL ║ FIELD NAMES ║ RECORD 56                     ║ RECORD 57           ║
╠═════╬═════════════╬═══════════════════════════════╬═════════════════════╣
║   1 ║ NAME        ║ Barrett                       ║ Merrill             ║
║   2 ║ PHONE       ║ (016710) 41756                ║ (012569) 68555      ║
║   3 ║ EMAIL       ║ pede.ac@malesuadavel.net      ║ Sed@egestas.edu     ║
║   4 ║ update_dt   ║ Jan 3, 2021                   ║ Jul 6, 2020         ║
║   5 ║ ORG_ID      ║ 779030709-00009               ║ 892857277-00008     ║
║   6 ║ RUT         ║ 19250060-5                    ║ 36605598-3          ║
║   7 ║ PID         ║ 16141207 1308                 ║ 16510511 1628       ║
║   8 ║ OID         ║ 992146 2330                   ║ 507227 1298         ║
║   9 ║ Address     ║ P.O. Box 531, 7721 Tempus Av. ║ 774-3652 Dictum Rd. ║
║  10 ║ city        ║ Lokeren                       ║ Uruapan             ║
║  11 ║ zip         ║ Z9743                         ║ 66-964              ║
║  12 ║ region      ║ OV                            ║ Mic                 ║
║  13 ║ country     ║ Cocos (Keeling) Islands       ║ Ukraine             ║
║  14 ║ lat_long    ║ -15.29691, -141.59539         ║ -16.01491, 55.35563 ║
║  15 ║ PAN         ║ 542765 3078199783             ║    5332814123831325 ║
╚═════╩═════════════╩═══════════════════════════════╩═════════════════════╝
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
installing `autoconf` and `automake`, then download a distribution
[package](https://github.com/mgualdron/tbx/releases/download/v0.0.3/tbx-0.0.3.tar.gz)
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
