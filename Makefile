
INCLUDE_THIRD_PARTY_INIH=./third-party/inih

INCLUDE_THIRD_PARTY= -I ${INCLUDE_THIRD_PARTY_INIH} 
INCLUDE=./include

SRC=./src

SRC_THIRD_PARTY=./third-party

OBJ=./obj

OBJ_THIRD_PARTY=./obj/third-party

LIB=./lib
CC=gcc

FLAGS=  -g -O0
CFLAGS=''

all: libopt PSO PSO_ini AIWPSO BA FPA FA CS CS_ini GP GA BHA WCA MBO GSGP BGSGP ABC HS IHS PSF-HS TensorPSO TensorAIWPSO TensorBA TensorFPA TensorFA TensorCS TensorBHA TensorABC TensorHS TensorIHS TensorPSF-HS

libopt: $(LIB)/libopt.a
	echo "libopt.a built..."

$(LIB)/libopt.a: \
$(OBJ)/common.o \
$(OBJ)/function.o \
$(OBJ)/random.o \
$(OBJ)/pso.o \
$(OBJ)/ba.o \
$(OBJ)/fpa.o \
$(OBJ)/fa.o \
$(OBJ)/cs.o \
$(OBJ)/gp.o \
$(OBJ)/ga.o \
$(OBJ)/bha.o \
$(OBJ)/wca.o \
$(OBJ)/mbo.o \
$(OBJ)/abc.o \
$(OBJ)/hs.o \
$(OBJ_THIRD_PARTY)/inih/ini.o \
$(OBJ_THIRD_PARTY)/inih/ini_reader.o \

	ar csr $(LIB)/libopt.a \
$(OBJ)/common.o \
$(OBJ)/function.o \
$(OBJ)/random.o \
$(OBJ)/pso.o \
$(OBJ)/ba.o \
$(OBJ)/fpa.o \
$(OBJ)/fa.o \
$(OBJ)/cs.o \
$(OBJ)/gp.o \
$(OBJ)/ga.o \
$(OBJ)/bha.o \
$(OBJ)/wca.o \
$(OBJ)/mbo.o \
$(OBJ)/abc.o \
$(OBJ)/hs.o \
$(OBJ_THIRD_PARTY)/inih/ini.o \
$(OBJ_THIRD_PARTY)/inih/ini_reader.o \

$(OBJ_THIRD_PARTY)/inih/ini.o: $(SRC_THIRD_PARTY)/inih/ini.c
	$(CC) $(FLAGS) -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -c $(SRC_THIRD_PARTY)/inih/ini.c -o $(OBJ_THIRD_PARTY)/inih/ini.o

$(OBJ_THIRD_PARTY)/inih/ini_reader.o: $(SRC_THIRD_PARTY)/inih/ini.c
	$(CC) $(FLAGS) -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -c $(SRC_THIRD_PARTY)/inih/ini_reader.c -o $(OBJ_THIRD_PARTY)/inih/ini_reader.o

$(OBJ)/common.o: $(SRC)/common.c
	$(CC) $(FLAGS) -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -c $(SRC)/common.c -o $(OBJ)/common.o

$(OBJ)/function.o: $(SRC)/function.c
	$(CC) $(FLAGS) -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -c $(SRC)/function.c -o $(OBJ)/function.o

$(OBJ)/random.o: $(SRC)/random.c
	$(CC) $(FLAGS) -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -c $(SRC)/random.c -o $(OBJ)/random.o

$(OBJ)/pso.o: $(SRC)/pso.c
	$(CC) $(FLAGS) -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -c $(SRC)/pso.c -o $(OBJ)/pso.o

$(OBJ)/ba.o: $(SRC)/ba.c
	$(CC) $(FLAGS) -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -c $(SRC)/ba.c -o $(OBJ)/ba.o

$(OBJ)/fpa.o: $(SRC)/fpa.c
	$(CC) $(FLAGS) -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -c $(SRC)/fpa.c -o $(OBJ)/fpa.o

$(OBJ)/fa.o: $(SRC)/fa.c
	$(CC) $(FLAGS) -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -c $(SRC)/fa.c -o $(OBJ)/fa.o

$(OBJ)/cs.o: $(SRC)/cs.c
	$(CC) $(FLAGS) -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -c $(SRC)/cs.c -o $(OBJ)/cs.o

$(OBJ)/gp.o: $(SRC)/gp.c
	$(CC) $(FLAGS) -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -c $(SRC)/gp.c -o $(OBJ)/gp.o

$(OBJ)/ga.o: $(SRC)/ga.c
	$(CC) $(FLAGS) -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -c $(SRC)/ga.c -o $(OBJ)/ga.o

$(OBJ)/bha.o: $(SRC)/bha.c
	$(CC) $(FLAGS) -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -c $(SRC)/bha.c -o $(OBJ)/bha.o

$(OBJ)/wca.o: $(SRC)/wca.c
	$(CC) $(FLAGS) -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -c $(SRC)/wca.c -o $(OBJ)/wca.o

$(OBJ)/mbo.o: $(SRC)/mbo.c
	$(CC) $(FLAGS) -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -c $(SRC)/mbo.c -o $(OBJ)/mbo.o

$(OBJ)/abc.o: $(SRC)/abc.c
	$(CC) $(FLAGS) -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -c $(SRC)/abc.c -o $(OBJ)/abc.o

$(OBJ)/hs.o: $(SRC)/hs.c
	$(CC) $(FLAGS) -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -c $(SRC)/hs.c -o $(OBJ)/hs.o

