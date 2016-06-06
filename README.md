     1	10:21	~/bin/fvmw2 &
     2	10:21	ls
     3	10:21	cd $U
     4	10:21	ls
     5	10:21	cd clpu/
     6	10:21	ls
     7	10:21	cat aspen/results/clpu.runner.log.gz
     8	10:21	1 ; 2c1 ; 2c1 ; 2c1 ; 2c1 ; 2c1 ; 2c1 ; 2c1 ; 2c1 ; 2c1 ; 2c1 ; 2c1 ; 2c1 ; 2c1 ; 2c1 ; 2c
     9	10:21	gzcat aspen/results/clpu.runner.log.gz
    10	10:21	ls
    11	10:22	ls
    12	10:22	cd mirror/
    13	10:22	ls
    14	10:22	cd data/
    15	10:22	ls
    16	10:22	cd Tuning/
    17	10:22	ls
    18	10:22	cd tun
    19	10:22	cd ../
    20	10:22	ls
    21	10:22	vi global_config/global_config.pnr
    22	10:22	cdw
    23	10:22	ls
    24	10:22	pwd
    25	10:22	ls
    26	10:22	cd Tuning/
    27	10:22	ls
    28	10:22	find . -type f
    29	10:22	find -type f
    30	10:23	foreach x ( `find -type f ` )
    31	10:23	cd ..
    32	10:23	ls
    33	10:23	foreach x ( `find -type f ` )
    34	10:24	ls
    35	10:24	cd Tuning/
    36	10:24	ls
    37	10:24	cd tune_files/
    38	10:24	ls
    39	10:24	cd general/
    40	10:24	ls
    41	10:28	cd $PROJ_ARCHIVE/power/pnr/results/deep_sleep_latest/
    42	10:28	ls
    43	10:28	cd ASPEN/
    44	10:28	ls
    45	10:28	cd indicator/
    46	10:28	ls
    47	10:28	cd ../../
    48	10:28	ls
    49	10:28	cd ../
    50	10:28	ls
    51	10:29	ls PNR_Power_Virus_pnr1_ww32/ASPEN/indicator/bptargettagdnm/results/bptargettagdnm.summary.gz
    52	10:29	less PNR_Power_Virus_pnr1_ww32/ASPEN/indicator/bptargettagdnm/results/bptargettagdnm.summary.gz
    53	10:29	gzgrep 'State' PNR_Power_Virus_pnr1_ww32/ASPEN/indicator/bptargettagdnm/results/bptargettagdnm.summary.gz
    54	10:29	gzgrep 'State' PNR_Power_Virus_pnr1_ww*/ASPEN/indicator/bptargettagdnm/results/bptargettagdnm.summary.gz
    55	10:29	ls ~mssikder/bptargettagdnm.map
    56	10:30	cd
    57	10:30	co $PROJ_ARCHIVE/power/pnr/mirror/latest/sfv/db/sessions/bptargettagdnm/sch2rtl/bptargettagdnm.map,v
    58	10:30	diff ~mssikder/bptargettagdnm.map bptargettagdnm.map
    59	10:31	diff ~mssikder/bptargettagdnm.map bptargettagdnm.map | wc -l
    60	10:52	cd
    61	10:52	cd fdc_arch/
    62	10:52	ls
    63	10:52	cd code/
    64	10:52	ls
    65	10:52	cd particleman/
    66	10:52	ls
    67	10:52	./good.exe
    68	10:52	./working.exe
    69	10:52	ls plotutils/
    70	10:52	ls plotutils/lib/
    71	10:53	setenv LD_PATH $PWD/plotutils/lib
    72	10:53	./working.exe
    73	10:53	setenv LD_LINPATH $PWD/plotutils/lib
    74	10:53	setenv LD_LIBPATH $PWD/plotutils/lib
    75	10:53	./working.exe
    76	10:53	./good.exe
    77	10:53	setenv LIBPATH $PWD/plotutils/lib
    78	10:53	./working.exe
    79	10:54	setenv LIBPATH $PWD/plotutils/lib/
    80	10:54	./working.exe
    81	10:54	setenv LD_LIBRARY_PATH $PWD/plotutils/lib/
    82	10:54	./working.exe
    83	10:54	./good.exe
    84	10:54	ls
    85	10:55	./one_charge
    86	10:55	./one_charge.exe
    87	10:55	./looper.pl
    88	10:55	ls
    89	10:55	./one_charge_wvectors.exe
    90	10:56	ls
    91	10:56	cd .
    92	10:56	ls
    93	10:56	cd ..
    94	10:56	ls
    95	10:56	ls rw
    96	10:56	cd particleman/
    97	10:56	ls
    98	10:56	gvim particleman.cpp
    99	10:57	./good.exe 100 10 1
   100	10:57	./good.exe 100 100 100
   101	10:57	./good.exe 1000 100 100
   102	10:57	./good.exe 100000 100 100
   103	10:58	./one_charge.exe 100000 100 100
   104	10:59	./one_charge_wforcebubbles.exe 100000 100 100
   105	11:00	./one_charge_wvectors.exe 100000 100 100
   106	11:02	./one_charge.exe 100000 1000 100
   107	11:06	history > his.txt
   108	11:06	ls
   109	11:06	gcc particleman.cpp
   110	11:06	gcc particleman.cpp -I plotutils/include
   111	11:06	gcc particleman.cpp -I plotutils/include -l plotutils/lib
   112	11:06	ls
   113	11:06	gvim particleman.cpp
   114	11:07	ll
   115	11:07	gcc oirg.cpp -I plotutils/include -l plotutils/lib
   116	11:07	gcc orig.cpp -I plotutils/include -l plotutils/lib
   117	11:07	g++ particleman.cpp -I plotutils/include -l plotutils/lib
   118	11:07	g++ orig.cpp -I plotutils/include -l plotutils/lib
   119	11:07	icc orig.cpp -I plotutils/include -l plotutils/lib
   120	11:08	g++ particleman.cpp -I plotutils/include -l plotutils/lib
   121	11:08	g++ particleman.cpp -I plotutils/include -l plotutils/lib
   122	11:08	g++ particleman.cpp -I plotutils/include -l plotutils/lib
   123	11:09	ls plotutils/lib/
   124	11:09	g++ particleman.cpp -I plotutils/include -Lplotutils/lib
   125	11:09	g++ particleman.cpp -I plotutils/include -Lplotutils/lib -lplotutils
   126	11:09	ls plotutils/lib/
   127	11:09	g++ particleman.cpp -I plotutils/include -Lplotutils/lib -lplot
   128	11:09	ls
   129	11:09	./a.out 1000 100 100
   130	11:09	g++ particleman.cpp -I plotutils/include -Lplotutils/lib -lplot
   131	11:09	./a.out 1000 100 100
   132	11:10	g++ particleman.cpp -I plotutils/include -Lplotutils/lib -lplot
   133	11:10	./a.out 1000 100 100
   134	11:10	g++ particleman.cpp -I plotutils/include -Lplotutils/lib -lplot
   135	11:10	./a.out 1000 100 100
   136	11:10	./a.out 10000 100 100
   137	11:11	history > his.txt
