*This project has been created as part of the 42 curriculum by herinaan*

# Born2beRoot

## Description

**Born2beRoot** is a system administration introductory project. The goal is to configure, from scratch, a virtual machine (via **VirtualBox** or **UTM**) running strictly in CLI mode (no graphical interface), while applying strict security rules:

- Encrypted disk partitioning using **LVM** (Logical Volume Manager).
- Strong password policy (root and user).
- Strict **sudo** configuration (limited attempts, logging, custom message, TTY mode, restricted PATH).
- Firewall (**UFW** for Debian / **firewalld** for Rocky) allowing only port **4242**.
- Working **SSH** service on port 4242, with root login disabled.
- A `monitoring.sh` script displaying the server's status every 10 minutes on all terminals (via `cron` and `wall`).

This project provides an understanding of how a VM works, the basics of securing a Linux server, and user/permission management.

---

## Instructions

### Operating system choice
This project uses **Debian** (latest stable version, no testing/unstable), recommended for beginners in system administration.

#### Debian

- Advantages: lightweight footprint, extensive documentation, large community, frequent updates, easier for beginners.

- Disadvantages: shorter/less predictable support cycle than RHEL-based distros, less suited to strict enterprise compliance needs.

#### Rocky Linux

- Advantages: enterprise-grade stability, long support cycle aligned with RHEL (~10 years), SELinux offers very fine-grained security control.
- Disadvantages: steeper learning curve, more complex configuration (SELinux, DNF), heavier setup for beginners.

### VM installation
1. Create a VM in VirtualBox (or UTM) using the Debian (or Rocky) ISO.
2. Do **not** install a graphical environment (strictly forbidden by the subject).
3. During installation, choose **manual partitioning** to set up LVM encryption.
4. The hostname must be: `<login>42` (e.g. `herinaan42`).

### Quick check (run once logged in as root)
```bash
lsblk                     ` Check LVM partitions`
sudo ufw status           ` Check the firewall (Debian)`
sudo firewall-cmd --state ` Check the firewall (Rocky)`
systemctl status ssh      ` Check the SSH service`
```

---

## Resources

