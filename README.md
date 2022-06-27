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

## tree

```
ks2cpp
│   .gitignore
│   LICENSE
│   README.md
│   sonar-project.properties
│   version_history.md
│
├───.github
│   └───workflows
│           build.yml
│
└───files
    │   main.py
    │
    ├───core
    │       generator.py
    │       lexer.py
    │       parser.py
    │
    ├───mod
    │       cytron.py
    │       tools.py
    │
    └───_ks
            main.ks
```

## steps

input:
    
```
40 + 2, 24 >> is_inv > print
```

lexer:

```py
[
    [
        {
            'iph': 0,
            'oph': 2,
            'cde': [
                [
                    {
                        'type': 'int',
                        'cnt': '40',
                    },
                    {
                        'type': 'op',
                        'cnt': '+'
                    },
                    {'type': 'int',
                    'cnt': '2'
                    }
                ],
                [
                    {
                        'type': 'int',
                        'cnt': '24'
                    }
                ]
            ]
        },
        {
            'iph': 2,
            'oph': 1,
            'cde': [
                [
                    {
                        'type': 'func',
                        'cnt': 'is_inv'
                    }
                ]
            ]
        },
        {
            'iph': 1,
            'oph': 0,
            'cde': [
                [
                    {
                        'type': 'func',
                        'cnt': 'print'
                    }
                ]
            ]
        }
    ]
]
```

parser:

```py
[
    {
        'type': 'func',
        'cnt': 'print',
        'arg': [
            {
                'type': 'func',
                'cnt': 'is_inv',
                'arg': [
                    {
                        'type': 'func',
                        'cnt': 'add',
                        'arg': [
                            {
                                'type': 'int',
                                'cnt': '40',
                            },
                            {
                                'type': 'int',
                                'cnt': '2',
                            }
                        ]
                    },
                    {
                        'type': 'int',
                        'cnt': '24',
                    }
                ]
            }
        ]
    }
]
```

generator:

```cpp
print(is_inv(add(40, 2), 24))
```
