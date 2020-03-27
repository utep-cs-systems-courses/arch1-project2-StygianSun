all:
	(cd demos; make)
	(cd project/src; make)

clean:
	(cd demos; make clean)
	(cd project/src; make clean)
	(cd project; rm -rf lib h)
