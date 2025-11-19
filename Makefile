# --- Variables ---
INSTALL_DIR ?= ./.install

# Flags
CFLAGS  += $(shell pkg-config --cflags libgpiod)
LDLIBS  += $(shell pkg-config --libs libgpiod)

# Programme à compiler
TARGET = gpio-toggle

all: $(TARGET)

install: $(TARGET)
	@echo "Installing $(TARGET) into $(INSTALL_DIR)/usr/bin"
	mkdir -p $(INSTALL_DIR)/usr/bin
	install -m 0755 $(TARGET) $(INSTALL_DIR)/usr/bin/

clean:
	rm -f $(TARGET) *.o
 
