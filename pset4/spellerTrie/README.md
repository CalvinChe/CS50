# [Speller](https://github.com/CalvinChe/CS50/blob/master/pset4/spellerTrie/dictionary.c)

A program that spell-checks a file using a trie.

## Usage
```bash
Usage: Speller [dictionary] text
```

```bash
$ ./speller dictionaries/small texts/cat.txt
MISSPELLED WORDS

A
is
not
a

WORDS MISSPELLED:     4
WORDS IN DICTIONARY:  2
WORDS IN TEXT:        6
TIME IN load:         0.00
TIME IN check:        0.00
TIME IN size:         0.00
TIME IN unload:       0.00
TIME IN TOTAL:        0.00
```

## Specification
1. Implement `load`, `size`, `check`, and `unload` as efficiently as possible using a trie in such a way that `TIME IN load`, `TIME IN check`, `TIME IN size`, and `TIME IN unload` are all minimized.
2. I may not alter `speller.c` or `Makefile`
3. `check` must be case-insensitive
4. `check` should only return true for words actually in `dictionary`
5. I can assume any `dictionary` passed to my program is alphabetically sorted from top to bottom with one word per line, each ending with `\n`
6. `check` will only be passed alphabetical characters and possibly apostrophes
7. I can alter the value of `N` and the implementation of `hash`
8. The spell checker must not leak any memory