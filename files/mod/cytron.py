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


import contextlib
###########################
##                       ##
##     IMPORTATIONS      ##
##                       ##
###########################

import os, sys
from urllib.request import urlopen

###########################
##                       ##
##    INITIALISATION     ##
##                       ##
###########################

global path_v, version, console_o

version_id = "cytron 15b"

console_o = False
path_v = os.path.dirname(sys.argv[0])

###########################
##                       ##
##       FONCTION        ##
##                       ##
###########################

def check_internet(site="https://google.com"):
    try:
        urlopen(site)
        return True
    except Exception:
        return False

def clear():
    os.system('cls' if os.name == 'nt' else 'clear')

def ls(chem):
    return(os.listdir(path_v + chem))

def version():
    return(version_id)

def path():
    return(path_v)

def mkdir(chem, nom):
    try:
        temp = path_v + chem + "/" + nom
        os.makedirs(temp)
        return("DONE")
    except Exception:
        return("erreur: 'chem rela + nom'")

def wget(chem, nom, addr):
    if check_internet():
        temp = path_v + chem + "/" + nom
        with open(temp, 'wb') as img: img.write(urlopen(addr).read())
        return("DONE")
    else: return("erreur: pas de connection internet")

def mkfil(chem, nom, text):
    temp = path_v + chem + "/" + nom
    with open(temp, "w") as fil:
        fil.write(str(text))
    fil.close()
    return("DONE")

def rfil(chem, nom):
    temp = path_v + chem + "/" + nom
    with contextlib.suppress(Exception):
        fil = open(temp, "r")
        return(fil.read())

###########################
##                       ##
##      POO - CY 15      ##
##                       ##
###########################

class File:
    def __init__(self, chem, nom):
        self.nom = nom
        self.path = path_v + chem + "/" + nom
        self.chem = chem
    
    def __str__(self) -> str:
        return self.read()

    def read(self) -> str:
        return rfil(self.chem, self.nom)
    
    def make(self, text: str) -> str:
        return mkfil(self.chem, self.nom, text)

    def wget(self, addr: str) -> str:
        return wget(self.chem, self.nom, addr)

###########################
##                       ##
##        CONSOLE        ##
##                       ##
###########################

def console():
    while True:
        retour = run(input('~} ').split(" "))
        if retour is None: clear()
        elif retour == "exit": exit()
        else: print(retour)

### commandes
def run(ipt):
    if ipt[0] == "":
        return
    if ipt[0] == "version": return(version())               # version
    elif ipt[0] == "path": return(path())                   # path
    elif ipt[0] == "mkdir":                                 # mkdir
        try: return(mkdir(ipt[1], ipt[2]))
        except: return("erreur: 'chem rela + nom'")
    elif ipt[0] == "wget":                                  # wget
        try: return(wget(ipt[1], ipt[2], ipt[3]))
        except: return("erreur: 'chem rela + nom + addr'")
    elif ipt[0] == "mkfil":                                 # mkfil
        try: return(mkfil(ipt[1], ipt[2], ipt[3]))
        except: return("erreur: 'chem rela + nom + text'")
    elif ipt[0] == "ls":                                    # ls
        try: return(ls(ipt[1]))
        except: return("erreur: 'chem rela'")
    elif ipt[0] == "rfil":                                  # rfil
        try: return(rfil(ipt[1], ipt[2]))
        except: return("erreur: 'chem rela + nom'")
    elif ipt[0] == "exit":                                  # exit
        return("exit")
    elif ipt[0] in ["aide", "help"]:              # aide
        return("version > affiche la version\npath    > affiche le chemain\nmkdir   > crée un dossier\nls      > affiche le contenue d'un dossier\nwget    > crée un fichier depuis le web\nmkfil   > créé un fichier\nrfil    > affiche le contenue d'un fichier\nhelp    > affiche l'aide")
    else: return("commande inconnu")

if __name__ == "__main__":
    console()

###########################
##                       ##
##  RETRO COMPATIBILITE  ##
##                       ##
###########################

def cy_ls(chem):                return(ls(chem))
def cy_version():               return(version())
def cy_path():                  return(path())
def cy_mkdire(chem, nom):       return(mkdir(chem, nom))
def cy_mkdir(chem, nom):        return(mkdir(chem, nom))
def cy_wget(chem, nom, addr):   return(wget(chem, nom, addr))
def cy_mkfil(chem, nom, text):  return(mkfil(chem, nom, text))
def cy_rfil(chem):              return(open(chem, "r").read())
def cy_rfil_rela(chem, nom):    return(rfil(chem, nom))
def cy_run(ipt):                return(run(ipt))