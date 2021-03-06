/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_dbaccess.hxx"
//#ifndef _SVX_TABWIN_HXX
//#include "tabwin.hxx"
//#endif
#ifndef DBAUI_RELATIONDIALOG_HRC
#include "RelationDlg.hrc"
#endif
#ifndef DBAUI_RELATIONDIALOG_HXX
#include "RelationDlg.hxx"
#endif

#ifndef _WRKWIN_HXX //autogen
#include <vcl/wrkwin.hxx>
#endif

#ifndef _SV_SVAPP_HXX //autogen
#include <vcl/svapp.hxx>
#endif
#ifndef _DBU_DLG_HRC_
#include "dbu_dlg.hrc"
#endif
#ifndef _DBA_DBACCESS_HELPID_HRC_
#include "dbaccess_helpid.hrc"
#endif
#ifndef _COM_SUN_STAR_SDBC_KEYRULE_HPP_
#include <com/sun/star/sdbc/KeyRule.hpp>
#endif

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef TOOLS_DIAGNOSE_EX_H
#include <tools/diagnose_ex.h>
#endif
#ifndef DBAUI_TOOLS_HXX
#include "UITools.hxx"
#endif
#ifndef DBAUI_JOINDESIGNVIEW_HXX
#include "JoinDesignView.hxx"
#endif
#ifndef DBAUI_JOINCONTROLLER_HXX
#include "JoinController.hxx"
#endif
#ifndef _DBHELPER_DBEXCEPTION_HXX_
#include <connectivity/dbexception.hxx>
#endif
#ifndef DBAUI_RTABLECONNECTIONDATA_HXX
#include "RTableConnectionData.hxx"
#endif
#ifndef DBAUI_RELATIONCONTROL_HXX
#include "RelationControl.hxx"
#endif
#ifndef _CPPUHELPER_EXC_HLP_HXX_
#include <cppuhelper/exc_hlp.hxx>
#endif

#include <algorithm>

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::beans;
using namespace ::dbaui;
using namespace ::dbtools;

//========================================================================
// class ORelationDialog
DBG_NAME(ORelationDialog)
//========================================================================
ORelationDialog::ORelationDialog( OJoinTableView* pParent,
								 const TTableConnectionData::value_type& pConnectionData,
								 sal_Bool bAllowTableSelect )
	:ModalDialog( pParent, ModuleRes(DLG_REL_PROPERTIES) )
	,m_pTableMap(pParent->GetTabWinMap())

    ,aFL_CascUpd(           this, ModuleRes(FL_CASC_UPD) )
	,aRB_NoCascUpd(			this, ModuleRes(RB_NO_CASC_UPD) )
	,aRB_CascUpd(			this, ModuleRes(RB_CASC_UPD) )
	,aRB_CascUpdNull(		this, ModuleRes(RB_CASC_UPD_NULL) )
	,aRB_CascUpdDefault(	this, ModuleRes(RB_CASC_UPD_DEFAULT) )
    ,aFL_CascDel(           this, ModuleRes(FL_CASC_DEL) )
	,aRB_NoCascDel(			this, ModuleRes(RB_NO_CASC_DEL) )
	,aRB_CascDel(			this, ModuleRes(RB_CASC_DEL) )
	,aRB_CascDelNull(		this, ModuleRes(RB_CASC_DEL_NULL) )
	,aRB_CascDelDefault(	this, ModuleRes(RB_CASC_DEL_DEFAULT) )

    ,aPB_OK( this, ModuleRes( PB_OK ) )
	,aPB_CANCEL( this, ModuleRes( PB_CANCEL ) )
	,aPB_HELP( this, ModuleRes( PB_HELP ) )

    ,m_pOrigConnData( pConnectionData )
	,m_bTriedOneUpdate(sal_False)
{
    DBG_CTOR(ORelationDialog,NULL);

	m_xConnection = pParent->getDesignView()->getController().getConnection();

	//////////////////////////////////////////////////////////////////////
	// Connection kopieren
	m_pConnData.reset( static_cast<ORelationTableConnectionData*>(pConnectionData->NewInstance()) );
	m_pConnData->CopyFrom( *pConnectionData );

	Init(m_pConnData);
	m_pTableControl.reset( new OTableListBoxControl(this,ModuleRes(WND_CONTROL),m_pTableMap,this) );

	aPB_OK.SetClickHdl( LINK(this, ORelationDialog, OKClickHdl) );

	m_pTableControl->Init( m_pConnData );
	if ( bAllowTableSelect )
		m_pTableControl->fillListBoxes();
	else
		m_pTableControl->fillAndDisable(pConnectionData);

	m_pTableControl->lateInit();

	m_pTableControl->NotifyCellChange();

	FreeResource();
}

