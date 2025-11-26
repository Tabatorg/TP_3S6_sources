# --- Variables ---
INSTALL_DIR ?= ./.install

# Flags
CFLAGS  += $(shell pkg-config --cflags libgpiod)
LDLIBS  += $(shell pkg-config --libs libgpiod)

# Program name
TARGET = esme-gpio-toggle

# Default target
all: esme-gpio-toggle

# Install target
install: $(TARGET) esme-gpio-toggle.sh
	@echo "Installing $(TARGET) into $(INSTALL_DIR)/usr/bin"
	mkdir -p $(INSTALL_DIR)/usr/bin
	install -m 0755 esme-gpio-toggle $(INSTALL_DIR)/usr/bin/

	@echo "Installing esme-gpio-toggle into $(INSTALL_DIR)/etc/init.d"
	mkdir -p $(INSTALL_DIR)/etc/init.d
	install -m 0755 esme-gpio-toggle.sh $(INSTALL_DIR)/etc/init.d/

# Clean target
clean:
	rm -f $(TARGET) *.o
