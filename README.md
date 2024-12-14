#### Raëd CHAMI  (Groupe TP 1)
# Traceur d'allocation : MemTrack

## Structure du projet  
Le dossier contient plusieurs répertoire:
- ```src/``` qui contient le fichier source du traceur ```mtrack_05.c```  
- ```include/``` qui contient le fichier header du traceur
- ```tests/``` qui contient les tests unitaires

La bibliothèque se situe dans le répertoire courant du projet.
## Compilation 
Pour utiliser le traceur sur un test unitaire souhaité, il faut spécifier le nom du fichier test dans le Makefile à la variable ```UNITARY_TEST```.  

Pour compiler la bibliothèque et le test associé, utilisez ```make```.  
Le Makefile réplique les commandes suivantes : 
```
gcc -c src/mtrack_05.c -fPIC -o mtrack_05.o
gcc -shared mtrack_05.o -o libmtrack.so
gcc -include include/mtrack_05.h -c tests/utest_free.c -o tests/utest_free.o
clang -Wl,-rpath,. -L. -lmtrack tests/utest_free.o -o main
```  

## Démonstration  
Le traceur d'allocation affiche à l'exécution un rapport d'analyse final détaillé, imitant les exemples montrés dans le sujet. 
```
–activate tracker – [VERS.5]–
––––––––––––––––-
Dec 14 2024 10:36:39
USER : raedc
HOST : DESKTOP-P90N6MI
–––––––––––––––––––––––
in file <tests/utest_free.c> function <main> line <06> - (call#01) - malloc(1)->0x7fffd461a6f0
in file <tests/utest_free.c> function <main> line <08> - (call#01) - free(0x7fffd461a6f0)
in file <tests/utest_free.c> function <main> line <09> - (call#01) - free(0x7fffd461a6f0) - ERROR : double free detected
in file <tests/utest_free.c> function <main> line <011> - (call#02) - free(0x7fffdc6e3368) - ERROR : illegal address -> ignored
–––––––––––––––––––––––
BILAN FINAL
total mémoire allouée : 1 octet
total mémoire libérée : 1 octet
ratio                 : 100.00%
<malloc>              : 1 appel
<calloc>              : 0 appel
<realloc>             : 0 appel
<free>                : 1 appel correct
                      : 2 appels incorrect
–––––––––––––––––––––––
```

## Documentation  
Les programmes du projet ont été documenté avec l'outil ```doxygen```.  
Pour la générer, utiliser la commande :  
```
doxygen
```

## Versions Bêta du traceur (mtrack_01 => mtrack_04)  
Il est possible de tester les différentes versions du traceur précèdant la version évoluée ```mtrack_05```.  

- ```mtrack_01``` : Pour compiler cette version du traceur, utilisez uniquement la commande  
```gcc -Wall track_01.c -o track_01```  

- ```mtrack_02``` : Pour compiler cette version du traceur, utilisez uniquement la commande  
```gcc -Wall track_02.c -o track_02``` 

- ```mtrack_03``` : Pour compiler cette version du traceur, utilisez  
```
gcc -c mtrack_03.c -o mtrack_03.o
gcc -include mtrack_03.h -c track_03.c -o track_03.o
gcc mtrack_03.o track_03.o -o main_03
```  

- ```mtrack_04``` : Pour compiler cette version du traceur, utilisez  
```
gcc -c mtrack_04.c -o mtrack_04.o
gcc -include mtrack_04.h -c track_04.c -o track_04.o
gcc mtrack_04.o track_04.o -o main_04 
```  
