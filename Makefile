####################################################################################################
#                                     Make file LargeInt 	                                   #
####################################################################################################

SUBDIRS:= src
     
subdirs:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done