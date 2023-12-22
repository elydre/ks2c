# ks2c

[![Wiki](https://img.shields.io/badge/esolang-wiki-lightgray)](https://esolangs.org/wiki/kS)
[![Github Project](https://img.shields.io/badge/project-open-lightgray)](https://github.com/elydre/ks2c/projects/2)
[![dif10](https://img.shields.io/badge/dif10-5.5-lightgray)](https://pf4.ddns.net/dif10/)
[![version](https://img.shields.io/badge/version-last-lightgray)](https://github.com/elydre/ks2c/blob/main/version_history.md)

## About

The [KS (KEA-stream)](https://kea-corp.github.io/stream/) is an [esolang](https://esolangs.org/wiki/Main_Page) designed to simplify the [KEA](https://kea-corp.github.io), a [modal](https://kea-corp.github.io/doc/modes.html) [interpreted](https://github.com/KEA-corp/KEA-php) esolang
```
KS => ks2kea => KEA => interpreter
```

However the KEA remains slow, so instead of compiling the KS to KEA why not do it to C
```
KS => ks2c => C => make => out-file
```

## Compilation of C output

Compile the C code
```
make
```

Execute the compiled code
```
./prog
```
