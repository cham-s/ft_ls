# ft_ls
implementation of the shell command ls with the following options : -A -R -S -a -p -d -t -1 -f -r

```shell
sh3.2$>./ft_ls -lRA
total 16
drwxr-xr-x  12 cattouma  staff   408 Mar 24 18:07 .git
-rw-r--r--   1 cattouma  staff  1487 Mar 24 18:07 Makefile
-rw-r--r--   1 cattouma  staff     9 Mar 24 18:07 auteur
drwxr-xr-x   3 cattouma  staff   102 Mar 24 18:07 includes
drwxr-xr-x  80 cattouma  staff  2720 Mar 24 18:12 libft
drwxr-xr-x  20 cattouma  staff   680 Mar 24 18:07 sources

./.git:
total 56
-rw-r--r--   1 cattouma  staff    23 Mar 24 18:07 HEAD
-rw-r--r--   1 cattouma  staff   305 Mar 24 18:07 config
-rw-r--r--   1 cattouma  staff    73 Mar 24 18:07 description
drwxr-xr-x  11 cattouma  staff   374 Mar 24 18:07 hooks
-rw-r--r--   1 cattouma  staff  8360 Mar 24 18:07 index
drwxr-xr-x   3 cattouma  staff   102 Mar 24 18:07 info
drwxr-xr-x   4 cattouma  staff   136 Mar 24 18:07 logs
drwxr-xr-x   4 cattouma  staff   136 Mar 24 18:07 objects
-rw-r--r--   1 cattouma  staff   670 Mar 24 18:07 packed-refs
drwxr-xr-x   5 cattouma  staff   170 Mar 24 18:07 refs
...
./includes:
total 8
-rw-r--r--  1 cattouma  staff  3946 Mar 24 18:07 ft_ls.h

./libft:
total 616
-rwxr-xr-x  1 cattouma  staff  2272 Mar 24 18:07 Makefile
-rw-r--r--  1 cattouma  staff  1299 Mar 24 18:07 ft_atoi.c
-rw-r--r--  1 cattouma  staff   973 Mar 24 18:07 ft_bzero.c
-rw-r--r--  1 cattouma  staff  1010 Mar 24 18:07 ft_isalnum.c
-rw-r--r--  1 cattouma  staff  1025 Mar 24 18:07 ft_isalpha.c
...
./libft/includes:
total 16
-rwxr-xr-x  1 cattouma  staff  4802 Mar 24 18:07 libft.h

./sources:
total 152
-rw-r--r--  1 cattouma  staff  6148 Mar 24 18:07 .DS_Store
-rw-r--r--  1 cattouma  staff  4096 Mar 24 18:07 ._.DS_Store
-rw-r--r--  1 cattouma  staff  2696 Mar 24 18:07 display.c
-rw-r--r--  1 cattouma  staff  2788 Mar 24 18:07 display2.c
-rw-r--r--  1 cattouma  staff  1928 Mar 24 18:07 display3.c
-rw-r--r--  1 cattouma  staff  2139 Mar 24 18:07 filelist.c
-rw-r--r--  1 cattouma  staff  2095 Mar 24 18:07 format.c
-rw-r--r--  1 cattouma  staff  3087 Mar 24 18:07 format2.c
-rw-r--r--  1 cattouma  staff  3577 Mar 24 18:07 format3.c
-rw-r--r--  1 cattouma  staff  1544 Mar 24 18:07 initopt.c
-rw-r--r--  1 cattouma  staff  2809 Mar 24 18:07 launcher.c
-rw-r--r--  1 cattouma  staff  1487 Mar 24 18:07 main.c
...
```
```shell
sh3.2$>./ft_ls -l
total 16
-rw-r--r--   1 cattouma  staff   508 Mar 24 18:14 Makefile
-rw-r--r--   1 cattouma  staff     9 Mar 23 22:40 auteur
drwxr-xr-x   3 cattouma  staff   102 Mar 24 05:42 includes
drwxr-xr-x  83 cattouma  staff  2822 Mar 24 18:14 libft
drwxr-xr-x   4 cattouma  staff   136 Mar 24 18:14 sources
```

```shell
sh3.2$>./ft_ls -lp
total 16
-rw-r--r--   1 cattouma  staff   508 Mar 24 18:14 Makefile
-rw-r--r--   1 cattouma  staff     9 Mar 23 22:40 auteur
drwxr-xr-x   3 cattouma  staff   102 Mar 24 05:42 includes/
drwxr-xr-x  83 cattouma  staff  2822 Mar 24 18:14 libft/
drwxr-xr-x   4 cattouma  staff   136 Mar 24 18:14 sources/
```

```shell
sh3.2$>./ft_ls -lpA
total 16
drwxr-xr-x  12 cattouma  staff   408 Mar 24 18:07 .git
-rw-r--r--   1 cattouma  staff   508 Mar 24 18:14 Makefile
-rw-r--r--   1 cattouma  staff     9 Mar 23 22:40 auteur
drwxr-xr-x   3 cattouma  staff   102 Mar 24 05:42 includes/
drwxr-xr-x  83 cattouma  staff  2822 Mar 24 18:14 libft/
drwxr-xr-x   4 cattouma  staff   136 Mar 24 18:14 sources/
```


