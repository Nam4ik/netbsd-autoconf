#!/bin/sh 

# NOTE: Snake notation of variables and functions 

Main() {

  echo "Nam4iks/NB-Autoconf&Fix - is a set of tools for automatically solving common problems related to NetBSD." 
  CheckRootAcess() 

}

CheckRootAcess() {

  if [ "$(id -u)" -ne 0 ]; then
    echo "We need root access to use this tool. Retry with `doas/sudo nbautoconf` or switch to root user."
    exit 1
  fi

}

NetworkFixes() {
  echo "Alright, we would try to fix your network connection."

  echo "Enter your your adapter chipset (it looks like RTL8821CE/RT2561 or other):" 
  read CHIPSET 
  
  echo "You entered the chipset model: $CHIPSET, are you sure there are no typos here? [y/n]: "
}
