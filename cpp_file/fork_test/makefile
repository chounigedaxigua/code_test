source = $(wildcard *.cpp *.c)
#source += $(wildcard *.c)

target_ = $(patsubst %.cpp,%.o,$(source))
target = $(patsubst %.c,%.o,$(target_))
$(info $(source))
$(info $(target))

main : $(target)
	g++ $(target) -o main
#       g++ $< $@

clean :
	rm $(target) main

