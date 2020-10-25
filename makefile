SUBDIRS = lib src

.PHONY: subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

$(SUBDIRS):
	@echo Building directory $@
	$(MAKE) -C $@ $(TARGET)

clean:
	@ make --no-print-directory -f makefile TARGET=clean

