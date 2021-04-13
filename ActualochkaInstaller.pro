TEMPLATE = subdirs

CONFIG +=   ordered \
            #actwin  \
	    #inst    \
	    #actand

ordered{
    SUBDIRS += \
            Actualochka \
	    Installer \
	    #ActualochkaAndroid
}else:actwin{
    SUBDIRS += \
            Actualochka \
}else:inst{
    SUBDIRS += \
            Installer \
}

else:actand{
    SUBDIRS += \
            ActualochkaAndroid \
}
