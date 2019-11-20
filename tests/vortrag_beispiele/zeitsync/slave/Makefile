#et the name of your application:
APPLICATION = foobar
# If no BOARD is found in the environment, use this default:
BOARD ?= samr21-xpro
# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../../RIOT

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
CFLAGS += -DDEVELHELP

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

FEATURES_REQUIRED = periph_i2c

# Modules to include:
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps
USEMODULE += periph_gpio
USEMODULE += periph_gpio_irq    #brauch ich für die interrupts
USEMODULE += gnrc_netdev_default
USEMODULE += auto_init_gnrc_netif
USEMODULE += gnrc_ipv6_default
USEMODULE += gnrc_icmpv6_echo
USEMODULE += gnrc_sock_udp
USEMODULE += gnrc_pktdump
USEMODULE += gnrc_udp


#USEMODULE += gnrc_udp

include $(RIOTBASE)/Makefile.include
