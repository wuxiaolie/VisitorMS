CC = gcc
SUBDIRS = src \
		  obj
OBJS = client.o key.o
BIN = client
OBJS_DIR = obj
BIN_DIR = bin
export CC OBJS BIN OBJS_DIR BIN_DIR

all: CHECK_DIR $(SUBDIRS)
CHECK_DIR :
	mkdir -p $(BIN_DIR)
$(SUBDIRS) : ECHO
	make -C $@
ECHO:
	@echo begin compile client!
clean:
	@$(RM) $(OBJS_DIR)/*.O
	@rm -rf $(BIN_DIR)
