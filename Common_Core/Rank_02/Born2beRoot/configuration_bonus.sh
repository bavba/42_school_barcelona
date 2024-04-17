#!/bin/bash

apt-get update
apt-get install -y lighttpd mariadb-server php php-mysql php-curl php-gd php-intl php-json php-mbstring php-xml php-xmlrpc

mysql_secure_installation

echo 'server.modules += ( "mod_fastcgi" )' >> /etc/lighttpd/lighttpd.conf
echo 'fastcgi.server += ( ".php" => ((
    "socket" => "/var/run/php/php7.4-fpm.sock",
    "broken-scriptfilename" => "enable"
)))' >> /etc/lighttpd/lighttpd.conf
systemctl restart lighttpd

wget https://wordpress.org/latest.tar.gz -P /tmp
tar -xzf /tmp/latest.tar.gz -C /var/www/html/
chown -R www-data:www-data /var/www/html/wordpress
mv /var/www/html/wordpress/wp-config-sample.php /var/www/html/wordpress/wp-config.php

mysql -u root -p <<MYSQL_SCRIPT
CREATE DATABASE wordpress;
CREATE USER 'wordpressuser'@'localhost' IDENTIFIED BY 'password';
GRANT ALL PRIVILEGES ON wordpress.* TO 'wordpressuser'@'localhost';
FLUSH PRIVILEGES;
MYSQL_SCRIPT

sed -i "s/database_name_here/wordpress/" /var/www/html/wordpress/wp-config.php
sed -i "s/username_here/wordpressuser/" /var/www/html/wordpress/wp-config.php
sed -i "s/password_here/yourpassword/" /var/www/html/wordpress/wp-config.php

systemctl restart lighttpd
systemctl restart php7.4-fpm

echo "WordPress installation completed!"

