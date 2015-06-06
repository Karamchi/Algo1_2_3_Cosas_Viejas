SRC=*.cpp
OBJ=$(SRC:%.cpp=%)

run: clean buildTests runTests

all: buildTests

clean:
	rm -f testArreglo testConj testConjAcotado testDicc testLista testVector

buildTests: testArreglo testConj testConjAcotado testDicc testLista testVector

runTests: buildTests
	./testArreglo
	./testConj
	./testConjAcotado
	./testDicc
	./testLista
	./testVector

testArreglo:
	$(CXX) test.cpp testArreglo.cpp -o testArreglo
testConj:
	$(CXX) test.cpp testConj.cpp -o testConj
testConjAcotado:
	$(CXX) test.cpp ../aed2/ConjAcotado.cpp testConjAcotado.cpp -o testConjAcotado
testDicc:
	$(CXX) test.cpp testDicc.cpp -o testDicc
testLista:
	$(CXX) test.cpp testLista.cpp -o testLista
testVector:
	$(CXX) test.cpp testVector.cpp -o testVector
