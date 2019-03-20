# config
target	= matrix
headers = 
# logic
COMPILER = gcc
CFLAGS = -Wall -O1
DIR_SRC		=	src
DIR_OBJ		=	obj
FILES_SRC	=	$(wildcard $(DIR_SRC)/*.c)
TMP			=	$(notdir $(FILES_SRC))
FILES_OBJ	=	$(addprefix $(DIR_OBJ)/,$(TMP:.c=.o))
includes	=	-I. -Isrc

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c $(headers)
	@echo -n "- compiling $<... "
	@mkdir -p $(DIR_OBJ)
	@$(COMPILER) $< -c -o $@ $(includes) $(CFLAGS) 
	@echo "done"

$(target): $(FILES_OBJ) $(headers)
	@echo "- compiling target..."
	@echo -n "  "
	$(COMPILER) $^ -o $@ $(includes) $(CFLAGS) 
	@echo "> COMPLETED: $(target) compiled."

.PHONY: clean
clean:
	@rm -rf $(DIR_OBJ)
	@rm -f $(target)
	@echo "> $(target) cleaned"