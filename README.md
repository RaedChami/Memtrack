#### Raëd Chami  (Groupe TP 1)
# Traceur d'allocation : MemTrack

## Structure du dossier Traceur  
Le dossier contient plusieurs répertoire:
- ```lib/``` qui contient la bibliothèque compilée.
- ```src/``` qui contient le fichier source du traceur ```mtrack_05.c```  
- ```include/``` qui contient le fichier header du traceur
## Compilation 
Pour utiliser le traceur sur un test unitaire souhaité, il faut indiquer dans le Makefile le nom du fichier test.c à la variable ```MAIN```.  

Pour compiler la bibliothèque et le test associé, utilisez ```make```.  
La commande réplique les commandes suivantes : 
```
gcc -c src/mtrack_05.c -fPIC -o mtrack_05.o
gcc -shared mtrack_05.o -o lib/libmtrack.so
gcc -include include/mtrack_05.h -c utest_free.c -o utest_free.o
clang -Wl,-rpath,. -L. -lmtrack utest_free.o -o main
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