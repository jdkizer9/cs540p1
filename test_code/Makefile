.PHONY: all
all: parser_test gen

.PHONY: gen
gen:
	g++ -O -Wall -Wno-unused -o gen XmlGenerator.cpp gen.cpp

.PHONY: parser_test
# Use -O or -O5 for performance testing.  Don't compile with -DNDEBUG, because
# it will compile out the asserts that check for bad XML.
#
# For memory tracing, compile with
#
#     -g -fno-inline -rdynamic -DCS540_MEMTRACE
#
# and do not turn on optimization.
parser_test:
	g++ -O -Wall -Wno-unused -o parser_test parser_test.cpp Element.cpp Parser.cpp String.cpp Text.cpp

clean:
	rm -rf gen parser_test *.o