//------------------------------------------------------------------------
void ORelationDialog::Init(const TTableConnectionData::value_type& _pConnectionData)
{
    ORelationTableConnectionData* pConnData = static_cast<ORelationTableConnectionData*>(_pConnectionData.get());
	// Update Rules
	switch (pConnData->GetUpdateRules())
	{
	case KeyRule::NO_ACTION:
	case KeyRule::RESTRICT:
		aRB_NoCascUpd.Check( sal_True );
		break;

	case KeyRule::CASCADE:
		aRB_CascUpd.Check( sal_True );
		break;

	case KeyRule::SET_NULL:
		aRB_CascUpdNull.Check( sal_True );
		break;
	case KeyRule::SET_DEFAULT:
		aRB_CascUpdDefault.Check( sal_True );
		break;
	}

	// Delete Rules
	switch (pConnData->GetDeleteRules())
	{
	case KeyRule::NO_ACTION:
	case KeyRule::RESTRICT:
		aRB_NoCascDel.Check( sal_True );
		break;

	case KeyRule::CASCADE:
		aRB_CascDel.Check( sal_True );
		break;

	case KeyRule::SET_NULL:
		aRB_CascDelNull.Check( sal_True );
		break;
	case KeyRule::SET_DEFAULT:
		aRB_CascDelDefault.Check( sal_True );
		break;
	}
}

//------------------------------------------------------------------------
ORelationDialog::~ORelationDialog()
{
    DBG_DTOR(ORelationDialog,NULL);
}

//------------------------------------------------------------------------


//------------------------------------------------------------------------
IMPL_LINK( ORelationDialog, OKClickHdl, Button*, /*pButton*/ )
{
	//////////////////////////////////////////////////////////////////////
	// RadioButtons auslesen
	sal_uInt16 nAttrib = 0;

	// Delete Rules
	if( aRB_NoCascDel.IsChecked() )
		nAttrib |= KeyRule::NO_ACTION;
	if( aRB_CascDel.IsChecked() )
		nAttrib |= KeyRule::CASCADE;
	if( aRB_CascDelNull.IsChecked() )
		nAttrib |= KeyRule::SET_NULL;
	if( aRB_CascDelDefault.IsChecked() )
		nAttrib |= KeyRule::SET_DEFAULT;

    ORelationTableConnectionData* pConnData = static_cast<ORelationTableConnectionData*>(m_pConnData.get());
	pConnData->SetDeleteRules( nAttrib );

	// Update Rules
	nAttrib = 0;
	if( aRB_NoCascUpd.IsChecked() )
		nAttrib |= KeyRule::NO_ACTION;
	if( aRB_CascUpd.IsChecked() )
		nAttrib |= KeyRule::CASCADE;
	if( aRB_CascUpdNull.IsChecked() )
		nAttrib |= KeyRule::SET_NULL;
	if( aRB_CascUpdDefault.IsChecked() )
		nAttrib |= KeyRule::SET_DEFAULT;
	pConnData->SetUpdateRules( nAttrib );

	m_pTableControl->SaveModified();

	//// wenn die ComboBoxen fuer die Tabellenauswahl enabled sind (Constructor mit bAllowTableSelect==sal_True), dann muss ich in die
	//// Connection auch die Tabellennamen stecken
	//m_pConnData->SetSourceWinName(m_pTableControl->getSourceWinName());
	//m_pConnData->SetDestWinName(m_pTableControl->getDestWinName());

	// try to create the relation
	try
	{
    	ORelationTableConnectionData* pOrigConnData = static_cast<ORelationTableConnectionData*>(m_pOrigConnData.get());
		if ( *pConnData == *pOrigConnData || pConnData->Update())
		{
			m_pOrigConnData->CopyFrom( *m_pConnData );
			EndDialog( RET_OK );
			return 0L;
		}
	}
	catch( const SQLException& )
	{
        ::dbaui::showError(	SQLExceptionInfo( ::cppu::getCaughtException() ),
							this,
							static_cast<OJoinTableView*>(GetParent())->getDesignView()->getController().getORB());
	}
    catch( const Exception& )
    {
        DBG_UNHANDLED_EXCEPTION();
    }

	m_bTriedOneUpdate = sal_True;
	// this means that the original connection may be lost (if m_pConnData was not a newly created but an
	// existent conn to be modified), which we reflect by returning RET_NO (see ::Execute)

	// try again
	Init(m_pConnData);
	m_pTableControl->Init( m_pConnData );
	m_pTableControl->lateInit();

	return 0;
}


//------------------------------------------------------------------------
short ORelationDialog::Execute()
{
	short nResult = ModalDialog::Execute();
	if ((nResult != RET_OK) && m_bTriedOneUpdate)
		return RET_NO;

	return nResult;
}
// -----------------------------------------------------------------------------
TTableConnectionData::value_type ORelationDialog::getConnectionData() const
{
	return m_pConnData;
}
// -----------------------------------------------------------------------------
void ORelationDialog::setValid(sal_Bool _bValid)
{
	aPB_OK.Enable(_bValid);
}
// -----------------------------------------------------------------------------
void ORelationDialog::notifyConnectionChange()
{
	Init(m_pConnData);
}
// -----------------------------------------------------------------------------


