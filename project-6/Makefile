all: parta partb partc partd

run: partd
	./partd

parta: parta.c
	gcc parta.c -o parta -lpthread
	
partb: partb.c
	gcc partb.c -o partb -lpthread
	
partc: partc.c
	gcc partc.c -o partc -lpthread
	
partd: partd.c
	gcc partd.c -o partd -lpthread

clean:
	rm parta
	rm partb
	rm partc
	rm partd

