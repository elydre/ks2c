'''    _             _
  ___ | | _   _   __| | _ __   ___
 / _ \| || | | | / _` || '__| / _ |
|  __/| || |_| || (_| || |   |  __/
 \___||_| \__, | \__,_||_|    \___|
          |___/
___________________________________

 - codé en : UTF-8
 - langage : python3
 - GitHub  : github.com/elydre
 - Licence : GNU GPL v3
'''

from mod.segmenteur import launch_segmenter as segmenter

version = "l-0.4"

class Lexer:
    def __init__(self, file: str) -> None:
        self.brut = file

    def run(self):
        return segmenter(self.brut)