PSO: examples/PSO.c
	$(CC) $(FLAGS) examples/PSO.c -o examples/bin/PSO -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -L $(LIB) -lopt -lm;

PSO_ini: examples/PSO_ini.c
	$(CC) $(FLAGS) examples/PSO_ini.c -o examples/bin/PSO_ini -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -L $(LIB) -lopt -lm;

AIWPSO: examples/AIWPSO.c
	$(CC) $(FLAGS) examples/AIWPSO.c -o examples/bin/AIWPSO -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -L $(LIB) -lopt -lm;

BA: examples/BA.c
	$(CC) $(FLAGS) examples/BA.c -o examples/bin/BA -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -L $(LIB) -lopt -lm;

FPA: examples/FPA.c
	$(CC) $(FLAGS) examples/FPA.c -o examples/bin/FPA -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -L $(LIB) -lopt -lm;

FA: examples/FA.c
	$(CC) $(FLAGS) examples/FA.c -o examples/bin/FA -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -L $(LIB) -lopt -lm;

CS: examples/CS.c
	$(CC) $(FLAGS) examples/CS.c -o examples/bin/CS -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -L $(LIB) -lopt -lm;

CS_ini: examples/CS_ini.c
	$(CC) $(FLAGS) examples/CS_ini.c -o examples/bin/CS_ini -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -L $(LIB) -lopt -lm;

GP: examples/GP.c
	$(CC) $(FLAGS) examples/GP.c -o examples/bin/GP -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -L $(LIB) -lopt -lm;

GA: examples/GA.c
	$(CC) $(FLAGS) examples/GA.c -o examples/bin/GA -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -L $(LIB) -lopt -lm;

BHA: examples/BHA.c
	$(CC) $(FLAGS) examples/BHA.c -o examples/bin/BHA -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -L $(LIB) -lopt -lm;

WCA: examples/WCA.c
	$(CC) $(FLAGS) examples/WCA.c -o examples/bin/WCA -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -L $(LIB) -lopt -lm;

MBO: examples/MBO.c
	$(CC) $(FLAGS) examples/MBO.c -o examples/bin/MBO -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -L $(LIB) -lopt -lm;

GSGP: examples/GSGP.c
	$(CC) $(FLAGS) examples/GSGP.c -o examples/bin/GSGP -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -L $(LIB) -lopt -lm;

BGSGP: examples/BGSGP.c
	$(CC) $(FLAGS) examples/BGSGP.c -o examples/bin/BGSGP -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -L $(LIB) -lopt -lm;

ABC: examples/ABC.c
	$(CC) $(FLAGS) examples/ABC.c -o examples/bin/ABC -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -L $(LIB) -lopt -lm;

HS: examples/HS.c
	$(CC) $(FLAGS) examples/HS.c -o examples/bin/HS -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -L $(LIB) -lopt -lm;

IHS: examples/IHS.c
	$(CC) $(FLAGS) examples/IHS.c -o examples/bin/IHS -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -L $(LIB) -lopt -lm;

PSF-HS: examples/PSF-HS.c
	$(CC) $(FLAGS) examples/PSF-HS.c -o examples/bin/PSF-HS -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -L $(LIB) -lopt -lm;

TensorPSO: examples/TensorPSO.c
	$(CC) $(FLAGS) examples/TensorPSO.c -o examples/bin/TensorPSO -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -L $(LIB) -lopt -lm;

TensorAIWPSO: examples/TensorAIWPSO.c
	$(CC) $(FLAGS) examples/TensorAIWPSO.c -o examples/bin/TensorAIWPSO -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -L $(LIB) -lopt -lm;

TensorBA: examples/TensorBA.c
	$(CC) $(FLAGS) examples/TensorBA.c -o examples/bin/TensorBA -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -L $(LIB) -lopt -lm;

TensorFPA: examples/TensorFPA.c
	$(CC) $(FLAGS) examples/TensorFPA.c -o examples/bin/TensorFPA -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -L $(LIB) -lopt -lm;

TensorFA: examples/TensorFA.c
	$(CC) $(FLAGS) examples/TensorFA.c -o examples/bin/TensorFA -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -L $(LIB) -lopt -lm;

TensorCS: examples/TensorCS.c
	$(CC) $(FLAGS) examples/TensorCS.c -o examples/bin/TensorCS -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -L $(LIB) -lopt -lm;

TensorBHA: examples/TensorBHA.c
	$(CC) $(FLAGS) examples/TensorBHA.c -o examples/bin/TensorBHA -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -L $(LIB) -lopt -lm;

TensorABC: examples/TensorABC.c
	$(CC) $(FLAGS) examples/TensorABC.c -o examples/bin/TensorABC -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -L $(LIB) -lopt -lm;

TensorHS: examples/TensorHS.c
	$(CC) $(FLAGS) examples/TensorHS.c -o examples/bin/TensorHS -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -L $(LIB) -lopt -lm;

TensorIHS: examples/TensorIHS.c
	$(CC) $(FLAGS) examples/TensorIHS.c -o examples/bin/TensorIHS -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -L $(LIB) -lopt -lm;

TensorPSF-HS: examples/TensorPSF-HS.c
	$(CC) $(FLAGS) examples/TensorPSF-HS.c -o examples/bin/TensorPSF-HS -I $(INCLUDE) $(INCLUDE_THIRD_PARTY) -L $(LIB) -lopt -lm;

clean:
	rm -f $(LIB)/lib*.a; rm -f $(OBJ)/*.o; rm -f $(OBJ)/third-party/inih/*.o; rm -rf examples/bin/*
