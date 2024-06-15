CC = g++ 

SRC_DIR = src

SRCS = $(SRC_DIR)/printer.cpp $(SRC_DIR)/errorHandler.cpp $(SRC_DIR)/inputHandler.cpp $(SRC_DIR)/treatment.cpp $(SRC_DIR)/patient.cpp $(SRC_DIR)/patientManager.cpp  $(SRC_DIR)/transactionManager.cpp $(SRC_DIR)/reportManager.cpp $(SRC_DIR)/client.cpp $(SRC_DIR)/main.cpp 

TARGET_DIR = build

TARGET = Hospital_Management_System

all: clean $(TARGET)

$(TARGET): $(SRCS)
	mkdir ${TARGET_DIR}
	$(CC) -Iincludes/ -o ${TARGET_DIR}/$(TARGET) $(SRCS)

clean: 
	rm -rf $(TARGET_DIR)