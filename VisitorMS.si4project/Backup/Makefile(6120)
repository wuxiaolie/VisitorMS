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
	#创建可执行程序所在的目录
	mkdir -p $(BIN_DIR)
$(SUBDIRS) : ECHO
	make -C $@
ECHO:
	@echo begin compile server
clean:
	@$(RM) $(OBJS_DIR)/*.o
	@rm -rf $(BIN_DIR)
