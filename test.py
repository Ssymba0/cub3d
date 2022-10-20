import os
import sys
import time
import datetime

#initialisation de variables
srv = sys.argv[1]
orasid = sys.argv[2]
string = orasid
string = string.lower()
orasid = string

USER = "IFP1\adm_psv9"
PASSWORD = "Pe0p1eS@fT"
WORKDIR = "\\\\irppsoft\\peoplesoft9\\commun\\scripts"

#definition du runtime
h = time.strftime("%H")
edate = time.strftime("%d-%m-%Y_%H%M%S")

#fichiers script et log pour la purge
LOGFILE = "\\\\irppsoft\\peoplesoft9\\commun\\scripts\\log\\PS_PURGE_LOGS_" + srv + "_" + orasid + "_" + edate + ".log"

#on oblige l'entree des parametres serveur (irntsv-oraps1,irntsv-dvoraps1,irntsv-dvoraps2)
if srv == "":
	print("l'un des parametres d'entree serveur, oracle_sid est manquant")
	sys.exit(1)

#on oblige l'entree des parametres suite (F91xxx,H91xxx)
if orasid == "":
	print("l'un des parametres d'entree serveur, oracle_sid est manquant")
	sys.exit(1)

#on regarde si le repertoire visé existe \\%srv%\L$\psoft\%suite%\webserv\%PIA%\servers\PIA\logs
wrkpathalert = "\\\\%s\\l$\\app\\Oracle\\diag\\rdbms\\%s\\%s\\alert" % (srv, orasid, orasid)
wrkpathtrace = "\\\\%s\\l$\\app\\Oracle\\diag\\rdbms\\%s\\%s\\trace" % (srv, orasid, orasid)

if not os.path.exists(wrkpathalert):
	print("le repertoire %s n'existe pas, verifier les parametres d'entree" % wrkpathalert)
	sys.exit(1)

if not os.path.exists(wrkpathtrace):
	print("le repertoire %s n'existe pas, verifier les parametres d'entree" % wrkpathtrace)
	sys.exit(1)

#on purge les alertes de plus de 10 jours
print("lancement de la purge des alert logs associees a %s" % orasid)
os.system("NET USE X: /DELETE /YES >>%s" % LOGFILE)
os.system("net use /PERSISTENT:NO x: %s >>%s" % (wrkpathalert, LOGFILE))
print("mapping x: %s" % wrkpathalert)
os.system("forfiles /M *.* /P x:\ /D -10 /C \"cmd /c DEL /Q @path\" >> %s" % LOGFILE)
print("unmapping x: %s" % wrkpathalert)
os.system("NET USE X: /DELETE /YES >> %s" % LOGFILE)

#on purge les traces de plus de 10 jours
print("lancement de la purge des trace logs associees a %s" % orasid)
os.system("NET USE X: /DELETE /YES >>%s" % LOGFILE)
os.system("net use /PERSISTENT:NO x: %s >>%s" % (wrkpathtrace, LOGFILE))
print("mapping x: %s" % wrkpathtrace)
os.system("forfiles /M *.* /P x:\ /D -10 /C \"cmd /c DEL /Q @path\" >> %s" % LOGFILE)
print("unmapping x: %s" % wrkpathtrace)
os.system("NET USE X: /DELETE /YES >> %s" % LOGFILE)

#fin de programme
print("purge terminee")
print(LOGFILE)
print("*** end %s %s ***" % (time.strftime("%d-%m-%Y"), time.strftime("%H:%M:%S")))

#end of script