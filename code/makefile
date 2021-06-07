SOURCE_HEADER=telemetry.h json.h main.h
SOURCE_TELEMETRY=telemetry.c
SOURCE_JSON = json.h
SOURCE_FILE=file.c
SOURCE_ARRAY=array.c
SOURCE_MAIN=main.c
SOURCE_BACKUP=backup.c
CC:= gcc
CMD=$(CC) $? -o $@

header: $(SOURCE_HEADER)
	$(CMD)
telemetry: $(SOURCE_TELEMETRY)
	$(CMD)
file: $(SOURCE_FILE)
	$(CMD)
json: $(SOURCE_JSON)
	$(CMD)
main: $(SOURCE_MAIN)
	$(CMD)
back: $(SOURCE_BACKUP)
	$(CMD)
