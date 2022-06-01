# ks2cpp

syntactic compiler from ks to cpp

[![Sourcery](https://img.shields.io/badge/sourcery-enabled-brightgreen)](https://sourcery.ai)
[![Sonar Cube Static Analysis](https://sonarcloud.io/api/project_badges/measure?project=elydre_ks2cpp&metric=ncloc)](https://sonarcloud.io/dashboard?id=elydre_ks2cpp)
[![Wiki](https://img.shields.io/badge/esolang-wiki-lightgray)](https://esolangs.org/wiki/kS)
[![Size](https://img.shields.io/github/repo-size/elydre/ks2cpp)](https://github.com/elydre/ks2cpp)
[![Github Project](https://img.shields.io/badge/project-open-brightgreen)](https://github.com/elydre/ks2cpp/projects/2)

## About

The [KS (KEA-stream)](https://kea-corp.github.io/stream/) is an [esolang](https://esolangs.org/wiki/Main_Page) designed to simplify the [KEA](https://kea-corp.github.io), a [modal](https://kea-corp.github.io/doc/modes.html) [interpreted](https://github.com/KEA-corp/KEA-php) esolang.
```
KS => ks2kea => KEA => interpeter
```

However the KEA remains slow, so instead of compiling the KS to KEA why not do it to C++
```
KS => ks2cpp => C++ => g++ => out-file
```