#**************************************************************
#  
#  Licensed to the Apache Software Foundation (ASF) under one
#  or more contributor license agreements.  See the NOTICE file
#  distributed with this work for additional information
#  regarding copyright ownership.  The ASF licenses this file
#  to you under the Apache License, Version 2.0 (the
#  "License"); you may not use this file except in compliance
#  with the License.  You may obtain a copy of the License at
#  
#    http://www.apache.org/licenses/LICENSE-2.0
#  
#  Unless required by applicable law or agreed to in writing,
#  software distributed under the License is distributed on an
#  "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
#  KIND, either express or implied.  See the License for the
#  specific language governing permissions and limitations
#  under the License.
#  
#**************************************************************



PRJ=..$/..$/..

PRJNAME=sal
TARGET=qa_osl_socket

ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk

CFLAGS+= $(LFS_CFLAGS)
CXXFLAGS+= $(LFS_CFLAGS)

# BEGIN ----------------------------------------------------------------
# auto generated Target:Socket by codegen.pl
SHL1OBJS=  \
	$(SLO)$/osl_Socket.obj

SHL1TARGET=osl_SocketOld
SHL1STDLIBS= $(SALLIB) $CPPUNITLIB) $(TESTSHL2LIB)

.IF "$(GUI)" == "WNT"
SHL1STDLIBS+= $(WS2_32LIB)
.ENDIF

.IF "$(GUI)" == "UNX"
SHL1STDLIBS+= -ldl -lnsl
.ENDIF

SHL1IMPLIB= i$(SHL1TARGET)
# SHL1DEF=    $(MISC)$/$(SHL1TARGET).def
DEF1NAME=$(SHL1TARGET)
# DEF1EXPORTFILE= export.exp
SHL1VERSIONMAP = $(PRJ)$/qa$/export.map
# auto generated Target:Socket
# END ------------------------------------------------------------------

# --- BEGIN --------------------------------------------------------
SHL2OBJS=  \
	$(SLO)$/osl_Socket_tests.obj
SHL2TARGET= osl_Socket_tests
SHL2STDLIBS= $(SALLIB) $CPPUNITLIB) $(TESTSHL2LIB)

SHL2IMPLIB= i$(SHL2TARGET)
DEF2NAME=    $(SHL2TARGET)
SHL2VERSIONMAP = $(PRJ)$/qa$/export.map

# END --------------------------------------------------------------

# BEGIN ----------------------------------------------------------------
# auto generated Target:Socket by codegen.pl
SHL3OBJS=  \
	$(SLO)$/sockethelper.obj \
	$(SLO)$/osl_StreamSocket.obj

SHL3TARGET= osl_StreamSocket
SHL3STDLIBS= $(SALLIB) $CPPUNITLIB) $(TESTSHL2LIB)

.IF "$(GUI)" == "WNT"
SHL3STDLIBS += $(WS2_32LIB)
.ENDIF

.IF "$(GUI)" == "UNX"
SHL3STDLIBS += -ldl -lnsl
.ENDIF

SHL3IMPLIB= i$(SHL3TARGET)
DEF3NAME=    $(SHL3TARGET)
SHL3VERSIONMAP = $(PRJ)$/qa$/export.map
# auto generated Target:Socket
# END ------------------------------------------------------------------

# BEGIN ----------------------------------------------------------------
# auto generated Target:Socket by codegen.pl
SHL4OBJS=  \
	$(SLO)$/sockethelper.obj \
	$(SLO)$/osl_DatagramSocket.obj

SHL4TARGET= osl_DatagramSocket
SHL4STDLIBS= $(SALLIB) $(CPPUNITLIB) $(TESTSHL2LIB)

.IF "$(GUI)" == "WNT"
SHL4STDLIBS += $(WS2_32LIB)
.ENDIF

.IF "$(GUI)" == "UNX"
SHL4STDLIBS += -ldl -lnsl
.ENDIF

