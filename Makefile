CC=gcc
CFLAGS=-Wall -Werror -g -lrt -lpthread

PROG=glob philo eco
SHM_DIR=shm
SHM_EJ=shm_create shm_read shm_unlink shm_write
MQ_DIR=mq
MQ_EJ=mq_open mq_getattr mq_send mq_receive mq_unlink
SEM_DIR=sem
SEM_EJ=sem_open sem_wait sem_post sem_unlink


BINARIES=$(PROG) $(addprefix $(SHM_DIR)/, $(SHM_EJ)) $(addprefix $(MQ_DIR)/, $(MQ_EJ)) $(addprefix $(SEM_DIR)/, $(SEM_EJ))

.PHONY: all
all: $(PROG) shm mq sem

.PHONY: shm
shm: $(addprefix $(SHM_DIR)/, $(SHM_EJ))

.PHONY: mq
mq: $(addprefix $(MQ_DIR)/, $(MQ_EJ))

.PHONY: sem
sem: $(addprefix $(SEM_DIR)/, $(SEM_EJ))

#$(BIN)/%: %.c
#	$(CC) -o $@ $< $(CFLAGS)

%: %.c
	$(CC) -o $@ $< $(CFLAGS)

html: README.md
	pandoc README.md -f markdown_github -t html -s -o README.html

pdf: README.md
	pandoc README.md -f markdown_github -s -o README.pdf

.PHONY: clean
clean:
	rm -f $(BINARIES)

