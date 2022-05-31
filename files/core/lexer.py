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

version = "l-0.5"

class Lexer:
    def __init__(self, file: str) -> None:
        self.brut = file


    def analyse(self, edit: str) -> dict:
        dico = {
            "in_push": 0,
            "out_push": 0,
            "code": "",
        }
        is_in = 1
        for car in edit:
            if car == ">":
                dico["in_push" if is_in else "out_push"] += 1
            else:
                dico["code"] += car
                is_in = 0

        return dico


    def split_push(self, e: str) -> list:
        sortie = []
        in_string = False
        in_push = False
        code_to_analyse = ""
        for car in e:
            if car in ["\"", "'"]:
                in_string = not in_string
            if in_string:
                continue
            if car == ">":
                in_push = True
            if in_push and car != ">":
                sortie.append(self.analyse(code_to_analyse))
                code_to_analyse = code_to_analyse[-sortie[-1]["out_push"]:]
                in_push = False
            code_to_analyse += car

        sortie.append(self.analyse(code_to_analyse))
        return sortie          


    def lexing(self, seg: list) -> list:
        sortie = []
        for e in seg:
            if type(e) == list:
                sortie.append(self.lexing(e))
            else:
                sortie.extend(self.split_push(e))
        return sortie


    def sup_space(self, e: str) -> str:
        in_string = False
        out = ""
        for car in e:
            if car in ["\"", "'"]:
                in_string = not in_string
            if not in_string and car == " ":
                continue
            out += car
        return out


    def run(self):
        seg = self.sup_space(self.brut)
        print(seg)
        seg = segmenter(seg)
        print(seg)
        return self.lexing(seg)