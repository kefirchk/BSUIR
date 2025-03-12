# GUIDE
___
## Requirements
___

```bash
sudo apt update && sudo apt upgrade

pip install mpi4py

sudo apt install python3-mpi4py

pip install numpy

sudo apt-get install openssh-server openssh-client

sudo systemctl start ssh

sudo apt install openmpi-bin openmpi-common libopenmpi-dev

sudo ufw disable
```

!!! ATTENTION !!!

Versions of packages and libs must be the same on all hosts.
Especially:
- numpy
- mpi
- python

## Launch
___
### 1. Create users
___
Create 3 users with same username and password.
   
**User example:**
   - user: *alexei*
   - password: *1234*
   
**Hosts example:**
   - 172.20.10.2
   - 172.20.10.3
   - 172.20.10.4

### 2. Preparing the environment
___
#### Computer 1 (172.20.10.2)
___
Fill the file *hosts.txt*.

```plain-text
# host.txt

172.20.10.2 slots=4    # count of slots == count of your computer kernels 
172.20.10.3 slots=4
172.20.10.4 slots=2
```

Run the following commands:

```bash
ssh-keygen  # Press Enter and write "yes"

ssh-copy-id alexei@172.20.10.3

ssh-copy-id alexei@172.20.10.4

mpiexec --hostfile hosts.txt python3 var1.py

mpiexec --hostfile hosts.txt python3 var2.py

```


You can check the connection by the following command:
```bash
ssh alexei@172.20.10.3

ssh alexei@172.20.10.4
```

#### Computer 2 (172.20.10.3)
___

You must have source files in root directory (**/home/alexei/**).

Then run the following commands:

```bash
ssh-keygen  # Press Enter and write "yes"

ssh-copy-id alexei@172.20.10.2
```

You can check the connection by the following command:
```bash
ssh alexei@172.20.10.2
```

#### Computer 3 (172.20.10.4)
___

You must have source files in root directory (**/home/alexei/**).

Then run the following commands:

```bash
ssh-keygen  # Press Enter and write "yes"

ssh-copy-id alexei@172.20.10.2
```

You can check the connection by the following command:
```bash
ssh alexei@172.20.10.2
```


