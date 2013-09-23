################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Attributes.cpp \
../DataBase.cpp \
../Harrison_Engine.cpp \
../JoshA_Engine.cpp \
../JoshA_main.cpp \
../JoshKruger_Engine.cpp \
../Parser.cpp \
../Relations.cpp \
../main.cpp 

OBJS += \
./Attributes.o \
./DataBase.o \
./Harrison_Engine.o \
./JoshA_Engine.o \
./JoshA_main.o \
./JoshKruger_Engine.o \
./Parser.o \
./Relations.o \
./main.o 

CPP_DEPS += \
./Attributes.d \
./DataBase.d \
./Harrison_Engine.d \
./JoshA_Engine.d \
./JoshA_main.d \
./JoshKruger_Engine.d \
./Parser.d \
./Relations.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


