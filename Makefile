all: algo1 algo2

algo1: rpd_main.c rpd_opponent1.c rpd.h rpd_algo1.c
	gcc rpd_main.c rpd_opponent1.c rpd_algo1.c -o algo1

algo2: rpd_main.c rpd_opponent1.c rpd.h rpd_algo2.c
	gcc rpd_main.c rpd_opponent1.c rpd_algo2.c -o algo2

clean:
	rm algo1 algo2
