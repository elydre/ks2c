# original code: https://github.com/elydre/elydre/blob/main/py-parser/PyParser/segmenteur.py

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

version = "0.1.3"

def car_compteur(texte, tofind) -> int:
    return len([l for l in texte if l == tofind])
    

def coups(liste,valeur):
    if type(liste[0]) is list and len(liste) == 1:
        return liste[0], valeur + 1, True
    else:
        return liste, valeur, False


def emboite(liste):
    valeur = 0
    contin = True
    while contin:
        liste, valeur, contin = coups(liste,valeur)
    return liste, valeur


def edit_liste(bigliste: list) -> list:
    new = []
    for liste in bigliste:
        if type(liste) is list:
            if len(liste) == 1:
                liste, valeur = emboite(liste)
                if valeur > 0:
                    new.append(edit_liste(liste))
                elif valeur == 0:
                    new.extend(iter(liste))
            else:
                new.extend(iter(edit_liste(liste)))
        else:
            new.append(liste)
    return new


def segmenter_string(code: str) -> list:
    actual = 0
    start = 0
    exit_code = code
    for i in range(len(code)):
        car = code[i]
        if car == "(":
            actual += 1
            if start == 0:
                start = i
        elif car == ")":
            actual -= 1
            if actual == 0:
                exit_code = [code[:start], [[code[start+1:i]]], code[i+1:]]
                while "" in exit_code:
                    exit_code.remove("")
                break
    return exit_code

def epurer(code: list) -> list:
    return [epurer(l[0]) if type(l) is list and len(l) == 1 and type(l[0]) is list else epurer(l) if type(l) is list else l for l in code]


def parenthese_in_code(code: list) -> bool:
    return True in [parenthese_in_code(l) if type(l) is list else "(" in l or ")" in l for l in code]


def segmenter(code: list) -> list:
    return [segmenter(l) if type(l) is list else segmenter_string(l) for l in code]


def launch_segmenter(code: str,) -> list:
    if car_compteur(code, "(") != car_compteur(code, ")"):
        print(f"Erreur le nombre de parentèse ne corespond pas:\n'(' -> {car_compteur(code,'(')}\n')' -> {car_compteur(code,')')}")
    else:
        code = [code]
        while parenthese_in_code(code):
            try:
                code = segmenter(code)
            except Exception:
                break
        return edit_liste(code) if len(code) == 1 else edit_liste(code[0])