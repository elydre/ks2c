# ks2c

[![Wiki](https://img.shields.io/badge/esolang-wiki-lightgray)](https://esolangs.org/wiki/kS)
[![Github Project](https://img.shields.io/badge/project-open-lightgray)](https://github.com/elydre/ks2c/projects/2)
[![dif10](https://img.shields.io/badge/dif10-5.5-lightgray)](https://pf4.ddns.net/dif10/)

## About

The [KS (KEA-stream)](https://elydre.github.io/kea/stream) is an [esolang](https://esolangs.org/wiki/Main_Page) designed to simplify the [KEA](https://elydre.github.io/kea), a [modal](https://elydre.github.io/kea/doc/modes.html) [interpreted](https://github.com/elydre/KEA/tree/main/inter) esolang
```
KS => ks2kea => KEA => interpreter
```

However the KEA remains slow, so instead of compiling the KS to KEA why not do it to C
```
KS => ks2c => C => make => out-file
```

## Build and run

```sh
# Compile the KS to C
python3 main.py

# Compile the C to an executable
make

# Execute the compiled code
./prog
```