- [Official Debian documentation](https://www.debian.org/doc/)
- [Official Rocky Linux documentation](https://docs.rockylinux.org/)
- [sudoers man page](https://man7.org/linux/man-pages/man5/sudoers.5.html)
- [LVM documentation (Red Hat)](https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/8/html/configuring_and_managing_logical_volumes/index)
- [UFW documentation](https://help.ubuntu.com/community/UFW)
- [firewalld documentation](https://firewalld.org/documentation/)
- 42 community forums

**AI usage:** an AI assistant was used occasionally to clarify theoretical concepts (differences between AppArmor/SELinux, how LVM works, PAM/sudoers syntax) and to structure this README.

---

## Operating system choice: Debian vs Rocky Linux

| Criterion | Debian | Rocky Linux |
|---|---|---|
| Origin | Independent distribution | Community clone of RHEL |
| Package manager | APT (`.deb`) | DNF/YUM (`.rpm`) |
| Security module | AppArmor | SELinux |
| Default firewall | UFW | firewalld |
| Target | General-purpose, lightweight, well documented | Enterprise environments, RHEL stability |
| Support cycle | Stable, frequent updates | Aligned with RHEL (~10 years) |
| Learning curve | Easier for beginners | More complex (SELinux, DNF) |

**Choice made: Debian**, for its lightweight footprint, extensive documentation, and ease of use — ideal for a first system administration project.

---

## Design choices

### Partitioning (encrypted LVM)
The disk is divided into logical partitions using LVM, with encryption (LUKS) on the main partition. Example structure:

```
sda
├─sda1        /boot        `(unencrypted, required for booting)`
└─sda5        encrypted partition (LUKS)
   └─sda5_crypt
      ├─vg-root         /
      ├─vg-swap         [SWAP]
      ├─vg-home         /home
      ├─vg-var          /var
      ├─vg-srv          /srv
      ├─vg-tmp          /tmp
      └─vg-var--log     /var/log
```

**Why LVM?** It allows logical volumes to be resized dynamically without reformatting, and separates sensitive data (`/home`) from the system. Encryption protects data in case of physical disk theft.

### Password policy
Configured via `/etc/login.defs` and `/etc/pam.d/common-password` (`pam_pwquality` module):
- Expires every 30 days, minimum 2 days between changes.
- Warning 7 days before expiration.
- At least 10 characters, including uppercase, lowercase, and a digit.
- No more than 3 consecutive identical characters.
- Must not contain the username.
- At least 7 characters different from the previous password (except for root).

### User management
- The `<login>` user belongs to the `sudo` and `user42` groups.
- An `evaluate` group is created for evaluators (assigned to the new user created during the defense).

### Sudo configuration
`sudo` is installed and configured through a dedicated file in `/etc/sudoers.d/` (edited safely with `visudo`) to comply with the strict rules imposed by the subject:
- **Limited attempts:** authentication fails after 3 incorrect password attempts (`Defaults passwd_tries=3`).
- **Custom error message:** a personalized message is displayed on a wrong password (`Defaults badpass_message="..."`).
- **Full logging:** every command run with `sudo` (input and output) is logged to `/var/log/sudo/sudo.log` (`Defaults logfile=...` and `Defaults log_input, log_output`).
- **TTY mode:** enabled for security reasons (`Defaults requiretty`), preventing sudo from being used through non-interactive/background shells.
- **Restricted PATH:** `secure_path` is set to `/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin`, so sudo only trusts binaries from these directories.

### SSH configuration
`openssh-server` is installed and configured via `/etc/ssh/sshd_config`:
- Listens on **port 4242** only (`Port 4242`), instead of the default port 22.
- **Root login is disabled** (`PermitRootLogin no`), forcing evaluators/users to connect with a standard user and use `sudo` for privileged actions.
- The service is enabled at boot and restarted after every configuration change (`systemctl restart ssh`).

### Installed services
- `openssh-server` (SSH on port 4242, root login disabled).
- `ufw` (Debian) / `firewalld` (Rocky), only port 4242 open.
- `sudo` configured strictly.
- `monitoring.sh` script run via `cron`.

### Monitoring script (`monitoring.sh`)
Written in `bash`, this script is triggered by a `cron` job every 10 minutes and broadcasts its output to all open terminals using `wall`, so any logged-in user can see the server status in real time. It reports:
- OS architecture and kernel version.
- Number of physical and virtual CPUs.
- RAM usage (available/used, in %).
- Disk usage (available/used, in %).
- CPU load (%).
- Date and time of the last reboot.
- Whether LVM is active.
- Number of active TCP connections.
- Number of users currently logged in.
- Server's IPv4 and MAC address.
- Number of commands executed via `sudo`.

The cron entry runs every 10 minutes; **the script itself is never modified** to stop it — instead, its execution is managed/interrupted through `cron` (e.g. commenting or removing the crontab entry), as required by the subject.

---

## Required comparisons

### AppArmor vs SELinux
| | AppArmor (Debian) | SELinux (Rocky) |
|---|---|---|
| Control type | Path-based | Based on security labels/contexts |
| Complexity | Easier to configure | More powerful but more complex |
| Granularity | Medium | Very fine-grained |
| Usage | Per-application profiles | System-wide policy (MAC) |

### UFW vs firewalld
| | UFW (Debian) | firewalld (Rocky) |
|---|---|---|
| Interface | Simplified, based on iptables | Based on "zones" (nftables/iptables) |
| Live changes | Sometimes requires a reload | Dynamic reload without downtime |
| Simplicity | Very simple (`ufw allow/deny`) | More flexible but more complex |

### VirtualBox vs UTM
| | VirtualBox | UTM |
|---|---|---|
| Platform | Windows/Linux/macOS (Intel) | macOS (especially Apple Silicon/M1+) |
| Virtualization | Software-based (VirtualBox Hypervisor) | Based on QEMU/Apple Hypervisor |
| Disk format | `.vdi` | `.qcow2` |
| Recommended use | Classic x86 machines | Mac M1/M2/M3 (ARM) |

---

## Useful commands (quick reference)

### Partitions & LVM
```bash
lsblk                         ` List disks and partitions`
sudo pvdisplay                ` Show physical volumes (PV)`
sudo vgdisplay                ` Show volume groups (VG)`
sudo lvdisplay                ` Show logical volumes (LV)`
sudo cryptsetup luksDump /dev/sda5   ` Info about the encrypted partition`
```

### User & group management
```bash
sudo adduser <login>              ` Create a user`
sudo usermod -aG sudo <login>     ` Add to the sudo group`
sudo usermod -aG user42 <login>   ` Add to the user42 group`
groups <login>                    ` Check a user s groups`
sudo groupadd evaluate            ` Create the evaluate group`
sudo usermod -aG evaluate <login> ` Add to the evaluate group`
```

### Password (policy)
```bash
sudo chage -l <login>          ` View the policy applied to a user`
sudo chage -M 30 -m 2 -W 7 <login>  ` Expiration 30d, min 2d, warning 7d`
sudo passwd <login>            ` Change the password`
sudo nano /etc/login.defs      ` Set the default password policy for all future users`
sudo nano /etc/pam.d/common-password    ` Configure the PAM module enforcing password rules`
sudo nano /etc/security/pwquality.conf  ` Configure password strength requirements (pam_pwquality)`
```

### Sudo
```bash
sudo visudo                       ` Safely edit /etc/sudoers or /etc/sudoers.d/ files`
sudo cat /var/log/sudo/sudo.log   ` Check sudo logs`
```

### Firewall
```bash
# Debian (UFW)
sudo ufw enable
sudo ufw allow 4242
sudo ufw status verbose

# Rocky (firewalld)
sudo firewall-cmd --state
sudo firewall-cmd --permanent --add-port=4242/tcp
sudo firewall-cmd --reload
sudo firewall-cmd --list-all
```

### SSH
```bash
sudo systemctl status ssh          ` SSH service status`
sudo nano /etc/ssh/sshd_config     ` Change the port (4242) and PermitRootLogin (no)`
sudo systemctl restart ssh         ` Restart SSH after changes`
ssh <login>@<ip> -p 4242           ` Connect via SSH`
```

### General checks (Debian)
```bash
head -n 2 /etc/os-release      ` OS name and version`
uname -a                       ` Architecture and kernel version`
/usr/sbin/aa-status            ` AppArmor status`
ss -tunlp                      ` Listening ports`
```

### General checks (Rocky)
```bash
head -n 2 /etc/os-release      ` OS name and version`
sestatus                       ` SELinux status`
ss -tunlp                      ` Listening ports`
```

### Monitoring / Cron
```bash
crontab -e                     ` Edit the user s scheduled tasks`
sudo crontab -e                ` Edit root s scheduled tasks`
*/10 * * * * /usr/local/bin/monitoring.sh   ` Example cron entry (every 10 min)`
sudo systemctl status cron     ` Check that cron is running`
```

### Virtual disk signature (submission)
```bash
# Linux
sha1sum <vm_name>.vdi

# macOS
shasum <vm_name>.vdi

# macOS M1 (UTM)
shasum <vm_name>.utm/Images/disk-0.qcow2

# Windows
certUtil -hashfile <vm_name>.vdi sha1
```
The output must be copied into `signature.txt` at the root of the repository.

---

## Points to watch (strict subject rules)
- No graphical interface allowed (X.org, Wayland forbidden).
- No snapshot must exist at the start of each evaluation.
- The signature of the `.vdi`/`.qcow2` file must exactly match the one in `signature.txt`.
- The root password must also comply with the password policy.
- The `monitoring.sh` script must never be modified to be "stopped" at startup — it's the cron task that needs to be managed instead.
