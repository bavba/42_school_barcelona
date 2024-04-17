#!/bin/bash

function configure_system() {
    distribution=$(lsb_release -is)
    version=$(lsb_release -rs)

    if [ "$distribution" == "Debian" ]; then
        echo "Detected Debian $version"
        apt-get update
        apt-get install -y lvm2 cryptsetup sudo apparmor pwgen ufw
        systemctl enable apparmor
        systemctl start apparmor
    elif [ "$distribution" == "Rocky" ]; then
        echo "Detected Rocky $version"
        dnf install -y lvm2 cryptsetup sudo selinux-policy-targeted policycoreutils-python-utils pwgen firewalld
        setenforce 1
        systemctl enable firewalld
        systemctl start firewalld
    else
        echo "Unsupported distribution: $distribution"
        exit 1
    fi
    cryptsetup luksFormat --type=luks2 /dev/sdX1
    cryptsetup luksFormat --type=luks2 /dev/sdX2
    cryptsetup open /dev/sdX1 luks_part1
    cryptsetup open /dev/sdX2 luks_part2
    pvcreate /dev/mapper/luks_part1
    pvcreate /dev/mapper/luks_part2
    vgcreate myvg /dev/mapper/luks_part1 /dev/mapper/luks_part2
    lvcreate -n mylv1 -L 2G myvg
    lvcreate -n mylv2 -L 1G myvg

    sed -i 's/#Port 22/Port 4242/' /etc/ssh/sshd_config
    sed -i 's/PermitRootLogin yes/PermitRootLogin no/' /etc/ssh/sshd_config
    systemctl restart sshd

    if [ "$distribution" == "Debian" ]; then
        ufw default deny incoming
        ufw default allow outgoing
        ufw allow 4242
        ufw enable
    elif [ "$distribution" == "Rocky" ]; then
        firewall-cmd --set-default-zone=public
        firewall-cmd --zone=public --add-service=ssh
        firewall-cmd --zone=public --add-port=4242/tcp --permanent
        firewall-cmd --reload
    fi

    sed -i 's/PASS_MAX_DAYS.*/PASS_MAX_DAYS 30/' /etc/login.defs
    sed -i 's/PASS_MIN_DAYS.*/PASS_MIN_DAYS 2/' /etc/login.defs
    sed -i 's/PASS_WARN_AGE.*/PASS_WARN_AGE 7/' /etc/login.defs
    apt-get install -y libpam-pwquality
    sed -i 's/pam_pwquality.so.*/pam_pwquality.so retry=3 minlen=10 ucredit=-1 dcredit=-1 ocredit=-1/' /etc/pam.d/common-password

    sed -i 's/^%sudo.*/%sudo ALL=(ALL:ALL) ALL/' /etc/sudoers

    useradd -m -G sudo -s /bin/bash aricalle	
    passwd 4242Barcelona

    echo "System configuration completed!"
}

configure_system