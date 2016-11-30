CPPFLAGS = -g -Wall
IN = PA.log
OUT = parsed
PLOTCONFIG = PlotOptNum PlotOptTime

Parser: Parser.o
	gcc $(CPPFLAGS) -o Parser Parser.o

%.o: %.c %.h
	gcc $(CPPFLAGS) -c -o $*.o $*.c

.PHONY: clean
clean:
	rm *.o
	rm *.out

$(OUT): Parser $(IN)
	./Parser $(IN) $(OUT)

PA.log:
	curl rogue-01.cs.uni-bonn.de/PA.log > PA.log

plot: $(OUT) PlotOptNum PlotOptTime
	gnuplot PlotOptNum 
	gnuplot PlotOptTime

TimeSelect: TimeSelect.o
	gcc $(CPPFLAGS) -o TimeSelect TimeSelect.o
