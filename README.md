# ks2cpp

syntactic compiler from ks to cpp

[![Sonar Cube Static Analysis](https://sonarcloud.io/api/project_badges/measure?project=ks2cpp&metric=ncloc)](https://sonarcloud.io/dashboard?id=ks2cpp)
[![Wiki](https://img.shields.io/badge/esolang-wiki-lightgray)](https://esolangs.org/wiki/kS)
[![Github Project](https://img.shields.io/badge/project-open-lightgray)](https://github.com/elydre/ks2cpp/projects/2)
[![dif10](https://img.shields.io/badge/dif10-5.5-lightgray)](https://pf4.ddns.net/dif10/)
[![version](https://img.shields.io/badge/version-last-lightgray)](https://github.com/elydre/ks2cpp/blob/main/version_history.md)

## About

The [KS (KEA-stream)](https://kea-corp.github.io/stream/) is an [esolang](https://esolangs.org/wiki/Main_Page) designed to simplify the [KEA](https://kea-corp.github.io), a [modal](https://kea-corp.github.io/doc/modes.html) [interpreted](https://github.com/KEA-corp/KEA-php) esolang.
```
KS => ks2kea => KEA => interpreter
```

However the KEA remains slow, so instead of compiling the KS to KEA why not do it to C++
```
KS => ks2cpp => C++ => g++ => out-file
```

## compilation of cpp output

create a output directory named `build`

```
mkdir build
cd build
```

compile the cpp code

```
cmake .. && make
```

execute the compiled code

```
./o_src/o_src
```

## tree

```
┌────────────────────────────
│   .gitignore
│   LICENSE
│   pusher.ps1
│   README.md
│   sonar-project.properties
│   version_history.md
│
└───files
    │   CMakeLists.txt
    │   input.ks
    │   main.py
    │
    ├───core
    │       generator.py
    │       lexer.py
    │       parser.py
    │
    └───o_src
            CMakeLists.txt
            fcm.cpp
            ks.h
            main.cpp
```
