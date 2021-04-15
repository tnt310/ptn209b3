#ifndef PROVISION_H_
#define PROVISION_H_

typedef struct
{
	char name[20];
	char type[10];
	char alias[15];

} provision_t;

extern provision_t table_provision[];

int creatJson_provison(char buffer[30]; char *name, char *type, char *alias);

#endif /* PROVISION_H_ */