SHL4IMPLIB= i$(SHL4TARGET)
DEF4NAME=    $(SHL4TARGET)
SHL4VERSIONMAP = $(PRJ)$/qa$/export.map
# auto generated Target:Socket
# END ------------------------------------------------------------------

# BEGIN ----------------------------------------------------------------
# auto generated Target:Socket by codegen.pl
SHL5OBJS=  \
	$(SLO)$/sockethelper.obj \
	$(SLO)$/osl_SocketAddr.obj

SHL5TARGET= osl_SocketAddr
SHL5STDLIBS= $(SALLIB) $(CPPUNITLIB) $(TESTSHL2LIB)

.IF "$(GUI)" == "WNT"
SHL5STDLIBS += $(WS2_32LIB)
.ENDIF

.IF "$(GUI)" == "UNX"
SHL5STDLIBS += -ldl -lnsl
.ENDIF

SHL5IMPLIB= i$(SHL5TARGET)
DEF5NAME=    $(SHL5TARGET)
SHL5VERSIONMAP = $(PRJ)$/qa$/export.map
# auto generated Target:Socket
# END ------------------------------------------------------------------

# BEGIN ----------------------------------------------------------------
# auto generated Target:Socket by codegen.pl
SHL6OBJS=  \
	$(SLO)$/sockethelper.obj \
	$(SLO)$/osl_Socket2.obj

SHL6TARGET= osl_Socket2
SHL6STDLIBS= $(SALLIB) $(CPPUNITLIB) $(TESTSHL2LIB)

.IF "$(GUI)" == "WNT"
SHL6STDLIBS += $(WS2_32LIB)
.ENDIF

.IF "$(GUI)" == "UNX"
SHL6STDLIBS += -ldl -lnsl
.ENDIF

SHL6IMPLIB= i$(SHL6TARGET)
DEF6NAME=    $(SHL6TARGET)
SHL6VERSIONMAP = $(PRJ)$/qa$/export.map
# auto generated Target:Socket
# END ------------------------------------------------------------------

# BEGIN ----------------------------------------------------------------
# auto generated Target:Socket by codegen.pl
SHL7OBJS=  \
	$(SLO)$/sockethelper.obj \
	$(SLO)$/osl_ConnectorSocket.obj

SHL7TARGET= osl_ConnectorSocket
SHL7STDLIBS= $(SALLIB) $(CPPUNITLIB) $(TESTSHL2LIB)

.IF "$(GUI)" == "WNT"
SHL7STDLIBS += $(WS2_32LIB)
.ENDIF

.IF "$(GUI)" == "UNX"
SHL7STDLIBS += -ldl -lnsl
.ENDIF

SHL7IMPLIB= i$(SHL7TARGET)
DEF7NAME=    $(SHL7TARGET)
SHL7VERSIONMAP = $(PRJ)$/qa$/export.map
# auto generated Target:Socket
# END ------------------------------------------------------------------

# BEGIN ----------------------------------------------------------------
# auto generated Target:Socket by codegen.pl
SHL8OBJS=  \
	$(SLO)$/sockethelper.obj \
	$(SLO)$/osl_AcceptorSocket.obj

SHL8TARGET= osl_AcceptorSocket
SHL8STDLIBS= $(SALLIB) $(CPPUNITLIB) $(TESTSHL2LIB)

.IF "$(GUI)" == "WNT"
SHL8STDLIBS += $(WS2_32LIB)
.ENDIF

.IF "$(GUI)" == "UNX"
SHL8STDLIBS += -ldl -lnsl
.ENDIF

SHL8IMPLIB= i$(SHL8TARGET)
DEF8NAME=    $(SHL8TARGET)
SHL8VERSIONMAP = $(PRJ)$/qa$/export.map
# auto generated Target:Socket
# END ------------------------------------------------------------------

#------------------------------- All object files -------------------------------
# do this here, so we get right dependencies
# SLOFILES=$(SHL1OBJS) $(SHL2OBJS)

# --- Targets ------------------------------------------------------

.INCLUDE :  target.mk
.INCLUDE : _cppunit.mk
