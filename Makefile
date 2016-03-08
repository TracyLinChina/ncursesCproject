# Programe By LSY
OBJS := Main.c win_ui.c
TARGET:= MiniBug
LINK := -lncurses
all:	
	$(CC) -g -Wall -O0 -o $(TARGET) $(OBJS) $(LINK)
clean:	
	$(RM) -rf $(TARGET) *.o
install:	
	cp $(TARGET) /usr/bin





