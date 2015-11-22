# MagicSetEditor

[![Gitter](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/CustomCardsOnline/MagicSetEditor?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

# Modifying the build system
To make any changes to the build system (if you're compiling this with autotools 
and such), the files you will need to edit are:

1. aclocal.m4 - This defines additional macros that are probably needed to generate the configure script
2. configure.ac - This is what autoconf uses to generate the configure script
3. MakeAM.sh - This is used to generate the Makefile.am since the source tree is so huge

Depending on which files you edit, you'll need to need to run these commands before 
the usual ```configure; make; make install```:

```
autoreconf                   # for aclocal.m4
autoconf                     # for generating the configure script
./MakeAM.sh                  # for generating the Makefile.am
automake [--add-missing|-a]  # for generating the Makefile.in, if it fails, use
                             # the --add-missing or -a flag to add the files that're missing
```
