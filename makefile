CPPFLAGS = -g -Wall
IN = PA.log
OUT = parsed.out
TIMED = timeOut.out
PLOTCONFIG = PlotOptNum PlotOptTime

Parser: Parser.o
	gcc $(CPPFLAGS) -o Parser Parser.o

%.o: %.c %.h
	gcc $(CPPFLAGS) -c -o $*.o $*.c

.PHONY: clean
clean:
	rm -f *.o
	rm -f *.out
	rm -f $$(find . -maxdepth 1 -type f -executable)
	rm -f *.log
	rm -f *.jpg

$(OUT): Parser $(IN)
	./Parser $(IN) $(OUT)

$(IN):
	wget rogue-01.cs.uni-bonn.de/PA.log

plot: $(OUT) PlotOptNum PlotOptTime
	gnuplot PlotOptNum
	gnuplot PlotOptTime

TimeSelect: TimeSelect.o
	gcc $(CPPFLAGS) -o TimeSelect TimeSelect.o

$(TIMED): TimeSelect $(OUT)
	./TimeSelect $(OUT) $(TIMED) 
