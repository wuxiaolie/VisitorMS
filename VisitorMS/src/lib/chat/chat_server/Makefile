CC = gcc
SUBDIRS = src \
		  obj
OBJS = server.o data.o key.o
BIN = server
OBJS_DIR = obj
BIN_DIR = bin
export CC OBJS BIN OBJS_DIR BIN_DIR

all: CHECK_DIR $(SUBDIRS)
CHECK_DIR :
	@mkdir -p $(BIN_DIR)
$(SUBDIRS) : ECHO
	@make -C $@
ECHO:
	@echo "prepare to compile server "
clean:
	@$(RM) $(OBJS_DIR)/*.o
	@rm -rf $(BIN_DIR)
	@echo "server cleanup complete. "

