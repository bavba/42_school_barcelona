#!/bin/bash
function setup_monitoring_script() {
    cat > /usr/local/bin/monitoring.sh << 'EOF'
#!/bin/bash

function gather_info() {
    architecture=$(uname -m)
    kernel_version=$(uname -r)
    cpu_physical=$(lscpu | grep "^CPU(s):" | awk '{print $2}')
    cpu_virtual=$(lscpu | grep "^Thread(s) per core:" | awk '{print $4}')
    memory_usage=$(free -m | grep "^Mem:" | awk '{print $3}')
    memory_total=$(free -m | grep "^Mem:" | awk '{print $2}')
    memory_percentage=$(echo "scale=2; $memory_usage / $memory_total * 100" | bc)

    disk_usage=$(df -h / | grep -v "Filesystem" | awk '{print $3}')
    disk_total=$(df -h / | grep -v "Filesystem" | awk '{print $2}')
    disk_percentage=$(df -h / | grep -v "Filesystem" | awk '{print $5}')

    cpu_load=$(top -bn1 | grep "Cpu(s)" | awk '{print $2}')

    last_boot=$(who -b | awk '{print $3, $4}')

    lvm_status=$(lvscan | grep -q "ACTIVE" && echo "yes" || echo "no")

    active_connections=$(netstat -an | grep "ESTABLISHED" | wc -l)
    user_count=$(who | wc -l)
    ipv4_address=$(hostname -I | awk '{print $1}')
    mac_address=$(ip link show | awk '/ether/ {print $2}')
    sudo_count=$(grep -c 'COMMAND=' /var/log/sudo/sudo.log)

    wall << INFO_EOF
 #Architecture: $architecture
 #Kernel Version: $kernel_version
 #CPU physical: $cpu_physical
 #vCPU: $cpu_virtual
 #Memory Usage: $memory_usage MB / $memory_total MB ($memory_percentage%)
 #Disk Usage: $disk_usage / $disk_total ($disk_percentage)
 #CPU load: $cpu_load
 #Last boot: $last_boot
 #LVM use: $lvm_status
 #Connexions TCP: $active_connections ESTABLISHED
 #User log: $user_count
 #Network: IP $ipv4_address ($mac_address)
 #Sudo: $sudo_count cmd
INFO_EOF
}

function run_monitoring() {
    while true; do
        gather_info
        sleep 600  # 10 minutes
    done
}

run_monitoring
EOF

    chmod +x /usr/local/bin/monitoring.sh

    echo "*/10 * * * * root /usr/local/bin/monitoring.sh > /dev/null 2>&1" > /etc/cron.d/monitoring_cron

    if [ -x "$(command -v systemctl)" ]; then
        systemctl restart cron
    elif [ -x "$(command -v service)" ]; then
        service cron restart
    fi

    echo "Monitoring script set up successfully."
}

setup_monitoring_script