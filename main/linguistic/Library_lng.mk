#*************************************************************************
#
# DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
# 
# Copyright 2000, 2011 Oracle and/or its affiliates.
#
# OpenOffice.org - a multi-platform office productivity suite
#
# This file is part of OpenOffice.org.
#
# OpenOffice.org is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License version 3
# only, as published by the Free Software Foundation.
#
# OpenOffice.org is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License version 3 for more details
# (a copy is included in the LICENSE file that accompanied this code).
#
# You should have received a copy of the GNU Lesser General Public License
# version 3 along with OpenOffice.org.  If not, see
# <http://www.openoffice.org/license.html>
# for a copy of the LGPLv3 License.
#
#*************************************************************************
	
$(eval $(call gb_Library_Library,lng))

$(eval $(call gb_Library_add_package_headers,lng,linguistic_inc))

$(eval $(call gb_Library_add_precompiled_header,lng,$(SRCDIR)/linguistic/inc/pch/precompiled_linguistic))

$(eval $(call gb_Library_set_componentfile,lng,linguistic/source/lng))

$(eval $(call gb_Library_add_api,lng,\
	udkapi \
	offapi \
))

$(eval $(call gb_Library_set_include,lng,\
	$$(INCLUDE) \
	-I$(SRCDIR)/linguistic/inc \
	-I$(SRCDIR)/linguistic/inc/pch \
))
	
$(eval $(call gb_Library_set_defs,lng,\
	$$(DEFS) \
	-DLNG_DLLIMPLEMENTATION \
))

$(eval $(call gb_Library_add_linked_libs,lng,\
	cppu \
	cppuhelper \
	comphelper \
	vos3 \
	tl \
	i18nisolang1 \
	svl \
	stl \
	sal \
	xo \
	ucbhelper \
	utl \
    $(gb_STDLIBS) \
))

$(call gb_Library_use_external,lng,icuuc)

$(eval $(call gb_Library_add_exception_objects,lng,\
	linguistic/source/convdic \
	linguistic/source/convdiclist \
	linguistic/source/convdicxml \
	linguistic/source/dicimp \
	linguistic/source/dlistimp \
	linguistic/source/gciterator \
	linguistic/source/hhconvdic \
	linguistic/source/hyphdsp \
	linguistic/source/hyphdta \
	linguistic/source/iprcache \
	linguistic/source/lngopt \
	linguistic/source/lngprophelp \
	linguistic/source/lngreg \
	linguistic/source/lngsvcmgr \
	linguistic/source/misc \
	linguistic/source/misc2 \
	linguistic/source/spelldsp \
	linguistic/source/spelldta \
	linguistic/source/thesdsp \
	linguistic/source/thesdta \
))

# vim: set noet sw=4 ts=4: