CC = gcc
CFLAGS = -std=c99 -Wall -Wno-cast-qual -Wenum-compare -w -std=gnu99
LDFLAGS =

SRCDIR = .
INCDIRS = ./
OBJDIR = obj
BINDIR = bin
TARGET = $(BINDIR)/output

SOURCES := $(shell find $(SRCDIR) -type f -name "*.c")
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))
DEPS := $(OBJECTS:.o=.d)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(addprefix -I, $(INCDIRS)) -MMD -MP -c $< -o $@

-include $(DEPS)

.PHONY: clean

clean:
	rm -rf $(OBJDIR) $(BINDIR)
