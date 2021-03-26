TEMPLATE = subdirs

CONFIG += ordered sub

sub{
    SUBDIRS += \
            Actualochka \
	    Installer
} else {
    SUBDIRS += \
        Actualochka \
}
