# config
target	= golden
headers = 
COMPILER 	=	gcc
CFLAGS 		=	-Wall -O1
LIBS 		=	-lm
includes	=	-I. -Isrc
# logic
DIR_SRC		=	src
DIR_OBJ		=	obj
FILES_SRC	=	$(wildcard $(DIR_SRC)/*.c)
TMP			=	$(notdir $(FILES_SRC))
FILES_OBJ	=	$(addprefix $(DIR_OBJ)/,$(TMP:.c=.o))

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c $(headers)
	@echo -n "- compiling $<... "
	@mkdir -p $(DIR_OBJ)
	@$(COMPILER) $< -c -o $@ $(includes) $(CFLAGS) $(LIBS)
	@echo "done"

$(target): $(FILES_OBJ) $(headers)
	@echo "- compiling target..."
	@echo -n "  "
	$(COMPILER) $^ -o $@ $(includes) $(CFLAGS) $(LIBS)
	@echo "> COMPLETED: $(target) compiled."

.PHONY: clean
clean:
	@rm -rf $(DIR_OBJ)
	@rm -f $(target)
	@echo "> $(target) cleaned"