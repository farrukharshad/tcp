#
# Makefile
# Created On: 
# Author	: Farrukh Arshad <farrukh.arshad@gmail.com>
#

CC      		= $(CROSS_COMPILE)gcc
APP     		= tcp 
OBJ_DIR 		= obj
SRC_DIR 		= src
CHK_DIR_EXISTS 	= test -d
MKDIR         	= mkdir -p

# Project Source Files
C_SOURCES += $(SRC_DIR)/tcp.c
		  
OBJECTS   += $(OBJ_DIR)/tcp.o
		  
INCLUDES  += -Iinc

.PHONEY : all
all: $(APP)

# Link Objects & Produce Output
$(APP): $(OBJECTS)
		@echo ""
		@echo "Linking..." $(APP)
		@$(CC) $(LDFLAGS) $(OBJECTS) -o $(APP)	

# Compile all objects
$(OBJ_DIR)/%.o : %.c
	@$(CHK_DIR_EXISTS) $(OBJ_DIR) || $(MKDIR) $(OBJ_DIR) 
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	
.PHONEY : clean
clean:
	@echo ""
	@echo "Cleaning..."
	@rm -rf $(OBJECTS) $(APP) $(OBJ_DIR)
	@echo "DONE"
	
.PHONEY : install
install:
	@echo ""
	@echo "Installing..."
	@cp $(APP) $(TARGETFS)/usr/bin
	
vpath %.c $(SRC_DIR)
vpath %.o $(OBJ_DIR)
