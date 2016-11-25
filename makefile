PAROBJECTS = Parser.o
CPPFLAGS = -g -Wall
IN = PA.log
OUT = parsed
PLOTCONFIG = PlotOptNum PlotOptTime

parser: $(PAROBJECTS)
	gcc $(CPPFLAGS) -o parser $(PAROBJECTS)

%.o: %.c %.h
	gcc $(CPPFLAGS) -c -o $*.o $*.c

.PHONY: clean
clean:
	rm *.o
	rm *.out

$(OUT): parser $(IN)
	./parser $(IN) $(OUT)

PA.log:
	curl rogue-01.cs.uni-bonn.de/PA.log > PA.log

plot: $(OUT) $(PLOTCONFIG)
	gnuplot $(PLOTCONFIG)
