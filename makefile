CXX = g++
CFLAGS += -std=c++11
LIBS := -lcurl
SUBDIRS := src ./
USER_OBJS = 
FOLDERS = tmp
MAIN = tmp/cpp-curl-v1.o

OBJS += \
./tmp/main.o \
./tmp/Curl.o

all:$(FOLDERS) $(MAIN)

$(MAIN): $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	$(CXX) -c -D__GXX_EXPERIMENTAL_CXX0X__ $(CFLAGS) -Llibs/lib -o "$@" $(OBJS) $(USER_OBJS) $(LIBS)
	ar rvs cpp-curl-v1.a $(OBJS) $(USER_OBJS)

tmp/%.o:src/%.cpp
	@echo 'Building file: $<'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -Ilibs/include -Ihdr -O0 -g3 -Wall -c -fmessage-length=0 $(CFLAGS) -o "$@" "$<" $(LIBS)

tmp/main.o:main.cpp
	@echo 'Building file: $<'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -Ilibs/include -Ihdr -O0 -g3 -Wall -c -fmessage-length=0 $(CFLAGS) -o "$@" "$<" $(LIBS)
	
$(FOLDERS):
	@echo 'Creating tmp'
	@mkdir -p tmp

clean:
	@echo 'Cleaning...'
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) $(MAIN)
	-@echo ' '

	@echo 'Cleaning folders...'
	-$(RM) -r $(FOLDERS)
	-@echo ' '

.PHONY: all clean dependents