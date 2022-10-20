:: Ce scripts sert a purger les logs oracle des environnents peoplesoft
:: le  08/07/2013 EBY
@echo off
cls
::initialisation de variables
set srv=%1
set orasid=%2
set string=%orasid%
call :LoCase string 
set string 
set orasid=%string%

SET USER=IFP1\adm_psv9
SET PASSWORD=Pe0p1eS@fT
set WORKDIR=\\irppsoft\peoplesoft9\commun\scripts


::definition du runtime
if !%time:~0,1%==! (set h=0%time:~1,1%) else (set h=%time:~0,2%)
set edate=%date:~0,2%-%date:~3,2%-%date:~6,8%_%h%%time:~3,2%%time:~6,2%

::fichiers script et log pour la purge
set LOGFILE=\\irppsoft\peoplesoft9\commun\scripts\log\PS_PURGE_LOGS_%srv%_%orasid%_%edate%.log

:start
echo *** start %date% %time% ***>%LOGFILE%
:: on oblige l'entree des parametres serveur (irntsv-oraps1,irntsv-dvoraps1,irntsv-dvoraps2)
if "%srv%"=="" goto :errparametre
:: on oblige l'entree des parametres suite (F91xxx,H91xxx)
if "%orasid%"=="" goto :errparametre
:: on regarde si le repertoire visé existe \\%srv%\L$\psoft\%suite%\webserv\%PIA%\servers\PIA\logs

set wrkpathalert=\\%srv%\l$\app\Oracle\diag\rdbms\%orasid%\%orasid%\alert

rem set wrkpathalert=\\irntsv-ps9ora\l$\app\Oracle\diag\rdbms\fs91prd\fs91prd\alert
set wrkpathtrace=\\%srv%\l$\app\Oracle\diag\rdbms\%orasid%\%orasid%\trace

rem set wrkpathtrace=\\irntsv-ps9ora\l$\app\Oracle\diag\rdbms\fs91prd\fs91prd\trace
if not exist %wrkpathalert% (
  goto :errconfalert
)

if not exist %wrkpathtrace% (
  goto :errconftrace
)

:main
call :purgealert
call :purgetrace
goto :end

:purgealert
::ici on purge les alertes de plus de 10 jours
echo lancement de la purge des alert logs associees a %orasid% >>%LOGFILE%
NET USE X: /DELETE /YES >>%LOGFILE%
net use /PERSISTENT:NO x: %wrkpathalert% >>%LOGFILE%
echo mapping x: %wrkpathalert% >> %LOGFILE%
forfiles /M *.* /P x:\ /D -10 /C "cmd /c DEL /Q @path" >> %LOGFILE%
echo unmapping x: %wrkpathalert% >> %LOGFILE%
NET USE X: /DELETE /YES >> %LOGFILE%
goto :eof

:purgetrace
::ici on purge les traces de plus de 10 jours
echo lancement de la purge des trace logs associees a %orasid% >>%LOGFILE%
NET USE X: /DELETE /YES >>%LOGFILE%
net use /PERSISTENT:NO x: %wrkpathtrace% >>%LOGFILE%
echo mapping x: %wrkpathtrace% >> %LOGFILE%
forfiles /M *.* /P x:\ /D -10 /C "cmd /c DEL /Q @path" >> %LOGFILE%
echo unmapping x: %wrkpathtrace% >> %LOGFILE%
NET USE X: /DELETE /YES >> %LOGFILE%
goto :eof

:LoCase
::passage des majuscules en minuscules
for %%i in ("A=a" "B=b" "C=c" "D=d" "E=e" "F=f" "G=g" "H=h" "I=i" "J=j" "K=k" "L=l" "M=m" "N=n" "O=o" 
"P=p" "Q=q" "R=r" "S=s" "T=t" "U=u" "V=v" "W=w" "X=x" "Y=y" "Z=z") do call set "%1=%%%1:%%~i%%"
goto :eof

:errparametre
:: gestion d'erreur de parametres en entree
set ERRLEV=1
echo l'un des parametres d'entree serveur, oracle_sid est manquant
goto :eof

:errconfalert
:: gestion d'erreur sur les repertoires inexistant
set ERRLEV=1
echo le repertoire %wrkpathalert% n'existe pas, verifier les parametres d'entree
goto :eof

:errconftrace
:: gestion d'erreur sur les repertoires inexistant
set ERRLEV=1
echo le repertoire %wrkpathtrace% n'existe pas, verifier les parametres d'entree
goto :eof

:end
:: fin de programme
echo purge terminée >>%LOGFILE%
echo %LOGFILE%>>%LOGFILE%
echo *** end %date% %time% *** >>%LOGFILE%
type %LOGFILE%
exit /B