Requires plotutils.

argv[1] : # of iterations

argv[2] : # of points

argv[3] : srand

```
    81	10:54	setenv LD_LIBRARY_PATH $PWD/plotutils/lib/
   130	11:09	g++ particleman.cpp -I plotutils/include -Lplotutils/lib -lplot
   131	11:09	./a.out 1000 100 100
```
