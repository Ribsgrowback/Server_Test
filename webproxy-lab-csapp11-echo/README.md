# CSAPP Chapter 11 Echo Server (Iterative)

This folder is a separate copy-style workspace for the Chapter 11 echo example.

## Files

- `echoserveri.c`: iterative echo server
- `echo.c`: echo routine (`readline` + write back)
- `echoclient.c`: simple test client
- `csapp.c`, `csapp.h`: CSAPP wrapper/util library
- `Makefile`

## Build (Ubuntu / WSL)

```bash
make
```

## Run

Terminal 1:

```bash
./echoserveri 5001
```

Terminal 2:

```bash
./echoclient 127.0.0.1 5001
hello
CSAPP
```

You should see each line echoed back.
